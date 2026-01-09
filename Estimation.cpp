#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int battery = 0, addstandcost = 0, totalapp = 0, profile_number = 0, earthing = 0;
float area, totalpower, totalHeavyEnergy, totalLightEnergy, kw;
string forename, surname, username, password, confirmpassword, logusername, logpassword;
const string adminUsername = "admin", adminPw = "abcd";

float marla()
{
	float marlasize;

	do
	{
		cout << "\nKindly enter the size of your house in Marla: ";
		cin >> marlasize;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (marlasize < 5 || marlasize > 20)
		{
			cout << "Kindly enter size between 5 and 20." << endl;
		}
	} while (marlasize < 5 || marlasize > 20 || cin.fail());

	marlasize /= 20;

	return marlasize;
}
float kanal()
{
	// returns kanals
	float kanalsize;

	do
	{
		cout << "\nKindly enter the size of your house in Kanal: ";
		cin >> kanalsize;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (kanalsize <= 0 || kanalsize > 15)
		{
			cout << "Kindly enter size between 1 and 15." << endl;
		}
	} while (kanalsize <= 0 || kanalsize > 15 || cin.fail());

	return kanalsize;
}
int checkRoom()
{
	// return number of rooms that use electricity
	int rooms;
	do
	{
		cout << "\nKindly enter the number of rooms that actively use electricity : ";
		cin >> rooms;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (rooms <= 0 || rooms >= static_cast<int>(20 * area))
		{
			cout << "Kindly enter rooms between 1 and " << static_cast<int>(20 * area) << endl;
		}

	} while (cin.fail() || rooms <= 0 || rooms >= static_cast<int>(25 * area));

	return rooms;
}

float ValidTime()
{
	float time;
	do
	{
		cout << "\nKindly enter the number of hours it is used daily: ";
		cin >> time;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (time < 1 || time > 24)
		{
			cout << "Kindly enter time between 0 and 24." << endl;
		}
	} while (time < 0 || time > 24 || cin.fail());

	return time;
}

// heavy Appliances 1) ask number 2) return their energies
float energyCars(float noOfCars)
{
	// returns energy in Wh used by all electric cars
	if (noOfCars == 0)
		return 0;

	return 7200 * noOfCars * ValidTime() * 30;
}
float energyFridge(float noOfFridge)
{
	// returns energy in Wh used by all refrigerators
	return 400 * noOfFridge * 24 * 30;
}
float energyAC(float noOfAC)
{
	// returns energy in Wh used by all AC's

	return 1200 * noOfAC * ValidTime() * 30;
}
float energyMiscHeavy(float misHeavyAppliances)
{
	// returns energy in Wh used by miscellaneous appliances

	return 500 * misHeavyAppliances * ValidTime() * 30;
}
float energyHeavyTotal()
{
	// returns total Wh of electric cars, ac, fridge
	int car, refrigerators, ac, mischeavy;
	float energy_car, energy_fridge, energy_AC, energy_mis_heavy;

	do
	{
		cout << "\nKindly enter the number of electric cars you wish to charge: ";
		cin >> car;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (car < 0 || car > static_cast<int>(area * 5))
		{
			cout << "Kindly enter a value between 0 and " << static_cast<int>(area * 5) << endl;
		}
	} while (car < 0 || car > static_cast<int>(area * 5) || cin.fail());

	energy_car = energyCars(car);

	do
	{
		cout << "\nKindly enter the number of refrigerators actively used in the entire house: ";
		cin >> refrigerators;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (refrigerators < 0 || refrigerators > static_cast<int>(area * 8))
		{
			cout << "Kindly enter a value between 0 and " << static_cast<int>(area * 8) << endl;
		}
	} while (refrigerators < 0 || refrigerators > static_cast<int>(area * 8) || cin.fail());

	energy_fridge = energyFridge(refrigerators);

	do
	{
		cout << "\nKindly enter the number of air conditioners actively used in the entire house: ";
		cin >> ac;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (ac < 0 || ac > static_cast<int>(area * 30))
		{
			cout << "Kindly enter a value between 0 and " << static_cast<int>(area * 30) << endl;
		}
	} while (ac < 0 || ac > static_cast<int>(area * 30) || cin.fail());

	energy_AC = energyAC(ac);

	do
	{
		cout << "\nKindly enter the number of heavy miscellaneous appliances you use: ";
		cin >> mischeavy;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (mischeavy < 0 || mischeavy > static_cast<int>(area * 15))
		{
			cout << "Kindly enter a value between 0 and " << static_cast<int>(area * 15) << endl;
		}
	} while (mischeavy < 0 || mischeavy > static_cast<int>(area * 15) || cin.fail());

	energy_mis_heavy = energyMiscHeavy(mischeavy);
	totalapp = car + mischeavy + ac + refrigerators;
	return energy_car + energy_fridge + energy_AC + energy_mis_heavy;
}
// light Appliances 1) ask number 2) return their energies
float energyFans(int noOfFans)
{
	// returns Wh of all fans

	return 50 * noOfFans * ValidTime() * 30;
}
float energyLights(int noOfLights)
{
	// returns Wh of all lights

	return 15 * noOfLights * ValidTime() * 30;
}
float energyMiscSmall(float misSmallAppl)
{
	// returns Wh of all small miscellaneous appliances

	return 20 * misSmallAppl * ValidTime() * 30;
}
float energyLightTotal(int rooms)
{
	// returns Wh of all light appliances
	int fans, lightsPerRoom, total_fans, total_lights, miscsmall;
	float energy_Fans, energy_Lights, energy_mis_small;

	do
	{
		cout << "\nKindly enter the number of fans used per room: ";
		cin >> fans;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (fans < 0 || fans > static_cast<int>(area * 3))
		{
			cout << "Kindly enter a value between 0 and " << static_cast<int>(area * 3) << endl;
		}
	} while (fans < 0 || fans > static_cast<int>(area * 3) || cin.fail());

	total_fans = fans * rooms;
	energy_Fans = energyFans(total_fans);

	do
	{
		cout << "\nKindly enter the number of lights used per room: ";
		cin >> lightsPerRoom;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (lightsPerRoom < 0 || lightsPerRoom > static_cast<int>(area * 20))
		{
			cout << "Kindly enter a value between 0 and " << static_cast<int>(area * 20) << endl;
		}
	} while (lightsPerRoom < 0 || lightsPerRoom > static_cast<int>(area * 20) || cin.fail());

	total_lights = lightsPerRoom * rooms;
	energy_Lights = energyLights(total_lights);

	do
	{
		cout << "\nKindly enter the number of small miscellaneous appliances you use: ";
		cin >> miscsmall;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (miscsmall < 0 || miscsmall > static_cast<int>(area * 20))
		{
			cout << "Kindly enter a value between 0 and " << static_cast<int>(area * 20) << endl;
		}
	} while (miscsmall < 0 || miscsmall > static_cast<int>(area * 20) || cin.fail());

	energy_mis_small = energyMiscSmall(miscsmall);
	totalapp = totalapp + miscsmall + total_fans + total_lights;
	return energy_Fans + energy_Lights + energy_mis_small;
}
// solar panels
int getSunpeakhours() // to calculate the peak sun hours per day
{
	// returns sun hours
	int sunhours;

	do
	{
		cout << "\n\t\tCalculation for the Sun Peak Hours in your Area\n\n";
		cout << "\nFor Upper Pakistan, Enter 5.\n";
		cout << "\nFor Lower Pakistan, Enter 6.\n";
		cout << "\nPlease enter the number of sun peak hours: ";
		cin >> sunhours;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (sunhours != 6 && sunhours != 5)
		{
			cout << "Kindly enter 5 or 6" << endl;
		}
	} while (sunhours != 6 && sunhours != 5 || cin.fail());

	return sunhours;
}
float calculationofWh(int sunhours, float total_energy) // to calculate the energy the solar has to generate per month
{
	// returns requirement in watt Hours
	float totalwh;
	totalwh = (total_energy) / (sunhours * 30);
	return totalwh;
}
float roofsize() // the roof area of the house in sq feet
{
	float roofSqFt;

	cout << "\nAccording to Pakistani bylaws, a 1 Kanal property has a 1300 sqft roof, and a 10 Marla property has a 1150 sqft roof." << endl;

	do
	{
		cout << "\nKindly enter the roof size in square feet: ";
		cin >> roofSqFt;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (roofSqFt < 500 || roofSqFt >= area * 5445 * 0.5)
		{
			cout << "Kindly enter value between 500 and " << area * 5445 * 0.5 << endl;
		}
	} while (roofSqFt < 500 || roofSqFt >= area * 5445 * 0.5 || cin.fail()); // area in kanal multiplied by sqft in 1 kanal multiplied by average ratio between roof and plot size
	return roofSqFt;
}
int platetype() // returns the plate type
{
	int typeofplate;

	do
	{
		cout << "\n\t\t Kindly Choose one of the Following Plate Options:\n";
		cout << "\n575 Watt Plate - Small in size, less efficient and more panels required for the same power usage.\n";
		cout << "\n595 Watt Plate - Large in size, more efficient and less panels required for the same power usage.\n";
		cout << "\nTherefore, ultimate panel cost is comparable.\n";
		cout << "\nType (575/595): ";
		cin >> typeofplate;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (typeofplate != 575 && typeofplate != 595)
		{
			cout << "Kindly enter 575 or 595 only!" << endl;
		}
	} while ((typeofplate != 575 && typeofplate != 595) || cin.fail());
	return typeofplate;
}
int calculationofplates(float Wh_requirement, float roof_size, int typeofplate) // to calculate the plates required
{
	int totalplates, n;
	float areaofplates;
	totalplates = Wh_requirement / typeofplate;
	if (typeofplate == 595)
	{									 // choice is 595
		areaofplates = totalplates * 30; // 30 square feet is size of one panel.
		if (areaofplates > roof_size)
		{
			do
			{

				cout << "\nWe regret to inform you that there is insufficient space for the current setup. If you are willing to incur additional charges for mounting stands to optimize the installation, kindly press 1 to proceed, or 2 to continue without the stand installation: ";
				cin >> n;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\nInvalid input! Kindly enter integer value.\n";
				}
				else if (n != 1 && n != 2)
				{
					cout << "Kindly enter 1 or 2 only!" << endl;
				}
			} while ((n != 1 && n != 2) || cin.fail());

			if (n == 1)
			{
				int addstandcost = 1;
				return totalplates;
			}
			else
			{
				return totalplates = roof_size / 30.0;
			}
		}
		else
		{
			return totalplates;
		}
	}
	else
	{ // choice is 575
		areaofplates = totalplates * 28.0;
		if (areaofplates > roof_size)
		{
			do
			{

				cout << "\nWe regret to inform you that there is insufficient space for the current setup. If you are willing to incur additional charges for mounting stands to optimize the installation, kindly press 1 to proceed, or kindly 2 to continue without the stand installation: ";
				cin >> n;
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\nInvalid input! Kindly enter integer value.\n";
				}
				else if (n != 1 && n != 2)
				{
					cout << "Kindly enter 1 or 2 only!" << endl;
				}
			} while ((n != 1 && n != 2) || cin.fail());
			if (n == 1)
			{
				int addstandcost = 1;
				return totalplates;
			}
			else
			{
				return totalplates = roof_size / 28.0;
			}
		}
		else
		{
			return totalplates;
		}
	}
}
char Invertortype() // calculates the type of invertor(ongrid/hybrid)
// returns (O/H)
{
	char invertor;
	char ans1, ans2, invertorChoice;

	do
	{

		cout << "\nDo you require electricity after sunset? (Y/N) ";
		cin >> ans1;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter character\n";
		}
		else if (ans1 != 'Y' && ans1 != 'N')
		{
			cout << "Kindly enter 'N' or 'Y' only!" << endl;
		}
	} while (ans1 != 'Y' && ans1 != 'N' || cin.fail());

	do
	{

		cout << "\nDo you experience load shedding in your area? (Y/N) ";
		cin >> ans2;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter character.\n";
		}
		else if (ans2 != 'Y' && ans2 != 'N')
		{
			cout << "Kindly enter 'N' or 'Y' only!" << endl;
		}
	} while (ans2 != 'Y' && ans2 != 'N' || cin.fail());
	if (ans1 == 'N' && ans2 == 'N')
	{
		invertor = 'O';
		cout << "\nBased on your requirements, an On-Grid system is the most suitable option.\n";
	}
	else
	{

		do
		{

			cout << "\t\t\nWe recommend selecting a Hybrid inverter for optimal performance.\n";
			cout << "\nWould you like to incorporate a Hybrid Invertor with your On-Grid system ? (Y/N) ";
			cin >> invertorChoice;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "\nInvalid input! Kindly enter character.\n";
			}
			else if (invertorChoice != 'Y' && invertorChoice != 'N')
			{
				cout << "Kindly enter 'N' or 'Y' only!" << endl;
			}
		} while ((invertorChoice != 'Y' && invertorChoice != 'N') || cin.fail());

		if (invertorChoice == 'Y')
		{
			battery = 1;
			invertor = 'H';
			cout << "\t\t\Based on your requirements, a hybrid system combined with an on-grid setup is suitable.\n\n";
		}
		else
		{
			invertor = 'O';
			cout << "\nBased on your requirements, an On - Grid system is the most suitable option.\n";
		}
	}

	return invertor;
}
float invertorsize(char invertorType, int totalplates, int typeofplate) // to calculate the total size of the invertor
{
	char p;
	float kw = (static_cast<float>(totalplates) * typeofplate) / 1000;
	float invertorsize = 0;
	float estkw;
	float diff;

	do
	{

		cout << "\nDo you plan to expand your solar capacity in the future? (Y/N) ";
		cin >> p;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter character.\n";
		}
		else if (p != 'Y' && p != 'N')
		{
			cout << "Kindly enter 'N' or 'Y' only!" << endl;
		}
	} while ((p != 'Y' && p != 'N') || cin.fail());

	if (p == 'Y')
	{

		do
		{

			cout << "\nHow many additional estimated kW will you require in the future ? Please specify the amount: ";
			cin >> estkw;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "\nInvalid input! Kindly enter integer value.\n";
			}
			else if (estkw <= 0 || estkw > kw * 2)
			{
				cout << "Kindly enter value between 0 and " << kw * 2 << endl;
			}
		} while (estkw <= 0 || estkw > kw * 2 || cin.fail());

		kw = kw + estkw;
		diff = static_cast<float>(kw) - static_cast<int>(kw);
		if (diff == 0)
			invertorsize = kw;
		else
			invertorsize = kw + 1;
	}
	else if (p == 'N')
	{
		diff = static_cast<float>(kw) - static_cast<int>(kw);
		if (diff == 0)
			invertorsize = kw;

		else
			invertorsize = kw + 1;
	}

	return invertorsize;
}
int getHybridDiv(int invertorSize) // to calculate the size of the hybrid invertor
{
	int hybridKW;

	do
	{

		cout << "\nOut of " << invertorSize << "KW, how much do you require solely for a hybrid system (must be in integer): ";
		cin >> hybridKW;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (hybridKW < 0 || hybridKW > invertorSize)
		{
			cout << "Kindly enter value more than 0 or less than " << invertorSize << endl;
		}
	} while (hybridKW < 0 || hybridKW > invertorSize || cin.fail());

	return hybridKW;
	// once returned, pass it as parameter to getOngridDiv function to calculate the remaining KW for ongrid KW
}
int getOngridDiv(int invertorSize, char invertorType, int hybridKW) // to calculate the ongrid invertor size
{																	// will run in both cases (O and H)
	int onGridKW;
	if (invertorType == 'O')
		onGridKW = invertorSize;
	else
		onGridKW = invertorSize - hybridKW;
	return onGridKW;
}
float invertorcosts(int onGridKW, int hybridKW, char invertorType) // returns the total invertor cost
{
	if (invertorType == 'H')
		return (onGridKW * 20000) + (hybridKW * 55000);
	else
		return (onGridKW * 20000);
}
float platecost(int plateRequirement, int typeofplate) // to calculate the total cost of plates
{
	if (typeofplate == 595)
		return plateRequirement * 17850;
	else
		return plateRequirement * 16675;
}
float standcost(int totalplates) // returns the total cost of the stands
{
	if (addstandcost == 1)
		return 1500 * totalplates;
	else
		return 1200 * totalplates;
}
float labourcosts() // to calculate the total cost of the stands
{
	float labourcosts;
	if (kw <= 20)
	{
		labourcosts = 80000;
	}
	else
	{
		labourcosts = ((kw - 20) * 500) + (80000);
	}
	return labourcosts;
}
float batterycosts() // the total battery cost
{
	float batterycosts;
	if (battery == 1)
	{
		batterycosts = 200000;
		return batterycosts;
	}
	return 0;
}
float othercosts(int totalplates) // to calculate other costs like wires etc
{
	float othercosts = totalplates * 200;
	return othercosts;
}
float costs(float invertorcosts, float platecost, float labourcosts, float othercosts, float batterycosts, float standcost) // to calculate the total cost of the solar system
{
	float totalcost;
	char e;

	do
	{

		cout << "\nDo you require earthing to protect your appliances from lightning? (Y/N) ";
		cin >> e;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter character.\n";
		}
		else if (e != 'Y' && e != 'N')
		{
			cout << "Kindly enter 'Y' or 'N' only! " << endl;
		}
	} while ((e != 'Y' && e != 'N') || cin.fail());

	if (e == 'Y')
	{
		earthing = 25000;
		totalcost = invertorcosts + platecost + labourcosts + othercosts + batterycosts + standcost + 25000;
	}
	else
	{
		totalcost = invertorcosts + platecost + labourcosts + othercosts + batterycosts + standcost;
	}

	return totalcost;
}
float moneysaved(float total_energy)
{
	float billsaved = (total_energy / 1000) * 64;
	return billsaved;
}

// profile management
int userOption()
{
	int option;
	cout << endl
		 << endl;
	cout << "\t\t| MENU |" << endl;
	cout << "\n1: Create New Profile \n2: View All Profiles \n3: Update Profile \n4: Delete Profile \n5: Restore previous profile\n6: Tips and Resources\n7: Exit\n\n";

	do
	{

		cout << "\tKindly select an option from 1 to 7 to proceed: ";
		cin >> option;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter integer value.\n";
		}
		else if (option < 1 || option > 7)
		{
			cout << "Kindly enter value between 1 and 7 only! " << endl;
		}
	} while (option < 1 || option > 7 || cin.fail());

	return option;
}
bool login()
{
	cout << "\n\t\tKindly complete the required fields to proceed with your request.\n";

	do
	{
		cout << "\nKindly enter admin username: ";
		cin >> logusername;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter string value.\n";
		}
	} while (cin.fail());

	if (logusername == adminUsername)
	{

		do
		{
			cout << "\nKindly enter admin password: ";
			cin >> logpassword;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "\nInvalid input! Kindly enter string value.\n";
			}
		} while (cin.fail());

		if (logpassword == adminPw)
		{
			cout << "\nLogin successful. Welcome!" << endl
				 << endl;
			return true;
		}
		else
		{
			cout << "\nIncorrect admin username. Kindly try again." << endl
				 << endl;
			return false;
		}
	}
	else
	{
		cout << "\nIncorrect admin username. Kindly try again." << endl
			 << endl;
		return false;
	}

	// cout << "WELCOME USER: " << username << endl << endl << endl;
	// cout << "PLEASE FILL OUT THE FORM TO RECEIVE AN ACCURATE ESTIMATION OF YOUR SOLAR PANEL REQUIREMENTS. ENSURE THAT YOU PROVIDE PRECISE DETAILS AND FIGURES FOR THE MOST RELIABLE RESULTS. FEEL FREE TO VERIFY YOUR VALUES AGAINST YOUR ELECTRICITY BILLS OR CONSULT WITH A TRUSTED ADVISOR IF NEEDED. " << endl << endl << endl << endl << endl;
}
string createaccount()
{
	string firstLine;
	cout << "\t\t\t\t\tCREATE AN ACCOUNT\n\n";
	cout << "\nKindly complete the following fields to successfully set up your account. Ensure all information provided is accurate to proceed smoothly with the setup process\n\n";

	do
	{
		cout << "Kindly enter your forename: "; // add in file
		cin >> forename;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter string value.\n";
		}
	} while (cin.fail());

	do
	{
		cout << "Kindly enter your surname: "; // add in file
		cin >> surname;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter string value.\n";
		}
	} while (cin.fail());

	profile_number++;
	cout << "\n\t\t\tCongratulations! Your account has been successfully set up.\n\n";

	firstLine = "Profile Name: " + forename + " " + surname;
	return firstLine;
}
bool checkFile()
{
	ifstream inData("profiles.txt");
	if (!inData)
	{
		cout << "\nFile does not exist. Try another option.\n";
		return false;
	}
	inData.close();
	return true;
}

void SolarCalcToFile(string firstLine)
{
	float total_energy_usage, watt_hr_requirement, roof_size, invertor_size, plate_cost, stand_cost, labour_cost, battery_cost, other_costs, money_saved;

	char house, invertor_type;

	int rooms, sun_hours, plate_type, plates_requirement, total_cost, Ongrid_invertor_size, Hybrid_invertor_size{}, invertor_cost;
	cout << "\nPlease input the peak usage values during summers to ensure sufficient headroom and to minimize the risk of accidents.\n";
	do
	{

		cout << "\nKindly enter house measurement unit (M or Marla or K for Kanal): ";
		cin >> house;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter character.\n";
		}
		else if (house != 'K' && house != 'M')
		{
			cout << "Kindly enter 'K' or 'M' only! " << endl;
		}
	} while ((house != 'K' && house != 'M') || cin.fail());
	if (house == 'M')
		area = marla();
	else
		area = kanal();
	rooms = checkRoom();
	total_energy_usage = energyHeavyTotal() + energyLightTotal(rooms);
	sun_hours = getSunpeakhours();
	watt_hr_requirement = calculationofWh(sun_hours, total_energy_usage);
	roof_size = roofsize();
	plate_type = platetype();
	plates_requirement = calculationofplates(watt_hr_requirement, roof_size, plate_type);
	invertor_type = Invertortype();
	invertor_size = invertorsize(invertor_type, plates_requirement, plate_type);
	if (invertor_type == 'H')
	{
		Hybrid_invertor_size = getHybridDiv(invertor_size);
		Ongrid_invertor_size = getOngridDiv(invertor_size, invertor_type, Hybrid_invertor_size);
	}
	else
	{
		Ongrid_invertor_size = getOngridDiv(invertor_size, invertor_type, 0);
	}
	invertor_cost = invertorcosts(Ongrid_invertor_size, Hybrid_invertor_size, invertor_type);
	plate_cost = platecost(plates_requirement, plate_type);
	stand_cost = standcost(plates_requirement);
	labour_cost = labourcosts();
	battery_cost = batterycosts();
	other_costs = othercosts(plates_requirement);
	total_cost = costs(invertor_cost, plate_cost, labour_cost, other_costs, battery_cost, stand_cost);
	money_saved = moneysaved(total_energy_usage);
	ofstream outData;

	outData.open("profiles.txt", ios::app);
	outData << firstLine << endl;
	outData << "Size of house: " << area << " Kanal " << endl;
	outData << "Number of rooms: " << rooms << endl;
	outData << "Number of Appliances: " << totalapp << endl;
	outData << "Number of plates required: " << plates_requirement << endl;
	outData << "Invertor Cost: " << invertor_cost << " PKR" << endl;
	outData << "Plates cost: " << static_cast<int>(plate_cost) << " PKR" << endl;
	outData << "Stand cost: " << stand_cost << " PKR" << endl;
	outData << "Labour cost: " << labour_cost << " PKR" << endl;
	outData << "Battery cost: " << battery_cost << " PKR" << endl;
	outData << "Earthing cost: " << earthing << " PKR" << endl;
	outData << "Other costs: " << other_costs << " PKR" << endl;
	outData << "Total cost has ammounted to: " << total_cost << " PKR" << endl;
	outData << "Potential savings in bills: " << money_saved << " PKR" << endl
			<< endl;
	outData.close();
	cout << "\n\n\t\t\tRECORD ADDED TO FILE SUCCESSFULY.\n\n";
	outData.open("backup.txt", ios::app);
	outData << firstLine << endl;
	outData << "Size of house: " << area << " Kanal " << endl;
	outData << "Number of rooms: " << rooms << endl;
	outData << "Number of Appliances: " << totalapp << endl;
	outData << "Number of plates required: " << plates_requirement << endl;
	outData << "Invertor Cost: " << invertor_cost << " PKR" << endl;
	outData << "Plates cost: " << static_cast<int>(plate_cost) << " PKR" << endl;
	outData << "Stand cost: " << stand_cost << " PKR" << endl;
	outData << "Labour cost: " << labour_cost << " PKR" << endl;
	outData << "Battery cost: " << battery_cost << " PKR" << endl;
	outData << "Earthing cost: " << earthing << " PKR" << endl;
	outData << "Other costs: " << other_costs << " PKR" << endl;
	outData << "Total cost has ammounted to: " << total_cost << " PKR" << endl;
	outData << "Potential savings in bills: " << money_saved << " PKR" << endl
			<< endl;
	outData.close();
	cout << "\nTo access your summary, please select option 2.\n";
	return;
}

void readfile()
{
	ifstream inData("profiles.txt");
	if (!inData)
	{
		cout << "\nFile does not exist. Please try another option.\n";
		return;
	}
	string line;
	// Read file line by line
	while (getline(inData, line))
	{
		cout << line << endl; // Output each line to the console
	}
	cout << endl;
	inData.close();
}
bool nameExistsProfiles(string name)
{
	bool found = false;
	string line;
	ifstream inData("profiles.txt");
	if (!inData)
	{
		cout << "\nFile does not exist. Please try another option.\n";
		inData.close();
		return false;
	}
	while (getline(inData, line))
	{
		if (name == line)
		{
			inData.close();
			return true;
		}
	}
	inData.close();
	return false;
}
bool nameExistsBackup(string name)
{
	bool found = false;
	string line;
	ifstream inData("backup.txt");
	if (!inData)
	{
		cout << "\nFile does not exist. Please try another option.\n";
		inData.close();
		return false;
	}
	while (getline(inData, line))
	{
		if (name == line)
		{
			inData.close();
			return true;
		}
	}
	inData.close();
	return false;
}
void deleteProfile(string checkName)
{
	char choice;
	// format of checkName is "Profile Name: firsName LastName"

	do
	{
		cout << "\nAre you sure you want to delete this profile? (Y/N) ";
		cin >> choice;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input! Kindly enter character.\n";
		}
		else if (choice != 'Y' && choice != 'N')
		{
			cout << "Kindly enter 'Y' or 'N' only! " << endl;
		}
	} while (choice != 'Y' && choice != 'N' || cin.fail());

	if (choice == 'N')
		return;
	string line;
	// backup profile content to backup.txt
	ifstream inData("profiles.txt");
	ofstream outData("backup.txt");

	while (getline(inData, line))
	{
		outData << line << endl;
	}
	outData.close();
	inData.close();
	// copying profile data from profiles.txt to temp.txt

	inData.open("profiles.txt");
	outData.open("temp.txt");
	while (getline(inData, line))
	{
		if (line == checkName)
		{ // copy  13 lines
			for (int i = 0; i < 14; i++)
			{
				getline(inData, line);
			}
		}
		else
		{
			outData << line << endl;
		}
	}
	// profiles copied to temp.txt
	inData.close();
	outData.close();

	ofstream outDataFinal("profiles.txt", ios::trunc); // emptied contents of profile.txt
	ifstream inDataFinal("temp.txt");
	while (getline(inDataFinal, line))
	{
		outDataFinal << line << endl;
	}
	inDataFinal.close();
	outDataFinal.close();
	cout << "\nProfile deleted successfully" << endl;
	remove("temp.txt");
}
void updateProfile(string checkName)
{
	string line;
	ifstream inData("profiles.txt");
	ofstream outData("temp.txt");

	while (getline(inData, line))
	{
		if (line == checkName)
		{ // copy  13 lines
			for (int i = 0; i < 14; i++)
			{
				getline(inData, line);
			}
		}
		else
		{
			outData << line << endl;
		}
	}
	inData.close();
	outData.close();

	// profiles copied to temp.txt

	ofstream outDataFinal("profiles.txt", ios::trunc); // emptied contents of profile.txt
	ifstream inDataFinal("temp.txt");
	while (getline(inDataFinal, line))
	{
		outDataFinal << line << endl;
	}
	inDataFinal.close();
	outDataFinal.close();

	remove("temp.txt");

	SolarCalcToFile(checkName);
}
void restorefile()
{
	string line, checkline, fore, last;
	ifstream inData("backup.txt");
	ofstream outData("profiles.txt", ios::app);

	if (!inData)
	{
		cout << "File does not exist. Please choose another option to continue.\n";
		return;
	}
	cout << "Enter forename: ";
	cin >> fore;
	cout << "Enter surname: ";
	cin >> last;
	checkline = "Profile Name: " + fore + " " + last;
	if (!nameExistsBackup(checkline))
	{
		cout << "\nName does not exist for the file to be restored.\n";
		return;
	}
	while (getline(inData, line))
	{
		if (checkline == line)
		{
			outData << line << endl;
			for (int i = 0; i < 14; i++)
			{
				if (getline(inData, line))
				{
					outData << line << endl;
				}
				else
				{
					break;
				}
			}
			break;
		}
	}
	inData.close();
	outData.close();
	cout << "File restored successfully.\n";
}

int main()
{
	int option;
	bool fileExist = false, nameExistence, flag;
	string checkName, firstLine;

	cout << "\t\t\t\t==============================================\n";
	cout << "\t\t\t\t|    WELCOME TO THE SOLAR PANEL ESTIMATOR    |\n";
	cout << "\t\t\t\t==============================================\n";

	while (true)
	{
		option = userOption();
		switch (option)
		{
		case 1:
			// creates a new profile
			firstLine = createaccount();
			SolarCalcToFile(firstLine);

			break;
		case 2:
			// views all profiles
			// ask for pw and username
			// check file, if doesnt exist then print No profiles exist and ask options 1-5 again

			if (login())
				readfile();
			else
				cout << "\nLogin failed. Please choose a different option to proceed." << endl
					 << endl;

			break;
		case 3:
			// updates a profile
			// ask for pw and username
			// check file, if doesnt exist then print No profiles exist and ask options 1-5 again
			// if it exists, ask which profile in file
			if (!login())
				cout << "\nLogin failed. Please choose a different option to proceed." << endl
					 << endl;
			else
			{
				cout << "\n\t\tTo update your profile, please follow the provided steps.\n";

				do
				{
					cout << "\nKindly enter your first name: ";
					cin >> forename;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "\nInvalid input! Kindly enter string value.\n";
					}
				} while (cin.fail());

				do
				{
					cout << "\nKindly enter your last name : ";
					cin >> surname;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "\nInvalid input! Kindly enter string value.\n";
					}
				} while (cin.fail());
				checkName = "Profile Name: " + forename + " " + surname;
				nameExistence = nameExistsProfiles(checkName);
				if (!nameExistence)
				{
					cout << "\nProfile update unsuccessful. Please choose a different option to proceed." << endl
						 << endl;
				}
				else
				{
					updateProfile(checkName);
				}
			}

			break;
		case 4:
			// deletes profile
			// ask for pw and username
			// check file,
			// if doesnt exist then print No profiles exist and ask options 1-5 again
			// if exists, ask which profile in file
			// if profile doesnt exists, print no profile
			// else confirm deletion

			if (!login())
				cout << "\nLogin unsuccessful. Kindly select an alternative option to continue." << endl
					 << endl;
			else
			{
				cout << "\n\t\tTo delete your profile, please follow the provided steps.\n\n";
				do
				{
					cout << "Kindly enter your first name: ";
					cin >> forename;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "\nInvalid input! Kindly enter string value.\n";
					}
				} while (cin.fail());

				do
				{
					cout << "Kindly enter your last name : ";
					cin >> surname;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(1000, '\n');
						cout << "\nInvalid input! Kindly enter string value.\n";
					}
				} while (cin.fail());
				checkName = "Profile Name: " + forename + " " + surname;
				nameExistence = nameExistsProfiles(checkName);
				if (!nameExistence)
				{
					cout << "\nProfile deletion unsuccessful. Please choose a different option to proceed." << endl
						 << endl;
				}
				else
				{
					deleteProfile(checkName);
				}
			}
			break;
		case 5:
			restorefile();

			break;
		case 6:

			cout << "\nTo learn more about solar energy and the benefits you can achieve by installing solar panels, kindly visit the website provided below by pressing leftCtrl and left mouse button\n";
			cout << "https://www.constellation.com/energy-101/energy-innovation/solar-energy-pros-and-cons.html" << endl
				 << endl;
			cout << "Choosing a 575W solar panel over a 595W panel depends on specific needs and constraints:\n\n"
				 << "  1. Smaller Size         : Better fit for limited space or precise placements.\n"
				 << "  2. Ease of Installation : Lighter and easier to handle, reducing labor effort.\n"
				 << "  3. System Compatibility : Matches existing arrays in size or efficiency.\n"
				 << "  4. Cost                 : Lower upfront cost, despite comparable overall expense.\n"
				 << "  5. Availability         : Shorter lead times or higher stock levels.\n"
				 << "  6. Small Roofs          : Better suited for optimizing limited roof space.\n"
				 << "  7. Project Requirements : Tailored to specific efficiency or design needs.\n\n\n";

			cout << "Brushing solar panels periodically helps improve efficiency by:\n\n";
			cout << " 1. Removing dust and dirt that block sunlight absorption.\n";
			cout << " 2. Preventing long-term build-up of debris, avoiding damage.\n";
			cout << " 3. Ensuring optimal light absorption for maximum energy output.\n";
			cout << " 4. Preventing water and mineral deposits that reduce performance.\n";
			cout << " 5. Recommended cleaning every 6 to 12 months, depending on location.\n";
			cout << "Use a soft-bristled brush to avoid scratches and damage.\n";
			cout << "Regular brushing keeps panels at peak efficiency and extends their lifespan.\n\n\n";

			cout << "Solar Panel Maintenance Tips:\n\n";
			cout << " 1. Regular Cleaning: Clean panels every 6-12 months using a soft brush or hose. Avoid harsh chemicals.\n";
			cout << " 2. Inspect for Damage: Check for cracks, chips, and secure mounting. Repair if needed.\n";
			cout << " 3. Monitor Performance: Track energy output and check inverters for faults. A sudden drop may indicate an issue.\n";
			cout << " 4. Ensure Proper Ventilation: Keep space around panels clear of obstructions to prevent overheating.\n";
			cout << " 5. Check Electrical Connections: Inspect wiring for wear and corrosion, and ensure grounding.\n";
			cout << " 6. Professional Inspections: Get a technician to inspect the system every 1-2 years.\n";
			cout << " 7. Snow and Ice Maintenance: Remove snow gently using a soft broom. Avoid high-pressure water.\n";
			cout << " 8. System Firmware: Keep inverter firmware updated to optimize performance.\n";

			cout << "\nRegular maintenance ensures optimal efficiency and long-lasting solar panels!\n";
			break;
		case 7:
			cout << "\n\nThank you for using the Solar Estimator Program. We sincerely hope that our estimations meet your expectations and prove to be helpful. Should you require any further assistance, please do not hesitate to contact us at: \n l242553@lhr.nu.edu.pk\n l242591@lhr.nu.edu.pk\n l242501@lhr.nu.edu.pk" << endl;
			return 0;
		}
	}
	return 0;
}
