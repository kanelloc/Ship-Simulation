#pragma once
#include "Commercial.h"

class Passenger :
	public Commercial
{
public:
	Passenger(int, int, double, double, int, int);
	~Passenger();

	void setStype(string);
	void setID(int);

	int getID() const;
	bool getGoal() const;
	static int getCount();
	static int getDead();
	static int getTotalDamageTaken();
	static int getTotalTreasure();
	string getStype() const;

	void printInfo() const;
	void ShipFunc(vector<vector<GridPoint*> >&, vector<vector<Ship*> >&);
	static void createShip(vector<vector<GridPoint*> >&, vector<vector<Ship*> >&, int, int, double, double, int, int);
	void destroyShip(vector<vector<GridPoint*> >&, vector<vector<Ship*> >&, int, const char*);
private:
	string st;
	int id;
	static int countA, deadA;
};