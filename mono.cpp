#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <algorithm>
//#include <random> --------------------------
#include "mono.h"
//#include "Player.cpp" --------------------------
//#include "Property.cpp" --------------------------
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

	vector<Property*> properties;
	for (int i = 0; i < 22; i++){
		Property* property = new Property(propertyNames[i],propertyColor[i],i,propertyPrice[i],propertyHousePrice[i],initialRent[22],
				oneHouseRent[i],twoHouseRent[i],threeHouseRent[i],fourHouseRent[i],fiveHouseRent[i]);
		properties.push_back(property);
	}

	// for loop iterates through players vector
	// for (unsigned int i = 0; i < players.size(); i++){}

	int turn = 0;
	int location;
	bool doubles = false;
	bool passGo;
	int dice1 = 0;
	int dice2 = 0;
	Player* currPlayer;
	Property* property;

	while (true){

		currPlayer = players[turn];

		// would you like to buy/sell property/houses or roll dice?

		dice1 = rollDye();
		dice2 = rollDye();
		doubles = (dice1 == dice2) ? true : false;

		if (jail(currPlayer, dice1, dice2)){
			turn = (turn + 1) % nPlayers;
			continue;
		}
		if (currPlayer->getJail()){
			doubles = false;
			currPlayer->changeJail();
		}

		if (doubles) currPlayer->setDoubleTime(currPlayer->getDoubleTime()+1);
		if (currPlayer->getDoubleTime() >= 3){
			currPlayer->changeJail();
			currPlayer->setLocation(7);
			currPlayer->setDoubleTime(0);
			turn = (turn + 1) % nPlayers;
			continue;
		}

//		passGo = currPlayer->addLocation(dice1 + dice2);
//		location = currPlayer->getLocation();
//		if (passGo){
//			currPlayer->addMoney(200);
//			cout<< currPlayer->getName() << " passed GO. Collect $200." << endl;
//		}

		switch (location){

		case 0:
            cout << "Passed GO. Collect $200." << endl;
            currPlayer->addMoney(200);
			break;

		case 1://Mediterranean Avenue
			property = properties[0];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 2://Baltic Avenue
			property = properties[1];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 3://Income Tax
            cout << "Income Tax. Pay $200." << endl;
            currPlayer->subtractMoney(200);
			break;

		case 4://Oriental Avenue
			property = properties[2];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 5://Community Chest
            cout << "Community Chest." << endl;
			break;

		case 6://Vermont Avenue
			property = properties[3];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 7://Connecticut Avenue
			property = properties[4];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 8://JAIL
            cout << "JAIL." << endl;
			break;

		case 9://St. Charles Place
			property = properties[5];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 10://States Avenue
			property = properties[6];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 11://Virginia Avenue
			property = properties[7];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 12://Chance
            cout << "Chance." << endl;
			break;

		case 13://St. James Place
			property = properties[8];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 14://Tennessee Avenue
			property = properties[9];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 15://New York Avenue
			property = properties[10];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 16://Free Parking
            cout << "FREE PaRkInG!!!1!" << endl;
			break;

		case 17://Kentucky Avenue
			property = properties[11];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 18://Indiana Avenue
			property = properties[12];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 19://Illinois Avenue
			property = properties[13];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 20://Community Chest 2
            cout << "Community Chest." << endl;
			break;

		case 21://Atlantic Avenue
			property = properties[14];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 22://Ventor Avenue
			property = properties[15];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 23://Marvin Gardens
			property = properties[16];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 24://GO TO JAIL
            cout << "GO TO JAIL." << endl;
			break;

		case 25://Pacific Avenue
			property = properties[17];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 26://North Carolina Avenue
			property = properties[18];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 27://Pennsylvania Avenue
			property = properties[19];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 28://Luxury Tax
            cout << "Luxury Tax. Pay $200." << endl;
            currPlayer->subtractMoney(200);
			break;

		case 29://Park Place
			property = properties[20];
			landOnProperty(property, currPlayer, turn, players);
			break;

		case 30://Chance 2
            cout << "Chance." << endl;
			break;

		case 31://Boardwalk
			property = properties[21];
			landOnProperty(property, currPlayer, turn, players);
			break;

		default:
			cout << "Error: Unreachable?" << endl;
			exit(EXIT_SUCCESS);
			break;
		}

		monopoly(currPlayer->getProperties());

		// temporary code
		// players.erase(players.begin() + players.size() - 1);

		if (players.size() == 1){
			cout << "\nThe winner is " << players[0]->getName() << "!" << endl;
			exit(EXIT_SUCCESS);
		}

		if (doubles) continue;

		turn = (turn + 1) % nPlayers;
	}
}

// C++98 CODE ---------------------------
int rollDye() {
	return rand() % 6 + 1;
}

// C++11 CODE ---------------------------
//int rollDye() {
//
//	random_device rndm;
//	mt19937 generator(rndm());
//	uniform_int_distribution<> range(1, 6);
//
//	return range(generator);
//}



// returns true if still in jail, false if out of jail
// resets jail time and sets player's jail to false if released
bool jail(Player* player, int dice1, int dice2){

	// if player is not currently in jail, ends method and turn continues normally
	if (!player->getJail()) return false;

	if (player->getJailTime() < 2){

		cout << player->getName() << " is in jail. Would you like to pay $50 or roll for doubles? (pay/roll)" << endl;
		string input;
		do{
			cin >> input;
			transform(input.begin(), input.end(), input.begin(), ::toupper);
			if (input != "PAY" && input != "ROLL") cout << "Invalid choice. Please choose either pay or roll." << endl;
		} while (input != "PAY" && input != "ROLL");

		if (input == "PAY"){
			player->subtractMoney(50);
			player->setJailTime(0);
			return false;
		}
		if (dice1 == dice2){
			player->setJailTime(0);
			cout << player->getName() << " rolled doubles." << endl;
			return false;
		}
		cout << "Doubles were not rolled. " << player->getName() << " remains in jail." << endl;
		player->setJailTime(player->getJailTime()+1);
		return true;
	}

	cout << player->getName() << " is in jail. Rolling dice automatically." << endl;
	if (dice1 == dice2){
		player->setJailTime(0);
		cout << player->getName() << " rolled doubles." << endl;
		return false;
	}
	cout << player->getName() << " spent 3 turns in jail. Prisoner fined $50. Releasing hardened convict." << endl;
	player->setJailTime(0);
	player->subtractMoney(50);
	return false;
}


void landOnProperty(Property* property, Player* player, int turn, vector<Player*> players){

	int rent = property->getRent();
	string choice;

	if (rent == 0){
		cout << property->getName() << " is not owned. The price is $" << property->getPrice() <<
				". Would you like to buy " << property->getName() << "? (Y/N)" << endl;

		while (true){
			cin >> choice;
			if (choice == "Y" || choice == "y"){
				int cost = property->getPrice();
				player->subtractMoney(cost);
				property->setOwner(turn);
				player->addProperty(property);
				break;
			}
			else if (choice == "N" || choice == "n"){
				cout << property->getName() << " was not bought." << endl;
				break;
			}
			else cout << "Invalid choice, choose either 'Y' or 'N'" << endl;
		}
	}
	else if (turn != property->getOwner()){

		int owner = property->getOwner();

		cout << players[owner]->getName() << " owns " << property->getName() <<
				". You pay " << players[owner]->getName() << " $" << rent << "." << endl;

		players[owner]->addMoney(rent);
		player->subtractMoney(rent);
	}
}

void monopoly(vector<Property*> properties){

	// scans through current properties and determines if any of them are monopolies
	// so go through vector, find number of times, say, the color red occurs
	// and (for red specifically) if occur = 3, inMonopoly = true for all red ones

}
