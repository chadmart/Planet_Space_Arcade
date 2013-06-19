/*!\file moveBullets.cpp
 * 
 * \brief Contians the game logic implentations for moving the bullets in the SpaceWars class
 * 
 * \Created by: Spencer Moran 
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/17/2012
 *
 * This class contians the game logic implentations for moving the bullets in the SpaceWars class.
 */
#include "spacewars.h"

#include <list>

// Moves the player's bullets up the screen
void SpaceWars::moveGoodBullet()
{
	//increment through list, moving or deleting bullets
	list<Bullet*>::iterator i = bullets.begin();

	while (i != bullets.end())
	{
		if((*i)->getID()==0)
		{
			(*i)->move();
		}
		else if((*i)->getID()==1)
		{
			(*i)->move();
			(*i)->moveLeft();
		}
		else //if((*i)->getID()==2)
		{
			(*i)->move();
			(*i)->moveRight();
		}

		//delete any bullets that are out of bounds
		if ((*i)->offScreen())
		{
			list<Bullet*>::iterator del = i;
			i++;
			bullets.erase(del);
		}
		else
		{
			i++;
		}
	}
}

// Moves the BadGuys's bullets down the screen
void SpaceWars::moveBadBullet()
{
	//incremement through list, moving or deleting bullets
	list<Bullet*>::iterator j = badguyBullets.begin();

	while (j != badguyBullets.end())
	{
		(*j)->moveDown();

		//delete any bullets that are out of bounds
		if ((*j)->offScreen())
		{
			list<Bullet*>::iterator del = j;
			j++;
			badguyBullets.erase(del);
		}
		else
		{
			j++;
		}
	}
}

// Moves the Boss's bullets down the screen and towards the player
void SpaceWars::moveBossBullet()
{
	//incremement through list, moving or deleting bullets
	list<BossBullet*>::iterator j = bossBullets.begin();

	while (j != bossBullets.end())
	{
		(*j)->moveDown((*j)->trackDir((spaceship->getRect()).x()));

		//delete any bullets that are out of bounds
		if ((*j)->offScreen())
		{
			list<BossBullet*>::iterator del = j;
			j++;
			bossBullets.erase(del);
		}
		else
		{
			j++;
		}
	}
}

// Moves the power ups down the screen
void SpaceWars::movePowerUps()
{
	//iterate through list, moving or deleting bullets
	for(int i = 0; i < powerUps.size(); i++)
	{
		powerUps.at(i)->move(powerUps.at(i)->trackDir((spaceship->getRect()).x()));

		if(powerUps.at(i)->offScreen())
		{
			delete powerUps.at(i);
			powerUps.erase(i);
		}
	}
}

// Calls functions to move all bullets and power ups
void SpaceWars::moveBullets()
{
	//move any spaceship bullets that exist
	if (!bullets.empty())
		moveGoodBullet();

	//move any badguy bullets that exist
	if (!badguyBullets.empty())
		moveBadBullet();

	//move any boss bullets that exist
	if (!bossBullets.empty())
		moveBossBullet();

	//move powerUps if exist
	if(!powerUps.empty())
		movePowerUps();
}

