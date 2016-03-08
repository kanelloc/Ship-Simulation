#pragma once

#include <iostream>
#include <iomanip>
#include <string>

#define port1 "!!!"
#define sea1 "---"
#define treas1 "$$$"

using namespace std;

class GridPoint
{
public:
	GridPoint(int, int, int, bool, bool);
	~GridPoint();

	void setX(int);
	void setY(int);
	void setWeather(int);
	void setTreasure(bool);
	void setPort(bool);
	void setIsEmpty(bool);
	void setPtype(string);

	int getX() const;
	int getY() const;
	int getWeather() const;
	bool getTreasure() const;
	bool getPort() const;
	bool getIsEmpty() const;
	string getPtype() const;

	void printInfo() const;
	void printMap() const;
private:
	string pt;
	int x, y, w;
	bool t, p, e;
};