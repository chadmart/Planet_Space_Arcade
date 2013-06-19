/*!\file badguy.h
 * 
 * \brief Contians the badguy class and sub-classes
 * 
 * \Created by: Spencer Moran 
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/14/2012
 *
 * This class contians the badguy class and sub-classes.
 */
#ifndef BADGUY_H
#define BADGUY_H

#include <QRect>
#include <QImage>

// Abstract base class to all badguys and bosses
class Badguy
{

   public:
	Badguy();	
	~Badguy();

   public:
	// returns true if off screen
	bool offScreen();
	
	// Pure Virtual member function
	// moves the badguy in the specified pattern
	virtual void move() = 0;

	// sets the initial location and
	// moves the badguy to x,y location provided
	void setLocation(int, int);

	// sets active flag
	void setActive(bool);
	
	// returns active flag's value
	bool isActive();
	
	// returns exploded flag's value
	bool isExploded();

	// sets exploded flag
	void setExploded(bool);
	
	// returns exploding flag's value
	bool isExploding();

	// sets explodeing flag
	void setExploding(bool);

	// reloades specific image file based on sub-class type
	virtual void reloadImage();

	// returns badguy's hit points
	int getHitPoints();

	// lowers badguys hit points
	void lowerHitPoints(int);

	QRect getRect();
	QImage &getImage();


   protected:

	QRect rect;
	QImage image;

	// active flag
	bool active;
	
	// exploded flag
	bool badguyExploded;

	// exploding flag
	bool badguyExploding;

	// formation starting coordinates
	int intialX;
	int intialY; 
	
	// flags used to coordinate formation
	bool switchedXDir;
	bool switchedYDir;

	// baguy's hit points
	// zero hit points means next hit dead
	int hitPoints;
};

// level 1-2 badguys
class B1 : public Badguy
{
	public:
		B1();
		~B1();
		void reloadImage();

		// right to left movement formation
		void move();
};
//level 2-3 badguys
class B1b : public B1
{
	public:
		B1b();
		~B1b();
		void reloadImage();
		// uses movement formation of B1
};

// level 4-6 badguys
class B2 : public Badguy
{
	public:
		B2();
		~B2();
		void reloadImage();
		
		// square movement formation
		void move();
};
// Level 5-6 Badguys
class B2b : public B2
{
	public:
		B2b();
		~B2b();
		void reloadImage();
		// uses movement formation of B2
};

//level 7-9 badguys
class B3 : public Badguy
{
	public:
		B3();
		~B3();
		void reloadImage();

		// X movement formation
		void move();
};
//level 8-9 badguys
class B3b : public B3
{
	public:
		B3b();
		~B3b();
		void reloadImage();
		// uses movement formation of B3
};

//level 9 badguys
class B3c : public B3
{
	public:
		B3c();
		~B3c();
		void reloadImage();
		// uses movement formation of B3
};

//level 10-12 badguys
class B4 : public Badguy
{
	public:
		B4();
		~B4();
		void reloadImage();

		// X movement formation
		void move();
};
//level 10-12 badguys
class B4b : public B4
{
	public:
		B4b();
		~B4b();
		void reloadImage();
		// uses movement formation of B4
};
//level 12 badguys
class B4c : public B4
{
	public:
		B4c();
		~B4c();
		void reloadImage();
		// uses movement formation of B4
};


// Level 3 Boss
class Boss1 : public Badguy
{
	public:
		Boss1();
		~Boss1();

		//right to left movement formation
		void move(); 
};

// Level 6 Boss
class Boss2 : public Badguy
{
	public:
		Boss2();
		~Boss2();

		//right to left movement formation
		void move();
};

// Level 9 Boss
class Boss3 : public Badguy
{
	public:
		Boss3();
		~Boss3();

		// right to left movement formation 
		// with up and down wiggle
		void move();
	private:
		// allows up and odwn wiggle
		int wiggle;
		int wiggleCount;
};

// Level 12 Boss
class Boss4 : public Badguy
{
	public:
		Boss4();
		~Boss4();

		// right to left movement formation 
		// with up and down wiggle
		void move();
	private:
		// allows up and odwn wiggle
		int wiggle;
		int wiggleCount;
};

#endif
