/*
 * Property.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: mikel
 */

#include "mono.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Property::Property(string n, string c, int l, int p, int hp, int r0, int r1, int r2, int r3, int r4, int r5, int ownNum){
	name = n;
	color = c;
	location = l;
	price = p;
	housePrice = hp;
	rent[0] = r0;
	rent[1] = r1;
	rent[2] = r2;
	rent[3] = r3;
	rent[4] = r4;
	rent[5] = r5;
	nHouses = 0;
	isOwned = false;
	inMonopoly = false;
	owner = ownNum;
}

string Property::getName(){
	return name;
}

string Property::getColor(){
	return color;
}

int Property::getLocation(){
	return location;
}

int Property::getPrice(){
	return price;
}

int Property::getHousePrice(){
	return housePrice;
}

int Property::getRent(){
	if (!isOwned) return 0;
	else if(!inMonopoly) return rent[0];
	else if (inMonopoly && nHouses == 0) return rent[0] * 2;
	return rent[nHouses];
}

int Property::getHouses(){
	return nHouses;
}

void Property::setHouses(int h){  // if int h is b/w 0 and 5 inclusive
	nHouses = h;
}

int Property::getOwner(){
	return owner;
}

void Property::setOwner(int ownNum){
	owner = ownNum;
}

void Property::changeOwned(){
	isOwned = (isOwned) ? false : true;
}

void Property::changeMonopoly(){
	inMonopoly = (inMonopoly) ? false : true;
}