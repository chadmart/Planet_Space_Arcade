/*!\file shield.cpp
 * 
 * \brief Contians the shield class and sub-classes
 * 
 * \Created by: Chad Martin
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/14/2012
 *
 * This class contians the shield class and sub-classes.
 */
#include "shield.h"

QRect Shield::getRect()
{
	return rect;
}
QImage &Shield::getImage()
{
	return image;
}

// Moves shield to specified location
// Parameters should be the z,y coordinates of the good spaceship
void Shield::move(int x, int y)
{
	rect.moveTo(x, y);
}

// Shield activated during god mode
GodShield::GodShield()
{
	//load the image for the shield
	image.load("images/shield2.png");
	
	//set the shield rectangle
	rect = image.rect();
}
GodShield::~GodShield()
{
	// John Connor: Is it dead? 
	// The Terminator: Terminated. 
}

// Shield activated during Temp Shield mode
TempShield::TempShield()
{
	//load the image for the badguy bullet
	image.load("images/shield1.png");
	
	//set the bullet rectangle below the badguy
	rect = image.rect();
}
TempShield::~TempShield()
{
	//The Terminator: My mission is to protect you. 
}
