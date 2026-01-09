[org 0x0100]

jmp start

print_score:
    pusha
    mov ax, 0xb800
    mov es, ax
    mov di, 320
    mov si, 0
    mov ah, 0x07
    mov cx, 6
score_print:
    mov al, [score+si]
    inc si
    mov word[es:di], ax
    add di, 2
    loop score_print
    mov ax, [game_score]
    mov cx, 0
    mov bx, 10
    mov di, 332
    cmp ax, 0
    jne not_zero_score
    mov al, '0'
    mov ah, 0x07
    mov bx, 0xb800
    mov es, bx
    mov [es:di], ax
    jmp print_score_done
not_zero_score:
extract_digits_score:
    xor dx, dx
    div bx
    push dx
    inc cx
    cmp ax, 0
    jne extract_digits_score
    mov bx, 0xb800
    mov es, bx
print_digits_score:
    pop dx
    add dl, '0'
    mov dh, 0x07
    mov [es:di], dx
    add di, 2
    loop print_digits_score
print_score_done:
    popa
    ret

add_turning_points_moves:
    pusha
    mov si, [total_moves]
    cmp si, 0
    jz skip_atpm
    shl si, 1
atpm:
    mov ax, [turning_points+si-2]
    mov [turning_points+si], ax
    mov ax, [turning_moves+si-2]
    mov [turning_moves+si], ax
    sub si, 2
    cmp si, 0
    jnz atpm
skip_atpm:
    mov dx, [head_location]
    call position_fixer
    mov [turning_points], dx
    mov ax, [move]
    mov [turning_moves], ax
    add word[total_moves], 1
    popa
    ret

compress_turning_points_moves:
    push di
    sub word[total_moves], 1
    mov di, [total_moves]
    shl di, 1
    mov word[turning_points+di], 0
    mov word[turning_moves+di], 0
    pop di
    ret

fill_Boundry_value:
    pusha
    mov ax, 480
    mov bx, 80
    mov dx, 20
    mov bp, 0
    mov cx, bx
fill_1:
    mov word[Boundry+bp], ax
    add ax, 2
    add bp, 2
    loop fill_1
    mov cx, dx
fill_2:
    mov word[Boundry+bp], ax
    add ax, 160
    add bp, 2
    loop fill_2
    mov cx, bx
fill_3:
    mov word[Boundry+bp], ax
    add ax, 2
    add bp, 2
    loop fill_3
    mov cx, dx
    sub ax, 162
fill_4:
    mov word[Boundry+bp], ax
    sub ax, 160
    add bp, 2
    loop fill_4
    popa
    ret

print_Boundry:
    pusha
    call fill_Boundry_value
    mov ax, 0xb800
    mov es, ax
    mov cx, 200
    mov si, 0
print_b:
    mov di, [Boundry+si]
    mov word[es:di], 0x3020
    add si, 2
    loop print_b
    popa
    ret

wait_until_key_press:
    push ax
    mov ah, 0
    int 0x16
    pop ax
    ret

generate_random_feed:
    mov ah, 0
    int 0x1a
    shl dx, 8
    and dx, 0x0ffe
    cmp dx, 480
    ja skip_min
    add dx, 480
skip_min:
    cmp dx, 4000
    jb skip_max
    sub dx, 96
skip_max:
    mov [random_position], dx
    ret

fill_feed:
    pusha
    mov ax, 0xb800
    mov es, ax
generate_empty_postion:
    call generate_random_feed
    mov di, [random_position]
    mov si, 0
    mov cx, 200
check_feed_for_Boundry:
    cmp di, [Boundry+si]
    je generate_empty_postion
    add si, 2
    loop check_feed_for_Boundry
    mov ax, [Feed]
    mov word[es:di], ax
    popa
    ret

tail_increase_check:
    push ax
    push si
    mov si, [total_moves]
    cmp si, 0
    jz similar_increase_check
    dec si
    shl si, 1
    mov ax, [turning_moves+si]
    jmp not_similar_increase_check
similar_increase_check:
    mov ax, word[move]
not_similar_increase_check:
    cmp ax, 1
    jne tic11
    add bx, 2
tic11:
    cmp ax, 2
    jne tic12
    sub bx, 2
tic12:
    cmp ax, 3
    jne tic13
    add bx, 160
tic13:
    cmp ax, 4
    jne tic14
    sub bx, 160
tic14:
tic_end:
    pop si
    pop ax
    ret

check_feed_for_body:
    pusha
    mov ax, 0xb800
    mov es, ax
    mov ax, [Feed]
    mov di, 640
    mov cx, 1600
    cld
    repne scasw
    je skip_body_check
    call fill_feed
skip_body_check:
    popa
    ret

check_head_for_body:
    pusha
    mov ax, 0xb800
    mov es, ax
    mov ah, 0x07
    mov al, [body]
    mov dx, [head_location]
    call position_fixer
    mov di, dx
    scasw
    jne skip_head_check
    mov word[stop], 1
skip_head_check:
    popa
    ret

feed_in:
    push cx
again:
    mov bx, [head_location]
    call position_fixer
    cmp [random_position], bx
    jnz remain_same
    call fill_feed
    call tail_decrease
    add word[game_score], 1
remain_same:
    pop cx
    ret

tail_decrease:
    push ax
    push bx
    mov bx, [total_moves]
    cmp bx, 0
    jz similar_decrease
    dec bx
    shl bx, 1
    mov ax, [turning_moves+bx]
    jmp not_similar_decrease
similar_decrease:
    mov ax, word[move]
not_similar_decrease:
    cmp ax, 1
    jne td11
    sub byte[tail_location], 1
td11:
    cmp ax, 2
    jne td12
    add byte[tail_location], 1
td12:
    cmp ax, 3
    jne td13
    sub byte[tail_location+1], 1
td13:
    cmp ax, 4
    jne td14
    add byte[tail_location+1], 1
td14:
td_end:
    pop bx
    pop ax
    ret

delay:
    push cx
    mov cx, [delays]
d1:
    push cx
d2:
    loop d2
    pop cx
    loop d1
    pop cx
    ret

check_move:
    push dx
    mov dx, [head_location]
    cmp dl, 0
    jne cm1
    mov word[stop], 1
cm1:
    cmp dl, 79
    jne cm2
    mov word[stop], 1
cm2:
    cmp dh, 3
    jne cm3
    mov word[stop], 1
cm3:
    cmp dh, 24
    jne cm4
    mov word[stop], 1
cm4:
    pop dx
    ret

head_increase:
    push ax
    mov ax, [head_location]
    cmp word[move], 1
    jne ddi1
    add byte[head_location], 1
ddi1:
    cmp word[move], 2
    jne ddi2
    sub byte[head_location], 1
ddi2:
    cmp word[move], 3
    jne ddi3
    add byte[head_location+1], 1
ddi3:
    cmp word[move], 4
    jne ddi4
    sub byte[head_location+1], 1
ddi4:
    call check_head_for_body
    call print_last_blank
    call tail_increase
    call check_tail_turn
    call check_move
    pop ax
    ret

tail_increase:
    push ax
    push bx
    mov bx, [total_moves]
    cmp bx, 0
    jz similar_increase
    dec bx
    shl bx, 1
    mov ax, [turning_moves+bx]
    jmp not_similar_increase
similar_increase:
    mov ax, word[move]
not_similar_increase:
    cmp ax, 1
    jne ti11
    add byte[tail_location], 1
ti11:
    cmp ax, 2
    jne ti12
    sub byte[tail_location], 1
ti12:
    cmp ax, 3
    jne ti13
    add byte[tail_location+1], 1
ti13:
    cmp ax, 4
    jne ti14
    sub byte[tail_location+1], 1
ti14:
ti_end:
    pop bx
    pop ax
    ret

position_fixer:
    push ax
    push cx
    push dx
    xor ax, ax
    mov al, bh
    xor bh, bh
    mov cx, 80
    mul cx
    add ax, bx
    shl ax, 1
    mov bx, ax
    pop ax
    push bx
    mov cx, ax
    mov al, ah
    xor ch, ch
    xor ah, ah
    mov bx, 80
    mul bx
    add ax, cx
    shl ax, 1
    mov dx, ax
    pop bx
    pop cx
    pop ax
    ret

print_snake_left:
    pusha
    mov ax, 0xb800
    mov es, ax
    mov ah, 0x07
    mov al, [body]
    mov di, dx
    mov si, bx
    cmp si, di
    jb psl_skip
    jmp print_left
psl_skip:
    xchg di, si
print_left:
    mov [es:si], ax
    cmp si, di
    je exit_pl
    sub si, 2
    jmp print_left
exit_pl:
    popa
    ret

print_snake_right:
    pusha
    mov ax, 0xb800
    mov es, ax
    mov ah, 0x07
    mov al, [body]
    mov di, dx
    mov si, bx
    cmp si, di
    jb psr_skip
    xchg di, si
psr_skip:
print_right:
    mov [es:si], ax
    cmp si, di
    je exit_pr
    add si, 2
    jmp print_right
exit_pr:
    popa
    ret

print_snake_up:
    pusha
    mov ax, 0xb800
    mov es, ax
    mov ah, 0x07
    mov al, [body]
    mov di, dx
    mov si, bx
    cmp si, di
    jae psu_skip
    xchg di, si
psu_skip:
print_up:
    mov [es:si], ax
    cmp si, di
    je exit_pu
    sub si, 160
    jmp print_up
exit_pu:
    popa
    ret

print_snake_down:
    pusha
    mov ax, 0xb800
    mov es, ax
    mov ah, 0x07
    mov al, [body]
    mov di, dx
    mov si, bx
    cmp si, di
    jnb psd_skip
    jmp print_down
psd_skip:
    xchg di, si
print_down:
    mov [es:si], ax
    cmp si, di
    je exit_pd
    add si, 160
    jmp print_down
exit_pd:
    popa
    ret

print_last_blank:
    push ax
    push es
    push bx
    mov ax, 0xb800
    mov es, ax
    mov bx, [tail_location]
    call position_fixer
    mov word[es:bx], 0x0720
    pop bx
    pop es
    pop ax
    ret

check_tail_turn:
    push bx
    push di
    mov di, [total_moves]
    cmp di, 0
    je skip_tail_turn
    shl di, 1
    mov bx, [tail_location]
    call position_fixer
    cmp bx, [turning_points+di-2]
    jne skip_tail_turn
    call compress_turning_points_moves
skip_tail_turn:
    pop di
    pop bx
    ret

moving_snake_direction:
    pusha
    mov di, [total_moves]
    cmp di, 0
    jnz for_turns
    mov bx, [tail_location]
    mov dx, [head_location]
    call position_fixer
    call print_type
    jmp to_end
for_turns:
    shl di, 1
    mov si, di
    mov bx, [tail_location]
    call position_fixer
    mov dx, [turning_points+si-2]
    push word[move]
    mov ax, [turning_moves+si-2]
    mov [move], ax
    call print_type
    pop word[move]
ft2:
    sub si, 2
    cmp si, 0
    jz ft_loop_end
    mov bx, [turning_points+si]
    mov dx, [turning_points+si-2]
    push word[move]
    mov ax, [turning_moves+si-2]
    mov [move], ax
    call print_type
    pop word[move]
    jmp ft2
ft_loop_end:
    mov dx, [head_location]
    call position_fixer
    mov bx, [turning_points]
    call print_type
to_end:
    popa
    ret

print_type:
    cmp word[move], 1
    jne ft11
    call print_snake_right
ft11:
    cmp word[move], 2
    jne ft21
    call print_snake_left
ft21:
    cmp word[move], 3
    jne ft31
    call print_snake_down
ft31:
    cmp word[move], 4
    jne ft41
    call print_snake_up
ft41:
    ret

move_snake:
    pusha
    cli
    call check_feed_for_body
    call head_increase
    call moving_snake_direction
    call feed_in
    call check_feed_for_body
    sti
    popa
    ret
printgameended:
    pusha
    mov ax, 0xb800
    mov es, ax
    mov bx, 25
    mov cx, 80
    mul cx
    shl ax, 1
    mov di, ax
    mov si, gameendedmsg
    mov ah, 0x8E
printloop:
    lodsb
    cmp al, 0
    je doneprint
    mov [es:di], ax
    add di, 2
    jmp printloop
doneprint:
    popa
    ret

print_snake_final:
    pusha
    call set_input_buttons
psf:
    call print_score
    call move_snake
    call delay
    cmp word[stop], 1
    jnz psf
    call printgameended
    call reset_kbisr
    popa
    ret

input_button:
    push ax
    push es
    push di
    jne skip_this_one
    xor ax, ax
    in al, 0x60
    test al, 0x80
    jnz skip_move1
    cmp al, 0xe0
    jne correct_scan
    in al, 0x60
    test al, 0x80
    jnz skip_move1
correct_scan:
    mov ah, al
    cmp ah, 0x48
    je up
    cmp ah, 0x4b
    je left
    cmp ah, 0x4d
    je right
    cmp ah, 0x50
    je down
    cmp ah, 0x01
    jne skip_move1
    mov word[stop], 1
    jmp skip_move1
up:
    cmp word[move], 4
    je skip_move1
    cmp word[move], 3
    je skip_move1
    call add_turning_points_moves
    mov word[move], 4
    jmp skip_move
skip_this_one:
    jmp skip_this_one_final
down:
    cmp word[move], 3
    je skip_move
    cmp word[move], 4
    je skip_move
    call add_turning_points_moves
    mov word[move], 3
skip_move1:
    jmp skip_move
left:
    cmp word[move], 2
    je skip_move
    cmp word[move], 1
    je skip_move
    call add_turning_points_moves
    mov word[move], 2
    jmp skip_move
right:
    cmp word[move], 1
    je skip_move
    cmp word[move], 2
    je skip_move
    call add_turning_points_moves
    mov word[move], 1
    jmp skip_move
skip_move:
    mov al, 0x20
    out 0x20, al
skip_this_one_final:
    pop di
    pop es
    pop ax
    iret

set_input_buttons:
    pusha
    xor ax, ax
    mov es, ax
    mov ax, [es:9*4]
    mov [oldisr], ax
    mov ax, [es:9*4+2]
    mov [oldisr+2], ax
    cli
    mov word[es:9*4], input_button
    mov word[es:9*4+2], cs
    sti
    popa
    ret

reset_kbisr:
    pusha
    xor ax, ax
    mov es, ax
    mov ax, [oldisr]
    mov bx, [oldisr+2]
    cli
    mov [es:9*4], ax
    mov [es:9*4+2], bx
    sti
    popa
    ret

clrscr:
    pusha
    mov ax, 0xb800
    mov es, ax
    mov ax, 0x0720
    mov di, 0
    mov cx, 2000
    rep stosw
    popa
    ret

print_title_page:
    pusha
    mov ax, 0xb800
    mov es, ax
    mov di, 1824
    mov si, titlemsg
nextchar_title:
    lodsb
    cmp al, 0
    je print_developers
    mov ah, 0x0E
    stosw
    jmp nextchar_title
print_developers:
    mov di, 2430
    mov si, developersmsg
nextchar_dev:
    lodsb
    cmp al, 0
    je done_title
    mov ah, 0x07
    stosw
    jmp nextchar_dev
done_title:
    popa
    ret

start:
    call clrscr
    call print_title_page
    call wait_until_key_press
    call clrscr
    call print_Boundry
    call print_snake_final

mov ah, 0x1
int 0x21
mov ax, 4c00h
int 21h

move: dw 1
Feed: dw 0x8E24
Boundry: times 200 dw 0
delays: dw 0x02ff
titlemsg: db 'Snake Game',0
developersmsg: db 'Developed by Abdullah Aftab and Mohid Israr',0
turning_points: times 100 dw 0
turning_moves: times 100 dw 0
total_moves: dw 0
stop: dw 0
tail_location: dw 0x0e10
head_location: dw 0x0e14
random_position: dw 0
body: db 'D'
empty_body: db ' '
oldisr: times 2 dw 0
feed_on_body: dw 0
game_score: dw 0
gameendedmsg: db 'GAME ENDED',0
score: db 'Score: '
