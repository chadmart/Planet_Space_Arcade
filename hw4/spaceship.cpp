/*!\file spaceship.cpp
 * 
 * \brief Contians the user controlled spaceship class
 * 
 * \Created by: Spencer Moran 
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/14/2012
 *
 * This class contians the controlled spaceship class.
 */
#include "spaceship.h"
#include <iostream>

Spaceship::Spaceship()
{
	//load the spaceship image when the spaceship object is created
	//and move the spaceship to the initial location
	resetState();
}

Spaceship::~Spaceship()
{
	//The Terminator: Hasta la vista, baby.
}

void Spaceship::moveLeft(int left)
{
	//move the spaceship to the left
	if (rect.left() >= 2)
		rect.moveTo(left, rect.top());
}

void Spaceship::moveRight(int right)
{
	//move the spaceship to the right
	if (rect.right() <= 798)
		rect.moveTo(right, rect.top());
}

void Spaceship::moveUp(int up)
{
	//move the spaceship up
	if (rect.top() >= 2)
		rect.moveTo(rect.left(), up);		
}

void Spaceship::moveDown(int down)
{
	//move the spaceship down
	if (rect.bottom() <= 698)
		rect.moveTo(rect.left(), down);		
}

void Spaceship::resetState()
{
	//load the spaceship image when the spaceship object is created
	image.load("images/spaceship.png");
	rect = image.rect();

	//move the spaceship to an initial position
	rect.moveTo(350, 633);
}

QRect Spaceship::getRect()
{
	return rect;
}

QImage &Spaceship::getImage()
{
	return image;
}
