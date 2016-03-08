#include "GridPoint.h"


//------------------------------------------Constructor------------------------------------------//
GridPoint::GridPoint(int xInd, int yInd, int WeatherIntensity, bool HasTreasure, bool IsPort)
{
	setX(xInd);
	setY(yInd);
	setWeather(WeatherIntensity);
	setTreasure(HasTreasure);
	setPort(IsPort);
	
	if (p)
	{
		pt = port1;
		setIsEmpty(false);
	}
	else if (t)
	{
		pt = treas1;
		setIsEmpty(true);
	}
	else if (!p && !t)
	{
		pt = sea1;
		setIsEmpty(true);
	}

}


//-------------------------------------------Destructor-------------------------------------------//
GridPoint::~GridPoint()
{
}


//--------------------------------------------Setters--------------------------------------------//
void GridPoint::setX(int xInd)
{
	x = xInd;
}

void GridPoint::setY(int yInd)
{
	y = yInd;
}

void GridPoint::setWeather(int WeatherIntensity)
{
	w = WeatherIntensity;
}

void GridPoint::setTreasure(bool HasTreasure)
{
	t = HasTreasure;
}

void GridPoint::setPort(bool IsPort)
{
	if (t)
	{
		p = false;
	}
	else
	{
		p = IsPort;
	}
}


void GridPoint::setPtype(string typ)
{
	pt = typ;
}

void GridPoint::setIsEmpty(bool em)
{
	e = em;
}


//--------------------------------------------Getters--------------------------------------------//
int GridPoint::getX() const
{
	return x;
}

int GridPoint::getY() const
{
	return y;
}

int GridPoint::getWeather() const
{
	return w;
}

bool GridPoint::getTreasure() const
{
	return t;
}

bool GridPoint::getPort() const
{
	return p;
}

string GridPoint::getPtype() const
{
	return pt;
}

bool GridPoint::getIsEmpty() const
{
	return e;
}


//--------------------------------------------Print--------------------------------------------//
//Print specific map point info
void GridPoint::printInfo() const
{
	cout << "\n--------------------------------------------------------------------------------" << endl;
	cout << "Information about the map point [" << x << "," << y << "] :" << endl;
	cout << "\tWeather Intensity : " << w << endl;

	if (p)
	{
		cout << "\tIt is a port." << endl;
	}
	else if (t)
	{
		cout << "\tIt has treasure." << endl;
	}
	else if (!p && !t)
	{
		cout << "\tIt is part of the plain sea." << endl;
	}

	if (!e && !p)
	{
		cout << "\tThere is a ship at this point." << endl;
	}
	else
	{
		cout << "\tThere isn't a ship at this point." << endl;
	}

	cout << "--------------------------------------------------------------------------------\n" << endl;

}

//Print the type (symbol) of a map point
void GridPoint::printMap() const
{
	cout << pt << "   ";
}