#include "Pirate.h"


//------------------------------------------Constructor------------------------------------------//
Pirate::Pirate(int xIn, int yIn, double MaxEnd, double CurEnd, int Speed, int TreasQ)
	: Ship(xIn, yIn, MaxEnd, CurEnd, 1, TreasQ)
{
	power = (rand() % maxPower) + 1;
	setStype(pir1);
	trA = 0;
	dc = 0;
	countP++;
	setID(400 + countP);

	tdtP += getDamageTaken();
	ttP += getTreasFund();
}


//-------------------------------------------Destructor-------------------------------------------//
Pirate::~Pirate()
{
	deadP++;
	countP--;
	cout << "The Pirate ship P" << to_string(getID())[1] << to_string(getID())[2] << " has been destroyed." << endl;
}


//--------------------------------------------Setters--------------------------------------------//
int Pirate::countP = 0;
int Pirate::deadP = 0;

void Pirate::setPower(int pow)
{
	power = pow;
}

void Pirate::setTreasAtt(int treaa)
{
	trA += treaa;
	setTreasFund(treaa);
}

void Pirate::setDamageCaused(int damc)
{
	dc += damc;
}

void Pirate::setStype(string typ)
{
	st = pir1;
}

void Pirate::setID(int sid)
{
	id = sid;
}


//--------------------------------------------Getters--------------------------------------------//
int Pirate::getPower() const
{
	return power;
}

int Pirate::getTreasAtt() const
{
	return trA;
}

int Pirate::getDamageCaused() const
{
	return dc;
}

string Pirate::getStype() const
{
	return st;
}

int Pirate::getID() const
{
	return id;
}

bool Pirate::getGoal() const
{
	if (getTreasFund() >= goalP)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Pirate::getCount()
{
	return countP;
}

int Pirate::getDead()
{
	return deadP;
}

int Pirate::getTotalDamageTaken()
{
	return tdtP;
}

int Pirate::getTotalTreasure()
{
	return ttP;
}


//-------------------------------------------Functions-------------------------------------------//
//Pirate Ship Function
void Pirate::ShipFunc(vector<vector<GridPoint*> >&GridMap, vector<vector<Ship*> >&ShipArray)
{
	size_t j;
	int x_Serv = getX();
	int y_Serv = getY();
	double treasg;

	//Check all existing ships
	for (j = 0; j < ShipArray.at(6).size(); ++j)
	{
		//Check if they are neighboring (left, right, up, doen) ships and attack them all
		if ((ShipArray[6][j]->getCurEndur() < ShipArray[6][j]->getMaxEndur()) && (((ShipArray[6][j]->getX() == (x_Serv - 1)) && (ShipArray[6][j]->getY() == (y_Serv))) || ((ShipArray[6][j]->getX() == (x_Serv)) && (ShipArray[6][j]->getY() == (y_Serv + 1))) || ((ShipArray[6][j]->getX() == (x_Serv + 1)) && (ShipArray[6][j]->getY() == (y_Serv))) || ((ShipArray[6][j]->getX() == (x_Serv)) && (ShipArray[6][j]->getY() == (y_Serv - 1)))))
		{
			treasg = ((.01 * (rand() % 10 + 10)) * ShipArray[6][j]->getTreasFund());
			setTreasAtt(treasg);
			setDamageCaused(power);

			ShipArray[6][j]->setTreasFund(-treasg);
			ShipArray[6][j]->setCurEndur(ShipArray[6][j]->getCurEndur() - power);
			ShipArray[6][j]->setDamageTaken(power);

			string shid = to_string(ShipArray[6][j]->getID());
			cout << "The Pirate ship P" << to_string(getID())[1] << to_string(getID())[2] << " earned " << treasg << " units of treasure from attacking the ship " << ShipArray[6][j]->getStype() << shid[1] << shid[2] << "." << endl;
		}
	}
}


//Print specific Pirate Ship info
void Pirate::printInfo() const
{
	cout << "\n\n--------------------------------------------------------------------------------" << endl;
	cout << "Information about the pirate ship P" << to_string(getID())[1] << to_string(getID())[2] << " at the map point [" << getX() << "," << getY() << "] :" << endl;
	cout << "\tCurrent Endurance : " << getCurEndur() << endl;
	cout << "\tTreasure Reserve : " << getTreasFund() << endl;
	cout << "\tSpeed : " << getSpeed() << endl;
	cout << "\tPower : " << power << endl;
	cout << "\tPositions moved since the beginning : " << getMoves() << endl;
	cout << "\tTreasure gained from attacks  since the beginning : " << getTreasAtt() << endl;
	cout << "\tDamage taken since the beginning : " << getDamageTaken() << endl;
	cout << "\tDamage caused since the beginning : " << getDamageCaused() << endl;
	cout << "--------------------------------------------------------------------------------\n\n" << endl;
}


//Create new Pirate Ship
void Pirate::createShip(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray, int xIn, int yIn, double MaxEnd, double CurEnd, int Speed, int TreasQ)
{
	Pirate* obj = new Pirate(xIn, yIn, MaxEnd, CurEnd, Speed, TreasQ);
	ShipArray.at(3).push_back(obj);
	ShipArray.at(6).push_back(obj);
	string obid = to_string((*obj).getID());
	GridMap[xIn][yIn]->setPtype((*obj).getStype() + obid[1] + obid[2]);
}


//Destroy specific Pirate Ship
void Pirate::destroyShip(vector<vector<GridPoint*> > &GridMap, vector<vector<Ship*> > &ShipArray, int j, const char* trans)
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
	vector<Ship*>::iterator iter = find(ShipArray.at(3).begin(), ShipArray.at(3).end(), ShipArray[6][j]);
	int off = distance(ShipArray.at(3).begin(), iter);

	vector<Ship*>::iterator iter3 = find(ShipArray.at(6).begin(), ShipArray.at(6).end(), ShipArray[6][j]);
	int off3 = distance(ShipArray.at(6).begin(), iter3);
	
	//Delete the ship and remove it from the Ship Array
	delete(this);
	ShipArray.at(3).erase(ShipArray.at(3).begin() + off);
	ShipArray.at(6).erase(ShipArray.at(6).begin() + off3);
}