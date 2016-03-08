#include "Explorer.h"


//------------------------------------------Constructor------------------------------------------//
Explorer::Explorer(int xIn, int yIn, double MaxEnd, double CurEnd, int Speed, int TreasQ)
	: Ship(xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ)
{
	setStype(expl1);
	countE++;
	setID(200 + countE);

	tdtE += getDamageTaken();
	ttE += getTreasFund();
}


//-------------------------------------------Destructor-------------------------------------------//
Explorer::~Explorer()
{
	deadE++;
	countE--;
	cout << "The Explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " has been destroyed." << endl;
}


//--------------------------------------------Setters--------------------------------------------//
int Explorer::countE = 0;
int Explorer::deadE = 0;

void Explorer::setStype(string typ)
{
	st = expl1;
}

void Explorer::setID(int sid)
{
	id = sid;
}


//--------------------------------------------Getters--------------------------------------------//
string Explorer::getStype() const
{
	return st;
}

int Explorer::getID() const
{
	return id;
}

bool Explorer::getGoal() const
{
	if (getTreasFund() >= goalE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Explorer::getCount()
{
	return countE;
}

int Explorer::getDead()
{
	return deadE;
}

int Explorer::getTotalDamageTaken()
{
	return tdtE;
}

int Explorer::getTotalTreasure()
{
	return ttE;
}


//-------------------------------------------Functions-------------------------------------------//
//Explorer Ship Function
void Explorer::ShipFunc(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray)
{
	int x_Old = getX();
	int y_Old = getY();
	bool doneUP = false;
	bool doneDO = false;
	bool doneLE = false;
	bool doneRI = false;

	//CHECK FOR DANGER @ UP
	//If the point (x-1, y) exists and there is bad weather or pirate ship above
	if ((getX() - 1 >= 0) && ((GridMap[getX() - 1][getY()]->getWeather() >= 7) || (GridMap[getX() - 1][getY()]->getPtype()[0] == 'P')))
	{
		//Try to move down
		if ((getX() + 1 < GridMap.size()) && (GridMap[getX() + 1][getY()]->getWeather() < 7) && (GridMap[getX() + 1][getY()]->getIsEmpty()))
		{
			setX(getX() + 1);
			doneUP = true;
		}
		//Try to move right
		else if ((getY() + 1 < GridMap.size()) && (GridMap[getX()][getY() + 1]->getWeather() < 7) && (GridMap[getX()][getY() + 1]->getIsEmpty()))
		{
			setY(getY() + 1);
			doneUP = true;
		}
		//Try to move left
		else if ((getY() - 1 >= 0) && (GridMap[getX()][getY() - 1]->getWeather() < 7) && (GridMap[getX()][getY() - 1]->getIsEmpty()))
		{
			setY(getY() - 1);
			doneUP = true;
		}
		
		//If it moved
		if (doneUP)
		{
			GridMap[x_Old][y_Old]->setPtype(sea1);
			GridMap[x_Old][y_Old]->setIsEmpty(true);
			
			setMoves(1);
			TreasurePoint(GridMap);

			GridMap[getX()][getY()]->setPtype(getStype() + to_string(getID())[1] + to_string(getID())[2]);
			GridMap[getX()][getY()]->setIsEmpty(false);
				

			if ((GridMap[x_Old - 1][y_Old]->getWeather() >= 7) && (GridMap[x_Old - 1][y_Old]->getPtype()[0] == 'P'))
			{
				cout << "The Explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " moved to [" << getX() << "," << getY() << "] due to bad weather and pirate ship existence.\n";
			}
			else if (GridMap[x_Old - 1][y_Old]->getWeather() >= 7)
			{
				cout << "The Explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " moved to [" << getX() << "," << getY() << "] due to bad weather.\n";
			}
			else
			{
				cout << "The Explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " moved to [" << getX() << "," << getY() << "] due to pirate ship existence.\n";
			}
		}
	}

	
	//CHECK FOR DANGER @ RIGHT
	//If the point (x, y+1) exists and there is bad weather or pirate ship at the right
	if ((getY() + 1 < GridMap.size()) && (!doneUP) && ((GridMap[getX()][getY() + 1]->getWeather() >= 7) || (GridMap[getX()][getY() + 1]->getPtype()[0] == 'P')))
	{
		//Try to move down
		if ((getX() + 1 < GridMap.size()) && (GridMap[getX() + 1][getY()]->getWeather() < 7) && (GridMap[getX() + 1][getY()]->getIsEmpty()))
		{
			setX(getX() + 1);
			doneRI = true;
		}
		//Try to move up
		else if ((getX() - 1 >= 0) && (GridMap[getX() - 1][getY()]->getWeather() < 7) && (GridMap[getX() - 1][getY()]->getIsEmpty()))
		{
			setX(getX() - 1);
			doneRI = true;
		}
		//Try to move left
		else if ((getY() - 1 >= 0) && (GridMap[getX()][getY() - 1]->getWeather() < 7) && (GridMap[getX()][getY() - 1]->getIsEmpty()))
		{
			setY(getY() - 1);
			doneRI = true;
		}
		
		//If it moved
		if (doneRI)
		{
			GridMap[x_Old][y_Old]->setPtype(sea1);
			GridMap[x_Old][y_Old]->setIsEmpty(true);

			setMoves(1);
			TreasurePoint(GridMap);

			GridMap[getX()][getY()]->setPtype(getStype() + to_string(getID())[1] + to_string(getID())[2]);
			GridMap[getX()][getY()]->setIsEmpty(false);


			if ((GridMap[x_Old][y_Old + 1]->getWeather() >= 7) && (GridMap[x_Old][y_Old + 1]->getPtype()[0] == 'P'))
			{
				cout << "The Explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " moved to [" << getX() << "," << getY() << "] due to bad weather and pirate ship existence.\n";
			}
			else if (GridMap[x_Old][y_Old + 1]->getWeather() >= 7)
			{
				cout << "The Explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " moved to [" << getX() << "," << getY() << "] due to bad weather.\n";
			}
			else
			{
				cout << "The Explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " moved to [" << getX() << "," << getY() << "] due to pirate ship existence.\n";
			}
		}
	}


	//CHECK FOR DANGER @ DOWN
	//If the point (x+1, y) exists and there is bad weather or pirate ship below
	if ((getX() + 1 < GridMap.size()) && (!doneUP) && (!doneRI) && ((GridMap[getX() + 1][getY()]->getWeather() >= 7) || (GridMap[getX() + 1][getY()]->getPtype()[0] == 'P')))
	{
		//Try to move right
		if ((getY() + 1 < GridMap.size()) && (GridMap[getX()][getY() + 1]->getWeather() < 7) && (GridMap[getX()][getY() + 1]->getIsEmpty()))
		{
			setY(getY() + 1);
			doneDO = true;
		}
		//Try to move up
		else if ((getX() - 1 >= 0) && (GridMap[getX() - 1][getY()]->getWeather() < 7) && (GridMap[getX() - 1][getY()]->getIsEmpty()))
		{
			setX(getX() - 1);
			doneDO = true;
		}
		//Try to move left
		else if ((getY() - 1 >= 0) && (GridMap[getX()][getY() - 1]->getWeather() < 7) && (GridMap[getX()][getY() - 1]->getIsEmpty()))
		{
			setY(getY() - 1);
			doneDO = true;
		}

		//If it moved
		if (doneDO)
		{
			GridMap[x_Old][y_Old]->setPtype(sea1);
			GridMap[x_Old][y_Old]->setIsEmpty(true);

			setMoves(1);
			TreasurePoint(GridMap);
			
			GridMap[getX()][getY()]->setPtype(getStype() + to_string(getID())[1] + to_string(getID())[2]);
			GridMap[getX()][getY()]->setIsEmpty(false);


			if ((GridMap[x_Old + 1][y_Old]->getWeather() >= 7) && (GridMap[x_Old + 1][y_Old]->getPtype()[0] == 'P'))
			{
				cout << "The Explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " moved to [" << getX() << "," << getY() << "] due to bad weather and pirate ship existence.\n";
			}
			else if (GridMap[x_Old + 1][y_Old]->getWeather() >= 7)
			{
				cout << "The Explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " moved to [" << getX() << "," << getY() << "] due to bad weather.\n";
			}
			else
			{
				cout << "The Explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " moved to [" << getX() << "," << getY() << "] due to pirate ship existence.\n";
			}
		}
	}


	//CHECK FOR DANGER @ LEFT
	//If the point (x, y-1) exists and there is bad weather or pirate ship at left
	if ((getY() - 1 >= 0) && (!doneUP) && (!doneRI) && (!doneDO) && ((GridMap[getX()][getY() - 1]->getWeather() >= 7) || (GridMap[getX()][getY() - 1]->getPtype()[0] == 'P')))
	{
		//Try to move right
		if ((getY() + 1 < GridMap.size()) && (GridMap[getX()][getY() + 1]->getWeather() < 7) && (GridMap[getX()][getY() + 1]->getIsEmpty()))
		{
			setY(getY() + 1);
			doneLE = true;
		}
		//Try to move up
		else if ((getX() - 1 >= 0) && (GridMap[getX() - 1][getY()]->getWeather() < 7) && (GridMap[getX() - 1][getY()]->getIsEmpty()))
		{
			setX(getX() - 1);
			doneLE = true;
		}
		//Try to move down
		else if ((getX() + 1 < GridMap.size()) && (GridMap[getX() + 1][getY() - 1]->getWeather() < 7) && (GridMap[getX() + 1][getY() - 1]->getIsEmpty()))
		{
			setX(getX() + 1);
			doneLE = true;
		}

		//If it moved
		if (doneLE)
		{
			GridMap[x_Old][y_Old]->setPtype(sea1);
			GridMap[x_Old][y_Old]->setIsEmpty(true);

			setMoves(1);
			TreasurePoint(GridMap);

			GridMap[getX()][getY()]->setPtype(getStype() + to_string(getID())[1] + to_string(getID())[2]);
			GridMap[getX()][getY()]->setIsEmpty(false);


			if ((GridMap[x_Old][y_Old - 1]->getWeather() >= 7) && (GridMap[x_Old][y_Old - 1]->getPtype()[0] == 'P'))
			{
				cout << "The Explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " moved to [" << getX() << "," << getY() << "] due to bad weather and pirate ship existence.\n";
			}
			else if (GridMap[x_Old][y_Old - 1]->getWeather() >= 7)
			{
				cout << "The Explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " moved to [" << getX() << "," << getY() << "] due to bad weather.\n";
			}
			else
			{
				cout << "The Explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " moved to [" << getX() << "," << getY() << "] due to pirate ship existence.\n";
			}
		}
	}
}


//Print specific Explorer Ship info
void Explorer::printInfo() const
{
	cout << "\n\n--------------------------------------------------------------------------------" << endl;
	cout << "Information about the explorer ship E" << to_string(getID())[1] << to_string(getID())[2] << " at the map point [" << getX() << "," << getY() << "] :" << endl;
	cout << "\tCurrent Endurance : " << getCurEndur() << endl;
	cout << "\tTreasure reserve : " << getTreasFund() << endl;
	cout << "\tSpeed : " << getSpeed() << endl;
	cout << "\tPositions moved since the beginning : " << getMoves() << endl;
	cout << "\tDamage taken since the beginning : " << getDamageTaken() << endl;
	cout << "--------------------------------------------------------------------------------\n\n" << endl;
}


//Create new Exlporer Ship
void Explorer::createShip(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray, int xIn, int yIn, double MaxEnd, double CurEnd, int Speed, int TreasQ)
{
	Explorer* obj = new Explorer(xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ);
	ShipArray.at(1).push_back(obj);
	ShipArray.at(6).push_back(obj);
	string obid = to_string((*obj).getID());
	GridMap[xIn][yIn]->setPtype((*obj).getStype() + obid[1] + obid[2]);
}


//Destroy specific Explorer Ship
void Explorer::destroyShip(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray, int j, const char* trans)
{
	//Replace map point with sea/port/treasure
	GridMap[getX()][getY()]->setPtype(trans);

	//Update flags if needed
	if (trans == treas1)
	{
		GridMap[getX()][getY()]->setTreasure(true);
	}
	else if (trans == port1)
	{
		GridMap[getX()][getY()]->setPort(true);
	}

	//Find the specific ship's position in the relevants Ship Array rows
	vector<Ship*>::iterator iter = find(ShipArray.at(1).begin(), ShipArray.at(1).end(), ShipArray[6][j]);
	int off = distance(ShipArray.at(1).begin(), iter);

	vector<Ship*>::iterator iter3 = find(ShipArray.at(6).begin(), ShipArray.at(6).end(), ShipArray[6][j]);
	int off3 = distance(ShipArray.at(6).begin(), iter3);

	//Delete the ship and remove it from the Ship Array
	delete(this);
	ShipArray.at(1).erase(ShipArray.at(1).begin() + off);
	ShipArray.at(6).erase(ShipArray.at(6).begin() + off3);
}