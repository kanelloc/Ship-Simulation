#include "Tanker.h"


//------------------------------------------Constructor------------------------------------------//
Tanker::Tanker(int xIn, int yIn, double MaxEnd, double CurEnd, int Speed, int TreasQ)
	: Commercial(xIn, yIn, MaxEnd, CurEnd, 2, TreasQ)
{
	setStype(tank1);
	countT++;
	setID(600 + countT);

	tdtT += getDamageTaken();
	ttT += getTreasFund();
}


//-------------------------------------------Destructor-------------------------------------------//
Tanker::~Tanker()
{
	deadT++;
	countT--;
	cout << "The Tanker ship T" << to_string(getID())[1] << to_string(getID())[2] << " has been destroyed." << endl;
}


//--------------------------------------------Setters--------------------------------------------//
int Tanker::countT = 0;
int Tanker::deadT = 0;

void Tanker::setStype(string typ)
{
	st = tank1;
}

void Tanker::setID(int sid)
{
	id = sid;
}


//--------------------------------------------Getters--------------------------------------------//
string Tanker::getStype() const
{
	return st;
}

int Tanker::getID() const
{
	return id;
}

bool Tanker::getGoal() const
{
	if (getTreasFund() >= goalT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Tanker::getCount()
{
	return countT;
}

int Tanker::getDead()
{
	return deadT;
}

int Tanker::getTotalDamageTaken()
{
	return tdtT;
}

int Tanker::getTotalTreasure()
{
	return ttT;
}


//-------------------------------------------Functions-------------------------------------------//
//Tanker Ship Function
void Tanker::ShipFunc(vector<vector<GridPoint*> >&GridMap, vector<vector<Ship*> >&ShipArray)
{
	//Check if there is a neighboring port and increase treasure reserve
	if (((getX() - 1 >= 0) && (GridMap[getX() - 1][getY()]->getPort())) || ((getX() + 1 < GridMap.size()) && (GridMap[getX() + 1][getY()]->getPort())) || ((getY() - 1 >= 0) && (GridMap[getX()][getY() - 1]->getPort())) || ((getY() + 1 < GridMap.size()) && (GridMap[getX()][getY() + 1]->getPort())))
	{
		setTreasPort(3);
		cout << "The Tanker ship T" << to_string(getID())[1] << to_string(getID())[2] << " increased its treasure by 3 units at the port.\n";
	}
}


//Print specific Tanker Ship info
void Tanker::printInfo() const
{
	cout << "\n\n--------------------------------------------------------------------------------" << endl;
	cout << "Information about the tanker ship T" << to_string(getID())[1] << to_string(getID())[2] << " at the map point [" << getX() << "," << getY() << "] :" << endl;
	cout << "\tCurrent Endurance : " << getCurEndur() << endl;
	cout << "\tTreasure reserve : " << getTreasFund() << endl;
	cout << "\tSpeed : " << getSpeed() << endl;
	cout << "\tPositions moved since the beginning : " << getMoves() << endl;
	cout << "\tTreasure gained from port visits  since the beginning : " << getTreasPort() << endl;
	cout << "\tDamage taken since the beginning : " << getDamageTaken() << endl;
	cout << "--------------------------------------------------------------------------------\n\n" << endl;
}


//Create new Tanker Ship
void Tanker::createShip(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray, int xIn, int yIn, double MaxEnd, double CurEnd, int Speed, int TreasQ)
{
	Tanker* obj = new Tanker(xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ);
	ShipArray.at(5).push_back(obj);
	ShipArray.at(0).push_back(obj);
	ShipArray.at(6).push_back(obj);
	string obid = to_string((*obj).getID());
	GridMap[xIn][yIn]->setPtype((*obj).getStype() + obid[1] + obid[2]);
}


//Destroy specific Tanker Ship
void Tanker::destroyShip(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray, int j, const char* trans)
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
	vector<Ship*>::iterator iter = find(ShipArray.at(5).begin(), ShipArray.at(5).end(), ShipArray[6][j]);
	int off = distance(ShipArray.at(5).begin(), iter);

	vector<Ship*>::iterator iter2 = find(ShipArray.at(0).begin(), ShipArray.at(0).end(), ShipArray[6][j]);
	int off2 = distance(ShipArray.at(0).begin(), iter2);

	vector<Ship*>::iterator iter3 = find(ShipArray.at(6).begin(), ShipArray.at(6).end(), ShipArray[6][j]);
	int off3 = distance(ShipArray.at(6).begin(), iter3);

	//Delete the ship and remove it from the Ship Array
	delete(this);
	ShipArray.at(5).erase(ShipArray.at(5).begin() + off);
	ShipArray.at(0).erase(ShipArray.at(0).begin() + off2);
	ShipArray.at(6).erase(ShipArray.at(6).begin() + off3);
}