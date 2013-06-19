/*!\file user.h
 * 
 * \brief Contians the user class definitions
 * 
 * \Created by: Chad Martin
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/26/2012
 *
 * This class contians the user class definitions.
 */
#ifndef USER_H
#define USER_H

#include <vector>
#include <string>

using namespace std;

class User
{

    public:
	User(int , string ,int);
	User(User& other);
	~User();

    public:

	// returns ID of user
	unsigned int getID();

	// returns username of user
	string getUsername();

	// returns Year at USC of user
	unsigned int getYear();

	// sets Year at USC of user
	void setYear(unsigned int);

	// returns Year Name at USC of user
	string getYearName();

	// returns Highest score of user
	unsigned int getScore();

	// sets Highest score of user
	void setScore(unsigned int);
	
	// adds a friend to friends vector
 	void addFriend(unsigned int newId);

	// deletes a friend from the friends vector
	void deleteFriend(unsigned int oldId);

	// resets level, parent pointer, and visited flag
	void reset();

	// copies info from other user
	void copyInfo(User& other);


    private:
	// Allows use of private members in the SpaceWars class
	friend class SpaceWars;

	// if user has been visited by current algorithm
	bool visited;

	// level of friendships from current user to this user
	// level is set during BFS search
	int level;

	// pointer to user that is one level up in the shortest path
	// parent is set during BFS search
	User * parent;

	// list of friend user IDs
	vector<unsigned int> friends; 

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
