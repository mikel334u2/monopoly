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
	bool isOwned, inMonopoly;

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
	void changeOwned();
	void changeMonopoly();

};

class Player{

private:

	string name;
	string piece;
	int money;
	int currLoc;
	vector<Property> properties;
	bool isActive;

public:

	Player(string, string);
	string getName();
	string getPiece();
	int getMoney();
	bool hasMonopoly();
	void addHouse();
	void addProperty(Property);
	void setCurrLoc(int);
};




#endif /* MONO_H_ */