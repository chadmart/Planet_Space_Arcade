/*!\file slots.cpp
 * 
 * \brief Contians the game logic implentations for the slots of the SpaceWars class
 * 
 * \Created by: Chad Martin
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/26/2012
 *
 * This class contians the game logic implentations for the slots of the SpaceWars class.
 */

#include "spacewars.h"
#include <QPainter>
#include <QApplication>
#include <list>
#include <stdlib.h>
#include <sstream>

// logs in user selected on log in screen and displays users screen
void SpaceWars::logInUser(QModelIndex modelIndex)
{
	  if(!currentUser)
	  {
		// grabs username that the user clicked on from the list view
		string findUser = modelIndex.data(Qt::DisplayRole).toString().toStdString();

		//  iterate through userlist
		for(unsigned int i =0; i < userList.size() ;i++)
		{
			// when user found, log in user and display users screen
			if(userList[i]->getUsername() == findUser)
			{
				// log in user
				currentUser = userList[i];

				// set up flags to display user screen
				displayUserScreen = true;
				displayLogIn = false;
				
				// hide text box and button
				if(viewUsersBox)
					viewUsersBox->hide();
				if(goBackButton)
					goBackButton->hide();

				// show log off button
				if(logOffButton)
					logOffButton->show();

				// set up friends box
				addFriendBox();

				// set up users screen buttons
				buildUserScreenButtons();

				// set focus to game window
				this->setFocus();

				break;
			}	
		}
	  }
				// call paint event
				repaint();


}

// logs in user selected on log in screen and displays users screen
void SpaceWars::deleteUser(QModelIndex modelIndex)
{
		// grabs username that the user clicked on from the list view
		string findUser = modelIndex.data(Qt::DisplayRole).toString().toStdString();

		// iterate through userlist
		for(unsigned int i =0; i < userList.size() ;i++)
		{
			// when user found, delete user and users relationship, and then display users screen
			if(userList[i]->getUsername() == findUser)
			{
				// save to be deleted user id
				unsigned int temp = userList[i]->getID();

				// delete user and decrement user count
				delete userList[i];
				userList.erase(userList.begin()+i);
				userCount--;	

				// iterate through each users friends list
				for(unsigned int j = 0; j < userList.size();j++)
				{
					for(unsigned int g = 0; g < userList[j]->friends.size() ;g++)
						// if deleted users ID is on another friend list delete it
						if(temp == userList[j]->friends[g])
							userList[j]->friends.erase(userList[j]->friends.begin()+g);
							
				}

				// set up users screen
				if(addUserButton)
					addUserButton->show();
				if(deleteUserButton)
					deleteUserButton->show();
				if(logOnButton)
					logOnButton->show();
				if(listAllScoresButton)
					listAllScoresButton->show();
				if(quitButton)
					quitButton->show();

				displayStartUp = true;
				displayDeleteUser = false;
				if(viewUsersBox)				
					viewUsersBox->hide();
				if(goBackButton)				
					goBackButton->hide();

				// update relation count
				updateRelations();
				repaint();

				// set focus to game window
				this->setFocus();

				break;
			}	
		}	 
}

// trys to add user from selected in addUserBox on add user screen
// if user input valid, displays start up screen
// if user input invalid, displays appropriate message and remians on add user screen
void SpaceWars::tryAddUser()
{
	// grab input from text box
	string inputString = addUserBox->displayText().toStdString();

	// declare helper variables
	string newUsername = "";
	string trash;
	unsigned int newYear = 7;
	unsigned int newID = 1;
  	stringstream ss;
	bool badInput = false;

	// reset warning messages
	warningDupeUser = false;
	warningInvalidInput = false;
	warningYearOOR = false;
	warningUserOOR = false;
	warningCorruptDB = false;

	// read input from input string
	ss << inputString; 

	// write out username to string
	ss >> newUsername;

	// check if something was written
	if(newUsername == "")
	{
		badInput = true;
		warningInvalidInput = true;
	}

	// check if user name is only has alphanumeric or underscore characters
	badInput = !(validateUsername(newUsername));
	warningUserOOR = badInput;

	// write out new year to int
	ss >> newYear;

	// check if something was written
	if(ss >> trash)
	{
		badInput = true;
		warningInvalidInput = true;
	}

	// check if username is unique 
	for(unsigned int i = 0; i < userList.size() && !badInput;i++)
		if(newUsername == userList[i]->getUsername())
		{
			badInput = true;
			warningDupeUser = true;
		}
	
	// check if year is range	
	if(newYear < 1 || newYear > 5)
	{
		badInput = true;
		warningYearOOR = true;
	}

	// create unique ID
	for(unsigned int j = 0; j < userList.size() && !badInput;j++)
	{
		bool uniqueID = true;

		for(unsigned int i = 0; i < userList.size();i++)
		  if(newID == userList[i]->getID())
		  {
			newID++;
			uniqueID = false;
		  }

		if(uniqueID) break;
	}


	// if input was valid, add user to vector and increase user count and display start up screen
	if(!badInput)
	{
		// add user to vector and increase user count
		User * newUser = new User(newID,newUsername,newYear);
		userList.push_back(newUser);
		userCount++;
		
		// reset warning flags		
		warningAddUser = false;
		warningDupeUser = false;
		warningInvalidInput = false;
		warningYearOOR = false;
		warningUserOOR = false;

		//set up start up screens
		displayStartUp = true;
		displayAddUser = false;

		addUserBox->hide();
		goBackButton->hide();

		if(addUserButton)
			addUserButton->show();
		if(deleteUserButton)
			deleteUserButton->show();
		if(logOnButton)
			logOnButton->show();
		if(listAllScoresButton)
			listAllScoresButton->show();
		if(quitButton)
			quitButton->show();

		// call paint event
		repaint();

		// set focus to game window
		this->setFocus();
	}
	else // if validation failed
	{
		// clear text box
		addUserBox->clear();

		// display warning
		if(newUsername != "")
			warningAddUser = true;

		// call paint event
		repaint();

		// set focus to game window
		this->setFocus();
	}
}

// sets focus back to game window 
void SpaceWars::refocus()
{
	// sets focus back to game window 
	this->setFocus();
}

// add friendship between current user and selected user on add friend screen
// and displays users screen	
void SpaceWars::addFriend(QModelIndex modelIndex)
{
	// grabs username that the user clicked on from the list view
	string findUser = modelIndex.data(Qt::DisplayRole).toString().toStdString();

	// iterate through userlist
	for(unsigned int i =0; i < userList.size() ;i++)
	{
		// when user found, add friendship between current user and selected user 		
		if(userList[i]->getUsername() == findUser)
		{
			bool existingFriend = false;

			// iterate through users friend list
			for(unsigned int j =0; j < userList[i]->friends.size() ;j++)
			{
				if(currentUser->getID() == userList[i]->friends[j])
					existingFriend = true;
			}
		
			if(!existingFriend)
			{
				// add mutal friendship and increase relation count
				relationCount++;
				userList[i]->addFriend(currentUser->getID());	
				currentUser->addFriend(userList[i]->getID());	
	
				// set up users screen
				displayUserScreen = true;
				displayAddFriend = false;
				if(viewUsersBox)
					viewUsersBox->hide();
				if(goBackButton)
					goBackButton->hide();
				buildUserScreenButtons();
				addFriendBox();

				// call paint event
				repaint();
	
				// set focus to game window
				this->setFocus();

				break;
			}
		}	
	}
}

// deletes friendship between current user and selected user on delete friend screen
// and displays users screen
void SpaceWars::deleteFriend(QModelIndex modelIndex)
{
	// grabs username that the user clicked on from the list view
	string findUser = modelIndex.data(Qt::DisplayRole).toString().toStdString();

	// iterate through userlist
	for(unsigned int i =0; i < userList.size() ;i++)
	{
		// when user found, add delete friendship between current user and selected user 		
		if(userList[i]->getUsername() == findUser)
		{
			bool existingFriend = false;

			for(unsigned int j =0; j < userList[i]->friends.size() ;j++)
			{
				if(currentUser->getID() == userList[i]->friends[j])
					existingFriend = true;
			}
		
			if(existingFriend)
			{
				// delete mutual friendship and reduce relation count
				relationCount--;
				userList[i]->deleteFriend(currentUser->getID());	
				currentUser->deleteFriend(userList[i]->getID());	

				// set up users screen
				displayUserScreen = true;
				displayDeleteFriend = false;
				viewUsersBox->hide();
				goBackButton->hide();
				buildUserScreenButtons();
				addFriendBox();

				// call paint event
				repaint();

				// set focus to game window
				this->setFocus();

				break;
			}
		}	
	}
}

// finds shortest path between current user and selected user on shortest path screen
// if path exists, path is displayed
// if path does not exist, appropriate message is diplayed
void SpaceWars::findShortestPath(QModelIndex modelIndex)
{
	// grabs username that the user clicked on from the list view
	string findUser = modelIndex.data(Qt::DisplayRole).toString().toStdString();

	// set up helper variables
 	string printThis = "";
 	string printThis2 = "";
	User *tempUser = NULL;

	// iterate through userlist and assign temp user to selected user, once found
	for(unsigned int i =0; i < userList.size() ;i++)
	{
		if(userList[i]->getUsername() == findUser)
		{
			tempUser = userList[i];
		}	
	}
	
	// if user no path tell user
	if(tempUser->parent == NULL)
	{
		printThis = "No path from " + tempUser->getUsername() + " to " + currentUser->getUsername(); 
	}
	else
	{
	  //set up strings to display path
	  printThis = "Shortest path from " + tempUser->getUsername() + " to " + currentUser->getUsername() + ":";
	  while(tempUser!=NULL)
	  {		
		if(tempUser->parent!=NULL)
			printThis2 += tempUser->getUsername() + ", "; 
		else
			printThis2 += tempUser->getUsername();

		tempUser = tempUser->parent;
	  }
	}

	// set display strings to new path
	shortestPathString1 =  QString::fromStdString(printThis);
	shortestPathString2 =  QString::fromStdString(printThis2);

	// call paint event
	repaint();
	
	// set focus to game window
	this->setFocus();
}

// logs off current user and displays start up screen
void SpaceWars::logOff()
{
  if(currentUser)
  {
	//sets game logic to initial state
	if(paused)
	  pauseGame();
	if(gameStarted)
	{
		restartGame();
	}

	// sets up variables for start up screen	
	displayStartUp = true;
	displayScores = false;
	displayFriendsScores = false;
	displayUserScreen = false;
	displayUserList = false;
	displayAddFriend = false; 
	displayDeleteFriend = false; 
	displayShortestPath = false;
	currentUser= NULL;

	// hide acitve buttons
	if(addUserBox)
		addUserBox->hide();
	if(viewUsersBox)
		viewUsersBox->hide();
	if(highScoreBox)
		highScoreBox->hide();
	if(logOffButton)
		logOffButton->hide();
	if(goBackButton)
		goBackButton->hide();
	if(quitGameButton)
		quitGameButton->hide();
	if(restartButton)
		restartButton->hide();

	hideUserScreenButtons();

	// delete small friends box
	if(smallFriendsBox)
	{
		delete smallFriendsBox;
		smallFriendsBox = NULL;
	}

	// show start up screen buttons
	if(addUserButton)
		addUserButton->show();
	if(deleteUserButton)
		deleteUserButton->show();
	if(logOnButton)
		logOnButton->show();
	if(listAllScoresButton)
		listAllScoresButton->show();
	if(quitButton)
		quitButton->show();

	// call a paint event
	repaint();
  }
}

// displays start up screen
void SpaceWars::goBack2StartUp()
{
	if(!currentUser)
	{
		// sets up variables for start up screen
		displayStartUp = true;
		displayAddUser = false;
		displayScores = false;
		displayFriendsScores = false;
		displayUserScreen = false;
		displayUserList = false;
		displayAddFriend = false; 
		displayDeleteFriend = false; 
		displayShortestPath = false;
		displayLogIn = false;
		displayDeleteUser = false;
		warningAddUser = false;
		warningDupeUser = false;
		warningInvalidInput = false;
		warningYearOOR = false;
		warningUserOOR = false;
		warningCorruptDB = false;
		menuDisplayed = true;

		// hides active buttons
		if(addUserBox)
			addUserBox->hide();
		if(viewUsersBox)
			viewUsersBox->hide();
		if(highScoreBox)
			highScoreBox->hide();
		if(logOffButton)
			logOffButton->hide();
		if(goBackButton)
			goBackButton->hide();

		hideUserScreenButtons();

		// displays start up screen buttons
		if(addUserButton)
			addUserButton->show();
		if(deleteUserButton)
			deleteUserButton->show();
		if(logOnButton)
			logOnButton->show();
		if(listAllScoresButton)
			listAllScoresButton->show();
		if(quitButton)
			quitButton->show();

		// call a paint event
		repaint();

		this->setFocus();
	}
}

// displays users screen
void SpaceWars::goBack2UserScreen()
{
	if(currentUser)
	{
		//sets up variables to go back to users screen
		shortestPathString1 = "";
		shortestPathString2 = "";
		displayStartUp = false;
		displayAddUser = false;
		displayScores = false;
		displayFriendsScores = false;
		displayUserScreen = true;
		displayUserList = false;
		displayAddFriend = false; 
		displayDeleteFriend = false; 
		displayShortestPath = false;
		displayLogIn = false;
		displayDeleteUser = false;
		warningAddUser = false;
		warningDupeUser = false;
		warningInvalidInput = false;
		warningYearOOR = false;
		warningUserOOR = false;
		warningCorruptDB = false;
		menuDisplayed = true;

		// hides active buttons
		if(addUserBox)
			addUserBox->hide();
		if(viewUsersBox)
		{
			viewUsersBox->hide();
		}
		if(highScoreBox)
			highScoreBox->hide();
		if(goBackButton)
			goBackButton->hide();
		if(quitGameButton)
			quitGameButton->hide();

		// build users screen widgets
		buildUserScreenButtons();
		addFriendBox();
	
		// calls a paint event
		repaint();

		// set focus to game window
		this->setFocus();
	}
}

// displays add user screen
void SpaceWars::addUserButtonSlot()
{
	if(displayStartUp)
	{
		// delete text box if it exists		
		if(addUserBox)
			delete addUserBox;

		//sets up variables to add user screen
		displayAddUser = true;
		displayStartUp = false;
		warningAddUser = false;
		warningDupeUser = false;
		warningInvalidInput = false;
		warningYearOOR = false;
		warningUserOOR = false;

		// hide active buttons
		addUserButton->hide();
		deleteUserButton->hide();
		logOnButton->hide();
		listAllScoresButton->hide();
		quitButton->hide();

		// set up add user text field
		addUserBox = new QLineEdit(this);
		addUserBox->setPalette(pal);
		addUserBox->setFont(QFont("Chicago", 15));
		addUserBox->setFixedSize(350,30);
		addUserBox->move(225,344);
		addUserBox->show();	
		QObject::connect(addUserBox, SIGNAL(returnPressed()),this,SLOT(tryAddUser()));

		// set up go back button
		QFontMetrics fm(QFont("Chicago", 20));
		int buttonWidth = fm.width("Go Back");
		goBackButton->move(400-buttonWidth/2,452);
		goBackButton->show();

		//call paint event
		repaint();

		// set focus to text field
		addUserBox->setFocus();
	}
}
// displays delete user screen
void SpaceWars::deleteUserButtonSlot()
{
	if(displayStartUp)
	{
		// delete user list box if it exists
		if(viewUsersBox)
		{
			delete viewUsersBox;
			viewUsersBox = NULL;
		}

		// set up variables for delete user screen
		displayDeleteUser = true;
		displayStartUp = false;

		// hide active buttons
		addUserButton->hide();
		deleteUserButton->hide();
		logOnButton->hide();
		listAllScoresButton->hide();
		quitButton->hide();

		// build user list box
		QStringList  firstList;
		for(unsigned int i = 0; i < userList.size();i++)
		{
			firstList.append(QString::fromStdString(userList[i]->getUsername()));
		}
		viewUsersBox = new QListView(this);
		viewUsersBox->setPalette(pal);
		viewUsersBox->setFont(QFont("Chicago", 15));
		viewUsersBox->setModel(new QStringListModel(firstList));
		viewUsersBox->setFixedSize(400,400);
		viewUsersBox->move(200,164);
		QObject::connect(viewUsersBox, SIGNAL(clicked(QModelIndex)),this,SLOT(deleteUser(QModelIndex)));	
		viewUsersBox->show();

		// display go back button
		QFontMetrics fm(QFont("Chicago", 20));
		int buttonWidth = fm.width("Go Back");
		goBackButton->move(400-buttonWidth/2,596);
		goBackButton->show();

		// call a paint event
		repaint();
	}
}

// displays log on screen
void SpaceWars::logOnButtonSlot()
{
	if(displayStartUp)
	{
		// delete user list box if it exists
		if(viewUsersBox)
		{
			delete viewUsersBox;
			viewUsersBox = NULL;
		}

		// set up variables for delete user screen
		displayLogIn = true;
		displayStartUp = false;

		addUserButton->hide();
		deleteUserButton->hide();
		logOnButton->hide();
		listAllScoresButton->hide();
		quitButton->hide();

		// build user list box
		QStringList  firstList;
		for(unsigned int i = 0; i < userList.size();i++)
		{
			firstList.append(QString::fromStdString(userList[i]->getUsername()));
		}
		viewUsersBox = new QListView(this);
		viewUsersBox->setPalette(pal);
		viewUsersBox->setFont(QFont("Chicago", 15));
		viewUsersBox->setModel(new QStringListModel(firstList));
		viewUsersBox->setFixedSize(400,400);
		viewUsersBox->move(200,164);
		QObject::connect(viewUsersBox, SIGNAL(clicked(QModelIndex)),this,SLOT(logInUser(QModelIndex)));	
		viewUsersBox->show();

		// set up go back button
		QFontMetrics fm(QFont("Chicago", 20));
		int buttonWidth = fm.width("Go Back");
		goBackButton->move(400-buttonWidth/2,596);
		goBackButton->show();

		// call a paint event
		repaint();
	}
}

// displays high scores screen
void SpaceWars::listAllScoresButtonSlot()
{
	if(displayStartUp || displayUserScreen)
	  {
		// if it exist delete high score box
		if(highScoreBox)
		{
			delete highScoreBox;
			highScoreBox = NULL;
		}
		// delete user list box if it exists
		if(viewUsersBox)
		{
			delete viewUsersBox;
			viewUsersBox = NULL;
		}

		// delete small friends list box if it exists
		if(smallFriendsBox)
		{
			delete smallFriendsBox;
			smallFriendsBox = NULL;
		}

		// sort users by high score
		scoresSort();

		// hide active buttons
		if(displayStartUp)
		{
			addUserButton->hide();
			deleteUserButton->hide();
			logOnButton->hide();
			listAllScoresButton->hide();
			quitButton->hide();
		}
		hideUserScreenButtons();

		// create high score table
		highScoreBox = new QTableView(this);
		QStandardItemModel * highScoreModel = new QStandardItemModel(0,2,this); //0 Rows and 2 Columns
		highScoreModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Player")));
            	highScoreModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Score")));
		for(unsigned int i = 0; i < userList.size();i++)
		{
			highScoreModel->insertRow(i);
			highScoreModel->setItem(i,0,new QStandardItem(QString(userList[i]->getUsername().c_str())));
                	char score[11];
                	sprintf(score,"%u",userList[i]->getScore());
                	highScoreModel->setItem(i,1,new QStandardItem(score));
		}
		highScoreBox->setPalette(pal);
		highScoreBox->setFont(QFont("Chicago", 15));
		highScoreBox->setModel(highScoreModel);
		highScoreBox->setFixedSize(400,460);
		highScoreBox->setColumnWidth(0,220);
		highScoreBox->setColumnWidth(1,156);
		highScoreBox->move(200,128);
		highScoreBox->show();
		QObject::connect(highScoreBox, SIGNAL(clicked(QModelIndex)),this,SLOT(refocus()));	

		// set up go back button
		QFontMetrics fm(QFont("Chicago", 20));
		int buttonWidth = fm.width("Go Back");
		goBackButton->move(400-buttonWidth/2,614);
		goBackButton->show();

		// set up flags to display scores screen
		displayScores = true;
		displayStartUp = false;
		displayUserScreen = false;

		// set focus to game window
		this->setFocus();

		// call a paint event
		repaint();
	  }
}

// Quits entire application (game)
void SpaceWars::quitButtonSlot()
{
	  // Quit
          qApp->exit();
}

// displays user list screen
void SpaceWars::listAllUsersButtonSlot()
{
	if(displayUserScreen && currentUser)
	{
		// delete user list box if it exists
		if(viewUsersBox)
		{
			delete viewUsersBox;
			viewUsersBox = NULL;
		}

		// delete small friends list box if it exists
		if(smallFriendsBox)
		{
			delete smallFriendsBox;
			smallFriendsBox = NULL;
		}

		// set up flags to display user list screen
		displayUserScreen = false;
		displayUserList = true;
			
		// hide user screen buttons
		hideUserScreenButtons();

		// build user list box
		QStringList  firstList;
		for(unsigned int i = 0; i < userList.size();i++)
		{
			firstList.append(QString::fromStdString(userList[i]->getUsername()));
		}
		viewUsersBox = new QListView(this);
		viewUsersBox->setPalette(pal);
		viewUsersBox->setFont(QFont("Chicago", 15));
		viewUsersBox->setModel(new QStringListModel(firstList));
		viewUsersBox->setFixedSize(400,400);
		viewUsersBox->move(200,164);
		QObject::connect(viewUsersBox, SIGNAL(clicked(QModelIndex)),this,SLOT(refocus()));	
		viewUsersBox->show();

		// set up go back button
		QFontMetrics fm(QFont("Chicago", 20));
		int buttonWidth = fm.width("Go Back");
		goBackButton->move(400-buttonWidth/2,596);
		goBackButton->show();

		// call paint event
		repaint();
	}
}

// displays add friend screen
void SpaceWars::addFriendButtonSlot()
{
	if(displayUserScreen && currentUser)
	{
		// delete user list box if it exists
		if(viewUsersBox)
		{
			delete viewUsersBox;
			viewUsersBox = NULL;
		}

		// delete small friends list box if it exists
		if(smallFriendsBox)
		{
			delete smallFriendsBox;
			smallFriendsBox = NULL;
		}

		// set up flags to display add friend screen
		displayUserScreen = false;
		displayAddFriend = true;

		// hide user screen buttons
		hideUserScreenButtons();

		// select and build user list box with only current user's non-friends
		QStringList  firstList;
		for(unsigned int i = 0; i < userList.size();i++)
		{
			// check if friend is on users list
			bool existingFriend = false;
			if(currentUser->getID() != userList[i]->getID())
			{
				for(unsigned int j = 0; j < userList[i]->friends.size();j++)
				{
					if(currentUser->getID() == userList[i]->friends[j])
					{
						existingFriend = true;
					}
				}
			}
			else // set existingFriend flag to force addition of current user to list
			{
				existingFriend = true;
			}

			// If not a friend or not self, add selected user to list
			if(!existingFriend)
				firstList.append(QString::fromStdString(userList[i]->getUsername()));
		}

		// build user list box with only current user's non-friends
		viewUsersBox = new QListView(this);
		viewUsersBox->setPalette(pal);
		viewUsersBox->setFont(QFont("Chicago", 15));
		viewUsersBox->setModel(new QStringListModel(firstList));
		viewUsersBox->setFixedSize(400,400);
		viewUsersBox->move(200,164);
		QObject::connect(viewUsersBox, SIGNAL(clicked(QModelIndex)),this,SLOT(addFriend(QModelIndex)));	
		viewUsersBox->show();

		// set up go back button
		QFontMetrics fm(QFont("Chicago", 20));
		int buttonWidth = fm.width("Go Back");
		goBackButton->move(400-buttonWidth/2,596);
		goBackButton->show();

		// call a paint event
		repaint();
	}
}

// displays delete friend screen
void SpaceWars::deleteFriendButtonSlot()
{
	if(displayUserScreen && currentUser)
	{
		// delete user list box if it exists
		if(viewUsersBox)
		{
			delete viewUsersBox;
			viewUsersBox = NULL;
		}

		// delete small friends list box if it exists
		if(smallFriendsBox)
		{
			delete smallFriendsBox;
			smallFriendsBox = NULL;
		}


		// set up flags to display delete friend screen
		displayUserScreen = false;
		displayDeleteFriend = true;

		// hide user screen buttons
		hideUserScreenButtons();

		// select and build user list box with only current user's friends
		QStringList  firstList;
		for(unsigned int i = 0; i < currentUser->friends.size();i++)
		{
			for(unsigned int j = 0; j < userList.size();j++)
			{
				if(userList[j]->getID() == currentUser->friends[i])
					firstList.append(QString::fromStdString(userList[j]->getUsername()));
			}
		}
		viewUsersBox = new QListView(this);
		viewUsersBox->setPalette(pal);
		viewUsersBox->setFont(QFont("Chicago", 15));
		viewUsersBox->setModel(new QStringListModel(firstList));
		viewUsersBox->setFixedSize(400,400);
		viewUsersBox->move(200,164);
		QObject::connect(viewUsersBox, SIGNAL(clicked(QModelIndex)),this,SLOT(deleteFriend(QModelIndex)));	
		viewUsersBox->show();

		// set up go back button
		QFontMetrics fm(QFont("Chicago", 20));
		int buttonWidth = fm.width("Go Back");
		goBackButton->move(400-buttonWidth/2,596);
		goBackButton->show();

		// call a paint event
		repaint();
	}
}

// displays friend's high score screen
void SpaceWars::listFriendsScoresButtonSlot()
{
	if(displayUserScreen && currentUser)
	{
		// if it exist delete high score box
		if(highScoreBox)
		{
			delete highScoreBox;
			highScoreBox = NULL;
		}

		// delete user list box if it exists
		if(viewUsersBox)
		{
			delete viewUsersBox;
			viewUsersBox = NULL;
		}

		// delete small friends list box if it exists
		if(smallFriendsBox)
		{
			delete smallFriendsBox;
			smallFriendsBox = NULL;
		}

		// set up flags to display friends scores screen
		displayFriendsScores = true;
		displayUserScreen = false;
		
		// hide user screen buttons	
		hideUserScreenButtons();

		// sort users by high score
		scoresSort();

		// create high score table of only friends
		highScoreBox = new QTableView(this);
		QStandardItemModel * highScoreModel = new QStandardItemModel(0,2,this); //0 Rows and 2 Columns
		highScoreModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Player")));
            	highScoreModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Score")));
		unsigned int k = 0;
		for(unsigned int i = 0; i < userList.size();i++)
		{
		  bool isFriend = false;
		  for(unsigned int j = 0; j < currentUser->friends.size();j++)
		  {
			if(currentUser->friends[j] == userList[i]->getID() || currentUser->getID() == userList[i]->getID())
			{
				isFriend = true;
			}
		  }
		  // only add friends to table
		  if(isFriend)
		  {
			highScoreModel->insertRow(k);
			highScoreModel->setItem(k,0,new QStandardItem(QString(userList[i]->getUsername().c_str())));
                	char score[11];
                	sprintf(score,"%u",userList[i]->getScore());
                	highScoreModel->setItem(k,1,new QStandardItem(score));
			k++;
		  }
		}
		highScoreBox->setPalette(pal);
		highScoreBox->setFont(QFont("Chicago", 15));
		highScoreBox->setModel(highScoreModel);
		highScoreBox->setFixedSize(400,460);
		highScoreBox->setColumnWidth(0,220);
		highScoreBox->setColumnWidth(1,156);
		highScoreBox->move(200,128);
		highScoreBox->show();
		QObject::connect(highScoreBox, SIGNAL(clicked(QModelIndex)),this,SLOT(refocus()));	

		// set up go back button
		QFontMetrics fm(QFont("Chicago", 20));
		int buttonWidth = fm.width("Go Back");
		goBackButton->move(400-buttonWidth/2,614);
		goBackButton->show();

		// set focus to game window
		this->setFocus();

		// call a paint event
		repaint();
	}
}

// diplays shortest path screen
void SpaceWars::shortestPathButtonSlot()
{
	if(displayUserScreen && currentUser)
	{
		// delete user list box if it exists
		if(viewUsersBox)
		{
			delete viewUsersBox;
			viewUsersBox = NULL;
		}

		//hide small friends list
		if(smallFriendsBox)
			smallFriendsBox->hide();

		// set up flags to display shortest path screen
		displayUserScreen = false;
		displayShortestPath = true;

		// hide user screen buttons
		hideUserScreenButtons();

		// Run BFS serach on currentUser
		// BFS search sets up variables on all users for shortest path to current user
		if(currentUser)
			BFSearch(currentUser->getUsername());

		// select and build user list box
		QStringList  firstList;
		for(unsigned int i = 0; i < userList.size();i++)
		{
		  if(currentUser->getUsername() != userList[i]->getUsername())
			firstList.append(QString::fromStdString(userList[i]->getUsername()));
		}
		viewUsersBox = new QListView(this);
		viewUsersBox->setPalette(pal);
		viewUsersBox->setFont(QFont("Chicago", 15));
		viewUsersBox->setModel(new QStringListModel(firstList));
		viewUsersBox->setFixedSize(400,400);
		viewUsersBox->move(200,182);
		QObject::connect(viewUsersBox, SIGNAL(clicked(QModelIndex)),this,SLOT(findShortestPath(QModelIndex)));	
		viewUsersBox->show();

		// set up go back button
		QFontMetrics fm(QFont("Chicago", 20));
		int buttonWidth = fm.width("Go Back");
		goBackButton->move(400-buttonWidth/2,614);
		goBackButton->show();

		// call a paint event
		repaint();
	}
}

// diplays intro Screen 
// disables menu flag 
// and sets game into game mode
void SpaceWars::playGameButtonSlot()
{
	  if(displayUserScreen && currentUser)
	  {
		// set up flags to display game intro screen
	 	displayUserScreen = false;
		menuDisplayed = false;

		// hide user list box
		if(viewUsersBox)
			viewUsersBox->hide();

		// hide small friend list box	
		if(smallFriendsBox)
			smallFriendsBox->hide();

		// hide user screen buttons
		hideUserScreenButtons();
	
		// set up helper variables
		QFontMetrics fm(QFont("Chicago", 20));
		int buttonWidth = fm.width("Go Back");
		buttonWidth +=10;

		// set up go back button
		goBackButton->move(400-buttonWidth*3/2,452);
		goBackButton->show();

		// set up quit game button
		quitGameButton->move(400+buttonWidth/2,452);
		quitGameButton->show();

		
		// set focus to game window
		this->setFocus();

		// call a paint event
		repaint();
	  }
}

// restarts game and diplays intro Screen
void SpaceWars::restartGameButtonSlot()
{
	if(!menuDisplayed)
	{
		// hide restart button
		if(restartButton)
			restartButton->hide();

		// declare helper variables
		QFontMetrics fm(QFont("Chicago", 20));
		int buttonWidth = fm.width("Go Back");
		buttonWidth +=10;

		// set up go back button
		goBackButton->move(400-buttonWidth*3/2,452);
		goBackButton->show();

		// set up quit game button
		quitGameButton->move(400+buttonWidth/2,452);
		quitGameButton->show();
		
		// set focus to game window
		this->setFocus();

		//restart game
		restartGame();
	}
}
