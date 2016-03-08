#pragma once
#include "Commercial.h"

class Tanker :
	public Commercial
{
public:
	Tanker(int, int, double, double, int, int);
	~Tanker();

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
	static int countT, deadT;
};