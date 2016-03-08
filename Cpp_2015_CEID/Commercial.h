#pragma once
#include "Ship.h"

class Commercial :
	public Ship
{
public:
	Commercial(int, int, double, double, int, int);
	~Commercial();
	
	void setTreasPort(int);
	virtual void setStype(string);
	virtual void setID(int);
	
	int getTreasPort() const;
	static int getCount();
	static int getDead();
	static int getTotalDamageTaken();
	static int getTotalTreasure();
	virtual int getID() const;
	virtual bool getGoal() const;
	virtual string getStype() const;

	virtual void printInfo() const;
	virtual void ShipFunc(vector<vector<GridPoint*> >&, vector<vector<Ship*> >&);
	static void createShip(vector<vector<GridPoint*> >&, vector<vector<Ship*> >&, int, int, double, double, int, int);
	virtual void destroyShip(vector<vector<GridPoint*> >&, vector<vector<Ship*> >&, int, const char*);
private:
	string st;
	int id, trP;
	static int deadC, countC;
};