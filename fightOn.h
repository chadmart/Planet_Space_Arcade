/*!\file fightOn.h
 * 
 * \brief Contians the fight on music class definitions
 * 
 * \Created by: Chad Martin
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/24/2012
 *
 * This class contians the fight on music class definitions.
 */
#ifndef FIGHTON_H
#define FIGHTON_H

#include <vector>
#include <string>
#include <QSound>

class FightOn
{

    public:
	FightOn();
	~FightOn();

    public:

	// returns ID of user
	unsigned int getID();

	// returns username of user
	string getUsername();

	// returns Year at USC of user
	int getYear();

	// sets Year at USC of user
	void setYear(unsigned int);

	// returns Year Name at USC of user
	string getYearName();

	// returns Highest score of user
	int getScore();

	// sets Highest score of user
	void setScore(unsigned int);
	
	// adds a friend to friends vector
 	void addFriend(unsigned int newId);

	// deletes a friend from the friends vector
	void deleteFriend(unsigned int oldId);

	void printFriends();

	void Reset();
	void copyInfo(User& other);

	// list of friend user IDs
	vector<unsigned int> friends; 

	bool Visited;
	int Level;
	User * Parent;

    private:
	// ID of user
	unsigned int ID;

	// Username of user
	string username;

	// Year at USC of user
	unsigned int year;

	// Highest score of user
	unsigned int score;
};


#endif