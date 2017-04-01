/*
 * Property.cpp
 *
 *  Created on: Mar 25, 2017
 *      Author: mikel
 */

#include "mono.h"

Property::Property(int location, int buyPrice, int initialRent, int oneHouseRent, int twoHouseRent
	int threeHouseRent, int fourHouseRent, int hotelRent, int numberOfHouses, int housePrices,
	bool isOwned, bool inMonopoly)
{
	this.location = location;
	this.buyPrice = buyPrice;

	rentAmounts[0] = initialRent;
	rentAmounts[1] = oneHouseRent;
	rentAmounts[2] = twoHouseRent;
	rentAmounts[3] = threeHouseRent;
	rentAmounts[4] = fourHouseRent;
	rentAmounts[5] = hotelHouseRent;

	this.numberOfHouses = numberOfHouses;
	this.isOwned = isOwned;
	this.inMonopoly = inMonopoly;
}

int rentCost()
{
	if(!(inMonopoly))
		return rentAmounts[0];

	else
	{
		if(numberOfHouses == 0)
			return rentAmounts[0] * 2;

		else if(numberOfHouses == 1)
			return rentAmounts[1]

		else if(numberOfHouses == 2)
			return rentAmounts[2]

		else if(numberOfHouses == 3)
			return rentAmounts[3]

		else if(numberOfHouses == 4)
			return rentAmounts[4]

		else if(numberOfHouses == 5)
			return rentAmounts[5]
	}

	return 0;
}