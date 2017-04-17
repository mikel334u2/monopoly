#include "mono.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

Player::Player(string n, string p){
	name = n;
	piece = p;
	money = 1500;
	location = 0;
	inJail = false;
	jailTime = 0;
	doubleTime = 0;
	hasMonopoly = false;
	vector<Property*> properties;
	vector<string> monoColors;
}

string Player::getName(){
	return name;
}

string Player::getPiece(){
	return piece;
}

int Player::getMoney(){
	return money;
}

void Player::setMoney(int m){
	money = m;
}

void Player::addMoney(int m){
	money += m;
}

void Player::subtractMoney(int m){
	money -= m;
}

int Player::getLocation(){
	return location;
}

bool Player::getJail(){
	return inJail;
}

void Player::changeJail(){
	inJail = !inJail;
}

int Player::getJailTime(){
	return jailTime;
}

void Player::setJailTime(int time){
	jailTime = time;
}

int Player::getDoubleTime(){
	return doubleTime;
}

void Player::setDoubleTime(int time){
	doubleTime = time;
}

void Player::setLocation(int loc){
	location = loc;
}

void Player::setMonopoly(bool mono){
	hasMonopoly = mono;
}

bool Player::getMonopoly(){
	return hasMonopoly;
}

bool Player::addLocation(int addSpaces){
	int prevLoc = location;
	location = (location + addSpaces) % 32;
	if (location - prevLoc < 0){
		return true;
	}
	return false;
}

void Player::addProperty(Property* property){
	properties.push_back(property);
}

vector<Property*> Player::getProperties(){
	return properties;
}

vector<string> Player::getColors(){
	return monoColors;
}

void Player::addColors(string color){
	monoColors.push_back(color);
}
