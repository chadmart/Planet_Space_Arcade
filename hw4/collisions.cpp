/*!\file collisions.cpp
 * 
 * \brief Contians the collision game logic implentations of the SpaceWars class
 * 
 * \Created by: Spencer Moran 
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/17/2012
 *
 * This class contians the collision game logic implentations of the SpaceWars class.
 */

#include "spacewars.h"

#include <list>

// Checking for intersections between good and bad bullets
void SpaceWars::checkBulletsCollision()
{
		//iterate through list, checking for intersections between good and bad bullets
		list<Bullet*>::iterator i = bullets.begin();
		while (i != bullets.end())
		{
			list<Bullet*>::iterator j = badguyBullets.begin();
			bool bullet_collision = false;

			while (j != badguyBullets.end() && i != bullets.end())
			{
				if ((*i)->getRect().intersects((*j)->getRect()))
				{
					bullet_collision = true;
					list<Bullet*>::iterator del = i;
					i++;
					delete (*del);
					bullets.erase(del);
					
					list<Bullet*>::iterator delj = j;
					j++;
					delete (*delj);
					badguyBullets.erase(delj);
				}

				else
					j++;
			}

			if (!bullet_collision)
				i++;
		}
}

// Checking for intersections between good and boss bullets
void SpaceWars::checkBossBulletsCollision()
{
		//iterate through list, checking for intersections between good and boss bullets
		list<Bullet*>::iterator i = bullets.begin();
		while (i != bullets.end())
		{
			list<BossBullet*>::iterator j = bossBullets.begin();
			bool bullet_collision = false;

			while (j != bossBullets.end() && i != bullets.end())
			{
				if ((*i)->getRect().intersects((*j)->getRect()))
				{
					bullet_collision = true;
					list<Bullet*>::iterator del = i;
					i++;
					delete (*del);
					bullets.erase(del);
					
					list<BossBullet*>::iterator delj = j;
					j++;

					//explode boss bullet and allow chance to drop power up
					dropPowerUp(*delj);
					explodingBossBullet.push_back(*delj);

					bossBullets.erase(delj);
				}
				else
					j++;
			}

			if (!bullet_collision)
				i++;
		}
}

// Checking to see if spaceship is hit
bool SpaceWars::checkGoodShipHit()
{
	bool hit = false;

	if(!badguyBullets.empty())
	{
		//iterate through list, checking to see if spaceship is hit by a badguy bullet
		list<Bullet*>::iterator j = badguyBullets.begin();

		while (j != badguyBullets.end())
		{
			if ((*j)->getRect().intersects(spaceship->getRect()))
			{
				hit = TRUE;

				list<Bullet*>::iterator delj = j;
				j++;
				delete (*delj);
				badguyBullets.erase(delj);
			}
				
			else
				j++;
		}
	}



	if(!bossBullets.empty())
	{
		//iterate through list, checking to see if spaceship is hit by a boss bullet
		list<BossBullet*>::iterator j = bossBullets.begin();

		while (j != bossBullets.end())
		{
			if ((*j)->getRect().intersects(spaceship->getRect()))
			{
				hit = TRUE;

				list<BossBullet*>::iterator delj = j;
				j++;

				// explode boss bullet
				explodingBossBullet.push_back(*delj);

				bossBullets.erase(delj);
			}
				
			else
				j++;
		}
	}

	return hit;
}

// Checking to see if the Boss got hit
bool SpaceWars::checkBossShipHit()
{
	bool hit = false;

	//iterate through list, checking to see if the Boss got hit
	list<Bullet*>::iterator i = bullets.begin();
	while (i != bullets.end())
	{
		if ((*i)->getRect().intersects(boss->getRect()))
		{	
			hit = true;

			list<Bullet*>::iterator del = i;
			i++;
			
			delete (*del);
			bullets.erase(del);
		}
		else
			i++;
	}
	
	return hit;
}

// Checking to see if badguys got hit
bool SpaceWars::checkBadShipHit(int badIndex,int j)
{
	bool hit = false;

	//iterate through list, checking to see if badguys got hit
	list<Bullet*>::iterator i = bullets.begin();
	while (i != bullets.end())
	{
		if ((*i)->getRect().intersects(badguys[badIndex][j]->getRect()))
		{	
			hit = true;

			list<Bullet*>::iterator del = i;
			i++;
			delete (*del);
			bullets.erase(del);
		}

		else
			i++;
	}
	
	return hit;
}

// Checking for intersections between ship and powerUps
void SpaceWars::checkPowerUpsCollision()
{
	if(!powerUps.empty())
	{
		for(int i = 0; i <  powerUps.size(); i++)
		{
			if (powerUps.at(i)->getRect().intersects(spaceship->getRect()))
			{
				powerUps.at(i)->powerShip(this);
				delete powerUps.at(i);
				powerUps.erase(i);

				if(score >= 4294967295ll-3)
					score = 4294967295ll;
				else
					score += 3;
			}
		}
	}

	if(lives == 0)
	{
		gameOver = true;

        // if not on screen, build end game buttons
        if(!restartButton->isVisible())
            buildEndGameButtons();
	}
	
		
}

/*
//check to see if player spaceship collided with a badguy's ship
bool SpaceWars::checkSpaceshipCollision(int badIndex, int j)
{
	bool collision = false;

	if (badguys[badIndex][j]->getRect().intersects(spaceship->getRect()))
		collision = true; 

	return collision;
}

//check to see if player spaceship collided with the Boss's ship
bool SpaceWars::checkSpaceshipBossCollision()
{
	bool collision = false;

	if (boss->getRect().intersects(spaceship->getRect()))
		collision = true; 

	return collision;
}*/

//check to see which collisions occured and set appropriate flags
void SpaceWars::checkCollisions(bool& spaceshipHit, bool badguyhit[4][3], bool& bossHit)
{
	// Checking for intersections between good and bad bullets
	if (!bullets.empty() && !badguyBullets.empty())
		checkBulletsCollision();

	// Checking for intersections between good and boss bullets
	if (!bullets.empty() && !bossBullets.empty())
		checkBossBulletsCollision();

	// Checking to see if spaceship is hit
	if (!badguyBullets.empty() || !bossBullets.empty()) 
	{
		spaceshipHit = checkGoodShipHit();
	}


	if (!bullets.empty())
	{
		// Checking to see if the Boss got hit
		if (boss->isActive())
			bossHit = checkBossShipHit();

		// Checking to see if badguys got hit
		for(int i = 0; i < 4;i++)
		{
		  for(int j = 0; j < 3; j++)
		  {
			if (badguys[i][j]->isActive())
			{
				badguyhit[i][j] = checkBadShipHit(i,j);
			}
		  }
		}
	}

	/*
	//check if ships hit each other
	for(int i = 0; i < 4;i++)
	{
	  for(int j = 0; j < 3; j++)
	  {
		if (badguys[i][j]->isActive())
		{
			if (checkSpaceshipCollision(i,j))
			{
				spaceshipHit = true;
				badguyhit[i][j] = true;

			}
		}
	  }
	}

	//check if ship and boss hit each other
	if(boss->isActive())
	{
		if(checkSpaceshipBossCollision())
		{
			spaceshipHit = true;
			bossHit = true;
		}
	}*/

	// Checking for intersections between ship and powerUps
	if(!powerUps.empty())
		checkPowerUpsCollision();

	// remove temp shield and spaceshipHit, if they are both true
	if(spaceshipHit && shieldFlag)
	{
		if(!godMode)
			shieldFlag = false;

		spaceshipHit = false;
	}

}

