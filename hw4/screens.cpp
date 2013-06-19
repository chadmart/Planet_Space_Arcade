/*!\file screens.cpp
 * 
 * \brief Contians the game logic implentations for displaying the different screens of the SpaceWars class
 * 
 * \Created by: Chad Martin
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/26/2012
 *
 * This class contians the game logic implentations for displaying the different screens  of the SpaceWars class.
 */

#include "spacewars.h"
#include <QPainter>
#include <QApplication>
#include <iostream>
#include <QTextStream>

// Calls endGame and displays victory text and window
void SpaceWars::victoryScreen(QPainter &painter)
{
	// call end game
	endGame();

	// draws appropriate window
	painter.drawImage(windowRect, windowImage);

	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 20));
	QFontMetrics fm2(QFont("Chicago", 18));
	int textWidth;
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 20)); 

	// Paint Text
	textWidth = fm.width("VICTORY, YOU WIN!!");
	painter.drawText(400-textWidth/2, 344, "VICTORY, YOU WIN!!");

	textWidth = fm2.width("Fight On for ol' SC!");
	painter.setFont(QFont("Chicago", 18)); 
	painter.drawText(400-textWidth/2, 390, "Fight On for ol' SC!");

	/*textWidth = fm2.width("Fight On to victory!");
	painter.setFont(QFont("Chicago", 18)); 
	painter.drawText(400-textWidth/2, 416, "Fight On to victory!");

	textWidth = fm2.width("Our Alma Mater dear, looks up to you");
	painter.setFont(QFont("Chicago", 18)); 
	painter.drawText(400-textWidth/2, 416, "Our Alma Mater dear, looks up to you");*/
}

// Calls endGame and displays game over text and window
void SpaceWars::gameOverScreen(QPainter &painter)
{
	// call end game
	endGame();

	// draws appropriate window
	painter.drawImage(windowRect, windowImage);

	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 20));
	QFontMetrics fm2(QFont("Chicago", 18));
	int textWidth;
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 20)); 

	// Paint Text
	textWidth = fm.width("You Lose!");
	painter.drawText(400-textWidth/2, 344, "You Lose!");

	textWidth = fm2.width("Way to Bruin the Day!");
	painter.setFont(QFont("Chicago", 18)); 
	painter.drawText(400-textWidth/2, 380, "Way to Bruin the Day!");
}
 
// Displays intro screen text and window
void SpaceWars::introScreen(QPainter &painter)
{
	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 18));
	QFontMetrics fm2(QFont("Chicago", 20));
	int textWidth;
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 20)); 

	// draws appropriate window
	painter.drawImage(windowRect, windowImage);

	// Paint Text
	textWidth = fm2.width("The Battle for Planet Space!");
	painter.drawText(400-textWidth/2, 344, "The Battle for Planet Space!");

	painter.setFont(QFont("Chicago", 18));
	textWidth = fm.width("Press the Space Bar to start the Game!");
	painter.drawText(400-textWidth/2, 420, "Press the Space Bar to start the Game!");
}

// Displays paused screen text and window
void SpaceWars::pauseScreen(QPainter &painter)
{

	// draws appropriate window
	painter.drawImage(windowRect, windowImage);

	// Paint Text
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 15)); 
	painter.drawText(329, 344, "Game Paused!");
	painter.drawText(248, 380, "Press 'P' to continue the Game!");
	painter.drawText(384, 398, "or");
	painter.drawText(257, 416, "Press 'ESC' to Quit the Game!");
}

// paints default start up menu text and window
void SpaceWars::startUpScreen(QPainter &painter)
{
	// draws appropriate window
	painter.drawImage(window2Rect, window2Image);

	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 15));
	int textWidth;
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 15)); 

	// make temp QString conversions
	QString int_userCount = QString::number(userCount);
	QString int_relationCount = QString::number(relationCount);

	// paint text
	textWidth = fm.width("Number of users: 99   Number of relations: 99");
	painter.drawText(400-textWidth/2, 300, "Number of users: ");
	textWidth = fm.width("Number of users: 99   Number of relations: 99");
	int textWidth2 = fm.width("Number of users: ");
	painter.drawText(400-textWidth/2+textWidth2, 300, int_userCount);

	textWidth2 = fm.width("Number of users: 99   ");
	painter.drawText(400-textWidth/2+textWidth2, 300, "Number of relations: ");
	textWidth2 = fm.width("Number of users: 99   Number of relations: ");
	painter.drawText(400-textWidth/2+textWidth2, 300, int_relationCount);

	textWidth = fm.width("Please enter one of the following commands: ");
	painter.drawText(400-textWidth/2, 318, "Please enter one of the following commands: ");
}

// paints users screen menu text and window 
void SpaceWars::usersScreen(QPainter &painter)
{
  if(currentUser)
  {
	// draws appropriate window
	painter.drawImage(bigWindowRect, bigWindowImage);

	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 15));
	int textWidth, textWidth2;
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 15)); 

	// make temp QString conversions
	QString string_userName = QString::fromStdString(currentUser->getUsername());
	QString int_userCount = QString::number(userCount);
	QString int_relationCount = QString::number(relationCount);
	QString int_high = QString::number(currentUser->getScore());
	QString string_year = QString::fromStdString(currentUser->getYearName());

	// Paint Text
	textWidth = fm.width("Please enter one of the following commands: ");
	painter.drawText(400-textWidth/2, 74, "Number of users: ");
	textWidth2 = fm.width("Number of users: ");
	painter.drawText(400-textWidth/2+textWidth2, 74, int_userCount);

	textWidth2 = fm.width("Number of users: 99   ");
	painter.drawText(400-textWidth/2+textWidth2, 74, "Number of relations: ");
	textWidth2 = fm.width("Number of users: 99   Number of relations: ");
	painter.drawText(400-textWidth/2+textWidth2, 74, int_relationCount);

	painter.drawText(400-textWidth/2, 92, "User logged on:");

	painter.drawText(400-textWidth/2, 110, "user name: ");
	textWidth2 = fm.width("user name: ");
	painter.drawText(400-textWidth/2+textWidth2, 110, string_userName);

	painter.drawText(400-textWidth/2, 128, "year: ");
	textWidth2 = fm.width("year: ");
	painter.drawText(400-textWidth/2+textWidth2, 110+18, string_year);

	painter.drawText(400-textWidth/2, 146, "high score: ");
	textWidth2 = fm.width("high score: ");
	painter.drawText(400-textWidth/2+textWidth2, 128+18, int_high);

	painter.drawText(400-textWidth/2, 164, "friends: ");

	textWidth = fm.width("Please enter one of the following commands: ");
	painter.drawText(400-textWidth/2, 300, "Please enter one of the following commands: ");
  }
}

// paints log in screen menu text and window
void SpaceWars::logInScreen(QPainter &painter)
{


	// draws appropriate window
	painter.drawImage(bigWindowRect, bigWindowImage);

	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 15));
	int textWidth;
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 15)); 

	// Paint Text
	textWidth = fm.width("Log On to User Account");
	painter.drawText(400-textWidth/2, 92, "Log On to User Account");

	textWidth = fm.width("Please enter one of the following commands: ");
	painter.drawText(400-textWidth/2, 128, "Please choose from one of the following users: ");
}

// paints delete User screen menu text and window 
void SpaceWars::deleteUserScreen(QPainter &painter)
{

	// draws appropriate window
	painter.drawImage(bigWindowRect, bigWindowImage);

	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 15));
	int textWidth;
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 15)); 

	// Paint Text
	textWidth = fm.width("Delete User Account");
	painter.drawText(400-textWidth/2, 92, "Delete User Account");

	textWidth = fm.width("Please enter one of the following commands: ");
	painter.drawText(400-textWidth/2, 128, "Please choose from one of the following users: ");
}

// paints add user screen menu text, warnings, and window 
void SpaceWars::addUserScreen(QPainter &painter)
{

	// draws appropriate window
	painter.drawImage(windowRect, windowImage);

	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 15));
	int textWidth;
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 15)); 

	// Paint Text
	textWidth = fm.width("Please enter a Username and Year");
	painter.drawText(400-textWidth/2, 307, "Please enter a Username and Year");
	textWidth = fm.width("seperated by a space and then press enter: ");
	painter.drawText(400-textWidth/2, 328, "seperated by a space and then press enter: ");

	// Change font color for warning messages
	painter.setPen(QColor("yellow"));

	// Paint Appropriate Warning message
	if(warningCorruptDB)
	{
		textWidth = fm.width("'DB.txt' is corrupt. Please add a new User.");
		painter.drawText(400-textWidth/2, 403, "'DB.txt' is corrupt. Please add a new User.");
	}

	if(warningAddUser)
	{
		textWidth = fm.width("Invalid Input. Please Try Again.");
		painter.drawText(400-textWidth/2, 403, "Invalid Input. Please Try Again.");
	}

	if(warningDupeUser)
	{
		textWidth = fm.width("Existing user with that username.");
		painter.drawText(400-textWidth/2, 425, "Existing user with that username.");
	}
	else if(warningInvalidInput)
	{
		textWidth = fm.width("Example Input: 't_Trojan9 3'");
		painter.drawText(400-textWidth/2, 425, "Example Input: 't_Trojan9 3'");
	}
	else if(warningUserOOR)
	{
		textWidth = fm.width("Username can only contain");
		painter.drawText(400-textWidth/2, 425, "Username can only contain");
		textWidth = fm.width("alphanumeric or underscore characters.");
		painter.drawText(400-textWidth/2, 445, "alphanumeric or underscore characters.");
	}
	else if(warningYearOOR)
	{
		textWidth = fm.width("Year must be an interger from 1 to 5.");
		painter.drawText(400-textWidth/2, 425, "Year must be an interger from 1 to 5.");
	}

	// just in case set font color back to white
	painter.setPen(QColor("white"));
}

// paints high scores screen menu text and window 
void SpaceWars::scoresScreen(QPainter &painter)
{

	// draws appropriate window
	painter.drawImage(bigWindowRect, bigWindowImage);

	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 15));
	int textWidth;
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 15)); 

	// Paint Text
	textWidth = fm.width("The Best Scores of All Time:");
	painter.drawText(400-textWidth/2, 92, "The Best Scores of All Time:");

}

// paints current user's friends high scores screen menu text and window 
void SpaceWars::friendsScoresScreen(QPainter &painter)
{
  if(currentUser)
  {
	// draws appropriate window
	painter.drawImage(bigWindowRect, bigWindowImage);

	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 15));
	int textWidth;
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 15)); 

	// make temp QString conversions
	QString string_name = QString::fromStdString(currentUser->getUsername());

	// Paints Text
	textWidth = fm.width("'s friend's High Scores");
	textWidth += fm.width(string_name);
	painter.drawText(400-textWidth/2, 77, string_name + "'s friend's High Scores");
	textWidth = fm.width("The Best Scores of All Time:");
	painter.drawText(400-textWidth/2, 112, "The Best Scores of All Time:");
  }
}

// paints user list screen menu text and window 
void SpaceWars::userListScreen(QPainter &painter)
{
	// draws appropriate window
	painter.drawImage(bigWindowRect, bigWindowImage);

	// set up helper variables
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 15)); 
	QFontMetrics fm(QFont("Chicago", 15));
	int textWidth;

	// Paints Text
	textWidth = fm.width("User Accounts");
	painter.drawText(400-textWidth/2, 92, "User Accounts");

	textWidth = fm.width("These are the following active users: ");
	painter.drawText(400-textWidth/2, 128, "These are the following active users: ");
}

// paints add friend screen menu text and window 
void SpaceWars::addFriendScreen(QPainter &painter)
{
	// draws appropriate window
	painter.drawImage(bigWindowRect, bigWindowImage);

	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 15));
	int textWidth;
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 15)); 

	// Paints Text
	textWidth = fm.width("Add Friend");
	painter.drawText(400-textWidth/2, 92, "Add Friend");

	textWidth = fm.width("Please choose from one of the following users:");
	painter.drawText(400-textWidth/2, 128, "Please choose from one of the following users:");
}

// paints delete friend screen menu text and window 
void SpaceWars::deleteFriendScreen(QPainter &painter)
{
	// draws appropriate window
	painter.drawImage(bigWindowRect, bigWindowImage);

	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 15));
	int textWidth;
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 15)); 

	// Paints Text
	textWidth = fm.width("Delete Friend");
	painter.drawText(400-textWidth/2, 92, "Delete Friend");

	textWidth = fm.width("Please choose from one of the following users:");
	painter.drawText(400-textWidth/2, 128, "Please choose from one of the following users:");
}

// paints shortest path screen menu text and window 
void SpaceWars::shortestPathScreen(QPainter &painter)
{
	// draws appropriate window
	painter.drawImage(bigWindowRect, bigWindowImage);

	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 15));
	int textWidth;
	painter.setPen(QColor("white"));
	painter.setFont(QFont("Chicago", 15)); 

	// Paints Text
	textWidth = fm.width("Please enter one of the following commands: ");
	painter.drawText(400-textWidth/2, 92, "Please Choose from one of the following users: ");

	if(shortestPathString2 > "")
		painter.setPen(QColor(Qt::green));
	else
		painter.setPen(QColor(Qt::red));

	textWidth = fm.width(shortestPathString1);
	painter.drawText(400-textWidth/2, 128, shortestPathString1);
	textWidth = fm.width(shortestPathString2);
	painter.drawText(400-textWidth/2, 146, shortestPathString2);
	painter.setPen(QColor("white"));

}
