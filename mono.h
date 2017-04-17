#ifndef MONO_H_
#define MONO_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Property{

private:

	string name;
	string color;
	int location;
	int price;
	int housePrice;
	int rent[6];
	int nHouses;
	bool inMonopoly;
	int owner;

public:

	Property(string, string, int, int, int, int, int, int, int, int, int);
	string getName();
	string getColor();
	int getLocation();
	int getPrice();
	int getHousePrice();
	int getRent();
	int getHouses();
	void setHouses(int);
	int getOwner();
	void setOwner(int);
	bool getMonopoly();
	void setMonopoly(bool);

};

class Player{

private:

	string name;
	string piece;
	int money;
	int location;
	vector<Property*> properties;
	bool inJail;
	int jailTime;
	int doubleTime;
	bool hasMonopoly;
	vector<string> monoColors;

public:

	Player(string, string);
	string getName();
	string getPiece();
	int getMoney();
	void setMoney(int);
	void subtractMoney(int);
	void addMoney(int);
	void addHouse();
	void addProperty(Property*);
	vector<Property*> getProperties();
	int getLocation();
	bool getJail();
	void changeJail();
	int getJailTime();
	void setJailTime(int);
	int getDoubleTime();
	void setDoubleTime(int);
	bool addLocation(int);
	void setLocation(int);
	void setMonopoly(bool);
	bool getMonopoly();
	vector<string> getColors();
	void addColors(string);
};

int rollDye();
bool jail(Player*, int&, int&);
void landOnProperty(Property*, Player*, int, vector<Player*>);
void monopoly(Player*);
void communityChest(Player*);
void chance(Player*);
bool menu(Player*, vector<Property*>);
void buildHouses(Player*, vector<Property*>);

#endif /* MONO_H_ */
