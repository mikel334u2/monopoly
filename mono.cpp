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

		// user input: number of players
		cin >> nPlayers;

		// if not an integer, clear buffer and reprompt
		if (!cin){
			cin.clear();
			while (cin.get() != '\n');
			nPlayers = 0;
		}

		// if not between 2-4, reprompt
		if (nPlayers > 4 || nPlayers < 2){
			cout << "Invalid input. Please try again: ";
		}
		else break;
	}

	vector<string> names;
	cout << "Please enter the names of the players: (max 10 characters)" << endl;
	for (int i = 0; i < nPlayers; i++){

		// user input: names
		string input;
		do{
			cout << i+1 << ". ";
			cin >> input;

			// if name is more than 10 characters, reprompt
			if (input.size() < 1 || input.size() > 10){
				cout << "Invalid name. Please enter again." << endl;
			}
		} while (input.size() < 1 || input.size() > 10);

		// add name to names vector
		names.push_back(input);
	}

	// adding possible pieces to pieces vector
	const string pcs[] = {"TERRIER","IRON","SHIP","CAR","POT","ROBOT","THIMBLE","PHONE"};
	vector<string> pieces(pcs, pcs + sizeof(pcs) / sizeof(pcs[0]));

	// list possible pieces
	cout << "\nPossible pieces: ";
	for (unsigned int i = 0; i < pieces.size(); i++){
		if (i < 7) cout << pieces[i] << ", ";
		else cout << pieces[i] << endl;
	}

	vector<string> playPieces;
	for(int i = 0; i < nPlayers; i++){
		string input = "";

		// while input is not in pieces vector
		while(find(pieces.begin(), pieces.end(), input) == pieces.end()){
			cout << names[i] << ", please choose your piece: ";

			// ask for the piece the player wants
			cin >> input;
			transform(input.begin(), input.end(), input.begin(), ::toupper);

			// if the piece input cannot be found (doesn't exist), reprompt
			if(find(pieces.begin(), pieces.end(), input) == pieces.end()){
				cout << "Invalid piece, please try again." << endl;
			}
		}

		// add piece to playPieces
		playPieces.push_back(input);

		// remove the piece from pieces vector so that next player can't use the same piece
		pieces.erase(remove(pieces.begin(), pieces.end(), input), pieces.end());
	}

	// shows who's who
	for (int i = 0; i < nPlayers; i++){
		cout << names[i] << " is " << playPieces[i] << "." << endl;
	}

	// creates main vector of player pointers
	vector<Player*> players;
	for (int i = 0; i < nPlayers; i++){
		Player* player = new Player(names[i],playPieces[i]);
		players.push_back(player);
	}

	// information for each property
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

	// creates main vector of property pointers
	vector<Property*> properties;
	for (int i = 0; i < 22; i++){
		Property* property = new Property(propertyNames[i],propertyColor[i],i,propertyPrice[i],propertyHousePrice[i],initialRent[22],
				oneHouseRent[i],twoHouseRent[i],threeHouseRent[i],fourHouseRent[i],fiveHouseRent[i]);
		properties.push_back(property);
	}

	// for loop iterates through players vector
	// for (unsigned int i = 0; i < players.size(); i++){}

	int turn = 0; // turn of current player
	int location; // location of player
	bool doubles = false; // bool if doubles are rolled, then true
	bool passGo; // if passes go, then true
	int dice1 = 0; // dice values
	int dice2 = 0;
	Player* currPlayer; // current player's turn
	Property* property; // pointer to property at landed location

	while (true){

		currPlayer = players[turn];

		string input;
		cout << currPlayer->getName() << "'s turn. Press ENTER";
		cin >> input;
		// would you like to buy/sell property/houses or roll dice?

		// roll dice, determine doubles
		dice1 = rollDye();
		dice2 = rollDye();
		doubles = (dice1 == dice2) ? true : false;

		// if still in jail, go to next player's turn
		if (jail(currPlayer, dice1, dice2)){
			turn = (turn + 1) % nPlayers;
			continue;
		}

		// if just out of jail, make doubles false no matter what
		if (currPlayer->getJail()){
			doubles = false;
			currPlayer->changeJail();
		}

		// if doubles rolled, count number of doubles
		if (doubles) currPlayer->setDoubleTime(currPlayer->getDoubleTime()+1);

		// if number of doubles is 3, send player to jail
		if (currPlayer->getDoubleTime() >= 3){
			currPlayer->changeJail();
			currPlayer->setLocation(8);
			currPlayer->setDoubleTime(0);
			turn = (turn + 1) % nPlayers;
			continue;
		}

		// move player by dice1 plus dice2
		passGo = currPlayer->addLocation(dice1 + dice2);

		// current location
		location = currPlayer->getLocation();

		// if passGo, collect $200
		if (passGo){
			currPlayer->addMoney(200);
			cout<< currPlayer->getName() << " passed GO. Collect $200." << endl;
		}

		// main switch for determining what to do at each space
		switch (location){

		// Go
		case 0:
			cout << "You're on GO" << endl;
			break;

		// Mediterranean Ave
		case 1:
			property = properties[0];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Baltic Ave
		case 2:
			property = properties[1];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Income Tax
		case 3:
			cout << "Income Tax. Pay $200." << endl;
			currPlayer->subtractMoney(200);
			break;

		// Oriental Ave
		case 4:
			property = properties[2];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Comm Chest
		case 5:
			cout << "Community Chest." << endl;
			break;

		// Vermont Ave
		case 6:
			property = properties[3];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Connecticut Ave
		case 7:
			property = properties[4];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Jail
		case 8:
			cout << "JAIL." << endl;
			break;

		// St. Charles Pl
		case 9:
			property = properties[5];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// States Ave
		case 10:
			property = properties[6];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Virginia Ave
		case 11:
			property = properties[7];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Chance
		case 12:
			cout << "Chance." << endl;
			break;

		// St. James Pl
		case 13:
			property = properties[8];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Tennessee Ave
		case 14:
			property = properties[9];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// NY Ave
		case 15:
			property = properties[10];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Free Parking
		case 16:
			cout << "FREE PaRkInG!!!1!" << endl;
			break;

		// Kentucky Ave
		case 17:
			property = properties[11];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Indiana Ave
		case 18:
			property = properties[12];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Illinois Ave
		case 19:
			property = properties[13];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Comm Chest
		case 20:
			cout << "Community Chest." << endl;
			break;

		// Atlantic Ave
		case 21:
			property = properties[14];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Ventor Ave
		case 22:
			property = properties[15];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Marvin Gardens
		case 23:
			property = properties[16];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Go to Jail
		case 24:
			cout << "GO TO JAIL." << endl;
			break;

		// Pacific Ave
		case 25:
			property = properties[17];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// NC Ave
		case 26:
			property = properties[18];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Penn Ave
		case 27:
			property = properties[19];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Luxury Tax
		case 28:
			cout << "Luxury Tax. Pay $200." << endl;
			currPlayer->subtractMoney(200);
			break;

		// Park Place
		case 29:
			property = properties[20];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// Chance
		case 30:
			cout << "Chance." << endl;
			break;

		// Boardwalk
		case 31:
			property = properties[21];
			landOnProperty(property, currPlayer, turn, players);
			break;

		// should never happen
		default:
			cout << "Error: Unreachable?" << endl;
			exit(EXIT_SUCCESS);
			break;
		}


		// determines if the player's properties are part of monopoly
		monopoly(currPlayer->getProperties());

		// temporary code
		// players.erase(players.begin() + players.size() - 1);

		// if 1 player left, end game
		if (players.size() == 1){
			cout << "\nThe winner is " << players[0]->getName() << "!" << endl;
			exit(EXIT_SUCCESS);
		}

		if (doubles){
			cout << "YOU ROLLED DOUBLES. ROLL AGAIN." << endl;
			continue;
		}

		// reset number of doubles of current player
		currPlayer->setDoubleTime(0);

		// next turn
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

	// if first or second turn in jail
	if (player->getJailTime() < 2){

		// user input: choose to pay or roll
		cout << player->getName() << " is in jail. Would you like to pay $50 or roll for doubles? (pay/roll)" << endl;
		string input;
		do{
			cin >> input;
			transform(input.begin(), input.end(), input.begin(), ::toupper);

			// if invalid choice, reprompt
			if (input != "PAY" && input != "ROLL") cout << "Invalid choice. Please choose either pay or roll." << endl;
		} while (input != "PAY" && input != "ROLL");

		// if pay, deduct $50 and exit jail
		if (input == "PAY"){
			player->subtractMoney(50);
			player->setJailTime(0);
			return false;
		}

		// if roll and doubles, exit jail
		if (dice1 == dice2){
			player->setJailTime(0);
			cout << player->getName() << " rolled doubles." << endl;
			return false;
		}

		// if not doubles, player is still in jail, move on to next player
		cout << "Doubles were not rolled. " << player->getName() << " remains in jail." << endl;
		player->setJailTime(player->getJailTime()+1);
		return true;
	}

	// if third turn in jail, player must roll
	cout << player->getName() << " is in jail. Rolling dice automatically." << endl;

	// if doubles rolled, exit jail
	if (dice1 == dice2){
		player->setJailTime(0);
		cout << player->getName() << " rolled doubles." << endl;
		return false;
	}

	// if doubles not rolled, has to pay $50, exits jail
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
    int purpleCounter;
    int lblueCounter;
    int pinkCounter;
    int orangeCounter;
    int redCounter;
    int yellowCounter;
    int greenCounter;
    int dblueCounter;

    for(unsigned int i = 0; i < properties.size(); i++){
        if(properties[i]->getColor() == "PURPLE") {
            purpleCounter++;
        }
        else if(properties[i]->getColor() == "L. BLUE") {
            lblueCounter++;
        }
        else if(properties[i]->getColor() == "PINK") {
            pinkCounter++;
        }
        else if(properties[i]->getColor() == "ORANGE") {
            orangeCounter++;
        }
        else if(properties[i]->getColor() == "RED") {
            redCounter++;
        }
        else if(properties[i]->getColor() == "YELLOW") {
            yellowCounter++;
        }
        else if(properties[i]->getColor() == "GREEN") {
            greenCounter++;
        }
        else if(properties[i]->getColor() == "D. BLUE") {
            dblueCounter++;
        }

        if(purpleCounter == 2 || lblueCounter == 3 || pinkCounter == 3 || orangeCounter == 3 || redCounter == 3 ||
            yellowCounter == 3 || greenCounter == 3 || dblueCounter == 2) {
        properties[i]->changeMonopoly();
        }
    }
	
}

/*
string communityChest[6] = {"Advance to Go (Collect $200)", "Bank error in your favor – Collect $200",
			 "Doctor's fees {fee} – Pay $50", "Income tax refund – Collect $20",
			 "Pay hospital fees of $100",  "You have won second prize in a beauty contest – Collect $10"};
string chance[5] = {"Advance to Go (Collect $200)", "Pay poor tax of $15",
			 "Your building {and} loan matures – Collect $150",  "You have won a crossword competition - Collect $100",
		         "Bank pays you dividend of $50"};
*/

//void communityChest(Player* player) {
//	int randNum = rand() % 6;
//
//	string communityChest[6] = {"Advance to Go (Collect $200)", "Bank error in your favor – Collect $200",
//				 "Doctor's fees {fee} – Pay $50", "Income tax refund – Collect $20",
//				 "Pay hospital fees of $100",  "You have won second prize in a beauty contest – Collect $10"};
//	cout << communityChest[randNum] << endl;
//	if(randNum == 0) {
//		// increase player's money by 200
//		player.addMoney(200);
//	}
//	else if(randNum == 1) {
//		// increase player's money by 200
//		player.addMoney(200);
//	}
//	else if(randNum == 2) {
//		// decrease player's money by 50
//		example.subtractMoney(50);
//	}
//
//	else if(randNum == 3) {
//		// increase player's money by 20
//		example.addMoney(20);
//	}
//
//	else if(randNum == 4) {
//		// decrease player's money by 100
//		example.subtractMoney(100);
//	}
//	else {
//		// increase player's money by 10
//		example.addMoney(10);
//	}
//}
//
//void chance(Player example) {
//	int randNum = rand() % 5;
//	cout << communityChest[randNum] << endl;
//	if(randNum == 0) {
//		// increase player's money by 200
//		example.addMoney(200);
//	}
//	else if(randNum == 1) {
//		// decrease player's money by 15
//		example.subtractMoney(15);
//	}
//	else if(randNum == 2) {
//		// increase player's money by 150
//		example.addMoney(150);
//	}
//
//	else if(randNum == 3) {
//		// increase player's money by 100
//		example.addMoney(100);
//	}
//
//	else {
//		// increase player's money by 50
//		example.addMoney(50);
//	}
//}
