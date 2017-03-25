/*
 * Player.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: mikel
 */

#include "mono.h"
#include<string>

#include <iostream>
using namespace std;

class player{

    private:
    string name;
    string typeOfPlace;
    int currentMoney;
    vector<Property> properties;
    
    public:
    player(string name, string piece, int money);
    bool hasMoney(Property property);
    void addHouse();
    string getPlayer();
    void setPlayer(string name);
    void afkCheck();
    bool checkMoneyForBuying();
    void removeProperty();
    void addProperty();
    


};
