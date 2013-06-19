/*!\file powerup.h
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
#ifndef POWERUP_H
#define POWERUP_H
#include "spacewars.h"

#include <QRect>
#include <QImage>

class SpaceWars;

//abstract base class to all power ups
class PowerUp
{

   public:
	PowerUp() {}	
	~PowerUp() {}

   public:
	// returns true if off screen
	bool offScreen();
	
	// moves power ups down screen
	virtual void move(int);
	
	// sets location of power up
	void setLocation(int, int);

	// used to track location of player
	// Parameter x: the x coordinate of the good space ship
	int trackDir(int x);

	// sets active flag
	void setActive(bool);
	
	// returns active flag's value
	bool isActive();

	// Pure Virtual member function
	// carries out Power up's task defined in the subclasses
	// Parameter spaceWar: pointer to spaceWar object (the game logic)
	virtual void powerShip(SpaceWars * spaceWar) = 0;

	QRect getRect();
	QImage &getImage();


   protected:
	// active flag
	bool active;

	QRect rect;
	QImage image;

};


// 1 extra life
class P1 : public PowerUp
{
	public:
		P1();
		~P1();
		void powerShip(SpaceWars * spaceWar);
};

// 3 extra life
class P2 : public PowerUp
{
	public:
		P2();
		~P2();
		void powerShip(SpaceWars * spaceWar);
};

// Lose one life
class P3 : public PowerUp
{
	public:
		P3();
		~P3();
		void powerShip(SpaceWars * spaceWar);
};

// double current points
class P4 : public PowerUp
{
	public:
		P4();
		~P4();
		void move(int x); // makes power up follow player's location
		void powerShip(SpaceWars * spaceWar);
};

// lose all points
class P5 : public PowerUp
{
	public:
		P5();
		~P5();
		void powerShip(SpaceWars * spaceWar);
};

// victory 
class P6 : public PowerUp
{
	public:
		P6();
		~P6();
		void powerShip(SpaceWars * spaceWar);
};

// +10 points
class P7 : public PowerUp
{
	public:
		P7();
		~P7();
		void move(int x); // makes power up follow player's location
		void powerShip(SpaceWars * spaceWar);
};

// +100 points
class P8 : public PowerUp
{
	public:
		P8();
		~P8();
		void move(int x); // makes power up follow player's location
		void powerShip(SpaceWars * spaceWar);
};

// freeze enemies for ...
class P9 : public PowerUp
{
	public:
		P9();
		~P9();
		void powerShip(SpaceWars * spaceWar);
};

// level up
class P10 : public PowerUp
{
	public:
		P10();
		~P10();
		void powerShip(SpaceWars * spaceWar);
};

// level down
class P11 : public PowerUp
{
	public:
		P11();
		~P11();
		void powerShip(SpaceWars * spaceWar);
};

// Game Over
class P12 : public PowerUp
{
	public:
		P12();
		~P12();
		void powerShip(SpaceWars * spaceWar);
};

// Temporary God Mode
class P14 : public PowerUp
{
	public:
		P14();
		~P14();
		void powerShip(SpaceWars * spaceWar);
};

// Temporary shield till next hit
class P15 : public PowerUp
{
	public:
		P15();
		~P15();
		void powerShip(SpaceWars * spaceWar);
};

// Triple Shot
class P16 : public PowerUp
{
	public:
		P16();
		~P16();
		void powerShip(SpaceWars * spaceWar);
};
#endif
