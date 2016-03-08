#pragma once
#include "Ship.h"

#define maxPower 5

class Pirate :
	public Ship
{
public:
	Pirate(int, int, double, double, int, int);
	~Pirate();

	void setStype(string);
	void setID(int);
	void setPower(int);
	void setTreasAtt(int);
	void setDamageCaused(int);
	
	int getID() const;
	int getPower() const;
	int getTreasAtt() const;
	int getDamageCaused() const;
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
	int power, id, dc, trA;
	static int countP, deadP;
};