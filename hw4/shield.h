/*!\file shield.h
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
#ifndef SHIELD_H
#define SHIELD_H

#include <QRect>
#include <QImage>

// base class to all shields
class Shield
{
    public:
	QRect getRect();
	QImage &getImage();

	// Moves shield to specified location
	// Parameters should be the z,y coordinates of the good spaceship
	void move(int x, int y);

    protected:
	QRect rect;
	QImage image;
};

// shield activated during god mode
class GodShield : public Shield
{
	public:
		GodShield();
		~GodShield();
};

// shield activated during Temp Shield mode
class TempShield : public Shield
{
	public:
		TempShield();
		~TempShield();
};


#endif
