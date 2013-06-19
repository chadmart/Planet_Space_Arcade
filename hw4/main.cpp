/*!\file main.cpp
 * 
 * \brief Contians Main function which initializes SpaceWars object.
 * 
 * \Created by: Spencer Moran 
 * 
 * \Edited by: Chad Martin
 * 
 * \Last Edited: 11/17/2012
 *
 * This file is used to generate and set up a window for 
 * the Battle of Planet Space to be played in.
 */

#include <QDesktopWidget> 
#include <QApplication>
#include <stdlib.h>
#include <time.h>
#include "spacewars.h"


//set window size and center the window on the screen
void center(QWidget &widget)
{
  int x, y;
  int screenWidth;
  int screenHeight;

  int WIDTH = 800;
  int HEIGHT = 700;
  

  QDesktopWidget *desktop = QApplication::desktop();

  screenWidth = desktop->width();
  screenHeight = desktop->height();
 
  x = (screenWidth - WIDTH) / 2;
  y = (screenHeight - HEIGHT) / 2;

  widget.setGeometry(x, y, WIDTH, HEIGHT);
  widget.setFixedSize(WIDTH, HEIGHT);

  //set window background color to black
  QPalette pal;
  pal.setColor(QPalette::Background, Qt::black);
//pal.setColor(QPalette::Background, QColor(55,55,55));
  widget.setAutoFillBackground(true);
  widget.setPalette(pal);
}


int main(int argc, char *argv[])
{
  QApplication app(argc, (char **) argv);  
  srand ( time(NULL) );
  
  //initialize the window
  SpaceWars window;
  
  //title the window
  window.setWindowTitle("The Battle for Planet Space");
  window.show();
  center(window);

  return app.exec();
}


