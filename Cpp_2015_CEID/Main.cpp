#pragma warning(push)
#pragma warning(disable: 4715)


#include <iostream>
#include <iomanip>
#include <time.h>
#include <windows.h>
#include <vector>
#include <string>

#include "GridPoint.h"
#include "Ship.h"
#include "Commercial.h"
#include "Explorer.h"
#include "Pirate.h"
#include "Service.h"
#include "Passenger.h"
#include "Tanker.h"

using namespace std;

void createShip0(vector<vector<GridPoint*> >&, vector<vector<Ship*> >&, int, int, double, double, int, int, int, int, bool);
void roundStart(vector<vector<GridPoint*> >&, vector<vector<Ship*> >&);
void roundCont(vector<vector<GridPoint*> >&, vector<vector<Ship*> >&);
void roundEnd(vector<vector<GridPoint*> >&, vector<vector<Ship*> >&);
void orderByTreas(vector<vector<Ship*> >);
void orderByEndur(vector<vector<Ship*> >);
void orderBySpeed(vector<vector<Ship*> >);
bool userMenu(vector<vector<GridPoint*> >&, vector<vector<Ship*> >&);



int main()
{
	int n, ty, MxEnd, Sped, Tres, rndm;
	bool menuEnter, simCont;
	size_t i, j, z;


	//Define console window and buffer size
	SMALL_RECT Coord{ 0, 0, 80, 35 };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), { 250, 300 });
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), true, &Coord);
	
	//Insert map dimensions and create Simulation Map
	do
	{
		cout << "\nPlease enter map dimension (integer value 5 - 20) : ";
		cin >> n;
		cout << "\n" << endl;
	} while (n < 5 || n>20);
	Sleep(2000);
	system("CLS");

	vector<GridPoint*> gcol(n);
	vector<vector<GridPoint*> > GridMap(n, gcol);


	//Create Ship Array
	vector<vector<Ship*> > ShipArray(7);
	

	//Create initial random map contents
	srand(time(NULL));	
	for (i = 0; i < GridMap.size(); ++i)
	{
		for (j = 0; j < GridMap.size(); ++j)
		{
			rndm = rand() % 11;

			if (rndm < 5)
			{
				//Plain Sea
				GridPoint* gp = new GridPoint(i, j, (1 + (rand() % 10)), false, false);
				GridMap[i][j] = gp;
			}
			else if (rndm < 9)
			{
				//Treasure
				GridPoint* gp = new GridPoint(i, j, (1 + (rand() % 10)), true, false);
				GridMap[i][j] = gp;
			}
			else
			{
				//Port
				GridPoint* gp = new GridPoint(i, j, (1 + (rand() % 10)), false, true);
				GridMap[i][j] = gp;
			}
		}
	}

	
	//Create initial random ships
	srand(time(NULL));
	for (z = 0; z < (rand() % ((n*n) / 2) + 10); ++z)
	{
		i = rand() % n;
		j = rand() % n;
		ty = rand() % 6 + 1;
		MxEnd = rand() % 10 + 10;
		Sped = rand() % 3 + 1;
		Tres = rand() % 10 + 1;
		
		createShip0(GridMap, ShipArray, i, j, MxEnd, MxEnd, Sped, Tres, n, ty, true);
	}
	

	//Print initial simulation map with random ships
	cout << "\n\n--------------------------------------------------------------------------------" << endl;
	cout << "Simulation begins!" << endl;
	cout << "Please press 'P' or 'p' during the simulation to pause and access the menu!" << endl;
	cout << "--------------------------------------------------------------------------------\n\n\n" << endl;
	Sleep(1000);

	string simstr = "---------- SIMULATION MAP : ----------";
	for (i = 0; i < (simstr.size() / 2); ++i)
	{
		cout << ' ';
	}
	cout << simstr << "\n\n\n" << endl;
	

	cout << "          ";
	for (j = 0; j < GridMap.size(); ++j)
	{
		string col = "[" + to_string(j) + "]  ";
		cout << left << setw(6) << col;
	}
	cout << "\n\n\n" << endl;

	
	for (i = 0; i < GridMap.size(); ++i)
	{
		string row = " [" + to_string(i) + "]     ";
		cout << setfill(' ') << setw(10) << row;

		for (j = 0; j < GridMap.size(); ++j)
		{
			GridMap[i][j]->printMap();
		}
		cout << "\n\n" << endl;
	}
	Sleep(5000);
	

	//Start simulation
	for (;;)
	{
		menuEnter = false;
		
		//If 'P' or 'p' has been pressed
		if (GetAsyncKeyState(80) || GetAsyncKeyState(112))
		{
			simCont = false;

			cout << "\n\n\n................................................................................\n" << endl;
			cout << "Press 'M' or 'm' to enter the User Menu." << endl;
			cout << "Press 'C' or 'c' to resume the simulation." << endl;
			cout << "................................................................................\n\n\n" << endl;
			
			while (!simCont)
			{
				//If 'M' or 'm' has been pressed
				if (GetAsyncKeyState(77) || GetAsyncKeyState(109))
				{
					menuEnter = true;
					while (menuEnter)
					{
						system("CLS");
						menuEnter = userMenu(GridMap, ShipArray);
					}

					simCont = true;
				}

				//If 'C' or 'c' has been pressed
				if (GetAsyncKeyState(67) || GetAsyncKeyState(99))
				{
					simCont = true;
				}
			}
		}

		//New round begins
		system("CLS");
		roundStart(GridMap, ShipArray);
		roundCont(GridMap, ShipArray);
		roundEnd(GridMap, ShipArray);
		Sleep(5000);
	}
	system("PAUSE");
}



void createShip0(vector<vector<GridPoint*> >&GridMap, vector<vector<Ship*> >&ShipArray, int xIn, int yIn, double MaxEnd, double CurEnd, int Speed, int TreasQ, int n, int ty, bool r)
{
	bool ggXY;
	bool ggXY2;
	bool corXY = true;
	
	do
	{
		//If the given coordinates aren't out of bounds
		if ((xIn > -1) && (xIn < n) && (yIn > -1) && (yIn < n))
		{
			ggXY = true;

			do
			{
				//If the map point is empty
				if (GridMap[xIn][yIn]->getIsEmpty())
				{
					GridMap[xIn][yIn]->setIsEmpty(false);
					corXY = true;

					//Create new ship of the given type "ty"
					if (ty == 1)
					{
						Commercial::createShip(GridMap, ShipArray, xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ);
					}
					else if (ty == 2)
					{
						Explorer::createShip(GridMap, ShipArray, xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ);
					}
					else if (ty == 3)
					{
						Passenger::createShip(GridMap, ShipArray, xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ);
					}
					else if (ty == 4)
					{
						Pirate::createShip(GridMap, ShipArray, xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ);
					}
					else if (ty == 5)
					{
						Service::createShip(GridMap, ShipArray, xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ);
					}
					else
					{
						Tanker::createShip(GridMap, ShipArray, xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ);
					}

				}
				//If the map point isn't empty
				else if ((!r) && (!(GridMap[xIn][yIn]->getIsEmpty())))
				{
					cout << "\nThe Grid point [" << xIn << "," << yIn << "] is not empty. Please enter other coordinates.\n" << endl;
					cout << "Enter x : ";
					cin >> xIn;
					cout << "Enter y : ";
					cin >> yIn;
					cout << "\n" << endl;
					corXY = false;
					
					do
					{
						ggXY2 = true;

						if ((xIn < 0) || (xIn > n - 1) || (yIn < 0) || (yIn > n - 1))
						{
							cout << "\nInvalid coordinates inserted. Please enter other coordinates. (-1 < x,y < n)\n" << endl;
							cout << "Enter x : ";
							cin >> xIn;
							cout << "Enter y : ";
							cin >> yIn;
							cout << "\n" << endl;
							ggXY2 = false;
						}
					} while (!ggXY2);
				}
			} while (!corXY);
		}
		else
		{
			cout << "\nInvalid coordinates inserted. Please enter other coordinates. (-1 < x,y < n)\n" << endl;
			cout << "Enter x : ";
			cin >> xIn;
			cout << "Enter y : ";
			cin >> yIn;
			cout << "\n" << endl;
			ggXY = false;
		}
	} while (!ggXY);
}



void roundStart(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray)
{
	size_t j;
	
	//Check each ship for weather damage, treasure existence, port existence
	for (j = 0; j < ShipArray.at(6).size(); ++j)
	{
		ShipArray[6][j]->WeatherDamage(GridMap);
		ShipArray[6][j]->TreasurePoint(GridMap);
		ShipArray[6][j]->PortPoint(GridMap);
	}
}



void roundCont(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray)
{
	size_t i, j;

	//Move each ship
	for (j = 0; j < ShipArray.at(6).size(); ++j)
	{
		ShipArray[6][j]->Move(GridMap);
	}


	//Print refreshed simulation map
	cout << "\n\n--------------------------------------------------------------------------------" << endl;
	cout << "Simulation begins!" << endl;
	cout << "Please press 'P' or 'p' during the simulation to pause and access the menu!" << endl;
	cout << "--------------------------------------------------------------------------------\n\n\n" << endl;
	
	string simstr = "---------- SIMULATION MAP : ----------";
	for (i = 0; i < (simstr.size() / 2); ++i)
	{
		cout << ' ';
	}
	cout << simstr << "\n\n\n" << endl;


	cout << "          ";
	for (j = 0; j < GridMap.size(); ++j)
	{
		string col = "[" + to_string(j) + "]  ";
		cout << left << setw(6) << col;
	}
	cout << "\n\n\n" << endl;


	for (i = 0; i < GridMap.size(); ++i)
	{
		string row = " [" + to_string(i) + "]     ";
		cout << setfill(' ') << setw(10) << row;

		for (j = 0; j < GridMap.size(); ++j)
		{
			GridMap[i][j]->printMap();
		}
		cout << "\n\n" << endl;
	}


	//Each ship executes its function
	cout << "\n--------------------------------------------------------------------------------" << endl;
	for (j = 0; j < ShipArray.at(6).size(); ++j)
	{
		ShipArray[6][j]->ShipFunc(GridMap, ShipArray);
	}
	cout << "--------------------------------------------------------------------------------\n\n\n" << endl;
}



void roundEnd(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray)
{
	size_t i, j;
	j = 0;

	//Check if any ships are dead and remove them
	while (j < ShipArray.at(6).size())
	{
		if ((ShipArray[6][j]->getCurEndur()) <= 0)
		{
			ShipArray[6][j]->destroyShip(GridMap, ShipArray, j, treas1);
		}
		else
		{
			++j;
		}
	}


	//Refresh weather intensity randomly (+1 / -1)
	for (i = 0; i < GridMap.size(); ++i)
	{
		for (j = 0; j < GridMap.size(); ++j)
		{
			int a = rand() % 2;

			if ((a == 1) && (GridMap[i][j]->getWeather() < 10))
			{
				GridMap[i][j]->setWeather(GridMap[i][j]->getWeather() + 1);
			}
			else if ((a == 0) && (GridMap[i][j]->getWeather() > 0))
			{
				GridMap[i][j]->setWeather(GridMap[i][j]->getWeather() - 1);
			}
		}
	}


	//Check if all ships are removed
	if (ShipArray.at(6).size() <= 0)
	{
		cout << "\nThere are no more ships at the map.\n\n" << endl;
		Sleep(1500);
		cout << "ENDING SIMULATION in ";

		for (i = 3; i >= 1; --i)
		{
			cout << i << ". ";
			Sleep(1000);
		}
		cout << endl;

		exit(0);
	}


	//Check if a ship has achieved its goal
	for (j = 0; j < ShipArray.at(6).size(); ++j)
	{
		if (ShipArray[6][j]->getGoal())
		{
			string obid = to_string(ShipArray[6][j]->getID());
			cout << "The ship " << ShipArray[6][j]->getStype() << obid[1] << obid[2] << " gathered an amount of " << ShipArray[6][j]->getTreasFund() << " treasure and achieved its objective.\n\n" << endl;
			Sleep(1500);
			cout << "ENDING SIMULATION in ";

			for (i = 3; i >= 1; --i)
			{
				cout << i << ". ";
				Sleep(1000);
			}
			cout << endl;

			exit(0);
		}
	}
}



void orderByTreas(vector<vector<Ship*> > ShipArray)
{
	size_t i, j;
	vector<Ship*> orderArray;
	Ship* temp;

	//Order existing ships by current treasure reserve, descending
	orderArray = ShipArray.at(6);
	for (i = 0; i < orderArray.size(); ++i)
	{
		for (j = 0; j < orderArray.size() - 1; ++j)
		{
			if (orderArray[j]->getTreasFund() < orderArray[j+1]->getTreasFund())
			{
				temp = orderArray[j];
				orderArray[j] = orderArray[j + 1];
				orderArray[j + 1] = temp;
			}
		}
	}

	//Print ordered ship array
	cout << "\n\n   The ranking of all existing ships classed in descending order, based on their current treasure reserve is :\n\n" << endl;
	cout << "   Ship :\tTreasure :" << endl;
	cout << " ---------------------------" << endl;
	for (i = 0; i < orderArray.size(); ++i)
	{
		string shid = to_string(orderArray[i]->getID());
		cout << "   " << orderArray[i]->getStype() << shid[1] << shid[2] << "\t\t" << orderArray[i]->getTreasFund() << endl;
	}
	cout << "\n\n" << endl;
}



void orderByEndur(vector<vector<Ship*> > ShipArray)
{
	size_t i, j;
	vector<Ship*> orderArray;
	Ship* temp;

	//Order existing ships by current endurance, descending
	orderArray = ShipArray.at(6);
	for (i = 0; i < orderArray.size(); ++i)
	{
		for (j = 0; j < orderArray.size() - 1; ++j)
		{
			if (orderArray[j]->getCurEndur() < orderArray[j + 1]->getCurEndur())
			{
				temp = orderArray[j];
				orderArray[j] = orderArray[j + 1];
				orderArray[j + 1] = temp;
			}
		}
	}

	//Print ordered ship array
	cout << "\n\n   The ranking of all existing ships classed in descending order, based on their current endurance is :\n\n" << endl;
	cout << "   Ship :\tEndurance :" << endl;
	cout << " ----------------------------" << endl;
	for (i = 0; i < orderArray.size(); ++i)
	{
		string shid = to_string(orderArray[i]->getID());
		cout << "   " << orderArray[i]->getStype() << shid[1] << shid[2] << "\t\t" << orderArray[i]->getCurEndur() << endl;
	}
	cout << "\n\n" << endl;
}



void orderBySpeed(vector<vector<Ship*> > ShipArray)
{
	size_t i, j;
	vector<Ship*> orderArray;
	Ship* temp;

	//Order existing ships by speed, descending
	orderArray = ShipArray.at(6);
	for (i = 0; i < orderArray.size(); ++i)
	{
		for (j = 0; j < orderArray.size() - 1; ++j)
		{
			if (orderArray[j]->getSpeed() < orderArray[j + 1]->getSpeed())
			{
				temp = orderArray[j];
				orderArray[j] = orderArray[j + 1];
				orderArray[j + 1] = temp;
			}
		}
	}

	//Print ordered ship array
	cout << "\n\n   The ranking of all existing ships classed in descending order, based on their speed is :\n\n" << endl;
	cout << "   Ship :\tSpeed :" << endl;
	cout << " ------------------------" << endl;
	for (i = 0; i < orderArray.size(); ++i)
	{
		string shid = to_string(orderArray[i]->getID());
		cout << "   " << orderArray[i]->getStype() << shid[1] << shid[2] << "\t\t" << orderArray[i]->getSpeed() << endl;
	}
	cout << "\n\n" << endl;
}



bool userMenu(vector<vector<GridPoint*> >&GridMap, vector<vector<Ship*> >&ShipArray)
{
	int ch;
	bool menuEnter;
	size_t i;
	string stp;

	//Choose function to perform
	cout << "\nWELCOME TO THE SIMULATION USER MENU !\n\n" << endl;
	cout << "Available functions :" << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "0. Resume simulation." << endl;
	cout << "1. Information about a specific ship." << endl;
	cout << "2. Information about a specific point of the map." << endl;
	cout << "3. Statistical data about a specific ship type." << endl;
	cout << "4. General information about the simulation." << endl;
	cout << "5. Add/Remove a ship." << endl;
	cout << "6. Add/Remove port or treasure." << endl;
	cout << "7. End simulation.\n" << endl;

	do
	{
		cout << "Please enter the number of the function you would like to perform (0 - 7) : ";
		cin >> ch;
		
		if ((ch < 0) || (ch > 7))
		{
			cout << "\n\nInvalid menu choice. Try again...";
		}

		cout << "\n\n" << endl;
	} while ((ch < 0) || (ch > 7));


	switch (ch)
	{
	//Resume simulation
	case 0:
		menuEnter = false;
		return menuEnter;
		break;

	//Information about a specific ship
	case 1:
		size_t j;
		int c1, id1;
		bool empt, disp;

		do
		{
			empt = false;
			
			//Choose ship type
			do
			{
				cout << "\n1. Commercial" << endl;
				cout << "2. Explorer" << endl;
				cout << "3. Passenger" << endl;
				cout << "4. Pirate" << endl;
				cout << "5. Service" << endl;
				cout << "6. Tanker\n" << endl;
				cout << "Please choose the preferred ship type to display its information : ";
				cin >> c1;

				if (c1 < 1 || c1 > 6)
				{
					cout << "\nInvalid ship type. Please try again..." << endl;
				}

				cout << "\n\n" << endl;
			} while (c1 < 1 || c1 > 6);


			//Check if there are ships of the given type left or not
			if (ShipArray.at(c1 - 1).size() == 0)
			{
				empt = true;
				cout << "There are not any ships of this type." << endl;
				cout << "Please choose another ship type." << endl;
				Sleep(2000);
			}
			else
			{
				do
				{
					disp = false;

					//Choose one of the existing ship IDs printed
					cout << "\nPlease choose one of the following ship ID : ";
					for (j = 0; j < ShipArray.at(c1 - 1).size(); ++j)
					{
						cout << ShipArray[c1 - 1][j]->getID() << " ";
					}

					cout << "\nID : ";
					cin >> id1;

					//Find the selected ship in the Ship Array and print its info
					for (j = 0; j < ShipArray.at(c1 - 1).size(); ++j)
					{
						if (ShipArray[c1 - 1][j]->getID() == id1)
						{
							disp = true;
							cout << (*ShipArray[c1 - 1][j]);
							system("PAUSE");
							break;
						}
					}

					if (!disp)
					{
						cout << "\nThis ID doesn't exist.";
					}
					
					cout << "\n\n" << endl;
				} while (!disp);
			}
		} while (empt);
		break;

	//Information about a specific point of the map
	case 2:
		int xIn2, yIn2;
		bool cor2;
		
		//Insert map point coordinates and print its info
		do
		{
			cor2 = false;
			cout << "\nPlease enter the coordinates of a specific map point. (-1 < x,y < n)\n" << endl;
			cout << "Enter x : ";
			cin >> xIn2;
			cout << "Enter y : ";
			cin >> yIn2;
			cout << "\n" << endl;

			if (xIn2 >=0 && xIn2 < GridMap.size() && yIn2 >=0 && yIn2 < GridMap.size())
			{
				cor2 = true;
				GridMap[xIn2][yIn2]->printInfo();
				system("PAUSE");
			}
			else
			{
				cout << "\nInvalid data inserted. Try again...\n" << endl;
			}
		} while (!cor2);

		cout << "\n\n" << endl;
		break;

	//Statistical data about a specific ship type
	case 3:
		int cnt, ant, dnt, tdt, c3;
		double tnt;
	
		//Choose ship type
		do
		{
			cout << "\n1. Commercial" << endl;
			cout << "2. Explorer" << endl;
			cout << "3. Passenger" << endl;
			cout << "4. Pirate" << endl;
			cout << "5. Service" << endl;
			cout << "6. Tanker" << endl;
			cout << "7. All ships\n" << endl;
			cout << "Please choose the preferred ship type to display its information : ";
			cin >> c3;

			if (c3 < 1 || c3 > 7)
			{
				cout << "\nInvalid ship type. Please try again..." << endl;
			}

			cout << "\n\n" << endl;
		} while (c3 < 1 || c3 > 7);


		//Retrieve the necessary information for the ship type given
		if (c3 == 1)
		{
			stp = " Commercial ";
			cnt = Commercial::getCount();
			ant = Commercial::getCount() - Commercial::getDead();
			dnt = Commercial::getDead();
			tnt = Commercial::getTotalTreasure();
			tdt = Commercial::getTotalDamageTaken();
		}
		else if (c3 == 2)
		{
			stp = " Explorer ";
			cnt = Explorer::getCount();
			ant = Explorer::getCount() - Explorer::getDead();
			dnt = Explorer::getDead();
			tnt = Explorer::getTotalTreasure();
			tdt = Explorer::getTotalDamageTaken();
		}
		else if (c3 == 3)
		{
			stp = " Passenger ";
			cnt = Passenger::getCount();
			ant = Passenger::getCount() - Passenger::getDead();
			dnt = Passenger::getDead();
			tnt = Passenger::getTotalTreasure();
			tdt = Passenger::getTotalDamageTaken();
		}
		else if (c3 == 4)
		{
			stp = " Pirate ";
			cnt = Pirate::getCount();
			ant = Pirate::getCount() - Pirate::getDead();
			dnt = Pirate::getDead();
			tnt = Pirate::getTotalTreasure();
			tdt = Pirate::getTotalDamageTaken();
		}
		else if (c3 == 5)
		{
			stp = " Service ";
			cnt = Service::getCount();
			ant = Service::getCount() - Service::getDead();
			dnt = Service::getDead();
			tnt = Service::getTotalTreasure();
			tdt = Service::getTotalDamageTaken();
		}
		else if (c3 == 6)
		{
			stp = " Tanker ";
			cnt = Tanker::getCount();
			ant = Tanker::getCount() - Tanker::getDead();
			dnt = Tanker::getDead();
			tnt = Tanker::getTotalTreasure();
			tdt = Tanker::getTotalDamageTaken();
		}
		else
		{
			stp = " ";
			cnt = Ship::getCountALL();
			ant = Ship::getCountALL() - Ship::getDeadALL();
			dnt = Ship::getDeadALL();
			tnt = Ship::getTotalTreasureALL();
			tdt = Ship::getTotalDamageALL();
		}

		//Print ship type info
		cout << "The statistical data calculated since the beginning of the simulation are :" << endl;
		cout << "\tQuantity of all the created" << stp << "ships : " << cnt << endl;
		cout << "\tQuantity of all the alive" << stp << "ships : " << ant << endl;
		cout << "\tQuantity of all the dead" << stp << "ships : " << dnt << endl;
		cout << "\tTotal treasure reserve of" << stp << "ships : " << tnt << endl;
		cout << "\tTotal damage taken of" << stp << "ships : " << tdt << "\n\n" << endl;

		system("PAUSE");
		break;

	//General information about the simulation
	case 4:
		int ch4;

		//Choose order type to display
		do
		{
			cout << "\n1. Ranking of all ships, based on their current treasure reserve, in descending order." << endl;
			cout << "2. Ranking of all ships, based on their current endurance, in descending order." << endl;
			cout << "3. Ranking of all ships, based on their speed, in descending order." << endl;
			cout << "\nChoose classification to display : ";
			cin >> ch4;

			if ((ch4 < 1) || (ch4 > 3))
			{
				cout << "\n\nWrong choice. Please try again...\n" << endl;
			}
		} while ((ch4 < 1) || (ch4 > 3));

		//Display the ordered ship list
		switch (ch4)
		{
		case 1:
			orderByTreas(ShipArray);
			break;
		case 2:
			orderByEndur(ShipArray);
			break;
		case 3:
			orderBySpeed(ShipArray);
			break;
		}

		system("PAUSE");
		cout << "\n\n" << endl;
		break;

	//Add - Remove a ship
	case 5:
		int ch5, ch51, c5, id5, xIn5, yIn5, me5, ce5, sp5, tr5, n5;
		bool del;

		//Choose action to perform
		do
		{
			cout << "\n1. Add ship at the map." << endl;
			cout << "2. Remove ship from the map." << endl;
			cout << "\nChoose action to perform : ";
			cin >> ch5;

			if ((ch5 < 1) || (ch5 > 2))
			{
				cout << "\n\nWrong choice. Please try again...\n" << endl;
			}
		} while ((ch5 < 1) || (ch5 > 2));


		//Choose ship type
		do
		{
			cout << "\n1. Commercial" << endl;
			cout << "2. Explorer" << endl;
			cout << "3. Passenger" << endl;
			cout << "4. Pirate" << endl;
			cout << "5. Service" << endl;
			cout << "6. Tanker\n" << endl;
			cout << "Please choose ship type : ";
			cin >> c5;

			if (c5 < 1 || c5 > 6)
			{
				cout << "\nInvalid ship type. Please try again..." << endl;
			}
		} while (c5 < 1 || c5 > 6);


		switch (ch5)
		{
		//Add ship
		case 1:
			//Choose where to add the ship
			do
			{
				cout << "\n1. Add ship at random map point." << endl;
				cout << "2. Add ship at specific map point." << endl;
				cout << "\nChoose action to perform : ";
				cin >> ch51;

				if ((ch51 < 1) || (ch51 > 2))
				{
					cout << "\n\nWrong choice. Please try again...\n" << endl;
				}
			} while ((ch51 < 1) || (ch51 > 2));


			switch (ch51)
			{
			//Add to random map point
			case 1:
				n5 = GridMap.size();
				xIn5 = rand() % n5;
				yIn5 = rand() % n5;
				me5 = rand() % 10 + 10;
				ce5 = me5;
				sp5 = rand() % 3 + 1;
				tr5 = rand() % 10 + 1;
				break;
			//Add to specific map point
			case 2:
				cout << "\n\nInsert the following data about the new ship :\n" << endl;
				cout << "\tX coordinate : ";
				cin >> xIn5;
				cout << "\n\tY coordinate : ";
				cin >> yIn5;
				cout << "\n\tMax Endurance : ";
				cin >> me5;
				cout << "\n\tCurrent Endurance : ";
				cin >> ce5;
				cout << "\n\tSpeed : ";
				cin >> sp5;
				cout << "\n\tTreasure Reserve : ";
				cin >> tr5;
				cout << "\n\n";
				break;
			}
			n5 = GridMap.size();

			//Create the new ship
			createShip0(GridMap, ShipArray, xIn5, yIn5, me5, ce5, sp5, tr5, n5, c5, false);
			system("PAUSE");
			break;
		
		//Remove ship
		case 2:
			//Check if there are ships of the given type left or not
			if (ShipArray.at(c5 - 1).size() == 0)
			{
				cout << "\nThere are not any ships of this type." << endl;
				cout << "Please choose another ship type." << endl;
				Sleep(2000);
			}
			else
			{
				do
				{
					del = false;

					//Choose one of the existing ship IDs printed
					cout << "\nPlease choose one of the following ship ID : ";
					for (j = 0; j < ShipArray.at(c5 - 1).size(); ++j)
					{
							cout << ShipArray[c5 - 1][j]->getID() << " ";
					}

					cout << "\nID : ";
					cin >> id5;

					//Find the selected ship in the Ship Array and delete it
					for (j = 0; j < ShipArray.at(6).size(); ++j)
					{
						if (ShipArray[6][j]->getID() == id5)
						{
							del = true;
							ShipArray[6][j]->destroyShip(GridMap, ShipArray, j, sea1);
							system("PAUSE");
							break;
						}
					}

					if (!del)
					{
						cout << "\nThis ID doesn't exist.";
					}

					cout << "\n\n" << endl;
				} while (!del);
			}
			break;
		}
		break;

	//Add - Remove port or treasure
	case 6:
		int ch6, ch61, ch62, xIn6, yIn6;
		bool trAdd, poAdd, exists, trExists, poExists;

		//Choose action to perform
		do
		{
			cout << "\n1. Add treasure point at the map." << endl;
			cout << "2. Add port point at the map." << endl;
			cout << "3. Remove treasure point from the map." << endl;
			cout << "4. Remove port point from the map." << endl;
			cout << "\nChoose action to perform : ";
			cin >> ch6;

			if ((ch6 < 1) || (ch6 > 4))
			{
				cout << "\n\nWrong choice. Please try again...\n" << endl;
			}
		} while ((ch6 < 1) || (ch6 > 4));


		switch (ch6)
		{
		//Add treasure
		case 1:
			//Choose where to add the treasure
			do
			{
				cout << "\n1. Add treasure at random map point." << endl;
				cout << "2. Add treasure at specific map point." << endl;
				cout << "\nPlease choose the preferable option : ";
				cin >> ch61;

				if ((ch61 < 1) || (ch61 > 2))
				{
					cout << "\n\nWrong choice. Please try again...\n" << endl;
				}
			}
			while ((ch61 < 1) || (ch61 > 2));

			do 
			{
				trAdd = false;

				switch (ch61)
				{
				//Add treasure to random map point
				case 1:
					xIn6 = rand() % GridMap.size();
					yIn6 = rand() % GridMap.size();

				//Add treasure to specific map point
				case 2:
					cout << "\nPlease enter the coordinates of a specific map point. (-1 < x,y < n)\n" << endl;
					cout << "Enter x : ";
					cin >> xIn6;
					cout << "Enter y : ";
					cin >> yIn6;
					cout << "\n" << endl;
				}

				//If the coordinates aren't out of bounds, the map point is empty and isn't treasure
				if ((xIn6 >= 0 && xIn6 < GridMap.size()) && (yIn6 >= 0 && yIn6 < GridMap.size()) && (GridMap[xIn6][yIn6]->getIsEmpty()) && !(GridMap[xIn6][yIn6]->getTreasure()))
				{
					trAdd = true;
					GridMap[xIn6][yIn6]->setTreasure(true);
					GridMap[xIn6][yIn6]->setPtype(treas1);
					cout << "You added treasure at the map point [" << xIn6 << "," << yIn6 <<"]\n" << endl;

				}
			} while (!trAdd);

			system("PAUSE");
			break;
		
		//Add port
		case 2:
			//Choose where to add the port
			do
			{
				cout << "\n1. Add port at random map point." << endl;
				cout << "2. Add port at specific map point." << endl;
				cout << "\nPlease choose the preferable option : " << endl;
				cin >> ch62;

				if ((ch62 < 1) || (ch62 > 2))
				{
					cout << "\n\nWrong choice. Please try again...\n" << endl;
				}
			} while ((ch62 < 1) || (ch62 > 2));

			do
			{
				poAdd = false;

				switch (ch62)
				{
				//Add port at random map point
				case 1:
					xIn6 = rand() % GridMap.size();
					yIn6 = rand() % GridMap.size();

				//Add port at specific map point
				case 2:
					cout << "\nPlease enter the coordinates of a specific map point. (-1 < x,y < n)\n" << endl;
					cout << "Enter x : ";
					cin >> xIn6;
					cout << "Enter y : ";
					cin >> yIn6;
					cout << "\n" << endl;
				}

				//If the coordinates aren't out of bounds, the map point is empty and isn't treasure
				if ((xIn6 >= 0 && xIn6 < GridMap.size()) && (yIn6 >= 0 && yIn6 < GridMap.size()) && (GridMap[xIn6][yIn6]->getIsEmpty()) && !(GridMap[xIn6][yIn6]->getTreasure()))
				{
					poAdd = true;
					GridMap[xIn6][yIn6]->setPort(true);
					GridMap[xIn6][yIn6]->setIsEmpty(false);
					GridMap[xIn6][yIn6]->setPtype(port1);
					cout << "You added a port at the map point [" << xIn6 << "," << yIn6 << "]\n" << endl;

				}
			} while (!poAdd);

			system("PAUSE");
			break;

		//Remove treasure
		case 3:
			exists = false;

			//Display all the treasure map points left
			cout << "\nThe existing treasure coordinates are the following :  \n";
			for (i = 0; i < GridMap.size(); ++i)
			{
				for (j = 0; j < GridMap.size(); ++j)
				{
					if (GridMap[i][j]->getTreasure())
					{
						exists = true;
						cout << "[" << i << "," << j << "] ";
					}
				}
			}

			//If there are no treasures left
			if (!exists)
			{
				cout << "\nThere are no treasures at the map!" << endl;
				Sleep(2000);
				break;
			}

			do
			{
				//Choose coordinates to remove treasure
				trExists = false;
				cout << "\n\nPlease enter the prefered coordinates : " << endl;
				cout << "\nX : ";
				cin >> xIn6;
				cout << "\nY : ";
				cin >> yIn6;
				cout << "\n\n" << endl;

				//If the coordinates aren't out of bounds and the map point is treasure
				if ((xIn6 >= 0 && xIn6 < GridMap.size()) && (yIn6 >= 0 && yIn6 < GridMap.size()) && (GridMap[xIn6][yIn6]->getTreasure()))
				{
						trExists = true;
						GridMap[xIn6][yIn6]->setTreasure(false);
						GridMap[xIn6][yIn6]->setPtype(sea1);
						cout << "You deleted a treasure at the map point [" << xIn6 << "," << yIn6 << "]\n" << endl;
				}
			} while (!trExists);

			system("PAUSE");
			break;

		//Remove port
		case 4:
			exists = false;

			//Display all the ports in the map left
			cout << "\nThe existing port coordinates are the following :  \n";
			for (i = 0; i < GridMap.size(); ++i)
			{
				for (j = 0; j < GridMap.size(); ++j)
				{
					if (GridMap[i][j]->getPort())
					{
						exists = true;
						cout << "[" << i << "," << j << "] ";
					}
				}
			}

			//If there are no ports left
			if (!exists)
			{
				cout << "\nThere are no ports at the map!" << endl;
				Sleep(2000);
				break;
			}

			do 
			{
				//Choose coordinates to remove port
				poExists = false;
				cout << "\n\nPlease enter the prefered coordinates : " << endl;
				cout << "\nX : ";
				cin >> xIn6;
				cout << "\nY : ";
				cin >> yIn6;
				cout << "\n\n" << endl;

				//If the coordinates aren't out of bounds and the map point is port
				if ((xIn6 >= 0 && xIn6 < GridMap.size()) && (yIn6 >= 0 && yIn6 < GridMap.size()) && (GridMap[xIn6][yIn6]->getPort()))
				{				
						poExists = true;
						GridMap[xIn6][yIn6]->setPort(false);
						GridMap[xIn6][yIn6]->setIsEmpty(true);
						GridMap[xIn6][yIn6]->setPtype(sea1);
						cout << "You deleted a port at the map point [" << xIn6 << "," << yIn6 << "]\n" << endl;
				}
			} while (!poExists);

			system("PAUSE");
			break;
		}
		break;

	//End Simulation
	case 7:
		cout << "ENDING SIMULATION in ";

		for (i = 3; i >= 1; --i)
		{
			cout << i << ". ";
			Sleep(1000);
		}
		cout << endl;

		exit(0);
		break;
	}
}