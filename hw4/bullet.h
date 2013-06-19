/*!\file bullet.h
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
#ifndef BULLET_H
#define BULLET_H

#include <QRect>
#include <QImage>

class Bullet
{

    public:
	Bullet();
	~Bullet();

    public:
	QRect getRect();
	QImage &getImage();

	//move the bullet up the screen
	//used for the player controlled spaceship
	void move();

	//moves the bullet left
	//used for the player controlled spaceship during triple shot
	void moveLeft();

	//move the bullet right
	//used for the player controlled spaceship during triple shot
	void moveRight();

	//move the bullet down the screen
	//used for the badguys
	void moveDown();

	//move the bullet down the screen and towards the player
	//used for the bosses
	//parameter should be result of trackDir 
	//when passing in the player's x coordinate
	void moveDown(int x);

	// used to track location of player
	// Parameter x: the x coordinate of the good space ship
	int trackDir(int x);

	// returns true if off screen
	bool offScreen();

	// returns ID of bullet
	// used in triple shot logic
	int getID();

    protected:
	// ID of Bullet
	// used in triple shot logic
	int ID;

	QRect rect;
	QImage image;
};

//The player controlled spaceship's bullets
class GoodBullet : public Bullet
{
	public:
		GoodBullet(int, int, int);
		~GoodBullet();
};

//The badguys' bullets
class BadBullet : public Bullet
{
	public:
		BadBullet(int, int);
		~BadBullet();
};

//The bosses' bullets
class BossBullet : public Bullet
{
	public:
		BossBullet(int, int);
		~BossBullet();

		//index functions used when exploding the boss bullets
		  //increments index
		    void addIndex();
		  //resets index to 1
		    void resetIndex();
		  //returns index
		    int getIndex();
	private:
		//used when exploding the boss bullets
		int index;
};

#endif
