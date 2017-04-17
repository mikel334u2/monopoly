#include "mono.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

// constructor for the players
Player::Player(string n, string p){

	name = n;
	piece = p;

	// players start with $1500 and start at GO
	money = 1500;
	location = 0;

	// starting conditions for in-game functions
	inJail = false;
	jailTime = 0;
	doubleTime = 0;
	hasMonopoly = false;
	vector<Property*> properties;
	vector<string> monoColors;
}

// returns the name of the player
string Player::getName(){
	return name;
}

// returns the piece of the player
string Player::getPiece(){
	return piece;
}

// returns the amount of money of the player
int Player::getMoney(){
	return money;
}

// sets the amount of money to a specified value
void Player::setMoney(int m){
	money = m;
}

// add the specified amount of money to money stash
void Player::addMoney(int m){
	money += m;
}

// subtract the specified amount of money from money stash
void Player::subtractMoney(int m){
	money -= m;
}

// returns the current location of the player on the board
int Player::getLocation(){
	return location;
}

// returns the jail status of the player
bool Player::getJail(){
	return inJail;
}

// changes the jail status of the player
void Player::changeJail(){
	inJail = !inJail;
}

// returns the number of turns the player has spent in jail
int Player::getJailTime(){
	return jailTime;
}

// sets the number of turns in jail to the specified jail time
void Player::setJailTime(int time){
	jailTime = time;
}

// returns the number of doubles rolled in a turn
int Player::getDoubleTime(){
	return doubleTime;
}

// sets the number of turns that doubles were rolled to a specified amount
void Player::setDoubleTime(int time){
	doubleTime = time;
}

// sets the location of the player to a specified location
void Player::setLocation(int loc){
	location = loc;
}

// sets whether or not the Player has monopoly
void Player::setMonopoly(bool mono){
	hasMonopoly = mono;
}

// returns whether or not the Player has monopoly
bool Player::getMonopoly(){
	return hasMonopoly;
}

// add the specified amount of spaces to the current location
// returns true if passed Go
bool Player::addLocation(int addSpaces){

	// previous location before the mod 32
	int prevLoc = location;
	location = (location + addSpaces) % 32;

	// if the difference between the new location and the old location is less than 0 (i.e. old is 31 and new is 1), then return true
	if (location - prevLoc < 0){
		return true;
	}
	return false;
}

// add the specified property to the player's own property vector
void Player::addProperty(Property* property){
	properties.push_back(property);
}

// returns the property vector
vector<Property*> Player::getProperties(){
	return properties;
}

// returns the vector of monopolized colors
vector<string> Player::getColors(){
	return monoColors;
}

// adds a color to the monopolized colors vector
void Player::addColors(string color){
	monoColors.push_back(color);
}
