#include "Ship.h"


//------------------------------------------Constructor------------------------------------------//
Ship::Ship(int xInd, int yInd, double MaxEndurance, double CurEndurance, int Speed, int TreasureQ)
{
	setX(xInd);
	setY(yInd);
	setMaxEndur(MaxEndurance);
	setCurEndur(CurEndurance);
	setSpeed(Speed);
	trQ = TreasureQ;
	movesCount = 0;
	dt = (MaxEndurance - CurEndurance);
	countALL++;
	setIDp(countALL);
}


//-------------------------------------------Destructor-------------------------------------------//
Ship::~Ship()
{
	countALL--;
	deadALL++;
}


//--------------------------------------------Setters--------------------------------------------//
int Ship::countALL = 0;
int Ship::deadALL = 0;

//Total damage taken by each ship type
int Ship::tdtC = 0;
int Ship::tdtE = 0;
int Ship::tdtA = 0;
int Ship::tdtP = 0;
int Ship::tdtS = 0;
int Ship::tdtT = 0;

//Total treasure collected by each ship type
int Ship::ttC = 0;
int Ship::ttE = 0;
int Ship::ttA = 0;
int Ship::ttP = 0;
int Ship::ttS = 0;
int Ship::ttT = 0;

void Ship::setX(int xInd)
{
	x = xInd;
}

void Ship::setY(int yInd)
{
	y = yInd;
}

void Ship::setMaxEndur(double MaxEndurance) 
{
	me = MaxEndurance;
}

void Ship::setCurEndur(double CurEndurance)
{
	ce = CurEndurance;
}

void Ship::setSpeed(int Speed)
{
	sp = Speed;
}

void Ship::setTreasFund(int TreasureQ)
{
	trQ += TreasureQ;

	if (getStype() == com1)
	{
		ttC += TreasureQ;
	}
	else if (getStype() == expl1)
	{
		ttE += TreasureQ;
	}
	else if (getStype() == pas1)
	{
		ttA += TreasureQ;
	}
	else if (getStype() == pir1)
	{
		ttP += TreasureQ;
	}
	else if (getStype() == serv1)
	{
		ttS += TreasureQ;
	}
	else
	{
		ttT += TreasureQ;
	}
}

void Ship::setDamageTaken(int damt)
{
	dt += damt;

	if (getStype() == com1)
	{
		tdtC += damt;
	}
	else if (getStype() == expl1)
	{
		tdtE += damt;
	}
	else if (getStype() == pas1)
	{
		tdtA += damt;
	}
	else if (getStype() == pir1)
	{
		tdtP += damt;
	}
	else if (getStype() == serv1)
	{
		tdtS += damt;
	}
	else
	{
		tdtT += damt;
	}
}

void Ship::setMoves(int mov)
{
	movesCount += mov;
}

void Ship::setIDp(int sid)
{
	pid = sid;
}


//--------------------------------------------Getters--------------------------------------------//
int Ship::getX() const
{
	return x;
}

int Ship::getY() const
{
	return y;
}

double Ship::getMaxEndur() const
{
	return me;
}

double Ship::getCurEndur() const
{
	return ce;
}

int Ship::getSpeed() const
{
	return sp;
}

int Ship::getTreasFund() const
{
	return trQ;
}

int Ship::getMoves() const
{
	return movesCount;
}

int Ship::getDamageTaken() const
{
	return dt;
}

int Ship::getIDp() const
{
	return pid;
}

int Ship::getCountALL()
{
	return countALL;
}

int Ship::getDeadALL()
{
	return deadALL;
}

int Ship::getTotalTreasureALL()
{
	return (ttC + ttE + ttA + ttP + ttS + ttT);
}

int Ship::getTotalDamageALL()
{
	return (tdtC + tdtE + tdtA + tdtP + tdtS + tdtT);
}


//-------------------------------------------Functions-------------------------------------------//
//Check for damage due to high weather intensity
void Ship::WeatherDamage(vector<vector<GridPoint*> > GridMap)
{
	if (GridMap[x][y]->getWeather() == 7)
	{
		ce--;
		setDamageTaken(1);
	}
	else if (GridMap[x][y]->getWeather() == 8)
	{
		ce -= 2;
		setDamageTaken(2);
	}
	else if (GridMap[x][y]->getWeather() == 9)
	{
		ce -= 3;
		setDamageTaken(3);
	}
	else if (GridMap[x][y]->getWeather() == 10)
	{
		ce -= 4;
		setDamageTaken(4);
	}
}


//Check if there is treasure at the ship's current position and collect
void Ship::TreasurePoint(vector<vector<GridPoint*> > &GridMap)
{
	if (GridMap[x][y]->getTreasure())
	{
		setTreasFund(1);
		GridMap[x][y]->setTreasure(false);
	}
}


//Check if there is port at the ship's neighboring position and repair/damage ship
void Ship::PortPoint(vector<vector<GridPoint*> > GridMap)
{
	bool atPort = false;

	//If there is port at the ship's neighboring position...
	if (((x - 1 >= 0) && (GridMap[x - 1][y]->getPort())) || ((x + 1 < GridMap.size()) && (GridMap[x + 1][y]->getPort())) || ((y - 1 >= 0) && (GridMap[x][y - 1]->getPort())) || ((y + 1 < GridMap.size()) && (GridMap[x][y + 1]->getPort())))
	{
		atPort = true;
	}

	//... and ship is pirate
	if ((atPort) && (getStype() == pir1))
	{
		ce--;
		setDamageTaken(1);
	}
	//... and ship is not pirate and is damaged
	else if ((atPort) && (getStype() != pir1) && (ce < me))
	{
		ce++;
	}
}


//Move Ship
void Ship::Move(vector<vector<GridPoint*> > &GridMap)
{
	srand(time(NULL));
	m = rand() % 4;
	i = 0;
	x_Old = x;
	y_Old = y;
	done = false;

	do
	{
		switch (m)
		{
		//Move UP
		case 0:
			if (x - sp >= 0)
			{
				if (GridMap[x - sp][y]->getIsEmpty())
				{
					x -= sp;
					done = true;
				}
			}
			if (!done)
			{
				m = 1;
			}
			break;
		//Move RIGHT
		case 1:
			if (y + sp < GridMap.size())
			{
				if (GridMap[x][y + sp]->getIsEmpty())
				{
					y += sp;
					done = true;
				}
			}
			if (!done)
			{
				m = 2;
			}
			break;
		//Move DOWN
		case 2:
			if (x + sp < GridMap.size())
			{
				if (GridMap[x + sp][y]->getIsEmpty())
				{
					x += sp;
					done = true;
				}
			}
			if (!done)
			{
				m = 3;
			}
			break;
		//Move LEFT
		case 3:
			if (y - sp >= 0)
			{
				if (GridMap[x][y - sp]->getIsEmpty())
				{
					y -= sp;
					done = true;
				}
			}
			if (!done)
			{
				m = 0;
			}
			break;
		}
		++i;
	} while (!done && i <= 3);

	//If the ship moved to a new position
	if (done)
	{
		GridMap[x_Old][y_Old]->setPtype(sea1);
		GridMap[x_Old][y_Old]->setIsEmpty(true);

		movesCount += sp;
		WeatherDamage(GridMap);
		TreasurePoint(GridMap);

		GridMap[x][y]->setPtype(getStype() + to_string(getID())[1] + to_string(getID())[2]);
		GridMap[x][y]->setIsEmpty(false);
	}
}


//--------------------------------------Operator Overloading--------------------------------------//
void Ship::operator++(int)
{
	//Increase ship's treasure
	trQ = trQ + 1;
}


void Ship::operator--(int)
{
	//Decrease ship's treasure
	trQ = trQ - 1;
}


bool Ship::operator<(const Ship &sh)
{
	//Compare the speed of 2 ships
	if (this->sp < sh.sp)
	{
		return true;
	}
	else
	{
		return false;
	}
}