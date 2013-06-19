/*!\file spacewars.h
 * 
 * \brief Contians the game logic definitions 
 * 
 * \Created by: Spencer Moran 
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/25/2012
 * 
 * This class contians the game logic for Planet Space.
 */

#ifndef SPACEWARS_H
#define SPACEWARS_H

#include "bullet.h"
#include "spaceship.h"
#include "badguy.h"
#include "powerup.h"
#include "shield.h"
#include "node.h"
#include "linkedlist.h"

#include <QWidget>
#include <QKeyEvent>
#include <QLineEdit>
#include <QFormLayout>
#include <QtCore>
#include <QtGui>
#include <QListView>
#include <QTableView>
#include <QTableWidget>
#include <QPushButton>

#include <list>
#include <vector>
#include <queue>

#include "user.h"
#include <fstream>

using namespace std;

//class prototype 
//tells compiler class will be defined later
class PowerUp;

class SpaceWars : public QWidget
{
   Q_OBJECT

   public:
	SpaceWars(QWidget *parent = 0);
	~SpaceWars();

   private:
	// Implementations located in spacewars.cpp

		// Paints the necessary object on the screen.
		void paintEvent(QPaintEvent *event);

		// Occurs when ever a timer event is called.
		void timerEvent(QTimerEvent *event);

		// Carries out the required actions for the specific key press
		void keyPressEvent(QKeyEvent *event);

		// Carries out the required actions for the specific key release
		void keyReleaseEvent(QKeyEvent *event);

		// Sets badguys up for the start of a new game
		void makeBadGuys();

		// Starts the timers and begins the actual game
		void startGame();

		// Pauses the Game
		void pauseGame();

		// Restarts the game
		void restartGame();

		// kills the timers and sets up variables to stop game play
		void endGame();

		// Respawns the players ship after a death
		void respawnShip();

		// Changes the level either up or down
		void changeLevel();

		// shoots bullets from the players ship
		void goodShipShoot();

		// deletes all active bullets
		void clearBullets();

		// reads in db.txt and validates it
		void readDB();

		// writes out to db.txt
		void writeDB();

		// resets markings sets each user to !visited, level = 0, parent=NULL 
		void resetMarkings();

		// Executes breadth first search on start user
		// Sets up each user's parent pointer and level member variables 
		// Parameter string start should be a valid username
		void BFSearch(string start);

		// sorts users by score
		void scoresSort();

		// updates relationCount after DB import
		void updateRelations();

		// checks for invalid or dangling friend references
		// if bad relationship detected, corruptDB = true
		void checkRelations();
	
		// returns true if user name only has alphanumeric or underscore characters
		bool validateUsername(string name);

		// build a list of the current users friends
		// used on users screen
		void addFriendBox();

		// sets up initial buttons
		void setUpInitialButtons();

		// sets up buttons for the users screen
		void buildUserScreenButtons();

		// hides the user screen buttons
		void hideUserScreenButtons();

		// sets up end game buttons
		void buildEndGameButtons();

		// returns style sheet string used on all buttons
		// parameter name is the partial path to button set
		// image files must follow a.png, b.png, c.png naming syntax
		QString buttonStyleSheetQS(const QString & name);

	// Implementations located in screens.cpp
		

		// Calls endGame and displays victory text and window
	 	void victoryScreen(QPainter &painter);

		// Calls endGame and displays game over text and window
		void gameOverScreen(QPainter &painter);

		// Displays paused screen text and window
		void pauseScreen(QPainter &painter);

		// Displays intro screen text and window
		void introScreen(QPainter &painter);
		
		// paints default start up menu text and window
		void startUpScreen(QPainter &painter);

		// paints log in screen menu text and window 
		void logInScreen(QPainter &painter);

		// paints users screen menu text and window 
		void usersScreen(QPainter &painter);

		// paints add user screen menu text, warnings, and window 
		void addUserScreen(QPainter &painter);

		// paints delete User screen menu text and window 
		void deleteUserScreen(QPainter &painter);
	
		// paints user list screen menu text and window 
		void userListScreen(QPainter &painter);
		
		// paints add friend screen menu text and window 
		void addFriendScreen(QPainter &painter);

		// paints delete friend screen menu text and window 
		void deleteFriendScreen(QPainter &painter);

		// paints shortest path screen menu text and window 
		void shortestPathScreen(QPainter &painter);

		// paints high scores screen menu text and window 
		void scoresScreen(QPainter &painter);

		// paints current user's friends high scores screen menu text and window 
		void friendsScoresScreen(QPainter &painter);

	// Implementations located in collisions.cpp

		// Checking for intersections between good and bad bullets
		void checkBulletsCollision();

		// Checking to see if spaceship is hit
		bool checkGoodShipHit();

		// Checking to see if badguys got hit
		bool checkBadShipHit(int badIndex, int j);

		// Check to see which collisions occured and set appropriate flags
		void checkCollisions(bool& spaceshipHit, bool badguyhit[4][3], bool& bossHit);

		// Checking to see if the Boss got hit
		bool checkBossShipHit();

		// Checking for intersections between good and boss bullets
		void checkBossBulletsCollision();

		// Checking for intersections between ship and powerUps
		void checkPowerUpsCollision();	

		//check to see if player spaceship collided with a badguy's ship
		//bool checkSpaceshipCollision(int badIndex, int j);

		//check to see if player spaceship collided with the Boss's ship
		//bool checkSpaceshipBossCollision();


	// Implementations located in explosions.cpp

		// Explodes player's spaceship
		void explodeSpaceship();

		// Explodes a BadGuys's ship
		void explodeBadguy(int i, int j);

		// Explodes the boss
		void explodeBoss();

		// Explodes the boss's bullets
		void explodeBossBullet(BossBullet * boss);

	// Implementations located in moveBullets.cpp

		// Calls functions to move all bullets and power ups
		void moveBullets();

		// Moves the player's bullets up the screen
		void moveGoodBullet();

		// Moves the BadGuys's bullets down the screen
		void moveBadBullet();

		// Moves the power ups down the screen
		void movePowerUps();

		// Moves the Boss's bullets down the screen and towards the player
		void moveBossBullet();

	// Implementations located in dropPowerUps.cpp

		// Drops a power up in the location of a Badguy 
		// that just got finished exploding
		// Parameters int i and int j are the [i][j] index of the badguy that just exploded
		void dropPowerUp(int i, int j);

		// Drops a power up in the location of a boss bullet 
		// that just got hit by a good bullet
		// Parameter Bullet * here is a pointer to a Boss bullet
		void dropPowerUp(Bullet * here);

		// Spawns a powerUp power from location (i,j)
		// Ability to choose power up and location to drop
		// Used in Cheat codes to test power ups
		// Parameter int i is x coordinate to drop from
		// Parameter int j is y coordinate to drop from
		// Parameter PowerUp * power is a pointer to the power up you want to drop
		void dropPowerUp(int i,int j, PowerUp * power);

		// Randomly chooses a power up to drop
		// may choose a NULL power up
		PowerUp* pickPowerUp();
 
   private:
	// Allows use of private members in the PowerUp class and sub-classes
	friend class PowerUp;
	friend class P1;
	friend class P2;
	friend class P3;
	friend class P4;
	friend class P5;
	friend class P6;
	friend class P7;
	friend class P8;
	friend class P9;
	friend class P10;
	friend class P11;
	friend class P12;
	friend class P14;
	friend class P15;
	friend class P16;

	// The players ship
	Spaceship *spaceship;

	// The boss activated every 3rd level
	Badguy *boss;

	// The 2D array of badguys
	Badguy *badguys[4][3];
	
	// Players's Bullets
	list<Bullet*> bullets;

	// Badguy's Bullets
	list<Bullet*> badguyBullets;

	// Boss's Bullets
	list<BossBullet*> bossBullets;

	// linked list of Power ups
	LinkedList<PowerUp*> powerUps;

	// Exloding boss bullets
	vector<BossBullet*> explodingBossBullet;

	// Green god mode shield
	GodShield godShield;

	// Purple temporary shield
	TempShield tempShield;

	// The main timer
	int timerId;

	// exlosion timer for badguys and exploding boss bullets
	int timerExplosions;

	// This timer controls the rate of fire of the badguy and boss bullets
	int timerBadguyBullet;

	// This timer controls the movement speed of the badguys and the boss
	int timerBadguyMove;

	//  exlosion timer for the player's ship
	int timerSpaceshipHit;

	//  exlosion timer for the boss
	int timerbossHit;

	// The timer delay that controls the speed of the badguys movement.
	int delayBadguyMove;

	// The timer delay that controls the speed of the badguys bullets.
	int delayBadguyBullet;

	// increment variable to control which explosion 
	// image is displayed for the player's ship
	int spaceshipIndex;

	// Whether or not the player's ship is exploding
	bool spaceshipExploding;

	// Whether or not the boss is exploding
	bool bossExploding;

	// increment variable to control which explosion 
	// image is displayed for the boss
	int bossIndex;

	// Array of increment variables to control which 
	// explosion image is displayed for badguys
	int badguyIndex[4][3];

	// increment variable to control bullet firing rate of the player's ship 
	unsigned int bulletCounter;

	// set equal to bulletCounter every time the player's ship shoots
	unsigned int lastShotTime;

	// Player's lives
	int lives;

	// Player's score
	unsigned int score;

	// Game Over Flag
	bool gameOver;

	// Game Won (victory) Flag
	bool gameWon;

	// Game Started Flag
	bool gameStarted;

	// Game Paused Flag
	bool paused;

	// Kill Player Flag
	bool killPlayer;
	
	// Level Background QImage
	QImage levelbackImage; 
	// Level Background QRect
	QRect levelbackRect;

	// Current Level
	int level;

	// Advance 1 Level flag
	bool nextLevel;

	// Go Back 1 Level flag
	bool prevLevel;

	// number of destroyed badguys in current level
	int deathCount;

	// freeze badguys flag
	bool freezeFlag;

	// increment variable to control the length of badguy freeze
	int freezeCount;

	// God Mode Flag
	bool godMode;

	// Temporary God Mode flag
	bool tempGodFlag;

	// increment variable to control the length of Temporary God Mode
	int godCount;
	
	// Temporary shield flag
	bool shieldFlag;

	// Triple Shot flag
	bool tripleShot;

	// Player got Deathshroom flag
	// Player will be killed
	bool deathShroom;

	// Left directional key is held down
	bool keepLeft;

	// Right directional key is held down
	bool keepRight;

	// Space bar is held down flag
	bool keepShoot;

	// User list vector
	vector<User*> userList;

	// Pointer to the currently logged in user
	User* currentUser;

	//  Number of distinct relationships between users
	unsigned int relationCount;

	// Number of active users
	unsigned int userCount;

	// Display Menu Flags
	bool displayStartUp, displayLogIn,menuDisplayed;
	bool displayOptions, displayScores, displayFriendsScores;
	bool displayUserScreen,displayDeleteUser,displayAddUser,displayUserList;
	bool displayAddFriend, displayDeleteFriend, displayShortestPath;

	// Corrupt Data Base Flags
	bool corruptDB;
	bool warningCorruptDB;

	// Adding new user error warning flags
	bool warningAddUser,warningDupeUser,warningInvalidInput,warningYearOOR,warningUserOOR;

	// Player has chaeated flag
	bool cheated;
	// Cheats are enable flag
	bool cheatsEnabled;


	// add user text field, used to add new users
	QLineEdit * addUserBox;

	// List of users Tables, reused on different screens
	QListView * viewUsersBox;

	// Small List of Friends  Tables, reused on different screens
	QListView * smallFriendsBox;

	// High Score Tables, reused on different screens
	QTableView * highScoreBox;

	// Strings used to print the shortest path
	QString shortestPathString1;
	QString shortestPathString2;

	// Different Push buttons
	QPushButton * logOffButton;
	QPushButton * goBackButton;
	QPushButton * addUserButton;
	QPushButton * deleteUserButton;
	QPushButton * logOnButton;
	QPushButton * listAllScoresButton;
	QPushButton * quitButton;
	QPushButton * listAllUsersButton;
	QPushButton * addFriendButton;
	QPushButton * deleteFriendButton;
	QPushButton * listFriendsScoresButton;
	QPushButton * listAllScores2Button;
	QPushButton * shortestPathButton; 
	QPushButton * playGameButton;
	QPushButton * quitGameButton;
	QPushButton * restartButton;
	
	// Window QImage
	QImage windowImage; 
	// Window QRect
	QRect windowRect; 
	// Window2 QImage
	QImage window2Image; 
	// Windo2w QRect
	QRect window2Rect;
	// Big Window QImage
	QImage bigWindowImage; 
	// Big Window QRect 
	QRect bigWindowRect;

	// top bar QImage
	QImage topBarImage; 
	// top bar QRect 
	QRect topBarRect;

	// Palette used for viewUsersBox, highScoreBox, and addUserBox
	QPalette pal;

    public slots:

	// logs in user selected on log in screen and displays users screen
	void logInUser(QModelIndex modelIndex);

	// deletes user selected on deletes user screen and displays start up screen
	void deleteUser(QModelIndex modelIndex);

	// trys to add user from selected in addUserBox on add user screen
	// if user input valid, displays start up screen
	// if user input invalid, displays appropriate message and remians on add user screen
	void tryAddUser();

	// sets focus back to game window 
	void refocus();

	// add friendship between current user and selected user on add friend screen
	// and displays users screen
	void addFriend(QModelIndex modelIndex);

	// deletes friendship between current user and selected user on delete friend screen
	// and displays users screen
	void deleteFriend(QModelIndex modelIndex);

	// finds shortest path between current user and selected user on shortest path screen
	// if path exists, path is displayed
	// if path does not exist, appropriate message is diplayed
	void findShortestPath(QModelIndex modelIndex);

	// logs off current user and displays start up screen
	void logOff();

	// displays start up screen
	void goBack2StartUp();

	// displays users screen
	void goBack2UserScreen();

	// displays add user screen
	void addUserButtonSlot();

	// displays delete user screen
	void deleteUserButtonSlot();

	// displays log on screen
	void logOnButtonSlot();

	// displays high scores screen
	void listAllScoresButtonSlot();

	// Quits entire application (game)
	void quitButtonSlot();

	// displays user list screen
	void listAllUsersButtonSlot();

	// displays add friend screen
	void addFriendButtonSlot();

	// displays delete friend screen
	void deleteFriendButtonSlot();

	// displays friend's high score screen
	void listFriendsScoresButtonSlot();

	// diplays shortest path screen
	void shortestPathButtonSlot();

	// diplays intro Screen 
	// disables menu flag 
	// and sets game into game mode
	void playGameButtonSlot();

	// restarts game and diplays intro Screen
	void restartGameButtonSlot();
};

#endif
