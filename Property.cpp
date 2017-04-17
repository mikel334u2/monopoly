#include "mono.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// constructor for the 22 properties
Property::Property(string n, string c, int l, int p, int hp, int r0, int r1, int r2, int r3, int r4, int r5){
	name = n;
	color = c;
	location = l;

	// various rents and prices of properties, as they are all mostly unique
	price = p;
	housePrice = hp;
	rent[0] = r0;
	rent[1] = r1;
	rent[2] = r2;
	rent[3] = r3;
	rent[4] = r4;
	rent[5] = r5;

	// starts with 0 houses and no owner
	nHouses = 0;
	inMonopoly = false;
	owner = -1;
}

// returns name of the Property
string Property::getName(){
	return name;
}

// returns color of the Property
string Property::getColor(){
	return color;
}

// returns location of the Property
int Property::getLocation(){
	return location;
}

// returns price of the Property
int Property::getPrice(){
	return price;
}

// returns the price of the houses for the Property
int Property::getHousePrice(){
	return housePrice;
}

// determines and returns the rent for the property
int Property::getRent(){

	// if no owner, rent is 0
	if (owner < 0) return 0;

	// if it's a monopoly with no houses, rent is doubled from original
	else if (inMonopoly && nHouses == 0) return rent[nHouses] * 2;

	// otherwise, the rent will match the rent at the index specified
	return rent[nHouses];
}

// returns the number of houses on that property
int Property::getHouses(){
	return nHouses;
}

// sets the number of houses for the Property
void Property::setHouses(int h){
	nHouses = h;
}

// returns the turn number of the owner of the property
int Property::getOwner(){
	return owner;
}

// sets the owner of the property to a player's specified turn
void Property::setOwner(int own){
	owner = own;
}

// returns if property is currently part of a monopoly
bool Property::getMonopoly(){
	return inMonopoly;
}

// sets whether or not the Property is part of a monopoly
void Property::setMonopoly(bool m){
	inMonopoly = m;
}
