/*!\file bullet.cpp
 * 
 * \brief Contians the bullet class and sub-classes
 * 
 * \Created by: Spencer Moran 
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/14/2012
 *
 * This class contians the bullet class and sub-classes.
 */
#include "bullet.h"

Bullet::Bullet()
{
	//set default ID
	ID = 0;
}

Bullet::~Bullet()
{
	// John Connor: Jesus, you were gonna kill that guy. 
	// The Terminator: Of course; I'm a terminator. 
}

QRect Bullet::getRect()
{
	return rect;
}

QImage &Bullet::getImage()
{
	return image;
}

void Bullet::move()
{
	//move the bullet up the screen
	//used for the player controlled spaceship
	rect.moveTo(rect.left(), (rect.top() - 2));
}

void Bullet::moveLeft()
{
	//moves the bullet left
	//used for the player controlled spaceship during triple shot
	rect.moveTo((rect.left()-1), (rect.top() + 0));
}

void Bullet::moveRight()
{
	//move the bullet right
	//used for the player controlled spaceship during triple shot
	rect.moveTo((rect.left()+1), (rect.top() + 0));
}

void Bullet::moveDown()
{
	//move the bullet down the screen
	//used for the badguys
	rect.moveTo(rect.left(), (rect.top() + 2));
}

void Bullet::moveDown(int x)
{
	// move the bullet down the screen
	// used for the boss 
	rect.moveTo((rect.left() + x), (rect.top() + 2));
}

// used to track location of player
// Parameter x: the x coordinate of the good space ship
// returns whether the item is to the left of right of the x point
// (1 and -1) respectively
int Bullet::trackDir(int x)	
{				
	if(rect.x()<x) return 1;
	else if (rect.x()>x) return -1;
	else return 0;
}

bool Bullet::offScreen()
{
	//returns true if the bullet is offscreen
	if (rect.bottom() <= 0 || rect.top() >= 800)
		return true;
	else
		return false;
}

// returns ID of bullet
// used in triple shot logic
int Bullet::getID()
{
	return ID;
}

//The player controlled spaceship's bullets
GoodBullet::GoodBullet(int x, int y, int bID)
{
	//load the image for the spaceship bullet
	image.load("images/goodbullet.png");
	
	//set the bullet rectangle above the spaceship
	rect = image.rect();
	rect.setLeft(x);
	rect.setBottom(y);
	rect.setTop(y - 20);
	rect.setHeight(20);
	rect.setWidth(4);
	
	ID = bID;
}

//The badguys' bullets
BadBullet::BadBullet(int x, int y)
{
	//load the image for the badguy bullet
	image.load("images/bullet.png");
	
	//set the bullet rectangle below the badguy
	rect = image.rect();
	rect.setLeft(x);
	rect.setBottom(y + 20);
	rect.setTop(y);
	rect.setHeight(20);
	rect.setWidth(4);
}

//The bosses' bullets
BossBullet::BossBullet(int x, int y)
{
	//load the image for the badguy bullet
	image.load("images/bossbullet.png");
	
	//set the bullet rectangle below the badguy
	rect = image.rect();
	rect.setLeft(x);
	rect.setBottom(y + 51);
	rect.setTop(y);
	rect.setHeight(51);
	rect.setWidth(31);

	//sets index to default value
	index = 1;
}
BossBullet::~BossBullet()
{}

//increments index
void BossBullet::addIndex()
{
	index++;
}

//resets index to 1
void BossBullet::resetIndex()
{
	index = 1;
}

//returns index
int BossBullet::getIndex()
{
	return index;
}
