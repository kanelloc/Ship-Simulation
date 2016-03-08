#include "Commercial.h"


//------------------------------------------Constructor------------------------------------------//
Commercial::Commercial(int xIn, int yIn, double MaxEnd, double CurEnd, int Speed, int TreasQ) 
	: Ship (xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ)
{
	trP = 0;
}


//-------------------------------------------Destructor-------------------------------------------//
Commercial::~Commercial()
{
}


//--------------------------------------------Setters--------------------------------------------//
int Commercial::countC = 0;
int Commercial::deadC = 0;

void Commercial::setTreasPort(int treasp)
{
	trP += treasp;
	setTreasFund(treasp);
}

void Commercial::setStype(string typ)
{
	st = com1;
}

void Commercial::setID(int sid)
{
	id = sid;
}


//--------------------------------------------Getters--------------------------------------------//
int Commercial::getTreasPort() const
{
	return trP;
}

string Commercial::getStype() const
{
	return st;
}

int Commercial::getID() const
{
	return id;
}

bool Commercial::getGoal() const
{
	if (getTreasFund() >= goalC)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Commercial::getCount()
{
	return countC;
}

int Commercial::getDead()
{
	return deadC;
}

int Commercial::getTotalDamageTaken()
{
	return tdtC;
}

int Commercial::getTotalTreasure()
{
	return ttC;
}



//-------------------------------------------Functions-------------------------------------------//
//Commercial Ship Function
void Commercial::ShipFunc(vector<vector<GridPoint*> >&GridMap, vector<vector<Ship*> >&ShipArray)
{
	//Check if there is a neighboring port and increase treasure reserve
	if (((getX() - 1 >= 0) && (GridMap[getX() - 1][getY()]->getPort())) || ((getX() + 1 < GridMap.size()) && (GridMap[getX() + 1][getY()]->getPort())) || ((getY() - 1 >= 0) && (GridMap[getX()][getY() - 1]->getPort())) || ((getY() + 1 < GridMap.size()) && (GridMap[getX()][getY() + 1]->getPort())))
	{
		setTreasPort(1);
		cout << "The Commercial ship C" << to_string(getID())[1] << to_string(getID())[2] << " increased its treasure by 1 unit at the port.\n";
	}
}


//Print specific Commercial Ship info
void Commercial::printInfo() const
{
	cout << "\n\n--------------------------------------------------------------------------------" << endl;
	cout << "Information about the commercial ship C" << to_string(getID())[1] << to_string(getID())[2] << " at the map point [" << getX() << "," << getY() << "] :" << endl;
	cout << "\tCurrent Endurance : " << getCurEndur() << endl;
	cout << "\tTreasure Reserve : " << getTreasFund() << endl;
	cout << "\tSpeed : " << getSpeed() << endl;
	cout << "\tPositions moved since the beginning : " << getMoves() << endl;
	cout << "\tTreasure gained from port visits  since the beginning : " << getTreasPort() << endl;
	cout << "\tDamage taken since the beginning : " << getDamageTaken() << endl;
	cout << "--------------------------------------------------------------------------------\n\n" << endl;
}


//Create new Commercial Ship
void Commercial::createShip(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray, int xIn, int yIn, double MaxEnd, double CurEnd, int Speed, int TreasQ)
{
	countC++;
	tdtC += (MaxEnd - CurEnd);
	ttC += TreasQ;

	Commercial* obj = new Commercial(xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ);

	(*obj).setStype(com1);
	(*obj).setID(100 + countC);

	ShipArray.at(0).push_back(obj);
	ShipArray.at(6).push_back(obj);
	string obid = to_string((*obj).getID());
	GridMap[xIn][yIn]->setPtype((*obj).getStype() + obid[1] + obid[2]);
}


//Destroy specific Commercial Ship
void Commercial::destroyShip(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray, int j, const char* trans)
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
	vector<Ship*>::iterator iter = find(ShipArray.at(0).begin(), ShipArray.at(0).end(), ShipArray[6][j]);
	int off = distance(ShipArray.at(0).begin(), iter);

	vector<Ship*>::iterator iter3 = find(ShipArray.at(6).begin(), ShipArray.at(6).end(), ShipArray[6][j]);
	int off3 = distance(ShipArray.at(6).begin(), iter3);

	//Destructor
	deadC++;
	countC--;
	cout << "The Commercial ship C" << to_string(getID())[1] << to_string(getID())[2] << " has been destroyed." << endl;

	//Delete the ship and remove it from the Ship Array
	delete(this);
	ShipArray.at(0).erase(ShipArray.at(0).begin() + off);
	ShipArray.at(6).erase(ShipArray.at(6).begin() + off3);
}