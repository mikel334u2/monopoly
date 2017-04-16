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
	Property* propertyClass; // pointer to property at landed location

	while (true){

		currPlayer = players[turn];

		cout << "\n" << currPlayer->getName() << "'s turn. What would you like to do?" << endl << endl;
		while (menu(currPlayer));

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
			cout << "You landed on GO!" << endl;
			break;

		// Mediterranean Ave
		case 1:
			propertyClass = properties[0];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Baltic Ave
		case 2:
			propertyClass = properties[1];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Income Tax
		case 3:
			cout << "You landed on INCOME TAX. Pay $200." << endl;
			currPlayer->subtractMoney(200);
			break;

		// Oriental Ave
		case 4:
			propertyClass = properties[2];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Comm Chest
		case 5:
			cout << "You landed on COMMUNITY CHEST!" << endl;
			communityChest(currPlayer);
			break;

		// Vermont Ave
		case 6:
			propertyClass = properties[3];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Connecticut Ave
		case 7:
			propertyClass = properties[4];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Jail
		case 8:
			cout << "You landed on JAIL, just visiting..." << endl;
			break;

		// St. Charles Pl
		case 9:
			propertyClass = properties[5];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// States Ave
		case 10:
			propertyClass = properties[6];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Virginia Ave
		case 11:
			propertyClass = properties[7];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Chance
		case 12:
			cout << "You landed on CHANCE!" << endl;
			chance(currPlayer);
			break;

		// St. James Pl
		case 13:
			propertyClass = properties[8];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Tennessee Ave
		case 14:
			propertyClass = properties[9];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// NY Ave
		case 15:
			propertyClass = properties[10];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Free Parking
		case 16:
			cout << "FREE PARKING!!" << endl;
			break;

		// Kentucky Ave
		case 17:
			propertyClass = properties[11];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Indiana Ave
		case 18:
			propertyClass = properties[12];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Illinois Ave
		case 19:
			propertyClass = properties[13];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Comm Chest
		case 20:
			cout << "You landed on COMMUNITY CHEST!" << endl;
			communityChest(currPlayer);
			break;

		// Atlantic Ave
		case 21:
			propertyClass = properties[14];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Ventor Ave
		case 22:
			propertyClass = properties[15];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Marvin Gardens
		case 23:
			propertyClass = properties[16];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Go to Jail
		case 24:
			cout << "GO TO JAIL." << endl;
			currPlayer->changeJail();
			currPlayer->setLocation(8);
			currPlayer->setDoubleTime(0);
			break;

		// Pacific Ave
		case 25:
			propertyClass = properties[17];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// NC Ave
		case 26:
			propertyClass = properties[18];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Penn Ave
		case 27:
			propertyClass = properties[19];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Luxury Tax
		case 28:
			cout << "Luxury Tax. Pay $200." << endl;
			currPlayer->subtractMoney(200);
			break;

		// Park Place
		case 29:
			propertyClass = properties[20];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Chance
		case 30:
			cout << "You landed on CHANCE!" << endl;
			chance(currPlayer);
			break;

		// Boardwalk
		case 31:
			propertyClass = properties[21];
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// should never happen
		default:
			cout << "Error: Unreachable?" << endl;
			exit(EXIT_SUCCESS);
			break;
		}

		// determines if the player's properties are part of monopoly
		monopoly(currPlayer);

		// temporary code
		// players.erase(players.begin() + players.size() - 1);

		// if 1 player left, end game
		if (players.size() == 1){
			cout << "\nThe winner is " << players[0]->getName() << "!" << endl;
			exit(EXIT_SUCCESS);
		}

		if (currPlayer->getJail()){
			turn = (turn + 1) % nPlayers;
			continue;
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



// Method: handles the condition of player being in jail
// returns true if still in jail, false if out of jail
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

// Method: handles landing on property
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
	else cout << "You landed on your own property..." << endl;
}

// Method: scans player's current properties, determines which are part of monopoly
void monopoly(Player* player){

	// scans through current properties and determines if any of them are monopolies
	// so go through vector, find number of times, say, the color red occurs
	// and (for red specifically) if occur = 3, inMonopoly = true for all red ones
	// for loop: property->getColor()
	// property->changeMonopoly()

	vector<Property*> properties = player->getProperties();

	int purple;
	int lblue;
	int pink;
	int orange;
	int red;
	int yellow;
	int green;
	int dblue;

	for(unsigned int i = 0; i < properties.size(); i++){

		if (properties[i]->getColor() == "PURPLE") purple++;
		else if (properties[i]->getColor() == "L. BLUE") lblue++;
		else if (properties[i]->getColor() == "PINK") pink++;
		else if (properties[i]->getColor() == "ORANGE") orange++;
		else if (properties[i]->getColor() == "RED") red++;
		else if (properties[i]->getColor() == "YELLOW") yellow++;
		else if (properties[i]->getColor() == "GREEN") green++;
		else if (properties[i]->getColor() == "D. BLUE") dblue++;
	}

	if (purple == 2 || lblue == 3 || pink == 3 || orange == 3 || red == 3 || yellow == 3 || green == 3 || dblue == 2) player->setMonopoly(true);
	for (unsigned int i = 0; i < properties.size(); i++){
		if ((purple == 2 && properties[i]->getColor() == "PURPLE") ||
				(lblue == 3 && properties[i]->getColor() == "L. BLUE") ||
				(pink == 3 && properties[i]->getColor() == "PINK") ||
				(orange == 3 && properties[i]->getColor() == "ORANGE") ||
				(red == 3 && properties[i]->getColor() == "RED") ||
				(yellow == 3 && properties[i]->getColor() == "YELLOW") ||
				(green == 3 && properties[i]->getColor() == "GREEN") ||
				(dblue == 2 && properties[i]->getColor() == "D. BLUE")){

			properties[i]->setMonopoly(true);
		}
	}
}

void communityChest(Player* player) {

	int randNum = rand() % 6;
	string communityChest[6] = {"Advance to Go (Collect $200)", "Bank error in your favor – Collect $200",
			"Doctor's fees {fee} – Pay $50", "Income tax refund – Collect $20",
			"Pay hospital fees of $100",  "You have won second prize in a beauty contest – Collect $10"};

	cout << communityChest[randNum] << endl;

	// set location to GO and add $200
	if (randNum == 0) {
		player->setLocation(0);
		player->addMoney(200);
	}

	// collect $200
	else if (randNum == 1) player->addMoney(200);

	// decrease player's money by 50
	else if (randNum == 2) player->subtractMoney(50);

	// increase player's money by 20
	else if (randNum == 3) player->addMoney(20);

	// decrease player's money by 100
	else if (randNum == 4) player->subtractMoney(100);

	// increase player's money by 10
	else player->addMoney(10);
}

void chance(Player* player) {

	int randNum = rand() % 5;
	string chance[5] = {"Advance to Go (Collect $200)", "Pay poor tax of $15",
			"Your building {and} loan matures – Collect $150",  "You have won a crossword competition - Collect $100",
			"Bank pays you dividend of $50"};

	cout << chance[randNum] << endl;

	// set location to GO and add $200
	if (randNum == 0) {
		player->setLocation(0);
		player->addMoney(200);
	}

	// decrease player's money by 15
	else if (randNum == 1) player->subtractMoney(200);

	// increase player's money by 150
	else if (randNum == 2) player->addMoney(150);

	// increase player's money by 100
	else if (randNum == 3) player->addMoney(100);

	// increase player's money by 50
	else player->addMoney(50);
}

// Method: Prints menu and looks for user input
bool menu(Player* player){

	vector<Property*> properties = player->getProperties();

	cout << "1. Display player info" << endl; // money, properties, location, jail status
	cout << "2. Roll dice" << endl;
	cout << "3. Buy/sell houses" << endl;
	// cout << "4. Mortgage property" << endl;

	int choice;
	while (true){
		// user input: choice
		cin >> choice;

		// if not an integer, clear buffer and reprompt
		if (!cin){
			cin.clear();
			while (cin.get() != '\n');
			choice = 0;
		}

		// if not between 1-3, reprompt
		if (choice > 3 || choice < 1){
			cout << "Invalid input. Please try again: ";
		}
		else break;
	}

	if (choice == 1){
		cout << "You have $" << player->getMoney() << ". You own ";
		if (!properties.empty()){
			for (unsigned int i=0; i < properties.size(); i++){
				if (i != properties.size() - 1) cout << properties[i]->getName() << ", ";
				else cout << properties[i]->getName() << ". ";
			}
		}
		else cout << "no properties. ";
		cout << "You are located at location " << player->getLocation() << ". ";
		if (player->getJail()){
			cout << "You are in turn #" << player->getJailTime() + 1 << " in jail.";
		}
		cout << endl;
		return true;
	}

	else if (choice == 3){
		if (player->getMonopoly()){
			buildHouses();
		}
		else {
			cout << "You do not have a monopoly. Unable to build houses." << endl;
		}
		return true;
	}
	return false;
}

void buildHouses(){

}
