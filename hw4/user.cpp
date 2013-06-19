/*!\file user.cpp
 * 
 * \brief Contians the user class implementations 
 * 
 * \Created by: Chad Martin
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/26/2012
 *
 * This class contians the user class implementations.
 */
#include "user.h"

#include <vector>
#include <string>

using namespace std;

User::User(int id, string name, int y)
{
	ID = id;
	username = name;
	this->setYear(y);
	score = 0;
	reset();
}
User::User(User &other)
{
	this->copyInfo(other);
}

User::~User()
{
}

void User::copyInfo(User& other)
{
	ID = other.ID;
	username = other.username;
	this->setYear(other.year);
	this->setScore(other.score);

	friends.clear();
	for(unsigned int i = 0; i < other.friends.size() ;i++)
	{
		this->friends.push_back(other.friends.at(i));
	}
 
	this->visited = other.visited;
	this->level = other.level;
	this->parent = other.parent;
}

// returns ID of user
unsigned int User::getID()
{
	return ID;
}

// returns username of user
string User::getUsername()
{
	return username;
}

// returns Year at USC of user
unsigned int User::getYear()
{
	return year;
}

// returns YearName at USC of user
string User::getYearName()
{
	string y;

	if(year==1)
		y = "Freshman";
	else if(year==2)
		y = "Sophomore";
	else if(year==3)
		y = "Junior";
	else if(year==4)
		y = "Senior";
	else //if(year==5)
		y = "Alumni";

	return y;
}

// sets Year at USC of user
void User::setYear(unsigned int y)
{
	if(y > 0 && y < 6)
		year = y;
}

// returns Highest score of user
unsigned int User::getScore()
{
	return score;
}

// sets Highest score of user
void User::setScore(unsigned int x)
{
	score = x;
}


// adds a friend to friends vector
void User::addFriend(unsigned int newId)
{
	friends.push_back(newId);
}

// deletes a friend from the friends vector
void User::deleteFriend(unsigned int oldId)
{
	for(unsigned int i  = 0; i < friends.size(); i++)
	{
		if(oldId == friends.at(i))
		{
			friends.erase(friends.begin() +i);
		}
	}
}

// resets level, parent pointer, and visited flag
void User::reset()
{ 
	visited = false; 
	level = 0; 
	parent = NULL; 
}
