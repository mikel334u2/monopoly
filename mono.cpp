/*
 * mono.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: mikel
 */

#include <iostream>
#include <string>
#include <exception>
#include "mono.h"
using namespace std;

int main(){

	int numPlayers = 0;

	cout << "Welcome to Monopoly!" << endl;
	cout << "Please input the number of players (2-4): ";

	while(numPlayers > 4 || numPlayers < 2){
		try{
			cin >> numPlayers;
		}
		catch(exception e){
			cout << "Invalid input. Please try again.";
		}
	}

	string* namePlayers = new string[numPlayers];
	string namePieces[] = {"BOOT","THIMBLE","TERRIER","CANNON"};

	cout << "Please enter the names of the players: " << endl;
	for (int i = 0; i < numPlayers; i++){
		cout << i+1 << ". ";
		cin >> namePlayers[i];
	}

	for (int i = 0; i < numPlayers; i++){
		cout << namePlayers[i] << " is " << namePieces[i] << "." << endl;
	}
}


