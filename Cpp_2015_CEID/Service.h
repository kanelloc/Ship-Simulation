#pragma once
#include "Ship.h"

class Service :
	public Ship
{
public:
	Service(int, int, double, double, int, int);
	~Service();

	void setStype(string);
	void setID(int);
	void setTreasGain(int);
	
	int getID() const;
	int getTreasGain() const;
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
	int id, trG;
	static int countS, deadS;
};