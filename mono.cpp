#include <iostream>
#include <string>
#include <exception>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
//#include <random> --------------------------

#include "mono.h"
//#include "Player.cpp" --------------------------
//#include "Property.cpp" --------------------------
//#include "boardView.cpp" -------------------------

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
	const string pcs[] = {"DOG","ROBOT","SHIP","CAR","IRON","POT","THIMBLE","PHONE"};
	vector<string> pieces(pcs, pcs + sizeof(pcs) / sizeof(pcs[0]));

	// list possible pieces
//	cout << "\nPossible pieces: ";
//	for (unsigned int i = 0; i < pieces.size(); i++){
//		if (i < 7) cout << pieces[i] << ", ";
//		else cout << pieces[i] << endl;
//	}

//	vector<string> playPieces;
//	for(int i = 0; i < nPlayers; i++){
//		string input = "";
//
//		// while input is not in pieces vector
//		while(find(pieces.begin(), pieces.end(), input) == pieces.end()){
//			cout << names[i] << ", please choose your piece: ";
//
//			// ask for the piece the player wants
//			cin >> input;
//			transform(input.begin(), input.end(), input.begin(), ::toupper);
//
//			// if the piece input cannot be found (doesn't exist), reprompt
//			if(find(pieces.begin(), pieces.end(), input) == pieces.end()){
//				cout << "Invalid piece, please try again." << endl;
//			}
//		}
//
//		// add piece to playPieces
//		playPieces.push_back(input);
//
//		// remove the piece from pieces vector so that next player can't use the same piece
//		pieces.erase(remove(pieces.begin(), pieces.end(), input), pieces.end());
//	}

	// shows who's who
	for (int i = 0; i < nPlayers; i++){
		cout << names[i] << " is " << pieces[i] << "." << endl;
	}

	// creates main vector of player pointers
	vector<Player*> players;
	for (int i = 0; i < nPlayers; i++){
		Player* player = new Player(names[i],pieces[i]);
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
		Property* property = new Property(propertyNames[i],propertyColor[i],i,propertyPrice[i],propertyHousePrice[i],initialRent[i],
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

		// displays menu, keeps running method while not "Proceed with turn"
		while (menu(currPlayer, properties));

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
		else {
			cout << "Press ENTER to roll dice." << endl;
			dice1 = rollDye();

			// halts game until ENTER pressed
			cin.ignore();
			cin.ignore();
			dice2 = rollDye();

			// determines doubles
			doubles = (dice1 == dice2) ? true : false;
			cout << "You rolled a " << dice1 << " and a " << dice2 << "." << endl;
		}

		// if doubles rolled, count number of doubles
		if (doubles) currPlayer->setDoubleTime(currPlayer->getDoubleTime()+1);

		// if number of doubles is 3, send player to jail
		if (currPlayer->getDoubleTime() >= 3){
			cout << currPlayer->getName() << " was sent to jail." << endl;
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
		// for property spaces, displays location & color and runs landOnProperty()
		switch (location){

		// Go
		case 0:
			cout << "You landed on GO!" << endl;
			break;

		// Mediterranean Ave
		case 1:
			propertyClass = properties[0];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Baltic Ave
		case 2:
			propertyClass = properties[1];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
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
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Comm Chest
		case 5:
			cout << "You landed on COMMUNITY CHEST #1!" << endl;
			communityChest(currPlayer);
			break;

		// Vermont Ave
		case 6:
			propertyClass = properties[3];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Connecticut Ave
		case 7:
			propertyClass = properties[4];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Jail
		case 8:
			cout << "You landed on JAIL, just visiting..." << endl;
			break;

		// St. Charles Pl
		case 9:
			propertyClass = properties[5];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// States Ave
		case 10:
			propertyClass = properties[6];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Virginia Ave
		case 11:
			propertyClass = properties[7];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Chance
		case 12:
			cout << "You landed on CHANCE #1!" << endl;
			chance(currPlayer);
			break;

		// St. James Pl
		case 13:
			propertyClass = properties[8];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Tennessee Ave
		case 14:
			propertyClass = properties[9];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// NY Ave
		case 15:
			propertyClass = properties[10];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Free Parking
		case 16:
			cout << "You landed on FREE PARKING!!" << endl;
			break;

		// Kentucky Ave
		case 17:
			propertyClass = properties[11];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Indiana Ave
		case 18:
			propertyClass = properties[12];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Illinois Ave
		case 19:
			propertyClass = properties[13];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Comm Chest
		case 20:
			cout << "You landed on COMMUNITY CHEST #2!" << endl;
			communityChest(currPlayer);
			break;

		// Atlantic Ave
		case 21:
			propertyClass = properties[14];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Ventor Ave
		case 22:
			propertyClass = properties[15];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Marvin Gardens
		case 23:
			propertyClass = properties[16];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Go to Jail
		case 24:
			cout << "Darn! You landed on GO TO JAIL." << endl;
			currPlayer->changeJail();
			currPlayer->setLocation(8);
			currPlayer->setDoubleTime(0);
			break;

		// Pacific Ave
		case 25:
			propertyClass = properties[17];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// NC Ave
		case 26:
			propertyClass = properties[18];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Penn Ave
		case 27:
			propertyClass = properties[19];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Luxury Tax
		case 28:
			cout << "You landed on LUXURY TAX. Pay $200." << endl;
			currPlayer->subtractMoney(200);
			break;

		// Park Place
		case 29:
			propertyClass = properties[20];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
			landOnProperty(propertyClass, currPlayer, turn, players);
			break;

		// Chance
		case 30:
			cout << "You landed on CHANCE #2!" << endl;
			chance(currPlayer);
			break;

		// Boardwalk
		case 31:
			propertyClass = properties[21];
			cout << "You landed on " << propertyClass->getName() << "!" << endl;
			cout << "Location: " << location << " | Color: " << propertyClass->getColor() << endl;
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

		// if player is bankrupt, delete player from players vector
		if (currPlayer->getMoney() < 0){
			cout << "You are bankrupt. You lose :(" << endl;

			// resets conditions of properties
			vector<Property*> props = currPlayer->getProperties();
			for (unsigned int i = 0; i < props.size(); i++){
				props[i]->setOwner(-1);
				props[i]->setMonopoly(false);
				props[i]->setHouses(0);
			}
			players.erase(players.begin() + turn);
			nPlayers--;
		}

		// if 1 player left, end game
		if (players.size() == 1){
			cout << "\nThe winner is " << players[0]->getName() << "!" << endl;
			exit(EXIT_SUCCESS);
		}

		// if landed on GO TO JAIL, then move to next player
		if (currPlayer->getJail()){
			turn = (turn + 1) % nPlayers;
			continue;
		}

		// redo loop without moving on to next player
		if (doubles){
			cout << "You rolled doubles. Roll Again!" << endl;
			continue;
		}

		// reset number of doubles of current player
		currPlayer->setDoubleTime(0);

		// next turn
		turn = (turn + 1) % nPlayers;
	}
}


// Method: generates random number from 1 to 6
// @return random int from 1 to 6

// C++98 CODE ---------------------------
int rollDye() {

	// sets random seed to the current time
	srand(time(0));

	// uses seed to generate random number
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
// @param player pointer to current player, int reference to the dice
// @return true if still in jail, false if out of jail
bool jail(Player* player, int& dice1, int& dice2){

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

		// roll the dice (no matter what, dice values must be retained)
		cout << "Press ENTER to roll dice." << endl;
		dice1 = rollDye();
		cin.ignore();
		cin.ignore();
		dice2 = rollDye();

		// if pay, deduct $50 and exit jail
		if (input == "PAY"){
			player->subtractMoney(50);
			player->setJailTime(0);
			return false;
		}

		cout << "You rolled a " << dice1 << " and a " << dice2 << "." << endl;

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
	cout << player->getName() << " is in jail. Rolling dice." << endl;

	// roll the dice
	cout << "Press ENTER to roll dice." << endl;
	dice1 = rollDye();
	cin.ignore();
	cin.ignore();
	dice2 = rollDye();

	cout << "You rolled a " << dice1 << " and a " << dice2 << "." << endl;

	// if doubles rolled, exit jail
	if (dice1 == dice2){
		player->setJailTime(0);
		cout << player->getName() << " rolled doubles." << endl;
		return false;
	}

	// if doubles not rolled, has to pay $50, exits jail
	cout << player->getName() <<
			" did not roll doubles and has spent 3 turns in jail. Prisoner fined $50. Releasing hardened convict." << endl;
	player->setJailTime(0);
	player->subtractMoney(50);
	return false;
}

// Method: handles landing on property
// if not owned, user can buy property or ignore it
// if owned by someone else, pay rent to that person
// @param Property pointer to current property, Player pointer to current player and his/her turn,
// and vector pointer of all the players
void landOnProperty(Property* property, Player* player, int turn, vector<Player*> players){

	// gets the rent
	int rent = property->getRent();
	string choice;

	// if rent = 0, the property is not owned
	if (rent == 0){

		// prompt to buy or ignore property
		cout << property->getName() << " is not owned. The price is $" << property->getPrice() <<
				". Would you like to buy " << property->getName() << "? (Y/N)" << endl;

		while (true){

			cin >> choice;

			// if choice is yes, break out of while loop
			if (choice == "Y" || choice == "y"){

				// cost of property
				int cost = property->getPrice();

				// deduct cost from player's money
				player->subtractMoney(cost);

				// make the owner of the property the current player
				property->setOwner(turn);

				// add property to player's own property vector
				player->addProperty(property);
				cout << "You bought " << property->getName() << "!" << endl;
				break;
			}

			// if choice is no, do nothing
			else if (choice == "N" || choice == "n"){
				cout << property->getName() << " was not bought." << endl;
				break;
			}

			// checks input, reruns if neither
			else cout << "Invalid choice, choose either 'Y' or 'N'" << endl;
		}
	}

	// if the property does not belong to the current player
	else if (turn != property->getOwner()){

		// essentially the "turn" of the opponent player
		int owner = property->getOwner();

		// if there are no houses on it...
		if (property->getHouses() == 0){

			// ...and is part of a monopoly, print this statement
			if (property->getMonopoly()){
				cout << players[owner]->getName() << " owns " << property->getName() << " in a monopoly. You pay " <<
						players[owner]->getName() << " $" << rent << "." << endl;
			}

			// ...and isn't part of a monopoly, print this
			else {
				cout << players[owner]->getName() << " owns " << property->getName() <<
						". You pay " << players[owner]->getName() << " $" << rent << "." << endl;
			}
		}

		// if one or more houses, print this
		else {
			cout << players[owner]->getName() << " owns " << property->getName() << " in a monopoly with " << property->getHouses() <<
					" house(s). You pay " << players[owner]->getName() << " $" << rent << "." << endl;
		}

		// give money from current player to opponent (owner)
		players[owner]->addMoney(rent);
		player->subtractMoney(rent);
	}

	// if current player lands on own property, do nothing
	else cout << "You landed on your own property..." << endl;
}

// Method: scans player's current properties, determines which are part of monopoly
// Determines which colors are monopolized
// @param player pointer to current player
void monopoly(Player* player){

	// vector of player's properties
	vector<Property*> properties = player->getProperties();

	// declare counters for each color
	int purple = 0;
	int lblue = 0;
	int pink = 0;
	int orange = 0;
	int red = 0;
	int yellow = 0;
	int green = 0;
	int dblue = 0;

	// goes through player's properties, increments if they are of a specific color
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

	// if at least one monopoly exists, set hasMonopoly to true for the player
	if (purple == 2 || lblue == 3 || pink == 3 || orange == 3 || red == 3 || yellow == 3 || green == 3 || dblue == 2)
		player->setMonopoly(true);

	// vector of the monopolized colors
	vector<string> colors = player->getColors();

	// if monopoly is true for a certain color and the colors vector doesn't already have it, add it to that vector
	if (purple == 2 && find(colors.begin(), colors.end(), "PURPLE") == colors.end()) player->addColors("PURPLE");
	if (lblue == 3 && find(colors.begin(), colors.end(), "L. BLUE") == colors.end()) player->addColors("L. BLUE");
	if (pink == 3 && find(colors.begin(), colors.end(), "PINK") == colors.end()) player->addColors("PINK");
	if (orange == 3 && find(colors.begin(), colors.end(), "ORANGE") == colors.end()) player->addColors("ORANGE");
	if (red == 3 && find(colors.begin(), colors.end(), "RED") == colors.end()) player->addColors("RED");
	if (yellow == 3 && find(colors.begin(), colors.end(), "YELLOW") == colors.end()) player->addColors("YELLOW");
	if (green == 3 && find(colors.begin(), colors.end(), "GREEN") == colors.end()) player->addColors("GREEN");
	if (dblue == 2 && find(colors.begin(), colors.end(), "D. BLUE") == colors.end()) player->addColors("D. BLUE");

	// sets the monopoly condition of each property to true if they are part of a monopolized color region
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

// Method: determines different outcomes of random community chest draw
// @param player pointer to current player
void communityChest(Player* player) {

	// chooses random number
	int randNum = rand() % 6;

	// text to display at index of random number
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

// Method: determines different outcomes of random chance draw
// @param player pointer to current player
void chance(Player* player) {

	// choose random number
	int randNum = rand() % 5;

	// text to display at index of random number
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
	else if (randNum == 1) player->subtractMoney(15);

	// increase player's money by 150
	else if (randNum == 2) player->addMoney(150);

	// increase player's money by 100
	else if (randNum == 3) player->addMoney(100);

	// increase player's money by 50
	else player->addMoney(50);
}

// Method: Prints menu and looks for user input
// @param player pointer to current player, vector of Property pointers to all properties that exist
// @return true if proceed with turn, false if anything else
bool menu(Player* player, vector<Property*> allProps){

	// vector of current player's properties
	vector<Property*> properties = player->getProperties();

	// print menu, options are integers
	cout << "1. Proceed with turn" << endl;
	cout << "2. Display player info" << endl;
	cout << "3. Buy/sell houses" << endl;
	cout << "4. Show visualization for properties held" << endl;
	cout << "5. Exit game" << endl;

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

		// if not between 1-5, reprompt
		if (choice > 5 || choice < 1){
			cout << "Invalid input. Please try again: ";
		}
		else break;
	}
	cout << endl;

	// display information about the player
	if (choice == 2){

		// print how much money player has
		cout << "You have $" << player->getMoney() << "." << endl;

		// use for loop to print which properties player owns
		cout << "You own ";
		if (!properties.empty()){
			for (unsigned int i=0; i < properties.size(); i++){
				if (i != properties.size() - 1) cout << properties[i]->getName() << ", ";
				else cout << properties[i]->getName() << "." << endl;
			}
		}
		else cout << "no properties." << endl;

		// location of player
		cout << "You are located at location " << player->getLocation() << "." << endl;

		// prints current turn in jail if in jail
		if (player->getJail()){
			cout << "You are in turn #" << player->getJailTime() + 1 << " in jail." << endl;
		}

		// prints current monopolies
		if (player->getMonopoly()){
			cout << "MONOPOLIES: ";
			for (unsigned int i = 0; i < player->getColors().size(); i++){
				if (i != player->getColors().size() - 1) cout << player->getColors()[i] << ", ";
				else cout << player->getColors()[i] << endl;
			}
		}
		cout << endl;
		return true;
	}

	// buy/sell houses
	else if (choice == 3){

		// if they have a monopoly, they can buy/sell houses
		if (player->getMonopoly()){

			// runs options for building/demolishing houses
			buildHouses(player, allProps);
		}

		// if they don't, exit method
		else {
			cout << "You do not have a monopoly. Unable to build houses." << endl;
		}
		cout << endl;
		return true;
	}

	// shows visualization for the properties that the player currently has
	// 'X' means that the property is not owned
	// a number indicates that how many houses are on the current property
	// the vertical lines separate properties of different colors/monopolies
	else if (choice == 4){

		for (unsigned int i = 0; i < allProps.size(); i++){
			if (find(properties.begin(), properties.end(), allProps[i]) != properties.end()){
				cout << allProps[i]->getHouses() << " ";
			}
			else cout << "X ";
			if (i == 1 || i == 4 || i == 7 || i == 10 || i == 13 || i == 16 || i == 19) cout << "| ";
		}
		cout << endl << endl;
		return true;
	}

	// exits game
	else if (choice == 5){
		exit(EXIT_SUCCESS);
	}

	// proceeds with the rest of the game
	return false;
}

// Method: build houses on a specific property
// @param player pointer to current player, vector of Property pointers to all possible properties
void buildHouses(Player* player, vector<Property*> allProps){

	// vector of player's properties
	vector<Property*> properties = player->getProperties();

	// vector of monopolized colors for this player
	vector<string> colors = player->getColors();
	vector<Property*> monoProps;

	// prompt whether to buy/sell houses
	cout << "Would you like to buy or sell houses? (buy/sell)" << endl;
	string input;
	do{
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::toupper);

		// if invalid choice, reprompt
		if (input != "BUY" && input != "SELL") cout << "Invalid choice. Please choose either buy or sell." << endl;
	} while (input != "BUY" && input != "SELL");

	// if user wants to sell houses...
	if (input == "SELL"){

		// pick monopoly color for which to sell houses on
		cout << "In which monopoly would you like to sell houses? (Pick a color)" << endl;
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::toupper);

		// fixes potential entries for specific colors L. BLUE and D. BLUE
		if (input == "LIGHT BLUE" || input == "L BLUE" || input == "LBLUE" || input == "L.BLUE") input = "L. BLUE";
		if (input == "DARK BLUE" || input == "D BLUE" || input == "DBLUE" || input == "D.BLUE") input = "D. BLUE";

		// if the color is not in monopolized colors vector, return to main menu
		if (find(colors.begin(), colors.end(), input) == colors.end()){
			cout << "Monopoly color not found. Returning to main menu." << endl;
			return;
		}

		// put all properties of that color in same property vector
		for (unsigned int i = 0; i < allProps.size(); i++){
			if (input == allProps[i]->getColor()){
				monoProps.push_back(allProps[i]);
			}
		}

		Property* temp;
		bool exists = false;

		// prompt which property player would like to sell houses on
		cout << "Which property do you want to sell houses on? (Must be sold evenly with other monopoly properties)" << endl;
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::toupper);

		// puts chosen property at front of vector
		for (unsigned int i = 0; i < monoProps.size(); i++){
			if (input == monoProps[i]->getName()){
				temp = monoProps[0];
				monoProps[0] = monoProps[i];
				monoProps[i] = temp;
				exists = true;
			}
		}

		// if invalid property or a property not in the monoProps vector, return to main menu
		if (!exists){
			cout << "Property not found. Returning to main menu." << endl;
			return;
		}

		// if no houses on this property, then there's nothing to sell
		if (monoProps[0]->getHouses() == 0){
			cout << "No houses on this property to sell. Returning to main menu." << endl;
			return;
		}

		// if there's at least one property in the same color group that has more houses, return to main menu
		for (unsigned int i = 1; i < monoProps.size(); i++){
			if (monoProps[0]->getHouses() < monoProps[i]->getHouses()) exists = false;
		}
		if (exists){
			cout << "Property has less houses than monopoly properties. Returning to main menu." << endl;
			return;
		}

		// decrease number of houses in chosen property by 1
		monoProps[0]->setHouses(monoProps[0]->getHouses() - 1);

		// give money to player, which is half of the house price for the property
		player->addMoney(monoProps[0]->getHousePrice() / 2);
		cout << "You earned $" << monoProps[0]->getHousePrice() / 2 << "." << endl;
	}
	else {

		// pick monopoly color for which to buy houses on
		cout << "Which monopoly would you like to develop on? (Pick a color)" << endl;
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::toupper);

		// fixes potential entries for specific colors L. BLUE and D. BLUE
		if (input == "LIGHT BLUE" || input == "L BLUE" || input == "LBLUE" || input == "L.BLUE") input = "L. BLUE";
		if (input == "DARK BLUE" || input == "D BLUE" || input == "DBLUE" || input == "D.BLUE") input = "D. BLUE";

		// if the color is not in monopolized colors vector, return to main menu
		if (find(colors.begin(), colors.end(), input) == colors.end()){
			cout << "Monopoly color not found. Returning to main menu." << endl;
			return;
		}

		// put all properties of that color in same property vector
		for (unsigned int i = 0; i < allProps.size(); i++){
			if (input == allProps[i]->getColor()){
				monoProps.push_back(allProps[i]);
			}
		}

		Property* temp;
		bool exists = false;

		// prompt which property player would like to buy houses on
		cout << "Which property do you want to buy houses on? (Must be built evenly with other monopoly properties)" << endl;
		cin >> input;
		transform(input.begin(), input.end(), input.begin(), ::toupper);

		// puts chosen property at front of vector
		for (unsigned int i = 0; i < monoProps.size(); i++){
			if (input == monoProps[i]->getName()){
				temp = monoProps[0];
				monoProps[0] = monoProps[i];
				monoProps[i] = temp;
				exists = true;
			}
		}

		// if invalid property or a property not in the monoProps vector, return to main menu
		if (!exists){
			cout << "Property not found. Returning to main menu." << endl;
			return;
		}

		// if five houses on this property, then you can't buy anymore, returns to main menu
		if (monoProps[0]->getHouses() == 5){
			cout << "Max number of houses already reached. Returning to main menu." << endl;
			return;
		}

		// if there's at least one property in the same color group that has less houses, return to main menu
		for (unsigned int i = 1; i < monoProps.size(); i++){
			if (monoProps[0]->getHouses() > monoProps[i]->getHouses()) exists = false;
		}
		if (exists){
			cout << "Property has more houses than monopoly properties. Returning to main menu." << endl;
			return;
		}

		// if player doesn't have enough money to buy house, return to main menu
		if (player->getMoney() < monoProps[0]->getHousePrice()){
			cout << "Insufficient funds. Returning to main menu." << endl;
			return;
		}

		// add one house to chosen property
		monoProps[0]->setHouses(monoProps[0]->getHouses() + 1);

		// subtract player's money by the price of houses for this property
		player->subtractMoney(monoProps[0]->getHousePrice());
		cout << "You bought a house on " << monoProps[0]->getName() << "!" << endl;
	}
}
