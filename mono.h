/*
 * mono.h
 *
 *  Created on: Mar 25, 2017
 *      Author: mikel
 */

#ifndef MONO_H_
#define MONO_H_

#include <iostream>
#include <string>
#include <vector>

class Property{

private:

	string name;
	string color;
	int location;
	int price;
	int housePrice;
	int rent[6];
	int nHouses;
	bool isOwned, inMonopoly;
	int owner;

public:

	Property(string, string, int, int, int, int, int, int, int, int, int, int);
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
	void changeOwned();
	void changeMonopoly();

};

class Player{

private:

	string name;
	string piece;
	int money;
	int location;
	vector<Property> properties;
	// bool isActive;
	bool inJail;
	int jailTime;

public:

	Player(string, string);
	string getName();
	string getPiece();
	int getMoney();
	void setMoney(int);
	void subtractMoney(int);
	void addMoney(int);
	bool hasMonopoly();
	void addHouse();
	void addProperty(Property);
	int getLocation();
	bool getJail();
	void setJail(bool);
	int getJailTime();
	void setJailTime(int);
	bool addLocation(int);
	void setLocation(int);
};

int rollDye();
bool jail(Player*, int, int);
void landOnProperty(Property*, Player*);


#endif /* MONO_H_ */