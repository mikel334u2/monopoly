/*
 * Player.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: mikel
 */

#include "mono.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//class Player{
//
//private:
//
//    string name;
//    string typeOfPlace;
//    int currentMoney;
//    vector<Property> properties;
//
//public:
//
//    Player(string name, string piece, int money);
//    bool hasMoney(Property property);
//    void addHouse();
//    string getPlayer();
//    void setPlayer(string name);
//    void afkCheck();
//    bool checkMoneyForBuying();
//    void removeProperty();
//    void addProperty();
//
//};

Player::Player(string n, string p){
	name = n;
	piece = p;
	money = 1500;
	location = 0;
	inJail = false;
	jailTime = 0;
	// vector<Property> properties;
}

// bool Player::hasMonopoly(){}

string Player::getName(){
	return name;
}

string Player::getPiece(){
	return piece;
}

int Player::getMoney(){
	return money;
}

int Player::getLocation(){
	return location;
}

bool Player::getJail(){
	return inJail;
}

int Player::getJailTime(){
	return jailTime;
}

void Player::setJailTime(int time){
	jailTime = time;
}

void Player::setLocation(int loc){
	location = loc;
}

bool Player::addLocation(int addSpaces){
	int prevLoc = location;
	location = (location + addSpaces) % 32;
	if (location - prevLoc < 0){
		return true;
	}
	return false;
}
