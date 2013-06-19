/*!\file badguy.cpp
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
#include "badguy.h"
#include <iostream>

Badguy::Badguy()
{
	//set the exploded flag to false for each badguy that is created
	setExploded(FALSE);

	// set default values
	intialX = 0;
	intialY = 0; 
	switchedXDir = false;
	switchedYDir = false;
	// zero hit points means next hit dead
	hitPoints = 0;
}

Badguy::~Badguy()
{
	//The Terminator: Come with me if you want to live! 
}

// sets exploded flag
void Badguy::setExploded(bool b)
{
	//set the exploded flag
	badguyExploded = b;
}

// returns exploded flag's value
bool Badguy::isExploded()
{
	//return the exploded flag
	return badguyExploded;
}

// sets explodeing flag
void Badguy::setExploding(bool b)
{
	//set the exploded flag
	badguyExploding = b;
}

// returns exploding flag's value
bool Badguy::isExploding()
{
	//return the exploded flag
	return badguyExploding;
}

// returns true if off screen
bool Badguy::offScreen()
{
	//returns true if the badguy is out of bounds
	//otherwise return false
	if (rect.bottom() < -500)
		return true;
	else if (rect.top() > 1300)
		return true;
	else if (rect.left() < -500)
		return true;
	else if (rect.right() > 1200)
		return true;
	else
		return false;
}

// sets active flag
void Badguy::setActive(bool d)
{
	//set the badguy to active
	active = d;
}

// returns active flag's value
bool Badguy::isActive()
{
	//return whether or not the badguy is active
	return active;
}

// sets the initial location and
// moves the badguy to x,y location provided
void Badguy::setLocation(int x, int y)
{
	intialX = x-50;
	intialY = y+500; 

	//move the badguy to the specified location
	rect.moveTo(x, y);
}

// reloades specific image file based on sub-class type
void Badguy::reloadImage()
{
	//load the correct image for badguy type one
	image.load("images/badguy.png");
	
	rect = image.rect();
}

// returns badguy's hit points
int Badguy::getHitPoints()
{
	return hitPoints;
}

// lowers badguys hit points
void Badguy::lowerHitPoints(int x)
{
	hitPoints -= x;
}

QRect Badguy::getRect()
{
	return rect;
}
QImage &Badguy::getImage()
{
	return image;
}

// level 1-2 badguys
B1::B1()
{
	//load the correct image for badguy type one
	image.load("images/badguy.png");
	
	rect = image.rect();
}

B1::~B1()
{}
void B1::reloadImage()
{
	//load the correct image for badguy type one
	image.load("images/badguy.png");
	
	rect = image.rect();
}
// right to left movement formation
void B1::move()
{
	if(rect.top() < intialY)
		rect.moveTo(rect.left(), (rect.top() + 2));
	else if(rect.left() == intialX && switchedXDir)
	{
		switchedXDir = false;
		rect.moveTo((rect.left()+2), (rect.top() + 0));
	}
	else if(rect.left() == intialX+250 && !switchedXDir)
	{
		switchedXDir = true;
		rect.moveTo((rect.left()-2), (rect.top() + 0));
	}
	else if(rect.left() > intialX && !switchedXDir)
		rect.moveTo((rect.left()+2), (rect.top() + 0));
	else if(rect.left() < intialX+250 && switchedXDir)
		rect.moveTo((rect.left()-2), (rect.top() + 0));
}

//level 2-3 badguys
B1b::B1b()
{
	//load the correct image for badguy type one
	image.load("images/badguy1b.png");
	
	rect = image.rect();

	hitPoints = 1;
}
B1b::~B1b()
{}
void B1b::reloadImage()
{
	//load the correct image for badguy type one
	image.load("images/badguy1b.png");
	
	rect = image.rect();
}

// level 4-6 badguys
B2::B2() 
{
	//load the correct image for badguy type two
	image.load("images/badguy2.png");
	
	rect = image.rect();

	hitPoints = 1;
}
B2::~B2()
{}
void B2::reloadImage()
{
	//load the correct image for badguy type one
	image.load("images/badguy2.png");
	
	rect = image.rect();
}
// square movement formation
void B2::move()
{
	if(rect.top() < intialY)
		rect.moveTo(rect.left(), (rect.top() + 2));
	else if(!switchedXDir && !switchedYDir && rect.left() == intialX+250)
	{
		switchedYDir = true;
		rect.moveTo((rect.left()+0), (rect.top() + 2));
	}
	else if(!switchedXDir && switchedYDir && rect.top() == intialY+150)
	{
		switchedXDir = true;
		rect.moveTo((rect.left()-2), (rect.top() + 0));
	}
	else if(switchedXDir && switchedYDir && rect.left() == intialX)
	{	
		switchedYDir = false;
		rect.moveTo((rect.left()+0), (rect.top() - 2));
	}
	else if(switchedXDir && !switchedYDir && rect.top() == intialY)
	{	
		switchedXDir = false;
		rect.moveTo((rect.left()+2), (rect.top() + 0));
	}
	else if(rect.left() > intialX && !switchedXDir && !switchedYDir)
	{
		rect.moveTo((rect.left()+2), (rect.top() + 0));	
	}
	else if(!switchedXDir && switchedYDir && rect.top() > intialY)
	{
		rect.moveTo((rect.left()+0), (rect.top() + 2));
	}
	else if(rect.left() < intialX+250 && switchedXDir && switchedYDir)
	{
		rect.moveTo((rect.left()-2), (rect.top() + 0));
	}
	else if(switchedXDir && !switchedYDir && rect.top() < intialY+150)
	{
		rect.moveTo((rect.left()+0), (rect.top() - 2));
	}
}
// Level 5-6 Badguys
B2b::B2b() 
{
	//load the correct image for badguy type two
	image.load("images/badguy2b.png");
	
	rect = image.rect();

	hitPoints = 2;
}
B2b::~B2b()
{}
void B2b::reloadImage()
{
	//load the correct image for badguy type one
	image.load("images/badguy2b.png");
	
	rect = image.rect();
}

//level 7-9 badguys
B3::B3()
{
	//load the correct image for badguy type three
	image.load("images/badguy3.png");
	
	rect = image.rect();

	hitPoints = 1;
}
B3::~B3()
{}
void B3::reloadImage()
{
	//load the correct image for badguy type one
	image.load("images/badguy3.png");
	
	rect = image.rect();
}

// X movement formation
void B3::move()
{
	if(rect.top() < intialY && rect.left() == intialX)
		rect.moveTo(rect.left(), (rect.top() + 2));
	else if(rect.top() < intialY)
		rect.moveTo((rect.left() - 2), (rect.top() + 2));
	else if (rect.top() == intialY && rect.left() == intialX)
	{
		switchedYDir = false;
		rect.moveTo((rect.left() + 2), (rect.top() + 2));
	}
	else if(rect.left() == intialX+250 && !switchedYDir && !switchedXDir)
	{
		switchedXDir = true;
		rect.moveTo((rect.left()+0), (rect.top() - 2));
	}
	else if(rect.top() == intialY &&  !switchedYDir &&  switchedXDir)
	{
		switchedYDir = true;
		rect.moveTo((rect.left()-2), (rect.top() + 2));
	}
	else if(rect.left() == intialX &&  switchedYDir &&  switchedXDir)
	{
		switchedXDir = false;
		rect.moveTo((rect.left()+0), (rect.top() - 2));
	}
	else if (rect.top() > intialY && rect.left() > intialX && !switchedXDir && !switchedYDir)
	{
		rect.moveTo((rect.left() + 2), (rect.top() + 2));
	}
	else if (rect.top() > intialY && rect.left() == intialX+250 && switchedXDir && !switchedYDir)
	{
		rect.moveTo((rect.left() + 0), (rect.top() - 2));
	}
	else if (rect.top() > intialY && rect.left() > intialX && switchedXDir && switchedYDir)
	{
		rect.moveTo((rect.left() - 2), (rect.top() + 2));
	}
	else if (rect.top() > intialY && rect.left() == intialX && !switchedXDir && switchedYDir)
	{
		rect.moveTo((rect.left() + 0), (rect.top() - 2));
	}
}

//level 8-9 badguys
B3b::B3b()
{
	//load the correct image for badguy type three
	image.load("images/badguy3b.png");
	
	rect = image.rect();

	hitPoints = 2;
}
B3b::~B3b()
{}
void B3b::reloadImage()
{
	//load the correct image for badguy type one
	image.load("images/badguy3b.png");
	
	rect = image.rect();
}

//level 9 badguys
B3c::B3c()
{
	//load the correct image for badguy type three
	image.load("images/badguy3c.png");
	
	rect = image.rect();

	hitPoints = 3;
}
B3c::~B3c()
{}
void B3c::reloadImage()
{
	//load the correct image for badguy type one
	image.load("images/badguy3c.png");
	
	rect = image.rect();
}

//level 10-12 badguys
B4::B4()
{
	//load the correct image for badguy type three
	image.load("images/badguy4.png");
	
	rect = image.rect();

	hitPoints = 2;
}
B4::~B4()
{}
void B4::reloadImage()
{
	//load the correct image for badguy type one
	image.load("images/badguy4.png");
	
	rect = image.rect();
}

// X movement formation
void B4::move()
{
	if(rect.top() < intialY && rect.left() == intialX)
		rect.moveTo(rect.left(), (rect.top() + 2));
	else if(rect.top() < intialY)
		rect.moveTo((rect.left() - 2), (rect.top() + 2));
	else if (rect.top() == intialY && rect.left() == intialX)
	{
		switchedYDir = false;
		rect.moveTo((rect.left() + 2), (rect.top() + 2));
	}
	else if(rect.left() == intialX+250 && !switchedYDir && !switchedXDir)
	{
		switchedXDir = true;
		rect.moveTo((rect.left()+0), (rect.top() - 2));
	}
	else if(rect.top() == intialY &&  !switchedYDir &&  switchedXDir)
	{
		switchedYDir = true;
		rect.moveTo((rect.left()-2), (rect.top() + 2));
	}
	else if(rect.left() == intialX &&  switchedYDir &&  switchedXDir)
	{
		switchedXDir = false;
		rect.moveTo((rect.left()+0), (rect.top() - 2));
	}
	else if (rect.top() > intialY && rect.left() > intialX && !switchedXDir && !switchedYDir)
	{
		rect.moveTo((rect.left() + 2), (rect.top() + 2));
	}
	else if (rect.top() > intialY && rect.left() == intialX+250 && switchedXDir && !switchedYDir)
	{
		rect.moveTo((rect.left() + 0), (rect.top() - 2));
	}
	else if (rect.top() > intialY && rect.left() > intialX && switchedXDir && switchedYDir)
	{
		rect.moveTo((rect.left() - 2), (rect.top() + 2));
	}
	else if (rect.top() > intialY && rect.left() == intialX && !switchedXDir && switchedYDir)
	{
		rect.moveTo((rect.left() + 0), (rect.top() - 2));
	}
}
//level 10-12 badguys
B4b::B4b()
{
	//load the correct image for badguy type three
	image.load("images/badguy4b.png");
	
	rect = image.rect();

	hitPoints = 3;
}
B4b::~B4b()
{}
void B4b::reloadImage()
{
	//load the correct image for badguy type one
	image.load("images/badguy4b.png");
	
	rect = image.rect();
}

//level 12 badguys
B4c::B4c()
{
	//load the correct image for badguy type three
	image.load("images/badguy4c.png");
	
	rect = image.rect();

	hitPoints = 4;
}
B4c::~B4c()
{}
void B4c::reloadImage()
{
	//load the correct image for badguy type one
	image.load("images/badguy4c.png");
	
	rect = image.rect();
}

// Level 3 Boss
Boss1::Boss1()
{
	//load the correct image for badguy type one
	image.load("images/boss1.png");
	
	rect = image.rect();

	hitPoints = 9;
}
Boss1::~Boss1()
{}
//right to left movement formation
void Boss1::move()
{
	if(rect.top() < intialY-24)
		rect.moveTo(rect.left(), (rect.top() + 2));
	else if(rect.left() == intialX && switchedXDir)
	{
		switchedXDir = false;
		rect.moveTo((rect.left()+2), (rect.top() + 0));
	}
	else if(rect.left() == intialX+450 && !switchedXDir)
	{
		switchedXDir = true;
		rect.moveTo((rect.left()-2), (rect.top() + 0));
	}
	else if(rect.left() > intialX && !switchedXDir)
		rect.moveTo((rect.left()+2), (rect.top() + 0));
	else if(rect.left() < intialX+450 && switchedXDir)
		rect.moveTo((rect.left()-2), (rect.top() + 0));
}

// Level 6 Boss
Boss2::Boss2()
{
	//load the correct image for badguy type one
	image.load("images/boss2.png");
	
	rect = image.rect();

	hitPoints = 15;
}
Boss2::~Boss2()
{}
//right to left movement formation
void Boss2::move()
{
	if(rect.top() < intialY-20)
		rect.moveTo(rect.left(), (rect.top() + 2));
	else if(rect.left() == intialX && switchedXDir)
	{
		switchedXDir = false;
		rect.moveTo((rect.left()+2), (rect.top() + 0));
	}
	else if(rect.left() == intialX+450 && !switchedXDir)
	{
		switchedXDir = true;
		rect.moveTo((rect.left()-2), (rect.top() + 0));
	}
	else if(rect.left() > intialX && !switchedXDir)
		rect.moveTo((rect.left()+2), (rect.top() + 0));
	else if(rect.left() < intialX+450 && switchedXDir)
		rect.moveTo((rect.left()-2), (rect.top() + 0));
}

// Level 9 Boss
Boss3::Boss3()
{
	//load the correct image for badguy type one
	image.load("images/boss3.png");
	
	rect = image.rect();

	hitPoints = 20;

	wiggle = 2;
	wiggleCount = 0;
}
Boss3::~Boss3()
{}

// right to left movement formation 
// with up and down wiggle
void Boss3::move()
{

	if(wiggleCount == 25)
	{	
		wiggle *= -1;
		switchedYDir = true;
		wiggleCount = 0;
	}
	else
		wiggleCount++;
	

	if(rect.top() < intialY-16)
		rect.moveTo(rect.left(), (rect.top() + 2));
	else if(rect.top() == intialY-16)
		rect.moveTo(rect.left(), (rect.top() + 4));
	else if(rect.left() == intialX && switchedXDir)
	{
		switchedXDir = false;
		rect.moveTo((rect.left()+2), (rect.top() + wiggle));
	}
	else if(rect.left() == intialX+450 && !switchedXDir)
	{
		switchedXDir = true;
		rect.moveTo((rect.left()-2), (rect.top() + wiggle));
	}
	else if(rect.left() > intialX && !switchedXDir)
		rect.moveTo((rect.left()+2), (rect.top() + wiggle));
	else if(rect.left() < intialX+450 && switchedXDir)
		rect.moveTo((rect.left()-2), (rect.top() + wiggle));
}

// Level 12 Boss
Boss4::Boss4()
{
	//load the correct image for badguy type one
	image.load("images/bossFinal.png");
	
	rect = image.rect();

	hitPoints = 25;

	wiggle = 2;
	wiggleCount = 0;
}
Boss4::~Boss4()
{}

// right to left movement formation 
// with up and down wiggle
void Boss4::move()
{
	if(wiggleCount == 25)
	{	
		wiggle *= -1;
		switchedYDir = true;
		wiggleCount = 0;
	}
	else
		wiggleCount++;
	

	if(rect.top() < intialY-16)
		rect.moveTo(rect.left(), (rect.top() + 2));
	else if(rect.top() == intialY-16)
		rect.moveTo(rect.left(), (rect.top() + 4));
	else if(rect.left() == intialX && switchedXDir)
	{
		switchedXDir = false;
		rect.moveTo((rect.left()+2), (rect.top() + wiggle));
	}
	else if(rect.left() == intialX+450 && !switchedXDir)
	{
		switchedXDir = true;
		rect.moveTo((rect.left()-2), (rect.top() + wiggle));
	}
	else if(rect.left() > intialX && !switchedXDir)
		rect.moveTo((rect.left()+2), (rect.top() + wiggle));
	else if(rect.left() < intialX+450 && switchedXDir)
		rect.moveTo((rect.left()-2), (rect.top() + wiggle));
}

