/*!\file dropPowerUps.cpp
 * 
 * \brief Contians the game logic implentations for choosing and dropping the power ups in the SpaceWars class
 * 
 * \Created by: Spencer Moran 
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/17/2012
 *
 * This class contians the game logic implentations for choosing and dropping the power ups in the SpaceWars class.
 */

#include "spacewars.h"

#include <list>
#include <stdlib.h>

// Drops a power up in the location of a boss bullet 
// that just got hit by a good bullet
// Parameter Bullet * here is a pointer to a Boss bullet
void SpaceWars::dropPowerUp(Bullet * here)
{
	// pick a new power up
	// could return a NULL power up
	PowerUp * power = pickPowerUp();

	if(power)
	{
		// move power up to boss bullets location
		power->setLocation(here->getRect().x(),here->getRect().y());
		// add power up to lost
		powerUps.push_front(power);
	}
}

// Drops a power up in the location of a Badguy 
// that just got finished exploding
// Parameters int i and int j are the [i][j] index of the badguy that just exploded
void SpaceWars::dropPowerUp(int i,int j)
{
	// pick a new power up
	// could return a NULL power up
	PowerUp * power = pickPowerUp();
					
	if(power)
	{
		// move power up to badguys location
		power->setLocation(badguys[i][j]->getRect().x(),badguys[i][j]->getRect().y());
		// add power up to lost
		powerUps.push_front(power);
	}
}

// Spawns a powerUp power from location (i,j)
// Ability to choose power up and location to drop
// Used in Cheat codes to test power ups
// Parameter int i is x coordinate to drop from
// Parameter int j is y coordinate to drop from
// Parameter PowerUp * power is a pointer to the power up you want to drop
void SpaceWars::dropPowerUp(int i,int j, PowerUp * power)
{			
	if(power)
	{
		// move power up to (i,j) location
		power->setLocation(i,j);
		// add power up to lost
		powerUps.push_front(power);
	}
}

// Randomly chooses a power up to drop
// may choose a NULL power up
PowerUp* SpaceWars::pickPowerUp()
{
	PowerUp * power = NULL;

	int randPick = (rand() % 32);

	if(randPick == 0)
		power = new P1;// 1 extra life
	else if(randPick == 1)
	{
		if((rand() % 2) == 0)
			power= new P2;// 3 extra life
	}
	else if(randPick == 2)
		power= new P3;// Lose one life
	else if(randPick == 3)
	{
		if((rand() % 2) == 0)
			power= new P4;// double current points
	}
	else if(randPick == 4)
	{
		if((rand() % 10) == 0)
			power= new P5;// lose all points
	}
	else if(randPick == 5)
	{
		if((rand() % 30) == 0)
			power= new P6;// victory 
	}
	else if(randPick == 6)
		power= new P7;// +10 points
	else if(randPick == 7)
	{
		if((rand() % 2) == 0)
			power= new P8;// +100 points
	}
	else if(randPick == 8)
		power= new P9;// freeze enemies for ...
	else if(randPick == 9)
	{
		if((rand() % 10) == 0)
		power= new P10;// level up
	}
	else if(randPick == 10)
	{
		if((rand() % 10) == 0)
		power= new P11;// level down
	}
	else if(randPick == 11)
	{
		if((rand() % 30) == 0)
			power= new P12;// Game Over
	}
	else if(randPick == 12)
	{
		if((rand() % 2) == 0)
		power= new P14;// Temporary God Mode
	}
	else if(randPick == 14)
		power= new P15;// Temporary shield till next hit
	else if(randPick == 15)
	{
		if((rand() % 2) == 0)
		power= new P16;// Triple Shot
	}
	else 
	{}

	return power;
}
