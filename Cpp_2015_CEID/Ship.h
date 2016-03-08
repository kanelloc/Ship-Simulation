#pragma once
#pragma warning(push)
#pragma warning(disable: 4018)
#pragma warning(disable: 4244)

#include <iostream>
#include <iomanip>
#include <time.h>
#include <vector>
#include <string>
#include <list>

#include "GridPoint.h"

#define pir1 "P"
#define com1 "C"
#define serv1 "S"
#define expl1 "E"
#define tank1 "T"
#define pas1 "A"

#define goalP 35
#define goalC 30
#define goalS 38
#define goalE 25
#define goalT 40
#define goalA 33

using namespace std;

class Ship
{
public:
	Ship(int, int, double, double, int, int);
	~Ship();

	void setX(int);
	void setY(int);
	void setMaxEndur(double);
	void setCurEndur(double);
	void setSpeed(int);
	void setTreasFund(int);
	void setMoves(int);
	void setDamageTaken(int);
	void setIDp(int);
	virtual void setStype(string) = 0;
	virtual void setID(int) = 0;

	int getX() const;
	int getY() const;
	double getMaxEndur() const;
	double getCurEndur() const;
	int getSpeed() const;
	int getTreasFund() const;
	int getMoves() const;
	int getDamageTaken() const;
	int getIDp() const;
	static int getCountALL();
	static int getDeadALL();
	static int getTotalTreasureALL();
	static int getTotalDamageALL();
	virtual int getID() const = 0;
	virtual bool getGoal() const = 0;
	virtual string getStype() const = 0;

	void WeatherDamage(vector<vector<GridPoint*> >);
	void TreasurePoint(vector<vector<GridPoint*> >&);
	void PortPoint(vector<vector<GridPoint*> >);
	void Move(vector<vector<GridPoint*> >&);
	virtual void ShipFunc(vector<vector<GridPoint*> >&, vector<vector<Ship*> >&) = 0;
	virtual void destroyShip(vector<vector<GridPoint*> >&, vector<vector<Ship*> >&, int, const char*) = 0;
	virtual void printInfo() const = 0;

	void operator++(int);
	void operator--(int);
	bool operator<(const Ship &);

	friend ostream &operator<<(ostream &output, const Ship& sh)
	{
		sh.printInfo();
		return output;
	}
protected:
	static int deadALL, countALL, tdtC, tdtE, tdtA, tdtP, tdtS, tdtT, ttC, ttE, ttA, ttP, ttS, ttT;
private:
	int x, x_Old, y, y_Old, sp, trQ, m, i, movesCount, pid, dt;
	bool done;
	double me, ce;
};