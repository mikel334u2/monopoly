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

	string typeOfProperty;
	int price;
	int rent;
	int numberOfHouses;
	int housePrices;

public:

	Property();

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
