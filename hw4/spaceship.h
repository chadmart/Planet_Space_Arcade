/*!\file spaceship.h
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
#ifndef SPACESHIP_H
#define SPACESHIP_H


#include <QRect>
#include <QImage>

class Spaceship
{
   public:
	Spaceship();
	~Spaceship();

   public:
	// load the spaceship image when the spaceship object is created
	// and move the spaceship to an initial position
	void resetState();

	// move the spaceship to the left
	void moveLeft(int);

	// move the spaceship to the right
	void moveRight(int);

	// move the spaceship up
	void moveUp(int);

	// move the spaceship down
	void moveDown(int);

	QRect getRect();
	QImage &getImage();

   private:
	QRect rect;
	QImage image;
};

#endif
