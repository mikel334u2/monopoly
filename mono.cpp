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
#include "mono.h"
using namespace std;

string communityChest[6] = { "Advance to Go (Collect $200)", "Bank error in your favor – Collect $200",
"Doctor's fees {fee} – Pay $50", "Income tax refund – Collect $20",
"Pay hospital fees of $100",  "You have won second prize in a beauty contest – Collect $10" };

string chance[5] = { "Advance to Go (Collect $200)", "Pay poor tax of $15",
"Your building {and} loan matures – Collect $150",  "You have won a crossword competition - Collect $100",
"Bank pays you dividend of $50" };

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

	vector<Player> players;
	for (int i = 0; i < nPlayers; i++){
		Player player(names[i],playPieces[i]);
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

	vector<Property> properties;
	for (int i = 0; i < 22; i++){
		Property property(propertyNames[i],propertyColor[i],i,propertyPrice[i],propertyHousePrice[i],initialRent[22],
				oneHouseRent[i],twoHouseRent[i],threeHouseRent[i],fourHouseRent[i],fiveHouseRent[i]);
		properties.push_back(property);
	}

	// for loop iterates through players vector
	// for (unsigned int i = 0; i < players.size(); i++){}

	int turn = 0;

	while (true){

		// temporary code
		players.erase(players.begin() + players.size() - 1);

		if (players.size() == 1){
			cout << "\nThe winner is " << players[0].getName() << "!" << endl;
			exit(EXIT_SUCCESS);
		}

		turn = (turn + 1) % nPlayers;
	}
}

int rollDye() {
	return rand() % 6 + 1;
}

/*
string communityChest[6] = {"Advance to Go (Collect $200)", "Bank error in your favor – Collect $200", 
			 "Doctor's fees {fee} – Pay $50", "Income tax refund – Collect $20",
			 "Pay hospital fees of $100",  "You have won second prize in a beauty contest – Collect $10"};

string chance[5] = {"Advance to Go (Collect $200)", "Pay poor tax of $15", 
			 "Your building {and} loan matures – Collect $150",  "You have won a crossword competition - Collect $100",
		         "Bank pays you dividend of $50"};
*/

void communityChest(Player example) {
	int randNum = rand() % 6;
	cout << communityChest[randNum] << endl;
	if(randNum == 0) {
		// increase player's money by 200
		example.addMoney(200);
	}
	else if(randNum == 1) {
		// increase player's money by 200
		example.addMoney(200);
	}
	else if(randNum == 2) {
		// decrease player's money by 50
		example.subtractMoney(50);
	}
	
	else if(randNum == 3) {
		// increase player's money by 20
		example.addMoney(20);
	}
	
	else if(randNum == 4) {
		// decrease player's money by 100
		example.subtractMoney(100);
	}
	else {
		// increase player's money by 10
		example.addMoney(10);
	}
}

void chance(Player example) {
	int randNum = rand() % 5;
	cout << communityChest[randNum] << endl;
	if(randNum == 0) {
		// increase player's money by 200
		example.addMoney(200);
	}
	else if(randNum == 1) {
		// decrease player's money by 15
		example.subtractMoney(15);
	}
	else if(randNum == 2) {
		// increase player's money by 150
		example.addMoney(150);
	}
	
	else if(randNum == 3) {
		// increase player's money by 100
		example.addMoney(100);
	}
	
	else {
		// increase player's money by 50
		example.addMoney(50);
	}
}
	
	


