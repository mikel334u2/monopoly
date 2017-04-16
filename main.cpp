//
//  main.cpp
//  Gui
//
//  Created by Harsh Patel on 4/1/17.
//  Copyright © 2017 Harsh Patel. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
//#include "mono.cpp"
#include "Player.cpp"
#include "Property.cpp"
#include "boardView.cpp"
#include "mono.h"

#include <chrono>
#include <random>
#include <exception>
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

int rollDye() {
    
    random_device rndm;
    mt19937 generator(rndm());
    uniform_int_distribution<> range(1, 6);
    
    return range(generator);
}



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

int main(int argc, const char * argv[]) {
    
    
    //creates the window that lopads the GUI
    RenderWindow app(VideoMode(2030, 1600), "Monopoly" );
    
    //if you want to create rectangles this is an example of it
//    RectangleShape rec(Vector2f(100, 100));
   
    app.setFramerateLimit(60);
    
    
    //font variable to hold font for the property text
    Font font;
    
    //loads the font
    if(!font.loadFromFile("/Users/harsh/Desktop/Gui/Gui/8-BIT WONDER.TTF")){
    
        cout<<"error"<<endl;
    
    
    }
    
    
    //font variable to hold font for the player/budget text
    Font font2;
    
    //loads the font
    if(!font2.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Arial.ttf")){
        
        cout<<"error"<<endl;
        
    }
    
    
    
    //Text is a variable that holds the desired strings to display on the GUI
//    Text playerName;
//    Text playerName2;
//    Text playerName3;
//    Text playerName4;

    vector <Text> playerName;
    
//    Text budget;
//    Text budget2;
//    Text budget3;
//    Text budget4;
    
    vector <Text> budget;

    Text propertiesText;
    
    
    //use this varibale to store input from the cosole and use the setString method which is shown on line 82 to set a string to the Text varables (they only accept strings)
    string input = "";
    
    //the methods for Text speak for themselves as to what thet do
//    
//    playerName.setCharacterSize(40);
//    playerName.setFillColor(Color::Color(62, 70, 255, 255));
//    playerName.setFont(font2);
//    playerName.setString("Player: Harsh" + input);
//    budget.setCharacterSize(35);
//    budget.setFillColor(Color::Color(62, 70, 255, 255));
//    budget.setFont(font2);
//    budget.setString("Budget: $1500");
//    
//    playerName2.setCharacterSize(40);
//    playerName2.setFillColor(Color::Color(255, 29, 29, 255));
//    playerName2.setFont(font2);
//    playerName2.setString("Player: Yasir" + input);
//    budget2.setCharacterSize(35);
//    budget2.setFillColor(Color::Color(255, 29, 29, 255));
//    budget2.setFont(font2);
//    budget2.setString("Budget: $1500");
    
//    playerName3.setCharacterSize(40);
//    playerName3.setFillColor(Color::Color(0, 151, 18, 255));
//    playerName3.setFont(font2);
//    playerName3.setString("Player: Dominic" + input);
//    budget3.setCharacterSize(35);
//    budget3.setFillColor(Color::Color(0, 151, 18, 255));
//    budget3.setFont(font2);
//    budget3.setString("Budget: $1500");
    
//    playerName4.setCharacterSize(40);
//    playerName4.setFillColor(Color::Color(134, 21, 176, 255));
//    playerName4.setFont(font2);
//    playerName4.setString("Player: Daniel" + input);
//    budget4.setCharacterSize(35);
//    budget4.setFillColor(Color::Color(134, 21, 176, 255));
//    budget4.setFont(font2);
//    budget4.setString("Budget: $1500");
    
    

    
    
    
    propertiesText.setCharacterSize(25);
    propertiesText.setFillColor(Color::Blue);
    propertiesText.setFont(font);
    propertiesText.setString("Properties Owned");

    
    //these variables will hold the position of the player on the tile. Tile starts at Go and is value 0, tile 1 is mediterannean avenue, tile 2 is baltic avenue.....etc.
    //increase the tilecounter+=dieValue (if you want to). I made 4 because 1 for each player. You guys can decide how you wanna do it
    int tileCounter = 0;
//    int tileCounter2 = 0;
//    int tileCounter3 = 0;
//    int tileCounter4 = 0;
    
    
    //Texture holds the value for each image
    //board texture
    Texture board;
    
    
    //all the pieces textures
    Texture robot;
    Texture Car;
    Texture Dog;
    Texture Iron;
    Texture Phone;
    Texture PotOfGold;
    Texture Ship;
    Texture Thimble;
    
    //textures for those sexy vertical and horizonal lines
    Texture vLine;
    Texture hLine;
    
    //all the tiles textures
    Texture tile0;
    Texture tile1;
    Texture tile2;
    Texture tile3;
    Texture tile4;
    Texture tile5;
    Texture tile6;
    Texture tile7;
    Texture tile8;
    Texture tile9;
    Texture tile10;
    Texture tile11;
    Texture tile12;
    Texture tile13;
    Texture tile14;
    Texture tile15;
    Texture tile16;
    Texture tile17;
    Texture tile18;
    Texture tile19;
    Texture tile20;
    Texture tile21;
    Texture tile22;
    Texture tile23;
    Texture tile24;
    Texture tile25;
    Texture tile26;
    Texture tile27;
    Texture tile28;
    Texture tile29;
    Texture tile30;
    Texture tile31;
    
    
    //all the property textures
    Texture prop1;
    Texture prop2;
    Texture prop3;
    Texture prop4;
    Texture prop5;
    Texture prop6;
    Texture prop7;
    Texture prop8;
    Texture prop9;
    Texture prop10;
    Texture prop11;
    Texture prop12;
    Texture prop13;
    Texture prop14;
    Texture prop15;
    Texture prop16;
    Texture prop17;
    Texture prop18;
    Texture prop19;
    Texture prop20;
    Texture prop21;
    Texture prop22;
    

    
    
    //loading all the pieces
    robot.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Robot.png");
    Car.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Car.png");
    Dog.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Dog.png");
    Iron.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Iron.png");
    Phone.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Phone.png");
    PotOfGold.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Pot of Gold.png");
    Ship.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Ship.png");
    Thimble.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Thimble.png");


    //loading all textures
    board.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Monopoly Board.png");
    vLine.loadFromFile("/Users/harsh/Desktop/Gui/Gui/vertical line.png");
    hLine.loadFromFile("/Users/harsh/Desktop/Gui/Gui/horizontal line.png");
    tile0.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Go.png");
    tile1.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Mediterranian Avenue.png");
    tile2.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Baltic Avenue.png");
    tile3.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Income Tax.png");
    tile4.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Oriental Avenue.png");
    tile5.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Community Chest1.png");
    tile6.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Vermont Avenue.png");
    tile7.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Connecticut Avenue.png");
    tile8.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Jail.png");
    tile9.loadFromFile("/Users/harsh/Desktop/Gui/Gui/St Charles Place.png");
    tile10.loadFromFile("/Users/harsh/Desktop/Gui/Gui/States Avenue.png");
    tile11.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Virginia Avenue.png");
    tile12.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Chance1.png");
    tile13.loadFromFile("/Users/harsh/Desktop/Gui/Gui/St James Place.png");
    tile14.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Tennessee Avenue.png");
    tile15.loadFromFile("/Users/harsh/Desktop/Gui/Gui/New York Avenue.png");
    tile16.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Free Parking.png");
    tile17.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Kentucky Avenue.png");
    tile18.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Indiana Avenue.png");
    tile19.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Illinois Avenue.png");
    tile20.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Community Chest2.png");
    tile21.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Atlantic Avenue.png");
    tile22.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Ventor Avenue.png");
    tile23.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Marvin Gardens.png");
    tile24.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Go To Jail.png");
    tile25.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Pacific Avenue.png");
    tile26.loadFromFile("/Users/harsh/Desktop/Gui/Gui/North Carolina Avenue.png");
    tile27.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Pennsylvania Avenue.png");
    tile28.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Luxury Tax.png");
    tile29.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Park Place.png");
    tile30.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Chance2.png");
    tile31.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Boardwalk.png");
    
    
    //loading all the properties
    prop1.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Mediterranian Avenue Label.png");
    prop2.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Atlantic Avenue Label.png");
    prop3.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Boardwalk Label.png");
    prop4.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Connecticut Avenue Label.png");
    prop5.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Illinois Avenue Label.png");
    prop6.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Indiana Avenue Label.png");
    prop7.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Baltic Avenue Label.png");
    prop8.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Kentucky Avenue Label.png");
    prop9.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Marvin Gardens Label.png");
    prop10.loadFromFile("/Users/harsh/Desktop/Gui/Gui/New York Avenue Label.png");
    prop11.loadFromFile("/Users/harsh/Desktop/Gui/Gui/North Carolina Ave Label.png");
    prop12.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Oriental Avenue Label.png");
    prop13.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Park Place Label.png");
    prop14.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Pennsylvania Avenue Label.png");
    prop15.loadFromFile("/Users/harsh/Desktop/Gui/Gui/St Charles Place Label.png");
    prop16.loadFromFile("/Users/harsh/Desktop/Gui/Gui/St James Place Label.png");
    prop17.loadFromFile("/Users/harsh/Desktop/Gui/Gui/States Avenue Label.png");
    prop18.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Tennessee Avenue Label.png");
    prop19.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Ventor Avenue Label.png");
    prop20.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Vermont Label.png");
    prop21.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Virginia Avenue Label.png");
    prop22.loadFromFile("/Users/harsh/Desktop/Gui/Gui/Pacific Avenue Label.png");


    
    
    

    //all the textures in a nice array
    Texture array [32] = {tile0, tile1, tile2, tile3, tile4, tile5, tile6, tile7, tile8, tile9, tile10, tile11, tile12, tile13, tile14, tile15, tile16, tile17, tile18, tile19, tile20, tile21, tile22, tile23, tile24, tile25, tile26, tile27, tile28, tile29, tile30, tile31};
    
    
    //all the properties in a vector (shouldve done the textures in a vector too but forgot they existed at the time so oh well)
    
    vector <Texture> propTextures;
    propTextures.push_back(prop1);
    propTextures.push_back(prop2);
    propTextures.push_back(prop3);
    propTextures.push_back(prop4);
    propTextures.push_back(prop5);
    propTextures.push_back(prop6);
    propTextures.push_back(prop7);
    propTextures.push_back(prop8);
    propTextures.push_back(prop9);
    propTextures.push_back(prop10);
    propTextures.push_back(prop11);
    propTextures.push_back(prop12);
    propTextures.push_back(prop13);
    propTextures.push_back(prop14);
    propTextures.push_back(prop15);
    propTextures.push_back(prop16);
    propTextures.push_back(prop17);
    propTextures.push_back(prop18);
    propTextures.push_back(prop19);
    propTextures.push_back(prop20);
    propTextures.push_back(prop21);
    propTextures.push_back(prop22);
    
    


    
    

    //The Sprite variable has textures object as you can (board) (tile0)
    
    //You have to turn the textures into sprites in order to draw them on the screen, move them around, scale them, or anything your heart desires.
    
    Sprite background (board);
    
    Sprite robotPiece(robot);
    Sprite carPiece (Car);
    Sprite dogPiece (Dog);
    Sprite ironPiece (Iron);
    Sprite phonePiece (Phone);
    Sprite potOfGoldPiece (PotOfGold);
    Sprite shipPiece (Ship);
    Sprite thimblePiece (Thimble);
    
    
    Sprite verticalLine(vLine);
    Sprite horizontalLine(hLine);
    Sprite secHorizontalLine(hLine);
    
    vector <Sprite> liveTileTextures;    //holds all the tiles in a Sprite vector. Use this information to dynamically update the tiles on the screen in the live tile section on the upper right
    vector <Sprite> property;            //holds all the properties in a sprite vector. Use this information to dynamically add or remove properties on/from the screen
    
    
    
    //puts all the property textures in the property sprite
    for(int i =0; i<propTextures.size(); i++){
        
        Sprite newProperty;
        newProperty.setTexture(propTextures[i]);
        
        property.push_back(newProperty);
    }
    
    //puts all the tile textures in the liveTileTexture sprite
    for(int i =0; i!=32; i++){
    
        Sprite newTile;
        newTile.setTexture(array[i]);
        
        liveTileTextures.push_back(newTile);

    }
    
    

    
    
    //moving objects
    
    //you guys are smart so i thing you can figure it out. The values inside the .move method is based on pixels. P.S. The total pixels the window is made up of is (2030, 1600) which is showcased in line 26
    
    liveTileTextures[tileCounter].move(1612, 0);
    verticalLine.move(1601,0);
    
    horizontalLine.move(1610,421);
    secHorizontalLine.move(1610,1308);
    
    
    //I leave the movement of the pieces to you smart guys
    
    robotPiece.scale(1.5, 1.5);
    robotPiece.move(40, 1280);
    carPiece.move(40,1450);
    dogPiece.move(40,1450);
    ironPiece.move(40,1450);
    phonePiece.move(40,1450);
    potOfGoldPiece.move(40,1450);
    shipPiece.move(40,1450);
    thimblePiece.move(40,1450);
    
    
    
    
    propertiesText.move(1627, 430);
    property[1].move(1620, 480);    //make sure you change the index for this otherwise it wont move properly. So if you change the index in the .draw method for property it wont be in the right position since only index one is moved.
    
    
//    playerName.move(1616, 1311);
//    budget.move(1616,1345);
    
//    playerName2.move(1616, 1382);
//    budget2.move(1616, 1418);
    
//    playerName3.move(1616, 1455);
//    budget3.move(1616,1489);
    
//    playerName4.move(1616, 1523);
//    budget4.move(1616, 1557);

    board.setSmooth(true);
    
    
    
    //starts here
    
    int nPlayers = 0;
    
    cout << "Welcome to Monopoly!"<<endl;
    cout << "Please input the number of players (2-4): "<<endl;
    
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
        Text pla;
        pla.setString(input);
        playerName.push_back(pla);
        playerName.at(i).setCharacterSize(40);
        playerName.at(i).setFillColor(Color::Color(62, 70, 255, 255));
        playerName.at(i).setFont(font2);
    }
    
    
    for(int i =0; i<playerName.size(); i++){
    
        Text budgetNew;
        budgetNew.setString("Budget: 1500");
        budget.push_back(budgetNew);
        budget.at(i).setCharacterSize(35);
        budget.at(i).setFillColor(Color::Color(62, 70, 255, 255));
        budget.at(i).setFont(font2);


    
    }
    int move0=0;
    
    for(int i=0; i<budget.size(); i++){
        budget.at(i).move(1616, 1345+move0);
        move0=move0+73;
        
    }
    
    
    
    
    int move = 0;
    for(int i=0; i<playerName.size(); i++){
        playerName.at(i).move(1616, 1311+move);
        move=move+71;
  
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
            cout << names.at(i)<< ", please choose your piece: "<<endl;
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
        Property* property = new Property(propertyNames[i],propertyColor[i],i,propertyPrice[i],propertyHousePrice[i],initialRent[21],
                                          oneHouseRent[i],twoHouseRent[i],threeHouseRent[i],fourHouseRent[i],fiveHouseRent[i]);
        properties.push_back(property);
    }
    
    // for loop iterates through players vector
    // for (unsigned int i = 0; i < players.size(); i++){}
    
    

   

    

    
    
//    this is WHERE ALL THE LOGIC WILL GO THAT NEEDS TO BE REPEATED. This while is responsible for maintaining/loading the gui on the screen at all times
    
    int turn = 0; // turn of current player
    int location; // location of player
    bool doubles = false; // bool if doubles are rolled, then true
    bool passGo; // if passes go, then true
    int dice1 = 0; // dice values
    int dice2 = 0;
    Player* currPlayer; // current player's turn
    Property* propertyClass; // pointer to property at landed location
    
        int check=0;

    while(app.isOpen()){
    
    

        Event e;
        while(app.pollEvent(e)){
        
            if(e.type==Event::Closed){
            
                app.close();
            
            }

        }
        
        
        //this line of code is an example of how key presses can be used but i don't think we will need it. This is just for reference
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
//        {
//            // left key is pressed: move our character
//            robotPiece.move(1, 0);
//        }
        
        

        // .draw function is responsible for actually "drawing" or displaying our objects on the window. SO MAKE SURE YOU KNOW WHAT TO DRAW AND WHEN!!!!!!!!!!!!!
        app.draw(background);
        app.draw(liveTileTextures[tileCounter]);
        app.draw(verticalLine);
        app.draw(horizontalLine);
        app.draw(secHorizontalLine);
        for(int i=0; i<playerName.size();i++)
            app.draw(playerName[i]);

        for(int i=0; i<budget.size();i++)
        app.draw(budget[i]);
        
        app.draw(propertiesText);
        app.draw(property[1]);     //change index for this to dynamically update the property and so that it can be moves in the right position. May need to be put in an if statement if we have to check what people have and dont
       
        app.draw(robotPiece);
        app.display();             //this opens the window that displays all our drawings
        
        
        app.clear(sf::Color(216, 255, 232, 45));      //This is responible for changing the background of the window

        
        //ALL THE REPEATED LOGIC WILL GO HERE!!!!!!!!!!!!!!!
        
        //this is the new stuff. Uncomment and have fun fixing.
//        
//            currPlayer = players[turn];
//            
//            string input;
//            cout << currPlayer->getName() << "'s turn. Press ENTER";
//            cin >> input;
//            // would you like to buy/sell property/houses or roll dice?
//            
//            // roll dice, determine doubles
//            dice1 = rollDye();
//            dice2 = rollDye();
//            doubles = (dice1 == dice2) ? true : false;
//            
//            // if still in jail, go to next player's turn
//            if (jail(currPlayer, dice1, dice2)){
//                turn = (turn + 1) % nPlayers;
//                continue;
//            }
//            
//            // if just out of jail, make doubles false no matter what
//            if (currPlayer->getJail()){
//                doubles = false;
//                currPlayer->changeJail();
//            }
//            
//            // if doubles rolled, count number of doubles
//            if (doubles) currPlayer->setDoubleTime(currPlayer->getDoubleTime()+1);
//            
//            // if number of doubles is 3, send player to jail
//            if (currPlayer->getDoubleTime() >= 3){
//                currPlayer->changeJail();
//                currPlayer->setLocation(8);
//                currPlayer->setDoubleTime(0);
//                turn = (turn + 1) % nPlayers;
//                continue;
//            }
//            
//            // move player by dice1 plus dice2
//            passGo = currPlayer->addLocation(dice1 + dice2);
//            
//            // current location
//            location = currPlayer->getLocation();
//            
//            // if passGo, collect $200
//            if (passGo){
//                currPlayer->addMoney(200);
//                cout<< currPlayer->getName() << " passed GO. Collect $200." << endl;
//            }
//            
//            // main switch for determining what to do at each space
//            switch (location){
//                    
//                    // Go
//                case 0:
//                    cout << "You're on GO" << endl;
//                    break;
//                    
//                    // Mediterranean Ave
//                case 1:
//                    propertyClass = properties[0];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Baltic Ave
//                case 2:
//                    propertyClass = properties[1];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Income Tax
//                case 3:
//                    cout << "Income Tax. Pay $200." << endl;
//                    currPlayer->subtractMoney(200);
//                    break;
//                    
//                    // Oriental Ave
//                case 4:
//                    propertyClass = properties[2];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    
//                    break;
//                    
//                    // Comm Chest
//                case 5:
//                    cout << "Community Chest." << endl;
//                    break;
//                    
//                    // Vermont Ave
//                case 6:
//                    propertyClass = properties[3];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Connecticut Ave
//                case 7:
//                    propertyClass = properties[4];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Jail
//                case 8:
//                    cout << "JAIL." << endl;
//                    break;
//                    
//                    // St. Charles Pl
//                case 9:
//                    propertyClass = properties[5];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // States Ave
//                case 10:
//                    propertyClass = properties[6];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Virginia Ave
//                case 11:
//                    propertyClass = properties[7];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Chance
//                case 12:
//                    cout << "Chance." << endl;
//                    break;
//                    
//                    // St. James Pl
//                case 13:
//                    propertyClass = properties[8];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Tennessee Ave
//                case 14:
//                    propertyClass = properties[9];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // NY Ave
//                case 15:
//                    propertyClass = properties[10];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Free Parking
//                case 16:
//                    cout << "FREE PaRkInG!!!1!" << endl;
//                    break;
//                    
//                    // Kentucky Ave
//                case 17:
//                    propertyClass = properties[11];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Indiana Ave
//                case 18:
//                    propertyClass = properties[12];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Illinois Ave
//                case 19:
//                    propertyClass = properties[13];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Comm Chest
//                case 20:
//                    cout << "Community Chest." << endl;
//                    break;
//                    
//                    // Atlantic Ave
//                case 21:
//                    propertyClass = properties[14];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Ventor Ave
//                case 22:
//                    propertyClass = properties[15];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Marvin Gardens
//                case 23:
//                    propertyClass = properties[16];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Go to Jail
//                case 24:
//                    cout << "GO TO JAIL." << endl;
//                    break;
//                    
//                    // Pacific Ave
//                case 25:
//                    propertyClass = properties[17];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // NC Ave
//                case 26:
//                    propertyClass = properties[18];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Penn Ave
//                case 27:
//                    propertyClass = properties[19];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Luxury Tax
//                case 28:
//                    cout << "Luxury Tax. Pay $200." << endl;
//                    currPlayer->subtractMoney(200);
//                    break;
//                    
//                    // Park Place
//                case 29:
//                    propertyClass = properties[20];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // Chance
//                case 30:
//                    cout << "Chance." << endl;
//                    break;
//                    
//                    // Boardwalk
//                case 31:
//                    propertyClass = properties[21];
//                    landOnProperty(propertyClass, currPlayer, turn, players);
//                    break;
//                    
//                    // should never happen
//                default:
//                    cout << "Error: Unreachable?" << endl;
//                    exit(EXIT_SUCCESS);
//                    break;
//            }
//            
//            
//            // determines if the player's properties are part of monopoly
//            monopoly(currPlayer->getProperties());
//            
//            // temporary code
//            // players.erase(players.begin() + players.size() - 1);
//            
//            // if 1 player left, end game
//            if (players.size() == 1){
//                cout << "\nThe winner is " << players[0]->getName() << "!" << endl;
//                exit(EXIT_SUCCESS);
//            }
//            
//            if (doubles){
//                cout << "YOU ROLLED DOUBLES. ROLL AGAIN." << endl;
//                continue;
//            }
//            
//            // reset number of doubles of current player
//            currPlayer->setDoubleTime(0);
//            
//            // next turn
//            turn = (turn + 1) % nPlayers;
        
        
        
        
        
        
        
        
        
        
        
      
        
//uncomment to draw the pieces on screen. Should be around go. If not check the .move method for piece.
//        
//        app.draw(carPiece);
//        app.draw(shipPiece);
//        app.draw(potOfGoldPiece);
//        app.draw(thimblePiece);
//        app.draw(phonePiece);
//        app.draw(dogPiece);
//        app.draw(ironPiece);


        
        check++;
        cout<<check<<endl;
        
        

    
    }

    
}
