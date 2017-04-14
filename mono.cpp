/*
 * mono.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: mikel
 */

#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <algorithm>
#include <random>
#include "mono.h"
#include "Player.cpp"
#include "Property.cpp"
using namespace std;

int main(){

	int nPlayers = 0;

	cout << "Welcome to Monopoly!" << endl;
	cout << "Please input the number of players (2-4): ";

	while (true){
		cin >> nPlayers;
		if (!cin){
			cin.clear();
			while (cin.get() != '\n');
			nPlayers = 0;
		}
		if (nPlayers > 4 || nPlayers < 2){
			cout << "Invalid input. Please try again: ";
		}
		else break;
	}

	vector<string> names;
	const string pcs[] = {"TERRIER","IRON","SHIP","CAR","POT","ROBOT","THIMBLE","PHONE"};
	vector<string> pieces(pcs, pcs + sizeof(pcs) / sizeof(pcs[0]));

	cout << "Please enter the names of the players: " << endl;
	for (int i = 0; i < nPlayers; i++){
		cout << i+1 << ". ";
		string input;
		cin >> input;
		names.push_back(input);
	}

	cout << "\nPossible pieces: ";
	for (unsigned int i = 0; i < pieces.size(); i++){
		if (i < 7) cout << pieces[i] << ", ";
		else cout << pieces[i] << endl;
	}

	vector<string> playPieces;
	for(int i = 0; i < nPlayers; i++){
		string input = "";
		while(find(pieces.begin(), pieces.end(), input) == pieces.end()){
			cout << names[i] << ", please choose your piece: ";
			cin >> input;
			transform(input.begin(), input.end(), input.begin(), ::toupper);
			if(find(pieces.begin(), pieces.end(), input) == pieces.end()){
				cout << "Invalid piece, please try again." << endl;
			}
		}
		playPieces.push_back(input);
		pieces.erase(remove(pieces.begin(), pieces.end(), input), pieces.end());
	}

	for (int i = 0; i < nPlayers; i++){
		cout << names[i] << " is " << playPieces[i] << "." << endl;
	}

	vector<Player*> players;
	for (int i = 0; i < nPlayers; i++){
		Player* player = new Player(names[i],playPieces[i]);
		players.push_back(player);
	}

	string propertyNames[22] = {"MEDITERRANEAN AVENUE","BALTIC AVENUE","ORIENTAL AVENUE","VERMONT AVENUE",
			"CONNECTICUT AVENUE","ST. CHARLES PLACE","STATES AVENUE","VIRGINIA AVENUE","ST. JAMES PLACE",
			"TENNESSEE AVENUE","NEW YORK AVENUE","KENTUCKY AVENUE","INDIANA AVENUE","ILLINOIS AVENUE",
			"ATLANTIC AVENUE","VENTOR AVENUE","MARVIN GARDENS","PACIFIC AVENUE","NORTH CAROLINA AVENUE",
			"PENNSYLVANIA AVENUE","PARK PLACE","BOARDWALK"};
	string propertyColor[22] = {"PURPLE","PURPLE","L. BLUE","L. BLUE","L. BLUE","PINK","PINK","PINK","ORANGE",
			"ORANGE","ORANGE","RED","RED","RED","YELLOW","YELLOW","YELLOW","GREEN","GREEN","GREEN","D. BLUE","D. BLUE"};		
	int propertyPrice[22] = {60,60,100,100,120,140,140,160,180,180,200,220,220,240,260,260,280,300,300,320,350,400};
	int propertyHousePrice[22] = {50,50,50,50,50,100,100,100,100,100,100,150,150,150,150,150,150,200,200,200,200,200};
	int initialRent[22] = {2,4,6,6,8,10,10,12,14,14,16,18,18,20,22,22,24,26,26,28,35,50};
	int oneHouseRent[22] = {10,20,30,30,40,50,50,60,70,70,80,90,90,100,110,110,120,130,130,150,175,200};
	int twoHouseRent[22] = {30,60,90,90,100,150,150,180,200,200,220,250,250,300,330,330,360,390,390,450,500,600};
	int threeHouseRent[22] = {90,180,270,270,300,450,450,500,550,550,600,700,700,750,800,800,850,900,900,1000,1100,1400};
	int fourHouseRent[22] = {160,320,400,400,450,625,625,700,750,750,800,875,875,925,975,975,1025,1100,1100,1200,1300,1700};
	int fiveHouseRent[22] = {250,450,550,550,600,750,750,900,950,950,1000,1050,1050,1100,1150,1150,1200,
			1275,1275,1400,1500,2000};		

	int propertyLocation[22] = {1,2,4,6,7,9,10,11,13,14,15,17,18,19,21,22,23,25,26,27,29,31};		

	vector<Property*> properties;
	for (int i = 0; i < 22; i++){
		Property* property = new Property(propertyNames[i],propertyColor[i],propertyLocation[i],propertyPrice[i],propertyHousePrice[i],initialRent[i],
			oneHouseRent[i],twoHouseRent[i],threeHouseRent[i],fourHouseRent[i],fiveHouseRent[i], 0);
		properties.push_back(property);
	}

	// for loop iterates through players vector
	// for (unsigned int i = 0; i < players.size(); i++){}

	int turn = 0;
	int location;
	bool doubles = false;
	bool passGo;
	bool inJail;
	int dice1 = 0;
	int dice2 = 0;
	Player* currPlayer;

	while (true){

		currPlayer = players[turn];

		dice1 = rollDye();
		dice2 = rollDye();
		bool doubles = false;
		if (dice1 == dice2){
			doubles = true;
		}
		
		inJail = jail(currPlayer, dice1, dice2);

		if(inJail)
		{
			turn = (turn + 1) % nPlayers;
			continue;
		}

		passGo = currPlayer->addLocation(dice1 + dice2);
		location = currPlayer->getLocation();

		if(passGo)
		{
			currPlayer->addMoney(200);
			cout<< currPlayer->getName() << " passed GO. Collect $200." << endl;
		}

		switch (location){

		case 0:
			break;

		case 1:
			break;

		case 2:
			break;
			
		case 3:
			break;
		
		case 4:
			break;
		
		case 5:
			break;
		
		case 6:
			break;
		
		case 7:
			break;
		
		case 8:
			break;
		
		case 9:
			break;
		
		case 10:
			break;
		
		case 11:
			break;
		
		case 12:
			break;
		
		case 13:
			break;
		
		case 14:
			break;
		
		case 15:
			break;
		
		case 16:
			break;
		
		case 17:
			break;
		
		case 18:
			break;
		
		case 19:
			break;
		
		case 20:
			break;
		
		case 21:
			break;
		
		case 22:
			break;
		
		case 23:
			break;
		
		case 24:
			break;
		
		case 25:
			break;
		
		case 26:
			break;
		
		case 27:
			break;
		
		case 28:
			break;
		
		case 29:
			break;
		
		case 30:
			break;
		
		case 31:
			break;
		}

		// temporary code
		//players.erase(players.begin() + players.size() - 1);

		if (players.size() == 1){
			cout << "\nThe winner is " << players[0]->getName() << "!" << endl;
			exit(EXIT_SUCCESS);
		}

		turn = (turn + 1) % nPlayers;
	}
}

int rollDye() {
	
	random_device rndm;
	mt19937 generator(rndm());
	uniform_int_distribution<> range(1, 6);

	return range(generator);
}

//returns true if still in jail, false if out of jail
//resets jail time and sets player's jail to false if released
bool jail(Player* player, int dice1, int dice2)
{
	//if player is not currently in jail, ends method and turn continues normally
	if(!(player->getJail()))
	{
		return false;
	}

	cout << player->getName() << " is in jail. Would you like to pay $50 or roll for doubles? (pay/roll)" << endl;
	
	string choice;
	int selector = 0;

	cin >> choice;

	transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

	if(choice == "PAY")
		selector = 1;

	else if(choice == "ROLL")
		selector = 2;

	while(selector != 5)
	{
		switch(selector)
		{
			case(1):
			{
				player->subtractMoney(50);
				player->setJail(false);
				player->setJailTime(0);
				return false;
			}

			//if choose to roll, releases player from jail if they roll doubles
			case(2):
			{
				if(dice1 == dice2)
				{
					player->setJail(false);
					player->setJailTime(0);
					cout << player->getName() << " rolled doubles." << endl;
					return false;
				}

				cout << "Doubles were not rolled. " << player->getName() << " remains in jail." << endl;
				selector = 5;
				break;
			}

			default:
			{
				cout << "Invalid input. Please select pay or roll." << endl;
				cin >> choice;

				transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

				if(choice == "PAY")
					selector = 1;

				else if(choice == "ROLL")
					selector = 2;
			}
		}
	}

	player->setJailTime(player->getJailTime() + 1);
	int time = player->getJailTime();

	//if player is in jail 3 turns, releases them and forces them to pay $50 fine
	if(time == 3)
	{
		cout << player->getName() << " spent 3 turns in jail. Prisoner fined $50. Releasing hardened convict." << endl;
		player->setJail(false);
		player->setJailTime(0);
		player->subtractMoney(50);
		return false;
	}
	
	return true;
}

void landOnProperty(Property* property, Player* player, int turn, vector<Player*> players)
{
	int rent = property->getRent();
	string choice;

	if(rent == 0)
	{
		cout << property->getName() << " is not owned. The price is $" << property->getPrice() << ". Would you like to buy " << property->getName() << "? (Y/N)" << endl;
		cin >> choice;

		if(choice == "Y" || choice == "y")
		{
			int cost = property->getPrice();
			player->subtractMoney(cost);
			property->setOwner(turn);
			player->addProperty(property);
			return;
		}

		else
		{
			cout << property->getName() << " was not bought." << endl;
			return;
		}
	}

	else
	{
		int owner = property->getOwner();

		cout << players[owner]->getName() << " owns " << property->getName() << ". You pay " << players[owner]->getName() << " $" << rent << "." << endl;

		players[owner]->addMoney(rent);
		player->subtractMoney(rent);
	}
	return;
}