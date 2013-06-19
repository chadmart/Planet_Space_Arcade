/*!\file spacewars.cpp
 * 
 * \brief Contians the basic game logic implentations of the SpaceWars class
 * 
 * \Created by: Spencer Moran 
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/26/2012
 *
 * This class contians the basic game logic implentations of the SpaceWars class.
 */

#include "spacewars.h"
#include <QPainter>
#include <QApplication>
#include <list>
#include <stdlib.h>
#include <fstream>
#include <sstream>



SpaceWars::SpaceWars(QWidget *parent)
    : QWidget(parent)
{

  // dark grey/blue color	
  QColor colorCustom( 34, 44, 61);
  // off white color
  QColor colorCustom2( 240, 239, 238);
  //set up pallette
  pal.setBrush(QPalette::Base,  colorCustom);
  pal.setBrush(QPalette::Button,  colorCustom);
  pal.setBrush(QPalette::Text, Qt::white);
  pal.setBrush(QPalette::Window, colorCustom2);

  //set up initial buttons
  setUpInitialButtons();

  //set the window focus policy
  this->setFocusPolicy(Qt::ClickFocus);

  //set the initial flag conditions
  cheated = false;
  cheatsEnabled = false;
  menuDisplayed = true;
  displayStartUp  = true;
  displayLogIn = false;
  displayDeleteUser = false;
  displayAddUser = false;
  displayOptions = false;
  displayScores = false;
  displayFriendsScores = false;
  displayUserScreen = false;
  displayUserList = false;
  displayAddFriend = false;
  displayDeleteFriend = false;
  displayShortestPath = false;
  warningAddUser = false;
  warningDupeUser = false;
  warningInvalidInput = false;
  warningYearOOR = false;
  warningUserOOR = false;
  warningCorruptDB = false;
  gameOver = false;
  gameWon = false;
  paused = false;
  gameStarted = false;
  killPlayer = false;
  nextLevel = false;
  prevLevel = false;
  freezeFlag = false;
  godMode = false;
  shieldFlag = false;
  tripleShot = false;
  deathShroom = false;
  keepLeft = false;
  keepRight = false;
  keepShoot = false;
  corruptDB= false;

  //initialize other variables
  lives = 3;
  score = 0;
  level = 0;
  freezeCount = 0;
  shortestPathString1 = "";
  shortestPathString2 = "";
  currentUser = NULL;
  viewUsersBox = NULL;
  smallFriendsBox = NULL;
  addUserBox = NULL;
  highScoreBox = NULL;

  //create a spaceship object
  spaceship = new Spaceship();

  //create the initial 3 badguys
  makeBadGuys();

  //create a boss object
  boss = new Boss2();
  boss->setActive(false);
  boss->setLocation(150, -450);

  // set up level 1 backgroud
  levelbackImage.load("images/level1.png"); 
  levelbackRect = levelbackImage.rect();
  levelbackRect.moveTo(0,0);

  // set up windows
  windowImage.load("images/window.png"); 
  windowRect = windowImage.rect();
  windowRect.moveTo(108,246);

  window2Image.load("images/window2.png"); 
  window2Rect = window2Image.rect();
  window2Rect.moveTo(108,246);

  bigWindowImage.load("images/bigwindow.png"); 
  bigWindowRect = bigWindowImage.rect();
  bigWindowRect.moveTo(108,20);

  // set up top bar
  topBarImage.load("images/topBar.png"); 
  topBarRect = topBarImage.rect();
  topBarRect.moveTo(0,0);

  //read in DB
  readDB();

  //check if database is corrupt 
  if(corruptDB)
  {	//if so display warning msg and go to add user screen
	warningCorruptDB = true;
	addUserButtonSlot();
  }

}

SpaceWars::~SpaceWars()
{
	// writes out to db.txt
	writeDB();

	//deallocate memory for the spaceship
	delete spaceship;

	//deallocate memory for the spaceship
	delete boss;

	//deallocate memory for the Badguys
	for(int i = 0; i < 4;i++)
	{
	  for(int j = 0; j < 3; j++)
	  {
		delete badguys[i][j];
	  }
	}

	//deallocate memory for the Users
	if(!userList.empty())
	{
		int size = userList.size();

		for(int i = 0; i < size; i++)
		{
			delete userList.at(0);
			userList.erase(userList.begin());
		}
	}
}

// Sets badguys up for the start of a new game
void SpaceWars::makeBadGuys()
{
	for(int i = 0; i < 4;i++)
	{
	  for(int j = 0; j < 3; j++)
	  {
		badguys[i][j] = new B1();
		badguys[i][j]->setActive(false);
		badguys[i][j]->setLocation(150+(i*100), -450+(j*100)); 
		badguys[i][j]->setExploded(false);
		badguys[i][j]->setExploding(false);
	  }
	}
}

// Paints the necessary object on the screen.
void SpaceWars::paintEvent(QPaintEvent *event)
{
	//create a QPainter object to paint in the window
	QPainter painter(this);

	//draws background image
	painter.drawImage(levelbackRect, levelbackImage);

	//draws topbar image
	if(currentUser && !gameStarted)
		painter.drawImage(topBarRect, topBarImage);

	//check to see if level Up conditions are met
	if(nextLevel)
	{
		//check to see if level Up is needed
		if(level > 0 && level < 12)
			changeLevel();
		//check to see if victory condition is met
		else if (level == 12)
		{
            gameWon = true;

            // if not on screen, build end game buttons
            if(!restartButton->isVisible())
                buildEndGameButtons();
		}
	}

	//check to see if level down conditions are met
	if(prevLevel)
	{
		//check to see if level Up is needed
		if(level > 1 && level <= 12)
			changeLevel();
		else
			prevLevel = false;
	}

	if(gameStarted)
	{
		//draw the spaceship
		painter.drawImage(spaceship->getRect(), spaceship->getImage());
	
		//if godMode, draw the godShield on top of the player's spaceship
		if(godMode)
		{
			godShield.move((spaceship->getRect()).x(),(spaceship->getRect()).y());
			painter.drawImage(godShield.getRect(), godShield.getImage());
		}

		//if shieldFlag, draw the tempShield on top of the player's spaceship
		if(shieldFlag)
		{
			tempShield.move((spaceship->getRect()).x(),(spaceship->getRect()).y());
			painter.drawImage(tempShield.getRect(), tempShield.getImage());
		}

		//draw the spaceship's bullets
		list<Bullet*>::iterator bulletIterator;
		for (bulletIterator = bullets.begin(); bulletIterator != bullets.end(); bulletIterator++)
		{
			painter.drawImage((*bulletIterator)->getRect(), (*bulletIterator)->getImage());
		}
	
		//draw all of the powerUps
		for(int i = 0; i < powerUps.size(); i++)
		{
			painter.drawImage(powerUps.at(i)->getRect(),powerUps.at(i)->getImage());
		}

		//draw boss if the boss is active
		if (boss->isActive())
				painter.drawImage(boss->getRect(), boss->getImage());


		//draw the all of the boss's bullets, if any
		if(!bossBullets.empty())
		{
			list<BossBullet*>::iterator bossIterator;
			for (bossIterator = bossBullets.begin(); bossIterator != bossBullets.end(); bossIterator++)
			{
				painter.drawImage((*bossIterator)->getRect(), (*bossIterator)->getImage());
			}
		}

		//draw the all of the exploding boss's bullets, if any
		if(!explodingBossBullet.empty())
		{
			for(unsigned int i = 0; i < explodingBossBullet.size(); i++)
			{
				painter.drawImage((explodingBossBullet.at(i))->getRect(), (explodingBossBullet.at(i))->getImage());
			}
		}

		//if the badguys are active, draw them
		for(int i = 0; i < 4;i++)
		{
		  for(int j = 0; j < 3; j++)
		  {
			if (badguys[i][j]->isActive())
				painter.drawImage(badguys[i][j]->getRect(), badguys[i][j]->getImage());
	     	  }
		}

		//draw the badguy's bullets, if any
		if(!badguyBullets.empty())
		{
			//draw the badguy's bullets
			list<Bullet*>::iterator badguyIterator;
			for (badguyIterator = badguyBullets.begin(); badguyIterator != badguyBullets.end(); badguyIterator++)
			{
				painter.drawImage((*badguyIterator)->getRect(), (*badguyIterator)->getImage());
			}
		}

		//if the flag for the spaceship being hit is true
		if (killPlayer)
		{
			//if the player is not out of lives, respawn the ship
			if (lives > 0)
			{
	  			respawnShip();
			}
			//if the player is out of lives, end the game
			else
			{
				gameOver = true;	
                // if not on screen, build end game buttons
                if(!restartButton->isVisible())
                    buildEndGameButtons();
				gameOverScreen(painter);
				killPlayer = false;
			}
		}

		//draws topbar image
		if(currentUser)
			painter.drawImage(topBarRect, topBarImage);
	
		// Don't let user get more than 99 lives
		if (lives > 99)
			lives = 99;

		// create a white pen to write in the window
		painter.setPen(QColor("white"));
    		painter.setFont(QFont("Chicago", 11)); 
		QString int_score = QString::number(score);
		QString int_lives = QString::number(lives);
		QString int_level = QString::number(level);

		// display correct oaused message to user
		if(paused)
			painter.drawText(90, 15, "Press P to Resume");
		else
			painter.drawText(90, 15, "Press P to Pause");

		// diplay info about cheats and high score to user
		if(cheated && cheatsEnabled)
			painter.drawText(220, 15, "Cheats Enabled High Score Disabled");
		else if(cheatsEnabled)
			painter.drawText(280, 15, "Cheats Enabled");
		else if(cheated)
			painter.drawText(280, 15, "High Score Disabled");

		// write the level in the window
		painter.drawText(500, 15, "Level: ");
		painter.drawText(547, 15, int_level);

		// write the lives in the window
		painter.drawText(573, 15, "Lives: ");
		if (lives > -1)
			painter.drawText(621, 15, int_lives);

		// write the score in the window
		painter.drawText(644, 15, "Score:");
		painter.drawText(699, 15, int_score);
	}

	if(paused)
	{
		//display paused text
		pauseScreen(painter);
	}
	//check to see if game over conditions are met
	if(!gameStarted && !gameWon && !gameOver )
	{
		//chooses correct menu screen
		if(displayStartUp)
		{
			startUpScreen(painter);
		}			
		else if(displayLogIn)
		{
			logInScreen(painter);
		}
		else if(displayAddUser)
		{
			addUserScreen(painter);
		}
		else if(displayDeleteUser)
		{
			deleteUserScreen(painter);
		}			
		else if(displayScores)
		{
			scoresScreen(painter);
		}
		else if(displayFriendsScores)
		{
			friendsScoresScreen(painter);
		}
		else if(displayUserScreen)
		{
			usersScreen(painter);
		}
		else if(displayUserList)
		{
			userListScreen(painter);
		}
  		else if (displayAddFriend)
		{
			addFriendScreen(painter);
		}
  		else if(displayDeleteFriend)
		{	
			deleteFriendScreen(painter);
		}
		else if(displayShortestPath)
		{
			shortestPathScreen(painter);
		}			
		else
			introScreen(painter);
	}
	//check to see if victory conditions are met
	else if(gameWon)
	{
		//display victory text
		victoryScreen(painter);
	}
	//check to see if game over conditions are met
	else if(gameOver)
	{
		//display game over text
		gameOverScreen(painter);
	}
}

// Occurs when ever a timer event is called.
void SpaceWars::timerEvent(QTimerEvent *e)
{
	if (e->timerId() == timerId)
	{
		//check if current user highscore is beaten
		if(currentUser)
		  if(currentUser->getScore() < score && !cheated)
			currentUser->setScore(score);
		
		//increment variable to control bullet firing rate
		bulletCounter++;

		//move the bullets
		moveBullets();

		//allows move and shoot!!!
			//if left directional is held down
			if(keepLeft)
			{
				int x = spaceship->getRect().x();
				spaceship->moveLeft(x-3);
			}
			//if right directional is held down
			if(keepRight)
			{
				int x = spaceship->getRect().x();
				spaceship->moveRight(x+3);
			}
			//if space bar is held down
			if(keepShoot)
				goodShipShoot();

		//create a flag for each ship to know if it is hit or not
		bool spaceshipHit = false, badguyhit[4][3], bossHit = false;

		//initialize badguyhit flags
		for(int i = 0; i <4; i++)
		{
		  for(int j = 0; j < 3; j++)
		  {
			badguyhit[i][j] = false;	
		  }
		}

		// if temporary god mode is activated
		if(tempGodFlag)
		{
			//set godMode = true
			godMode= true;
			//increment variable to temporary god mode
			godCount ++;

			if(godCount==700)
			{
				//terminate temporary god mode
				godMode= false;
				godCount = 0;	
				tempGodFlag = false;	
			}	
		}

		//check to see if a collision has occured
		checkCollisions(spaceshipHit, badguyhit, bossHit);

		// if ship hit and not in godMode, then explode
		if ((spaceshipHit || deathShroom) && !spaceshipExploding && !godMode)
		{
			spaceshipExploding = TRUE;
			timerSpaceshipHit = startTimer(100);
			QPoint center = spaceship->getRect().center();
			spaceship->getImage().load("images/explosionone.png");
			spaceship->getRect() = spaceship->getImage().rect();
			spaceship->getRect().moveCenter(center);
			spaceshipIndex = 1;
		}

		for(int i = 0; i < 4;i++)
		{
		  for(int j = 0; j < 3; j++)
		  {
			//if badguyhit and has hitpoints, lower hit points 
			if (badguyhit[i][j] && !badguys[i][j]->isExploding()  && badguys[i][j]->isActive() && badguys[i][j]->getHitPoints() > 0)
			{
				badguys[i][j]->lowerHitPoints(1);
			}
			//if badguyhit and has no hitpoints, set up for exploding badguy
			else if (badguyhit[i][j] && !badguys[i][j]->isExploding() && badguys[i][j]->isActive() && badguys[i][j]->getHitPoints() == 0)
			{
				badguys[i][j]->setExploding(TRUE);	
				QPoint center = badguys[i][j]->getRect().center();
				badguys[i][j]->getImage().load("images/explosionone.png");
				badguys[i][j]->getRect() = badguys[i][j]->getImage().rect();
				badguys[i][j]->getRect().moveCenter(center);
				badguyIndex[i][j] = 1;

				dropPowerUp(i,j);
			}
		  }
		}

		//if boss and has hitpoints, lower hit points 
		if (boss->isActive() && bossHit && !bossExploding && boss->getHitPoints() > 0)
		{
			boss->lowerHitPoints(1);
		}
		//if boss and has no hitpoints, set up for exploding boss
		else if (boss->isActive() && bossHit && !bossExploding && boss->getHitPoints() == 0)
		{
			bossExploding = TRUE;
			timerbossHit = startTimer(100);
			QPoint center = boss->getRect().center();
			boss->getImage().load("images/explosionone.png");
			boss->getRect() = spaceship->getImage().rect();
			boss->getRect().moveCenter(center);
			bossIndex = 1;
		}
	}

	//if spaceship is exploding, keep exploding it
	else if (e->timerId() == timerSpaceshipHit)
	{
		explodeSpaceship();
	}
	//if boss is exploding, keep exploding it
	else if (e->timerId() == timerbossHit)
	{
		explodeBoss();
	}
	else if(e->timerId() == timerExplosions)
	{
		for(int i = 0; i < 4;i++)
		{
		  for(int j = 0; j < 3; j++)
		  {
			//if badguy is exploding, keep exploding it
			if (badguys[i][j]->isExploding())
			{
				explodeBadguy(i,j);
			}
		  }
		}

		if(!explodingBossBullet.empty())
		{
			//if any boss bullets exploding, keep exploding it
			for(unsigned int i =0; i < explodingBossBullet.size() ;i++)
			{
				explodeBossBullet(explodingBossBullet.at(i));
			}

			//if any boss bullets is done exploding, delete it
			for(unsigned int i =0; i < explodingBossBullet.size() ;i++)
			{
				if(explodingBossBullet.at(i)->getIndex() == 6)
				{
					BossBullet *del = explodingBossBullet.at(i);
					explodingBossBullet.erase(explodingBossBullet.begin()+i);
					delete del;
					i--;
				}
			}
		}
	}
	else if (e->timerId() == timerBadguyBullet)
	{
	  // if not frozen, execute chance to shoot for badguys
	  if(!freezeFlag)
	  {
		for(int i = 0; i < 4;i++)
		{
		  for(int j = 0; j < 3; j++)
		  {
			// Chance to shoot for badguys inceases with the every 3 levels
			if (badguys[i][j]->isActive() && (rand() % (5-((level+2)/3)) == 0) )
			{
				Bullet *badguyBullet = new BadBullet((badguys[i][j]->getRect().left() + badguys[i][j]->getRect().right()) / 2 , badguys[i][j]->getRect().bottom());
	  			badguyBullets.push_back(badguyBullet);
			}
		  }
		}

		// Chance to shoot for the bosses inceases with the every 3 levels and when the boss has low hit points
		if(boss->isActive() && ((rand() % (5-((level+2)/3)) == 0) || (boss->getHitPoints() <= 4 && level >= 9)))
		{
			BossBullet *bossBullet = new BossBullet( (boss->getRect().left() + boss->getRect().right()) / 2 , boss->getRect().bottom());
	  		bossBullets.push_back(bossBullet);
		}

	  }
	}
	else if (e->timerId() == timerBadguyMove)
	{
	  
	  if(freezeFlag)
	  {
		// increment variable to control the length of badguy freeze		
		freezeCount++;
		if(freezeCount==200)
		{
			// reset freeze variables
			freezeCount = 0;
			freezeFlag = false;
		}
	  }
	  else //if badguys not frozen
	  {
		for(int i = 0; i < 4;i++)
		{
		  for(int j = 0; j < 3; j++)
		  {
			//move badguys
			if (badguys[i][j]->isActive())
 				badguys[i][j]->move();

			if (badguys[i][j]->offScreen())
			{
				badguys[i][j]->setActive(false);
			}	
		  }
		}

		//move boss
		if (boss->isActive())
 			boss->move();

		if (boss->offScreen())
		{
			boss->setActive(false);
		}
	  }
	}
		
	repaint();
}

// Carries out the required actions for the specific key press
void SpaceWars::keyPressEvent(QKeyEvent *event)
{
  // prevents repeat key press events & allows simultaneous key press actions
  if(event->isAutoRepeat() ) 
  {    
	return;  
  } 
  else 
  {

    switch (event->key()) {


    case Qt::Key_Semicolon:
       {
	  // toggle cheats enabled/disabled
	  if(cheatsEnabled)
		cheatsEnabled = false;
	  else
		cheatsEnabled = true;
	break;
       }
    case Qt::Key_L:
       {  
		// display log in screen
		if(displayStartUp)
		{
			logOnButtonSlot();
		}
        break;
       }
    case Qt::Key_H:
       {  
	  if(displayStartUp || displayUserScreen)
	  {
	  	// list highscores
		listAllScoresButtonSlot();
	  }
        break;
       }
    case Qt::Key_B:
       {  
	// Go back to previous screen or 
	// if User Screen  displayed then display shortest path screen
		if(displayScores)
		{
			if(!currentUser)
			{
				goBack2StartUp();
			}	
			else
			{
				goBack2UserScreen();
			}

		}
		else if(displayFriendsScores)
		{
			goBack2UserScreen();
		}
		else if(displayDeleteUser)
		{
			goBack2StartUp();
		}
		else if(displayLogIn)
		{
			goBack2StartUp();
		}
		else if(displayAddUser)
		{
			goBack2StartUp();
		}
		else if(displayUserList)
		{
			goBack2UserScreen();
		}
		else if(displayAddFriend)
		{
			goBack2UserScreen();
		}
		else if(displayDeleteFriend)
		{
			goBack2UserScreen();
		}
		else if(displayShortestPath)
		{
			goBack2UserScreen();
		}
		else if(displayUserScreen)
		{
			shortestPathButtonSlot();
		}
		else if(!gameStarted && !gameWon && !gameOver )
		{
			goBack2UserScreen();
		}

        break;
       }
    case Qt::Key_T: 
       {  
		if(gameStarted)
		{
		  // Toggle god mode
		  if(!godMode && cheatsEnabled)
		  {
			godMode = true;
			cheated = true;
		  }
		  else
			godMode = false;
		}
        break;
       }
      
    case Qt::Key_F:
       { 
		// display add new friend screen
		if(displayUserScreen)
		  {addFriendButtonSlot();}
	break;
	}  
    case Qt::Key_A:
       { 
		// display list of all users screen
		if(displayUserScreen)
		  {listAllUsersButtonSlot();}
    case Qt::Key_Left:
		//Go Left
		if(!gameStarted && !menuDisplayed)
			startGame();
		else if(gameStarted)
		{
		 	if(!keepLeft) 
			{
				int x = spaceship->getRect().x();

				spaceship->moveLeft(x-3);
			}
		}
				keepLeft = true;
        
       }
 	break;
    case Qt::Key_D:
        {
		// display delete a friend screen
		if(displayUserScreen)
		{deleteFriendButtonSlot();}
    case Qt::Key_Right:
		//Go Right
		if(!gameStarted && !menuDisplayed)
			startGame();
		else
		{
		 	if(!keepRight)
			{
		  		int x = spaceship->getRect().x();

				spaceship->moveRight(x+3);
		 	}
		}
				keepRight = true;
        }
        break;
   /* case Qt::Key_Up:
    case Qt::Key_W:
        { 
		//Go Up
		  int y = spaceship->getRect().y();
		  for (int i=1; i<=10; i++)
		    spaceship->moveUp(y--);
        }
	break;
    case Qt::Key_Down:*/
    case Qt::Key_S:
        { 
		// display list of all friends scores screen
		if(displayUserScreen)
			{listFriendsScoresButtonSlot();}
		/*//Go Down
		  int y = spaceship->getRect().y();
		  for (int i=1; i<=10; i++)
		    spaceship->moveDown(y++);*/
        }
	break;
    case Qt::Key_P:
        { 
	  if(displayUserScreen)
	  {
		// start playing game mode
	 	playGameButtonSlot();
	  }
	  else if(gameStarted && !gameOver && !gameWon)
	  {
		  //toggle pause game
		  pauseGame();
	  }
        }
        break;

    case Qt::Key_R:
	if(!menuDisplayed)
	{
		//restart game
		restartGameButtonSlot();
	}
		break;

    case Qt::Key_Space:
        {
		//Start Shoot
		if(!gameStarted && !menuDisplayed)
		{
			startGame();
		}
		else
		{
			if(!keepShoot) 
				goodShipShoot();
		}	
			keepShoot = true;	
        }
        break;
    case Qt::Key_M:
	{
	  if(!gameStarted && !menuDisplayed)
		//start game
		startGame();
	}
	break;
    case Qt::Key_Escape:
    case Qt::Key_Q:
        {
	  // Quit
          qApp->exit();
        }
        break;
    case Qt::Key_1:
	{
	  //if cheats enabled, drop an extra life
	  if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P1);
	  }
	}
	break;
    case Qt::Key_2:
	{
	  //if cheats enabled, drop a triple extra life
	  if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P2);
	  }
	}
	break;
    case Qt::Key_3:
	{
	  //if cheats enabled, drop a deathshroom
	  if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P3);
	  }
	}
	break;
    case Qt::Key_4:
	{
 	  //if cheats enabled, drop a double points
	  if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P4);
	  }
	}
	break;
    case Qt::Key_5:
	{
 	  //if cheats enabled, drop a bankrupt points
	  if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P5);
	  }
	}
	break;
    case Qt::Key_6:
	{
 	  //if cheats enabled, drop a vicotry pow
	  if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P6);
	  }
	}
	break;
    case Qt::Key_7:
	{
	  //if cheats enabled, drop a +10 points
	  if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P7);
	  }
	}
	break;
    case Qt::Key_8:
	{
	  //if cheats enabled, drop a +100 points
	  if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P8);
	  }
	}
	break;
    case Qt::Key_9:
	{
	  //if cheats enabled, drop a freeze
	  if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P9);
	  }
	}
	break;
    case Qt::Key_0:
	{
	  //if cheats enabled, drop a level up
	  if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P10);
	  }
	}
	break;
    case Qt::Key_Minus:
	{
	  //display delete user screen
	  if(displayStartUp)
	  {
		deleteUserButtonSlot();
	  }
	  //if cheats enabled, drop a level down
	  else if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P11);
	  }
	}
	break;
    case Qt::Key_Plus:
    case Qt::Key_Equal:
	{
	  // display add user screen
          if(displayStartUp)
		addUserButtonSlot();

	  //if cheats enabled, drop a game over skull
	  else if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P12);
	  }
	}
	break;
    case Qt::Key_Backspace:
	{
	  //if cheats enabled, drop a temporary gode mode star
	  if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P14);
	  }
	}
	break;
    case Qt::Key_Backslash:
	{
	  //if cheats enabled, drop a Temporary shield
	  if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P15);
	  }
	}
	break;
    case Qt::Key_BracketRight:
	{
	  //if cheats enabled, drop a triple shot mushroom
	  if (gameStarted && cheatsEnabled)
	  {
		cheated = true;
	  	dropPowerUp(350,-100, new P16);
	  }
	}
	break;
    default:
        QWidget::keyPressEvent(event);
    }
  }
}

// Carries out the required actions for the specific key release
void SpaceWars::keyReleaseEvent(QKeyEvent *event)
{
	// prevents repeat key release events & allows simultaneous key press actions
   	if(event->isAutoRepeat() ) 
	{    
            return;  
        } 
	else 
	{
		if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
   		{
			// if left directional is released stop moving left
			keepLeft = false;
		}
		else if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
		{
			// if right directional is released stop moving right
			keepRight = false;
		}
		else if(event->key() == Qt::Key_Space)
		{
			// if spacebar is released stop shoot
			keepShoot = false;
		}
		else
		{
       			QWidget::keyReleaseEvent(event);
		}
        }
}

// Starts the timers and begins the actual game
void SpaceWars::startGame()
{ 
  if (!gameStarted) {

	// hide buttons displayed on intro screen
	if(goBackButton)
		goBackButton->hide();
	if(quitGameButton)
		quitGameButton->hide();

	//move the spaceship to its initial position
    	spaceship->resetState();
    
	//initialize flag and counting variables
    	gameOver = false; 
    	gameWon = false; 
    	gameStarted = TRUE;
	lives = 3;
	score = 0;
	bulletCounter = 51;
	lastShotTime = 0;
	spaceshipExploding = false;
	bossExploding = false;
	deathCount = 0;
  	freezeFlag = false;
  	godMode = false;
	tempGodFlag = false;
	godCount = 0;
	shieldFlag = false;
	cheated = false;
	cheatsEnabled = false;

	//initialize timers
	delayBadguyMove = 20;
	delayBadguyBullet = 1500;
    	timerId = startTimer(10);
    	timerExplosions = startTimer(60);
	timerBadguyMove = startTimer(delayBadguyMove);
    	timerBadguyBullet = startTimer(delayBadguyBullet);
	
	//active badguys
	for(int i = 0; i < 4;i++)
	{
	  for(int j = 0; j < 3; j++)
	  {
		badguys[i][j]->setActive(TRUE);
		badguys[i][j]->setExploded(false);
		badguys[i][j]->setExploding(false);
	  }
	}

	//increase level to 1
	level++;

  }
}

// Pauses the Game
void SpaceWars::pauseGame()
{
  //if unpausing, start all the timers again
  if (paused) 
  {
    	timerId = startTimer(10);
    	timerExplosions = startTimer(60);
	timerBadguyMove = startTimer(delayBadguyMove);
    	timerBadguyBullet = startTimer(delayBadguyBullet);
    	paused = false;
  } 
  
  //if pausing, kill all active timers
  else 
  {
    	paused = TRUE;

	bulletCounter = 51;
	lastShotTime = 0;

    	killTimer(timerId);
	killTimer(timerExplosions);
	killTimer(timerBadguyMove);
	killTimer(timerBadguyBullet);
	
	repaint();
   }
}


// kills the timers and sets up variables to stop game play
void SpaceWars::endGame()
{
	//kill all timers
	killTimer(timerId);
	killTimer(timerExplosions);
	killTimer(timerBadguyMove);
	killTimer(timerBadguyBullet);
  
	//set all badguys to inactive
	for (int i = 0; i<4; i++)
	  for(int j= 0;j<3;j++)
		badguys[i][j]->setActive(false);

	//sets boss to inactive
	boss->setActive(false);

	//deletes all bullets
	clearBullets();

	//deletes active power ups
	if(!powerUps.empty())
	{
		int size = powerUps.size();

		for(int i = 0; i < size; i++)
		{
			delete powerUps.at(0);
			powerUps.erase(0);
		}
	}

	// disables shields
  	godMode = false;
  	shieldFlag = false;
}

// Restarts the game
void SpaceWars::restartGame()
{
	//kills all timers
	killTimer(timerId);
	killTimer(timerExplosions);
	killTimer(timerBadguyMove);
	killTimer(timerBadguyBullet);

	//deletes all bullets
	clearBullets();

	//deletes all active power ups
	if(!powerUps.empty())
	{
		int size = powerUps.size();

		for(int i = 0; i < size; i++)
		{
			delete powerUps.at(0);
			powerUps.erase(0);
		}
	}

	//set all badguys to inactive
	for(int i = 0; i < 4;i++)
	{
	  for(int j = 0; j < 3; j++)
	  {
		badguys[i][j]->setActive(false);
	  }
	}

	//deallocate memory for current spaceship
	delete spaceship;

	//create a new spaceship
	spaceship = new Spaceship();

	//deallocate memory for current boss
	delete boss;

	//create a new boss
	boss = new Boss1();
	boss->setActive(false);
  	boss->setLocation(150, -450);

	//deallocate memory for all badguys
	for(int i = 0; i < 4;i++)
	{
	  for(int j = 0; j < 3; j++)
	  {
		delete badguys[i][j];
	  }
	}

	//create the initial badguys
	makeBadGuys();
	
	//loads level 1 background image
	levelbackImage.load("images/level1.png"); 

	//sets up default variables
	lives = 3;
	score = 0; 
  	level = 0;	
	nextLevel = false;
	prevLevel = false;
	deathCount = 0;
  	godMode = false;
  	shieldFlag = false;
	tripleShot = false;
	deathShroom = false;
	gameWon = false;
	gameOver = false;
	gameStarted = false;
  	keepLeft = false;
  	keepRight = false;
  	keepShoot = false;

	//repaints new screen
	repaint();
}

//if spaceship is hit, respawn ship, and subtract a life
void SpaceWars::respawnShip()
{
	if (killPlayer)
	{
		//move the spaceship to its initial position
		spaceship->resetState();

		//initialize counting variables and flags
		spaceshipExploding = false;
		bulletCounter = 51;
		lastShotTime = 0;
		killPlayer = false;
		tripleShot = false;
		deathShroom = false;
		freezeFlag = false;
		tempGodFlag = false;
		shieldFlag = false;
	}
}

// Changes the level either up or down
void SpaceWars::changeLevel()
{
		if(nextLevel)
		{
			level++;
			nextLevel = false;
		}
		
		if(prevLevel)
		{
			level--;
			prevLevel = false;
		}

		//reset death count
		deathCount = 0;

		//delete old level of badguys
		for(int i = 0; i < 4;i++)
		{
		  for(int j = 0; j < 3; j++)
		  {
			delete badguys[i][j];
		  }
		}	

		//deallocate memory for current boss
		delete boss;

 		switch(level)
		{
		case 1:
			//Load level 1 image
			levelbackImage.load("images/level1.png"); 

			//Create level 1 badguys
			for(int i = 0; i < 4;i++)
			{
			  for(int j = 0; j < 3; j++)
			  {
				badguys[i][j] = new B1();
				badguys[i][j]->setActive(TRUE);
				badguys[i][j]->setExploded(false);
				badguys[i][j]->setExploding(false);
				badguys[i][j]->setLocation(150+(i*100), -450+(j*100)); 
			  }
			}

			//create a new boss
			boss = new Boss1();
			boss->setActive(false);

			// set level 1 speed
			delayBadguyMove = 20;
			delayBadguyBullet = 1500;
			killTimer(timerBadguyMove);
			killTimer(timerBadguyBullet);
			timerBadguyMove = startTimer(delayBadguyMove);
    			timerBadguyBullet = startTimer(delayBadguyBullet);

			break;

		case 2:
			//Load level 2 image
			levelbackImage.load("images/level2.png"); 

			//Create level 2 badguys
			for(int i = 0; i < 4;i++)
			{
			  for(int j = 0; j < 3; j++)
			  {
				if(j == 0)
					badguys[i][j] = new B1b();
				else
					badguys[i][j] = new B1();

				badguys[i][j]->setActive(TRUE);
				badguys[i][j]->setExploded(false);
				badguys[i][j]->setExploding(false);
				badguys[i][j]->setLocation(150+(i*100), -450+(j*100)); 
			  }
			}

			//create a new boss
			boss = new Boss1();
			boss->setActive(false);

			// set level 2 speed
			delayBadguyMove = 20;
			delayBadguyBullet = 1500;
			killTimer(timerBadguyMove);
			killTimer(timerBadguyBullet);
			timerBadguyMove = startTimer(delayBadguyMove);
    			timerBadguyBullet = startTimer(delayBadguyBullet);

			break;

		case 3:
			//Load level 3 image
			levelbackImage.load("images/level3.png"); 

			//Create level 3 badguys
			for(int i = 0; i < 4;i++)
			{
			  for(int j = 0; j < 3; j++)
			  {
				if(j < 2)
					badguys[i][j] = new B1b();
				else
					badguys[i][j] = new B1();

				badguys[i][j]->setActive(TRUE);
				badguys[i][j]->setExploded(false);
				badguys[i][j]->setExploding(false);
				badguys[i][j]->setLocation(150+(i*100), -450+(j*100)+75); 
			  }
			}

			//create a new boss
			boss = new Boss1();
			boss->setActive(TRUE);
			boss->setExploded(false);
	  		boss->setLocation(150, -450);

			// set level 3 speed
			delayBadguyMove = 20;
			delayBadguyBullet = 1500;
			killTimer(timerBadguyMove);
			killTimer(timerBadguyBullet);
			timerBadguyMove = startTimer(delayBadguyMove);
    			timerBadguyBullet = startTimer(delayBadguyBullet);

			break;

		case 4:
			//Load level 4 image
			levelbackImage.load("images/level4.png"); 

			//Create level 4 badguys
			for(int i = 0; i < 4;i++)
			{
			  for(int j = 0; j < 3; j++)
			  {
				badguys[i][j] = new B2();
				badguys[i][j]->setActive(TRUE);
				badguys[i][j]->setExploded(false);
				badguys[i][j]->setExploding(false);
				badguys[i][j]->setLocation(150+(i*100), -450+(j*100)); 
			  }
			}

			//create a new boss
			boss = new Boss2();
			boss->setActive(false);

			// set level 4 speed
			delayBadguyMove = 20;
			delayBadguyBullet = 1500;

			break;

		case 5:
			//Load level 5 image
			levelbackImage.load("images/level5.png"); 

			//Create level 5 badguys
			for(int i = 0; i < 4;i++)
			{
			  for(int j = 0; j < 3; j++)
			  {
				if(j == 0)
					badguys[i][j] = new B2b();
					
				else
					badguys[i][j] = new B2();
				badguys[i][j]->setActive(TRUE);
				badguys[i][j]->setExploded(false);
				badguys[i][j]->setExploding(false);
				badguys[i][j]->setLocation(150+(i*100), -450+(j*100)); 
			  }
			}

			//create a new boss
			boss = new Boss2();
			boss->setActive(false);

			// set level 5 speed
			delayBadguyMove = 20;
			delayBadguyBullet = 1500;
			killTimer(timerBadguyMove);
			killTimer(timerBadguyBullet);
			timerBadguyMove = startTimer(delayBadguyMove);
    			timerBadguyBullet = startTimer(delayBadguyBullet);

			break;

		case 6:
			//Load level 6 image
			levelbackImage.load("images/level6.png"); 

			//Create level 6 badguys
			for(int i = 0; i < 4;i++)
			{
			  for(int j = 0; j < 3; j++)
			  {
				if(j < 2)
					badguys[i][j] = new B2b();
					
				else
					badguys[i][j] = new B2();

				badguys[i][j]->setActive(TRUE);
				badguys[i][j]->setExploded(false);
				badguys[i][j]->setExploding(false);
				badguys[i][j]->setLocation(150+(i*100), -450+(j*100)); 
			  }
			}

			//create a new boss
			boss = new Boss2();
			boss->setActive(TRUE);
			boss->setExploded(false);
	  		boss->setLocation(150, -450);

			// set level 6 speed
			delayBadguyMove = 20;
			delayBadguyBullet = 1500;
			killTimer(timerBadguyMove);
			killTimer(timerBadguyBullet);
			timerBadguyMove = startTimer(delayBadguyMove);
    			timerBadguyBullet = startTimer(delayBadguyBullet);

			break;

		case 7:
			//Load level 7 image
			levelbackImage.load("images/level7.png"); 

			//Create level 7 badguys
			for(int i = 0; i < 4;i++)
			{
			  for(int j = 0; j < 3; j++)
			  {
				badguys[i][j] = new B3();
				badguys[i][j]->setActive(TRUE);
				badguys[i][j]->setExploded(false);
				badguys[i][j]->setExploding(false);
				badguys[i][j]->setLocation(150+(i*100), -450+(j*100)); 
			  }
			}

			//create a new boss
			boss = new Boss3();
			boss->setActive(false);

			// set level 7 speed
			delayBadguyMove =  20;
			delayBadguyBullet = 1500;
			killTimer(timerBadguyMove);
			killTimer(timerBadguyBullet);
			timerBadguyMove = startTimer(delayBadguyMove);
    			timerBadguyBullet = startTimer(delayBadguyBullet);

			break;

		case 8:
			//Load level 8 image
			levelbackImage.load("images/level8.png"); 

			//Create level 8 badguys
			for(int i = 0; i < 4;i++)
			{
			  for(int j = 0; j < 3; j++)
			  {
				if(j == 0)
					badguys[i][j] = new B3b();
					
				else
					badguys[i][j] = new B3();

				badguys[i][j]->setActive(TRUE);
				badguys[i][j]->setExploded(false);
				badguys[i][j]->setExploding(false);
				badguys[i][j]->setLocation(150+(i*100), -450+(j*100)); 

			  }
			}

			//create a new boss
			boss = new Boss3();
			boss->setActive(false);

			// set level 8 speed
			delayBadguyMove =  20;
			delayBadguyBullet = 1500;
			killTimer(timerBadguyMove);
			killTimer(timerBadguyBullet);
			timerBadguyMove = startTimer(delayBadguyMove);
    			timerBadguyBullet = startTimer(delayBadguyBullet);

			break;

		case 9:
			//Load level 9 image
			levelbackImage.load("images/level9.png"); 

			//Create level 9 badguys
			for(int i = 0; i < 4;i++)
			{
			  for(int j = 0; j < 3; j++)
			  {
				if(j == 0)
					badguys[i][j] = new B3c();			
				else if(j == 1)
					badguys[i][j] = new B3b();
					
				else
					badguys[i][j] = new B3();

				badguys[i][j]->setActive(TRUE);
				badguys[i][j]->setExploded(false);
				badguys[i][j]->setExploding(false);
				badguys[i][j]->setLocation(150+(i*100), -450+(j*100)); 
			  }
			}

			//create a new boss
			boss = new Boss3();
			boss->setActive(TRUE);
			boss->setExploded(false);
  			boss->setLocation(150, -450);

			// set level 9 speed
			delayBadguyMove =  20;
			delayBadguyBullet = 1500;
			killTimer(timerBadguyMove);
			killTimer(timerBadguyBullet);
			timerBadguyMove = startTimer(delayBadguyMove);
    			timerBadguyBullet = startTimer(delayBadguyBullet);

			break;

		case 10:
			//Load level 10 image
			levelbackImage.load("images/level10.png"); 

			//Create level 10 badguys
			for(int i = 0; i < 4;i++)
			{
			  for(int j = 0; j < 3; j++)
			  {
				if(j == 0)
					badguys[i][j] = new B4b();
					
				else
					badguys[i][j] = new B4();

				badguys[i][j]->setActive(TRUE);
				badguys[i][j]->setExploded(false);
				badguys[i][j]->setExploding(false);
				badguys[i][j]->setLocation(150+(i*100), -450+(j*100)); 

			  }
			}

			//create a new boss
			boss = new Boss4();
			boss->setActive(false);

			// set level 10 speed
			delayBadguyMove =  20 - 7;
			delayBadguyBullet = 1500 - 100;
			killTimer(timerBadguyMove);
			killTimer(timerBadguyBullet);
			timerBadguyMove = startTimer(delayBadguyMove);
    			timerBadguyBullet = startTimer(delayBadguyBullet);

			break;

		case 11:
			//Load level 11 image
			levelbackImage.load("images/level11.png"); 

			//Create level 11 badguys
			for(int i = 0; i < 4;i++)
			{
			  for(int j = 0; j < 3; j++)
			  {
				badguys[i][j] = new B4();

				badguys[i][j]->setActive(TRUE);
				badguys[i][j]->setExploded(false);
				badguys[i][j]->setExploding(false);
				badguys[i][j]->setLocation(150+(i*100), -450+(j*100)); 
			  }
			}

			//create a new boss
			boss = new Boss4();
			boss->setActive(false);

			// set level 11 speed
			delayBadguyMove =  20 - 8;
			delayBadguyBullet = 1500 - 200;
			killTimer(timerBadguyMove);
			killTimer(timerBadguyBullet);
			timerBadguyMove = startTimer(delayBadguyMove);
    			timerBadguyBullet = startTimer(delayBadguyBullet);

			break;

		case 12:
			//Load level 12 image
			levelbackImage.load("images/level12.png"); 

			//Create level 12 badguys
			for(int i = 0; i < 4;i++)
			{
			  for(int j = 0; j < 3; j++)
			  {
				if(j == 0)
					badguys[i][j] = new B4c();			
				else if(j == 1)
					badguys[i][j] = new B4b();
					
				else
					badguys[i][j] = new B4();

				badguys[i][j]->setActive(TRUE);
				badguys[i][j]->setExploded(false);
				badguys[i][j]->setExploding(false);
				badguys[i][j]->setLocation(150+(i*100), -450+(j*100)); 
			  }
			}

			//create a new boss
			boss = new Boss4();
			boss->setActive(TRUE);
			boss->setExploded(false);
  			boss->setLocation(150, -450);

			// set level 12 speed
			delayBadguyMove = 20 - 9;
			delayBadguyBullet = 1500 - 300;
			killTimer(timerBadguyMove);
			killTimer(timerBadguyBullet);
			timerBadguyMove = startTimer(delayBadguyMove);
    			timerBadguyBullet = startTimer(delayBadguyBullet);

			break;
		}
}

// Shoots bullets from the players ship
void SpaceWars::goodShipShoot()
{
		if (bulletCounter - lastShotTime > 50)
		{
			Bullet *bullet = new GoodBullet((spaceship->getRect().left() + spaceship->getRect().right()) / 2 , spaceship->getRect().top(),0);
			bullets.push_back(bullet);
		
		  if(godMode || tripleShot)
		  {
			//shoot 2 more bullets
			bullet = new GoodBullet((spaceship->getRect().left() + spaceship->getRect().right()) / 2 , spaceship->getRect().top(),1);
			bullets.push_back(bullet);
			bullet = new GoodBullet((spaceship->getRect().left() + spaceship->getRect().right()) / 2 , spaceship->getRect().top(),2);
			bullets.push_back(bullet);
		  }
			lastShotTime = bulletCounter;
		}
}

//deletes active bullets
void SpaceWars::clearBullets()
{
	if(!(bullets.empty()))
	{
		list<Bullet*>::iterator i = bullets.begin();
		while(i != bullets.end())
		{
			list<Bullet*>::iterator del = i;
			i++;
			delete (*del);
			bullets.erase(del);
		}
	}

	if(!(badguyBullets.empty()))
	{
		list<Bullet*>::iterator i = badguyBullets.begin();
		while(i != badguyBullets.end())
		{
			list<Bullet*>::iterator del = i;
			i++;
			delete (*del);
			badguyBullets.erase(del);
		}
	}

	if(!(bossBullets.empty()))
	{
		list<BossBullet*>::iterator i = bossBullets.begin();
		while(i != bossBullets.end())
		{
			list<BossBullet*>::iterator del = i;
			i++;
			delete (*del);
			bossBullets.erase(del);
		}
	}
}

// reads in db.txt and validates it
void SpaceWars::readDB()
{
	// decalre in file stream
	ifstream theFile;

	// open file db.txt
	theFile.open("db.txt");

	// delcare parsing variables
  	stringstream ss;
	vector<string> v;
	string line;

	// delcaring temp variables
	unsigned int id, year, highscore, temp;
	string  name;


    	// read in each line
    	while(getline(theFile,line)) 
	{
        	v.push_back(line);
    	}

	// check if data base empty
    	if(v.empty())
    	{
        	corruptDB = true;
    	}
    	else
    	{
		// read in user count
		ss << v[0];
		ss >> userCount;

		// check for text following user count
		string countTrash;
		if(ss >> countTrash)
		    corruptDB = true;

		ss.clear(); // clear ss buffer.

		//check if user count is in range
		if(userCount < 1 || userCount > 1000000000)
		    corruptDB = true;

		// check is file has correct number of lines
		if(userCount*5+1 != v.size())
		    corruptDB = true;


		// read in each user and validate info
		int j = 0;
		for(unsigned int i = 1; i < userCount*5  && !corruptDB; i+=5)
		{
		    // read in ID
		    ss << v[i];
		    ss >> id;

		    // check for text following id
		    string idTrash;
		    if(ss >> idTrash)
		    {
		        corruptDB = true;
		        break;
		    }
		    ss.clear(); // clear ss buffer.

		    //  check if id is in range
		    if(id < 1 || id > 1000000000)
		    {
		        corruptDB = true;
		        break;
		    }

		    // check if id is unique
		    for(unsigned int ii = 0; ii < userList.size(); ii++)
		        if(userList[ii]->getID() == id)
		        {
		            corruptDB = true;
		            break;
		        }

		    //read in user name
		    ss << v[i+1];
		    ss >> name;

		    // check for text following user name
		    string nameTrash;
		    if(ss >> nameTrash)
		    {
		        corruptDB = true;
		        break;
		    }
		    ss.clear(); // clear ss buffer.

		    // check if user name only has alphanumeric or underscore characters
		    corruptDB = !(validateUsername(name));

		    // check if user name is unique
		    for(unsigned int ii = 0; ii < userList.size(); ii++)//dupe username
		        if(userList[ii]->getUsername() == name)
		        {
		            corruptDB = true;
		            break;
		        }

		    // read in year
		    ss << v[i+2];
		    ss >> year;

		    // check for text following year
		    string yearTrash;
		    if(ss >> yearTrash)
		    {
		        corruptDB = true;
		        break;
		    }

		    ss.clear(); // clear ss buffer.

		    // check if year is in range
		    if(year < 1 || year > 5)
		    {
		        corruptDB = true;
		        break;
		    }

		    // read in high score
		    ss << v[i+3];
		    ss >> highscore;

		    // check for text following high score
		    string highScoreTrash;
		    if(ss >> highScoreTrash)
		    {
		        corruptDB = true;
		        break;
		    }

		    ss.clear(); // clear ss buffer.

		    // create new user from input
		    User *newUser = new User(id, name, year);

		    // add new user to vector
		    userList.push_back(newUser);

		    // sets visited to true
		    userList.at(userList.size()-1)->visited = true;

		    // sets new user high score
		    userList.at(j)->setScore(highscore);

		    // read in friends line to ss
		    ss << v[i+4];
		    //read in each friend and add it to appropriate friends vector
		    while(ss >> temp)
		    {
		        userList.at(j)->addFriend(temp);
		    }
		    ss.clear(); // clear ss buffer.

		    j++;
       	 	}

		// check if relationships are valid
		checkRelations();
	}


        // if data base corrupt, delete all users
        if(corruptDB)
        {
            //deallocate memory for the Users
            if(!userList.empty())
            {
                int size = userList.size();

                for(int i = 0; i < size; i++)
                {
                    if(userList.at(0))
                        delete userList.at(0);
                    userList.erase(userList.begin());
                }
            }
            userCount = 0;
        }
    	

	// Update Relations
	relationCount = 0;
	updateRelations();

	// close DB.txt
	theFile.close();
}

// writes out to db.txt
void SpaceWars::writeDB()
{
	// declare out file stream and open DB.txt
	ofstream theFile("db.txt");

	// write out user count
	theFile << userList.size();

	// write out each user and info
	for(unsigned int i = 0; i < userList.size(); i++)
	{
		theFile << std::endl << userList.at(i)->getID() << std::endl;
		theFile << '\t' << userList.at(i)->getUsername() << std::endl;
		theFile << '\t' << userList.at(i)->getYear() << std::endl;
		theFile << '\t' << userList.at(i)->getScore() << std::endl;
		for(unsigned int j = 0;  j < userList.at(i)->friends.size(); j++)
		{
			theFile << '\t' << userList.at(i)->friends.at(j);
		}
		if(userList.at(i)->friends.size() == 0)
			theFile  << '\t';
		
		if(userList[userList.size()-1]->getID() == userList[i]->getID() && userList.at(i)->friends.size() == 0)
			theFile  <<  std::endl;
	}

	// close DB.txt
	theFile.close();
}

// resets markings sets each user to !visited, level = 0, parent=NULL 
void SpaceWars::resetMarkings() 
{ 
	for(unsigned int i = 0; i < userList.size(); i++) 
		userList[i]->reset(); 
}

// Executes breadth first search on start user
// Sets up each user's parent pointer and level member variables 
// Parameter string start should be a valid username
void SpaceWars::BFSearch(string start)
{
	// resets markings sets each user to !visited, level = 0, parent=NULL 
	resetMarkings();

	//declare helper variables
	int s = -1, u;
	unsigned int v;

	// first we have to find the corresponding  user 'start'
	for(unsigned int i = 0; i < userList.size(); i++)	
	{	
		if (userList[i]->getUsername() == start)
		{
			s = i;
			break;
		}
	}
	if (s == -1) return;


	// mark start user
	userList[s]->visited = true;
	userList[s]->level = 0;
	userList[s]->parent = NULL;

	std::queue<int> myQueue;
	myQueue.push(s);   // adding start user to the queue
	while(!myQueue.empty())
	{

		// dequeue one element
		u = myQueue.front();
		myQueue.pop();

		// iterate over adjacent users to 'u'
		for(unsigned int i = 0; i < userList[u]->friends.size(); i++)
		{
			// user 'v' is adjacent to 'u'
			v = userList[u]->friends.at(i);
			for(unsigned int j=0; j < userList.size(); j++)
			{
				if(v == userList[j]->getID())
					v = j;
			}

			// if 'v' is a new user, add it to queue and update its markings
			if (userList[v]->visited == false)
			{
				userList[v]->visited = true;
				userList[v]->level = userList[u]->level + 1;
				userList[v]->parent = userList[u];
				myQueue.push(v);
			}
		}
	} // end of BFS while
}

// updates relationCount after DB import
void SpaceWars::updateRelations()
{
  if(!userList.empty())
  {
	// resets markings sets each user to !visited, level = 0, parent=NULL 
	resetMarkings();

	// declare helper variables
	vector<unsigned int> distinctRelations;
	bool newRelation = true;

	// add all of userList[0] to distinct friends vector
	for(unsigned int j = 0; j < userList[0]->friends.size(); j++)
	{
		distinctRelations.push_back(userList[0]->friends[j]);
	}
	// mark userList[0] as visited
	userList[0]->visited = true;

	// iterate through the rest of the users
	for(unsigned int i = 1; i < userList.size(); i++)
	{
		//  iterate through userList[i]'s friends
		for(unsigned int j = 0; j < userList[i]->friends.size(); j++)
		{
			//  iterate through the users again 
			//  checking if friendship is already added to distinct Relations vector
			for(unsigned int g = 0; g < userList.size(); g++)
			{
				if(userList[i]->friends[j] == userList[g]->getID() && userList[g]->visited)
					{newRelation = false; }
			}

			// if new relationship add it to distinct Relations vector
			if(newRelation)
				distinctRelations.push_back(userList[i]->friends[j]);

			newRelation = true;
		}

		// mark userList[i] as visited
		userList[i]->visited = true;
	}
	// set relation Count to size of distinct Relations vector
	relationCount = distinctRelations.size();
  }
}

// checks for invalid or dangling friend references
// if bad relationship detected, corruptDB = true
void SpaceWars::checkRelations()
{
  if(!userList.empty())
  {
	//  iterate through the userlist
	for(unsigned int i = 0; i < userList.size(); i++)
	{
	  //  iterate through userList[i]'s friends
	  for(unsigned int j = 0; j < userList[i]->friends.size(); j++)
	  {
		bool isGood = false;

		//  iterate through the users again 
		//  checking for a mutual friendship
		for(unsigned int k = 0; k <  userList.size();k++)
		{
			if(userList[i]->friends[j] == userList[k]->getID())
			  for(unsigned int ii = 0; ii < userList[k]->friends.size(); ii++)
			  {
				if(userList[k]->friends[ii] == userList[i]->getID())
					isGood = true;
			  }
		}

		if(!isGood)
			corruptDB = true;
	  }
	}
  }
}

// returns true if user name only has alphanumeric or underscore characters
bool SpaceWars::validateUsername(string name)
{
	// delcare helper variables
	bool valid = true;
	stringstream ss;
	char test;

	// write string to string stream
	ss << name; 

	// read out each char
	// checking if it is alphanumeric or underscore
	while(ss >> test)
	{
	  if((test>=48 && test<=57) || (test>=65 && test<=90) || (test==95) || (test>=97 && test<=122))
	  {//do nothing
	  }
	  else
	  {valid = false;}
	}

	return valid;
}

// sorts users by score
void SpaceWars::scoresSort()
{
	//  Uses simple bubble sort algorithm 
	//  iterate through the userlist
	for(unsigned int i = 0; i < userList.size();i++)
	{
		//  iterate through the unsorted userlist
		for(unsigned int j = 0; j < userList.size()-1-i;j++)
		{
			// if adjacent users are out of order swap them
			if(userList[j]->getScore() < userList[j+1]->getScore())
			{ 
				if(userList[j]->getID() == currentUser->getID())
					currentUser = userList[j+1];
				else if(userList[j+1]->getID() == currentUser->getID())
					currentUser = userList[j];

				User utemp(*userList.at(j));
				userList.at(j)->copyInfo(*userList.at(j+1));
				userList.at(j+1)->copyInfo(utemp);
			}
		}
	}
}

// sets up initial buttons
void SpaceWars::setUpInitialButtons()
{

	// set up helper variables
	QFontMetrics fm(QFont("Chicago", 15));
	QFontMetrics fm2(QFont("Chicago", 20));
	int buttonWidth, buttonWidth2, buttonWidth3 = 460;

	// set up log off button
	logOffButton = new QPushButton("Log Off",this);
	logOffButton->setStyleSheet(buttonStyleSheetQS("images/button1"));
	logOffButton->setFont(QFont("Chicago", 11));
	buttonWidth = fm.width("Log Off");
	logOffButton->setFixedSize(buttonWidth+10,24);
	logOffButton->move(-4,-1);
	logOffButton->hide();
	QObject::connect(logOffButton, SIGNAL(pressed()),this,SLOT(logOff()));

	// set up go back button	
	goBackButton = new QPushButton("Go Back",this);
	goBackButton->setStyleSheet(buttonStyleSheetQS("images/button1"));
	goBackButton->setFont(QFont("Chicago", 15));
	buttonWidth2 = fm2.width("Go Back");
	goBackButton->setFixedSize(buttonWidth2+10,30);
	goBackButton->hide();
	QObject::connect(goBackButton, SIGNAL(clicked()),this,SLOT(goBack2StartUp()));	
	QObject::connect(goBackButton, SIGNAL(clicked()),this,SLOT(goBack2UserScreen()));

	// set up add user button
	addUserButton = new QPushButton("Add user account",this);
	addUserButton->setStyleSheet(buttonStyleSheetQS("images/button2"));
	addUserButton->setFont(QFont("Chicago", 15));
	addUserButton->setFixedSize(buttonWidth3,32);
	addUserButton->move(400-buttonWidth3/2,328);
	addUserButton->show();
	QObject::connect(addUserButton, SIGNAL(clicked()),this,SLOT(addUserButtonSlot()));

	// set up delete user button
	deleteUserButton = new QPushButton("Delete user account",this);
	deleteUserButton->setStyleSheet(buttonStyleSheetQS("images/button2"));
	deleteUserButton->setFont(QFont("Chicago", 15));
	deleteUserButton->setFixedSize(buttonWidth3,32);
	deleteUserButton->move(400-buttonWidth3/2,370);
	deleteUserButton->show();
	QObject::connect(deleteUserButton, SIGNAL(clicked()),this,SLOT(deleteUserButtonSlot()));

	// set up log on button
	logOnButton = new QPushButton("Log on to user account",this);
	logOnButton->setStyleSheet(buttonStyleSheetQS("images/button2"));
	logOnButton->setFont(QFont("Chicago", 15));
	logOnButton->setFixedSize(buttonWidth3,32);
	logOnButton->move(400-buttonWidth3/2,412);
	logOnButton->show();
	QObject::connect(logOnButton, SIGNAL(clicked()),this,SLOT(logOnButtonSlot()));

	// set up list all high scores button
	listAllScoresButton = new QPushButton("List all users sorted by high scores",this);
	listAllScoresButton->setStyleSheet(buttonStyleSheetQS("images/button2"));
	listAllScoresButton->setFont(QFont("Chicago", 15));
	listAllScoresButton->setFixedSize(buttonWidth3,32);
	listAllScoresButton->move(400-buttonWidth3/2,454);
	listAllScoresButton->show();
	QObject::connect(listAllScoresButton, SIGNAL(clicked()),this,SLOT(listAllScoresButtonSlot()));

	// set up quit button
	quitButton = new QPushButton("Quit",this);
	quitButton->setStyleSheet(buttonStyleSheetQS("images/button2"));
	quitButton->setFont(QFont("Chicago", 15));
	quitButton->setFixedSize(buttonWidth3,32);
	quitButton->move(400-buttonWidth3/2,496);
	quitButton->show();
	QObject::connect(quitButton, SIGNAL(clicked()),this,SLOT(quitButtonSlot()));

	// set up in game quit button
	quitGameButton = new QPushButton("Quit",this);
	quitGameButton->setStyleSheet(buttonStyleSheetQS("images/button1"));
	quitGameButton->setFont(QFont("Chicago", 15));
	quitGameButton->setFixedSize(fm2.width("Go Back")+10,30);
	quitGameButton->move(400-(fm2.width("Go Back"))/2,452);
	quitGameButton->hide();
	QObject::connect(quitGameButton, SIGNAL(clicked()),this,SLOT(quitButtonSlot()));

	// set up restart button
	restartButton = new QPushButton("Restart",this);
	restartButton->setStyleSheet(buttonStyleSheetQS("images/button1"));
	restartButton->setFont(QFont("Chicago", 15));
	restartButton->setFixedSize(fm2.width("Go Back")+10,30);
	restartButton->move(400-(fm2.width("Go Back"))/2,452);
	restartButton->hide();
	QObject::connect(restartButton, SIGNAL(clicked()),this,SLOT(restartGameButtonSlot()));

	// set current User dependent buttons to NULL
	listAllUsersButton = NULL;
	addFriendButton = NULL;
	deleteFriendButton = NULL;
	listFriendsScoresButton = NULL;
	shortestPathButton = NULL;
	playGameButton = NULL;
	listAllScores2Button = NULL;

}

// build a list of the current users friends
// used on users screen
void SpaceWars::addFriendBox()
{
	if(currentUser)
	{
		// delete text box if exists
		if(smallFriendsBox)
		{
			delete smallFriendsBox;
			smallFriendsBox = NULL;
		}

		// adds  current users friends to list 
		QStringList  firstList;
		for(unsigned int i = 0; i < currentUser->friends.size();i++)
		{
			for(unsigned int j = 0; j < userList.size();j++)
			{
				if(userList[j]->getID() == currentUser->friends[i])
					firstList.append(QString::fromStdString(userList[j]->getUsername()));
			}
		}
		
		// sets up box and adds list to box
		smallFriendsBox = new QListView(this);
		smallFriendsBox->setPalette(pal);
		smallFriendsBox->setFont(QFont("Chicago", 15));
		smallFriendsBox->setModel(new QStringListModel(firstList));
		smallFriendsBox->setFixedSize(250,115);
		smallFriendsBox->move(260,157);
		QObject::connect(smallFriendsBox, SIGNAL(clicked(QModelIndex)),this,SLOT(refocus()));	
		smallFriendsBox->show();
	}
}

// hides the user screen buttons
void SpaceWars::hideUserScreenButtons()
{
	if(listAllUsersButton)
		listAllUsersButton->hide();
	if(addFriendButton)
		addFriendButton->hide();
	if(deleteFriendButton)
		deleteFriendButton->hide();
	if(listFriendsScoresButton)
		listFriendsScoresButton->hide();
	if(listAllScores2Button)
		listAllScores2Button->hide();
	if(shortestPathButton)
		shortestPathButton->hide();
	if(playGameButton)
		playGameButton->hide();
}

// sets up buttons for the users screen
void SpaceWars::buildUserScreenButtons()
{
  if(currentUser)
  {
	// deletes active user buttons
	if(listAllUsersButton)
		delete listAllUsersButton;
	if(addFriendButton)
		delete addFriendButton;
	if(deleteFriendButton)
		delete deleteFriendButton;
	if(listFriendsScoresButton)
		delete listFriendsScoresButton;
	if(listAllScores2Button)
		delete listAllScores2Button;
	if(shortestPathButton)
		delete shortestPathButton;
	if(playGameButton)
		delete playGameButton;

	//declare helper variables
	QFontMetrics fm2(QFont("Chicago", 20));
	int buttonWidth = 540;

	// set up list all users button
	listAllUsersButton = new QPushButton("List all usernames",this);
	listAllUsersButton->setStyleSheet(buttonStyleSheetQS("images/button2"));
	listAllUsersButton->setFont(QFont("Chicago", 15));
	listAllUsersButton->setFixedSize(buttonWidth,40);
	listAllUsersButton->move(400-buttonWidth/2,320);
	listAllUsersButton->show();
	QObject::connect(listAllUsersButton, SIGNAL(clicked()),this,SLOT(listAllUsersButtonSlot()));

	// set up add friend button
	QString buttonHelper = "Add a friend for " + QString::fromStdString(currentUser->getUsername());
	addFriendButton = new QPushButton(buttonHelper,this);
	addFriendButton->setStyleSheet(buttonStyleSheetQS("images/button2"));
	addFriendButton->setFont(QFont("Chicago", 15));
	addFriendButton->setFixedSize(buttonWidth,40);
	addFriendButton->move(400-buttonWidth/2,369);
	addFriendButton->show();
	QObject::connect(addFriendButton, SIGNAL(clicked()),this,SLOT(addFriendButtonSlot()));

	// set up de-friend button
	buttonHelper = "De-friend one of " + QString::fromStdString(currentUser->getUsername()) + "'s friends";
	deleteFriendButton = new QPushButton(buttonHelper,this);
	deleteFriendButton->setStyleSheet(buttonStyleSheetQS("images/button2"));
	deleteFriendButton->setFont(QFont("Chicago", 15));
	deleteFriendButton->setFixedSize(buttonWidth,40);
	deleteFriendButton->move(400-buttonWidth/2,418);
	deleteFriendButton->show();
	QObject::connect(deleteFriendButton, SIGNAL(clicked()),this,SLOT(deleteFriendButtonSlot()));


	// set up list friends high scores button button
	buttonHelper = "Sort all " + QString::fromStdString(currentUser->getUsername()) + "'s friends by score";
	listFriendsScoresButton = new QPushButton(buttonHelper,this);
	listFriendsScoresButton->setStyleSheet(buttonStyleSheetQS("images/button2"));
	listFriendsScoresButton->setFont(QFont("Chicago", 15));
	listFriendsScoresButton->setFixedSize(buttonWidth,40);
	listFriendsScoresButton->move(400-buttonWidth/2,467);
	listFriendsScoresButton->show();
	QObject::connect(listFriendsScoresButton, SIGNAL(clicked()),this,SLOT(listFriendsScoresButtonSlot()));

	// set up list all high scores button 2
	listAllScores2Button = new QPushButton("List all users sorted by high scores",this);
	listAllScores2Button->setStyleSheet(buttonStyleSheetQS("images/button2"));
	listAllScores2Button->setFont(QFont("Chicago", 15));
	listAllScores2Button->setFixedSize(buttonWidth,40);
	listAllScores2Button->move(400-buttonWidth/2,516);
	listAllScores2Button->show();
	QObject::connect(listAllScores2Button, SIGNAL(clicked()),this,SLOT(listAllScoresButtonSlot()));

	// set up shortest path button
	buttonHelper = "Shortest-path to " + QString::fromStdString(currentUser->getUsername()) + " from any user";
	shortestPathButton = new QPushButton(buttonHelper,this);
	shortestPathButton->setStyleSheet(buttonStyleSheetQS("images/button2"));
	shortestPathButton->setFont(QFont("Chicago", 15));
	shortestPathButton->setFixedSize(buttonWidth,40);
	shortestPathButton->move(400-buttonWidth/2,565);
	shortestPathButton->show();
	QObject::connect(shortestPathButton, SIGNAL(clicked()),this,SLOT(shortestPathButtonSlot()));

	// set up play game button
	playGameButton = new QPushButton("Play game",this);
	playGameButton->setStyleSheet(buttonStyleSheetQS("images/button2"));
	playGameButton->setFont(QFont("Chicago", 15));
	playGameButton->setFixedSize(buttonWidth,40);
	playGameButton->move(400-buttonWidth/2,614);
	playGameButton->show();
	QObject::connect(playGameButton, SIGNAL(clicked()),this,SLOT(playGameButtonSlot()));

  }
}

// sets up end game buttons
void SpaceWars::buildEndGameButtons()
{
	// declare helper variables
	QFontMetrics fm(QFont("Chicago", 20));
	int buttonWidth = fm.width("Go Back");
	buttonWidth +=10;

	// sets up restart button
	restartButton->move(400-buttonWidth*3/2,452);
	restartButton->show();

	// sets up quit game button 
	quitGameButton->move(400+buttonWidth/2,452);
	quitGameButton->show();

	// sets focus to game window
	this->setFocus();
}

// returns style sheet string used on all buttons
// parameter name is the partial path to button set
// image files must follow naming syntax
QString SpaceWars::buttonStyleSheetQS( const QString & name )
{
  const QString thisItemStyle( "QPushButton:focus {outline: none;} " "QPushButton {color: rgb(0, 0, 0);}"
			 "QPushButton:enabled { border-image: url(" + name + "a.png); }  "
                         "QPushButton:pressed { border-image: url(" + name + "b.png); }  "
                         "QPushButton:hover:!pressed { border-image: url(" + name + "c.png); }  "
                           );
  return thisItemStyle;
}
