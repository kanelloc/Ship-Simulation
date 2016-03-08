#include "Passenger.h"


//------------------------------------------Constructor------------------------------------------//
Passenger::Passenger(int xIn, int yIn, double MaxEnd, double CurEnd, int Speed, int TreasQ)
	: Commercial(xIn, yIn, MaxEnd, CurEnd, 3, TreasQ)
{
	setStype(pas1);
	countA++;
	setID(300 + countA);

	tdtA += getDamageTaken();
	ttA += getTreasFund();
}


//------------------------------------------Destructor------------------------------------------//
Passenger::~Passenger()
{
	deadA++;
	countA--;
	cout << "The Passenger ship A" << to_string(getID())[1] << to_string(getID())[2] << " has been destroyed." << endl;
}


//--------------------------------------------Setters--------------------------------------------//
int Passenger::countA = 0;
int Passenger::deadA = 0;

void Passenger::setStype(string typ)
{
	st = pas1;
}

void Passenger::setID(int sid)
{
	id = sid;
}


//--------------------------------------------Getters--------------------------------------------//
string Passenger::getStype() const
{
	return st;
}

int Passenger::getID() const
{
	return id;
}

bool Passenger::getGoal() const
{
	if (getTreasFund() >= goalA)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Passenger::getCount()
{
	return countA;
}

int Passenger::getDead()
{
	return deadA;
}

int Passenger::getTotalDamageTaken()
{
	return tdtA;
}

int Passenger::getTotalTreasure()
{
	return ttA;
}


//-------------------------------------------Functions-------------------------------------------//
//Passenger Ship Function
void Passenger::ShipFunc(vector<vector<GridPoint*> >&GridMap, vector<vector<Ship*> >&ShipArray)
{
	//Check if there is a neighboring port and increase treasure reserve
	if (((getX() - 1 >= 0) && (GridMap[getX() - 1][getY()]->getPort())) || ((getX() + 1 < GridMap.size()) && (GridMap[getX() + 1][getY()]->getPort())) || ((getY() - 1 >= 0) && (GridMap[getX()][getY() - 1]->getPort())) || ((getY() + 1 < GridMap.size()) && (GridMap[getX()][getY() + 1]->getPort())))
	{
		setTreasPort(2);
		cout << "The Passenger ship A" << to_string(getID())[1] << to_string(getID())[2] << " increased its treasure by 2 units at the port.\n";
	}
}


//Print specific Passenger Ship info
void Passenger::printInfo() const
{
	cout << "\n\n--------------------------------------------------------------------------------" << endl;
	cout << "Information about the passenger ship A" << to_string(getID())[1] << to_string(getID())[2] << " at the map point [" << getX() << "," << getY() << "] :" << endl;
	cout << "\tCurrent Endurance : " << getCurEndur() << endl;
	cout << "\tTreasure reserve : " << getTreasFund() << endl;
	cout << "\tSpeed : " << getSpeed() << endl;
	cout << "\tPositions moved since the beginning : " << getMoves() << endl;
	cout << "\tTreasure gained from port visits  since the beginning : " << getTreasPort() << endl;
	cout << "\tDamage taken since the beginning : " << getDamageTaken() << endl;
	cout << "--------------------------------------------------------------------------------\n\n" << endl;
}


//Create new Passenger Ship
void Passenger::createShip(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray, int xIn, int yIn, double MaxEnd, double CurEnd, int Speed, int TreasQ)
{
	Passenger* obj = new Passenger(xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ);
	ShipArray.at(2).push_back(obj);
	ShipArray.at(0).push_back(obj);
	ShipArray.at(6).push_back(obj);
	string obid = to_string((*obj).getID());
	GridMap[xIn][yIn]->setPtype((*obj).getStype() + obid[1] + obid[2]);
}


//Destroy specific Passenger Ship
void Passenger::destroyShip(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray, int j, const char* trans)
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
	vector<Ship*>::iterator iter = find(ShipArray.at(2).begin(), ShipArray.at(2).end(), ShipArray[6][j]);
	int off = distance(ShipArray.at(2).begin(), iter);

	vector<Ship*>::iterator iter2 = find(ShipArray.at(0).begin(), ShipArray.at(0).end(), ShipArray[6][j]);
	int off2 = distance(ShipArray.at(0).begin(), iter2);

	vector<Ship*>::iterator iter3 = find(ShipArray.at(6).begin(), ShipArray.at(6).end(), ShipArray[6][j]);
	int off3 = distance(ShipArray.at(6).begin(), iter3);

	//Delete the ship and remove it from the Ship Array
	delete(this);
	ShipArray.at(2).erase(ShipArray.at(2).begin() + off);
	ShipArray.at(0).erase(ShipArray.at(0).begin() + off2);
	ShipArray.at(6).erase(ShipArray.at(6).begin() + off3);
}