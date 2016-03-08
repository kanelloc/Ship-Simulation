#include "Service.h"


//------------------------------------------Constructor------------------------------------------//
Service::Service(int xIn, int yIn, double MaxEnd, double CurEnd, int Speed, int TreasQ)
	: Ship(xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ)
{
	setStype(serv1);
	trG = 0;
	countS++;
	setID(500 + countS);

	tdtS += getDamageTaken();
	ttS += getTreasFund();
}


//-------------------------------------------Destructor-------------------------------------------//
Service::~Service()
{
	deadS++;
	countS--;
	cout << "The Service ship S" << to_string(getID())[1] << to_string(getID())[2] << " has been destroyed." << endl;
}


//--------------------------------------------Setters--------------------------------------------//
int Service::countS = 0;
int Service::deadS = 0;

void Service::setTreasGain(int treag)
{
	trG += treag;
	setTreasFund(treag);
}

void Service::setStype(string typ)
{
	st = serv1;
}

void Service::setID(int sid)
{
	id = sid;
}


//--------------------------------------------Getters--------------------------------------------//
int Service::getTreasGain() const
{
	return trG;
}

string Service::getStype() const
{
	return st;
}

int Service::getID() const
{
	return id;
}

bool Service::getGoal() const
{
	if (getTreasFund() >= goalS)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Service::getCount()
{
	return countS;
}

int Service::getDead()
{
	return deadS;
}

int Service::getTotalDamageTaken()
{
	return tdtS;
}

int Service::getTotalTreasure()
{
	return ttS;
}


//-------------------------------------------Functions-------------------------------------------//
//Service Ship Function
void Service::ShipFunc(vector<vector<GridPoint*> >&GridMap, vector<vector<Ship*> >&ShipArray)
{
	size_t j;
	int x_Serv = getX();
	int y_Serv = getY();
	double treasg;

	//Check all existing ships
	for (j = 0; j < ShipArray.at(6).size(); ++j)
	{
		//Check if they are neighboring (left, right, up, doen) ships, that are not pirate and need repair
		if ((ShipArray[6][j]->getStype() != pir1) && (ShipArray[6][j]->getCurEndur() < ShipArray[6][j]->getMaxEndur()) && (((ShipArray[6][j]->getX() == (x_Serv - 1)) && (ShipArray[6][j]->getY() == (y_Serv))) || ((ShipArray[6][j]->getX() == (x_Serv)) && (ShipArray[6][j]->getY() == (y_Serv + 1))) || ((ShipArray[6][j]->getX() == (x_Serv + 1)) && (ShipArray[6][j]->getY() == (y_Serv))) || ((ShipArray[6][j]->getX() == (x_Serv)) && (ShipArray[6][j]->getY() == (y_Serv - 1)))))
		{
					treasg = ((.01 * (rand() % 20 + 10)) * ShipArray[6][j]->getTreasFund());
					setTreasGain(treasg);

					ShipArray[6][j]->setTreasFund(-treasg);
					ShipArray[6][j]->setCurEndur(ShipArray[6][j]->getCurEndur() + 1);
					string shid = to_string(ShipArray[6][j]->getID());
					cout << "The Service ship S" << to_string(getID())[1] << to_string(getID())[2] << " earned " << treasg << " units of treasure from the ship " << ShipArray[6][j]->getStype() << shid[1] << shid[2] << " for repairing it." << endl;
		}
	}
}


//Print specific Service Ship info
void Service::printInfo() const
{
	cout << "\n\n--------------------------------------------------------------------------------" << endl;
	cout << "Information about the service ship S" << to_string(getID())[1] << to_string(getID())[2] << " at the map point [" << getX() << "," << getY() << "] :" << endl;
	cout << "\tCurrent Endurance : " << getCurEndur() << endl;
	cout << "\tTreasure Reserve : " << getTreasFund() << endl;
	cout << "\tSpeed : " << getSpeed() << endl;
	cout << "\tPositions moved since the beginning : " << getMoves() << endl;
	cout << "\tTreasure gained from repairs since the beginning : " << getTreasGain() << endl;
	cout << "\tDamage taken since the beginning : " << getDamageTaken() << endl;
	cout << "--------------------------------------------------------------------------------\n\n" << endl;
}


//Create new Service Ship
void Service::createShip(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray, int xIn, int yIn, double MaxEnd, double CurEnd, int Speed, int TreasQ)
{
	Service* obj = new Service(xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ);
	ShipArray.at(4).push_back(obj);
	ShipArray.at(6).push_back(obj);
	string obid = to_string((*obj).getID());
	GridMap[xIn][yIn]->setPtype((*obj).getStype() + obid[1] + obid[2]);
}


//Destroy specific Service Ship
void Service::destroyShip(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray, int j, const char* trans)
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
	vector<Ship*>::iterator iter = find(ShipArray.at(4).begin(), ShipArray.at(4).end(), ShipArray[6][j]);
	int off = distance(ShipArray.at(4).begin(), iter);

	vector<Ship*>::iterator iter3 = find(ShipArray.at(6).begin(), ShipArray.at(6).end(), ShipArray[6][j]);
	int off3 = distance(ShipArray.at(6).begin(), iter3);

	//Delete the ship and remove it from the Ship Array
	delete(this);
	ShipArray.at(4).erase(ShipArray.at(4).begin() + off);
	ShipArray.at(6).erase(ShipArray.at(6).begin() + off3);
}