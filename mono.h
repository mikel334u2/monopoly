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

	string propertyColor;
	int location;
	int buyPrice;

	int initialRent;
	int oneHouseRent;
	int twoHouseRent;
	int threeHouseRent;
	int fourHouseRent;
	int hotelRent;
	
	int numberOfHouses;
	int housePrices;

	bool isOwned;

public:

	Property();

	int rentCost();

};

class Player{

private:

	string name;
	string piece;
	int money;
	vector<Property> properties;

public:

	Player(string, string, int);
	bool hasMonopoly(Property);
	void addHouse();

};




#endif /* MONO_H_ */