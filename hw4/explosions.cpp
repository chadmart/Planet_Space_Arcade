/*!\file explosions.cpp
 * 
 * \brief Contians the explosion game logic implentations of the SpaceWars class
 * 
 * \Created by: Spencer Moran 
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/17/2012
 *
 * This class contians the explosion game logic implentations of the SpaceWars class.
 */

#include "spacewars.h"
#include <QPainter>
#include <list>
#include <stdlib.h>

// Explodes player's spaceship
void SpaceWars::explodeSpaceship()
{
    //increment counting variable to control which explosion image is displayed
    spaceshipIndex++;

	//switch to display exploding images in correct order
    switch(spaceshipIndex)
    {
	case 2:
	{
		QPoint center = spaceship->getRect().center();
		spaceship->getImage().load("images/explosiontwo.png");
		spaceship->getRect() = spaceship->getImage().rect();
		spaceship->getRect().moveCenter(center);
		break;
	}

	case 3:
	{
		QPoint center = spaceship->getRect().center();
		spaceship->getImage().load("images/explosionthree.png");
		spaceship->getRect() = spaceship->getImage().rect();
		spaceship->getRect().moveCenter(center);
		break;
	}

	case 4:
	{
		QPoint center = spaceship->getRect().center();
		spaceship->getImage().load("images/explosionfour.png");
		spaceship->getRect() = spaceship->getImage().rect();
		spaceship->getRect().moveCenter(center);
		break;
	}

	case 5:
	{
		QPoint center = spaceship->getRect().center();
		spaceship->getImage().load("images/explosionfour.png");
		spaceship->getRect() = spaceship->getImage().rect();
		spaceship->getRect().moveCenter(center);
		break;
	}

	default:
		//set flag to go to lost a life screen
		killPlayer = true;

		//subtract a life
		lives--;

		//kill timers
		if(lives==0)
		{
			killTimer(timerId);
			killTimer(timerExplosions);
			killTimer(timerBadguyMove);
			killTimer(timerBadguyBullet);

			for (int i = 0; i<4; i++)
			{
			  for (int j = 0; j<3; j++)
			  {
				badguys[i][j]->setActive(false);
			  }
			}
		}

		killTimer(timerSpaceshipHit);

		//spaceship is done exploding, set to false
		spaceshipExploding = FALSE;

		//deletes active bullets
		clearBullets();

    }
	
}

// Explodes the boss
void SpaceWars::explodeBoss()
{
		//increment counting variable to control which explosion image is displayed
		bossIndex++;

		//switch to display exploding images in correct order
		switch(bossIndex)
		{
		case 2:
			{
			QPoint center = boss->getRect().center();
			boss->getImage().load("images/explosiontwo.png");
			boss->getRect() = boss->getImage().rect();
			boss->getRect().moveCenter(center);
			break;
			}

		case 3:
			{
			QPoint center = boss->getRect().center();
			boss->getImage().load("images/explosionthree.png");
			boss->getRect() = boss->getImage().rect();
			boss->getRect().moveCenter(center);
			break;
			}

		case 4:
			{
			QPoint center = boss->getRect().center();
			boss->getImage().load("images/explosionfour.png");
			boss->getRect() = boss->getImage().rect();
			boss->getRect().moveCenter(center);
			break;
			}

		case 5:
			{
			QPoint center = boss->getRect().center();
			boss->getImage().load("images/explosionfour.png");
			boss->getRect() = boss->getImage().rect();
			boss->getRect().moveCenter(center);
			break;
			}

		default:
			killTimer(timerbossHit);
			bossExploding = FALSE;
			boss->setActive(FALSE);
		
			//add score for destroying a boss
			if(score >= 4294967295ll-50)
				score = 4294967295ll;
			else
				score += 50;

			if(deathCount == 12 && !boss->isActive())
			{
				nextLevel = true;
			}

			//set flag, boss is now exploded
			boss->setExploded(TRUE);

		}
}

// Explodes a BadGuys's ship
void SpaceWars::explodeBadguy(int i, int j)
{
	//increment variable to control which explosion image is displayed
	badguyIndex[i][j]++;
	
	//switch to display exploding images in correct order
	switch(badguyIndex[i][j])
	{
	case 2:
		{
		QPoint center = badguys[i][j]->getRect().center();
		badguys[i][j]->getImage().load("images/explosiontwo.png");
		badguys[i][j]->getRect() = badguys[i][j]->getImage().rect();
		badguys[i][j]->getRect().moveCenter(center);
		break;
		}

	case 3:
		{
		QPoint center = badguys[i][j]->getRect().center();
		badguys[i][j]->getImage().load("images/explosionthree.png");
		badguys[i][j]->getRect() = badguys[i][j]->getImage().rect();
		badguys[i][j]->getRect().moveCenter(center);
		break;
		}

	case 4:
		{
		QPoint center = badguys[i][j]->getRect().center();
		badguys[i][j]->getImage().load("images/explosionfour.png");
		badguys[i][j]->getRect() = badguys[i][j]->getImage().rect();
		badguys[i][j]->getRect().moveCenter(center);
		break;
		}

	case 5:
		{
		QPoint center = badguys[i][j]->getRect().center();
		badguys[i][j]->getImage().load("images/explosionfour.png");
		badguys[i][j]->getRect() = badguys[i][j]->getImage().rect();
		badguys[i][j]->getRect().moveCenter(center);
		break;
		}

	default:
		//add score for destroying a badguy
		if(score >= 4294967295ll-5)
			score = 4294967295ll;
		else
			score += 5;

		deathCount++;

		if(deathCount == 12 && !boss->isActive())
		{
			nextLevel = true;
		}
	
		//set flag, badguy is now exploded
		badguys[i][j]->setActive(FALSE);
		badguys[i][j]->setExploded(TRUE);
		badguys[i][j]->setExploding(FALSE);
	}
}

// Explodes the boss's bullets
void SpaceWars::explodeBossBullet(BossBullet * boss)
{
		//increment counting variable to control which explosion image is displayed
		boss->addIndex();

		//switch to display exploding images in correct order
		switch(boss->getIndex())
		{
		case 2:
			{
			QPoint center = boss->getRect().center();
			boss->getImage().load("images/explosiontwo.png");
			boss->getRect() = boss->getImage().rect();
			boss->getRect().moveCenter(center);
			break;
			}

		case 3:
			{
			QPoint center = boss->getRect().center();
			boss->getImage().load("images/explosionthree.png");
			boss->getRect() = boss->getImage().rect();
			boss->getRect().moveCenter(center);
			break;
			}

		case 4:
			{
			QPoint center = boss->getRect().center();
			boss->getImage().load("images/explosionfour.png");
			boss->getRect() = boss->getImage().rect();
			boss->getRect().moveCenter(center);
			break;
			}

		case 5:
			{
			QPoint center = boss->getRect().center();
			boss->getImage().load("images/explosionfour.png");
			boss->getRect() = boss->getImage().rect();
			boss->getRect().moveCenter(center);
			break;
			}

		default:
		
			//add score for destroying a boss bullet
			if(score >= 4294967295ll-5)
				score = 4294967295ll;
			else
				score += 5;
		}
}

