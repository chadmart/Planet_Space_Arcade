/*!\file powerup.cpp
 * 
 * \brief Contians the powerup class and sub-classes
 * 
 * \Created by: Chad Martin 
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/14/2012
 *
 * This class contians the powerup class and sub-classes.
 */
#include "powerup.h"

bool PowerUp::offScreen()
{
	//returns true if the PowerUp is out of bounds
	//otherwise return false
	if (rect.bottom() < -635)
		return true;
	else if (rect.top() > 1300)
		return true;
	else if (rect.left() < -635)
		return true;
	else if (rect.right() > 1200)
		return true;
	else
		return false;
}

// virtual function subclass may redifine function
void PowerUp::move(int x)
{
	//moves the PowerUp down the screen
	rect.moveTo(rect.left(), (rect.top() + 2));
}


void PowerUp::setActive(bool d)
{
	//set the PowerUp to active
	active = d;
}

bool PowerUp::isActive()
{
	//return whether or not the PowerUp is active
	return active;
}

void PowerUp::setLocation(int x, int y)
{
	//move the PowerUp to the specified location
	rect.moveTo(x, y);
}

// used to track location of player
// Parameter x: the x coordinate of the good space ship
int PowerUp::trackDir(int x)	
{
	// returns whether the item is to the left of right of the x point
	// (1 and -1) respectively
	if(rect.x()<x) return 2;
	else if (rect.x()>x) return -2;
	else return 0;
}

QRect PowerUp::getRect()
{
	return rect;
}

QImage &PowerUp::getImage()
{
	return image;
}

// 1 extra life
P1::P1()
{
	//load the correct image for powerUp type one
	image.load("images/1up.png");
	
	rect = image.rect();
}
void P1::powerShip(SpaceWars * spaceWar)
{
	spaceWar->lives++;
}

// 3 extra life
P2::P2() 
{
	//load the correct image for powerUp type two
	image.load("images/3up.png");
	
	rect = image.rect();
}
void P2::powerShip(SpaceWars * spaceWar)
{
	spaceWar->lives += 3;
}

// Lose one life
P3::P3()
{
	//load the correct image for powerUp type three
	image.load("images/deathshroom.png");
	
	rect = image.rect();
}
void P3::powerShip(SpaceWars * spaceWar)
{
	if(!(spaceWar->godMode || spaceWar->shieldFlag))
		spaceWar->deathShroom = true;

	if(spaceWar->shieldFlag)
		spaceWar->shieldFlag = false;

	if(spaceWar->lives==0)
	{
		spaceWar->gameOver = true;

        // if not on screen, build end game buttons
        if(!spaceWar->restartButton->isVisible())
            spaceWar->buildEndGameButtons();
	}
}

// Double current points
P4::P4()
{
	//load the correct image for powerUp type one
	image.load("images/2x.png");
	
	rect = image.rect();
}
void P4::powerShip(SpaceWars * spaceWar)
{
	if(spaceWar->score >= 4294967295ll/2)
		spaceWar->score = 4294967295ll;
	else	
		spaceWar->score *= 2;
}
// makes power up follow player's location
void P4::move(int x)
{
	if(rect.top()  < 635)
		rect.moveTo((rect.left() + x), (rect.top() + 2));
	else
		rect.moveTo((rect.left() + x), (rect.top() - 2));
}


// Lose all points
P5::P5()
{
	//load the correct image for powerUp type one
	image.load("images/nopoints.png");
	
	rect = image.rect();
}
void P5::powerShip(SpaceWars * spaceWar)
{
	spaceWar->score = 0;
}

// Victory
P6::P6()
{
	//load the correct image for powerUp type one
	image.load("images/pow.png");
	
	rect = image.rect();
}
void P6::powerShip(SpaceWars * spaceWar)
{
	spaceWar->gameWon = true;

    if(!spaceWar->restartButton->isVisible())
        spaceWar->buildEndGameButtons();
}


// +10 points
P7::P7()
{
	//load the correct image for powerUp type one
	image.load("images/10+.png");
	
	rect = image.rect();
}
void P7::powerShip(SpaceWars * spaceWar)
{
	if(spaceWar->score >= 4294967295ll-10)
		spaceWar->score = 4294967295ll;
	else	
		spaceWar->score += 10;
}
// makes power up follow player's location
void P7::move(int x)
{
	if(rect.top()  < 635)
		rect.moveTo((rect.left() + x), (rect.top() + 2));
	else
		rect.moveTo((rect.left() + x), (rect.top() - 2));
}

// +100 points
P8::P8()
{
	//load the correct image for powerUp type one
	image.load("images/100+.png");
	
	rect = image.rect();
}
void P8::move(int x)
{
	if(rect.top() < 635)
		rect.moveTo((rect.left() + x), (rect.top() + 2));
	else
		rect.moveTo((rect.left() + x), (rect.top() - 2));
}
// makes power up follow player's location
void P8::powerShip(SpaceWars * spaceWar)
{
	if(spaceWar->score>= 4294967295ll-100)
		spaceWar->score = 4294967295ll;
	else	
		spaceWar->score += 100;
}

// freeze enemies for ...
P9::P9()
{
	//load the correct image for powerUp type one
	image.load("images/freeze.png");
	
	rect = image.rect();
}
void P9::powerShip(SpaceWars * spaceWar)
{
	spaceWar->freezeFlag = true;
}

// level up
P10::P10()
{
	//load the correct image for powerUp type one
	image.load("images/levelup2.png");
	
	rect = image.rect();
}
void P10::powerShip(SpaceWars * spaceWar)
{
	if(spaceWar->level < 12)
		spaceWar->nextLevel = true;
}

// level down
P11::P11()
{
	//load the correct image for powerUp type one
	image.load("images/leveldown2.png");
	
	rect = image.rect();
}
void P11::powerShip(SpaceWars * spaceWar)
{
	if(spaceWar->level > 0)
		spaceWar->prevLevel = true;
}

// Game Over
P12::P12()
{
	//load the correct image for powerUp type one
	image.load("images/Skull.png");
	
	rect = image.rect();
}
void P12::powerShip(SpaceWars * spaceWar)
{
	if(!(spaceWar->godMode))
	{
		spaceWar->deathShroom = true;
		spaceWar->lives = 1;
	}
}

// Temporary God Mode
P14::P14()
{
	//load the correct image for powerUp type one
	image.load("images/star.png");
	
	rect = image.rect();
}
void P14::powerShip(SpaceWars * spaceWar)
{
	if(!(spaceWar->godMode))
		spaceWar->tempGodFlag = true;
}


// Temporary shield till next hit
P15::P15()
{
	//load the correct image for powerUp type one
	image.load("images/goldshroom.png");
	
	rect = image.rect();
}
void P15::powerShip(SpaceWars * spaceWar)
{
	spaceWar->shieldFlag = true;
}

// triple shot
P16::P16()
{
	//load the correct image for powerUp type one
	image.load("images/mushroom.png");
	
	rect = image.rect();
}
void P16::powerShip(SpaceWars * spaceWar)
{
	spaceWar->tripleShot = true;
}
