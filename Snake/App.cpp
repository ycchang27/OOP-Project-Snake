#include "App.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <iomanip>

bool stopMove;
App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h){
    // Initialize state variables
    
	// IGNORE THE FOLLOWING (Still being tested):
	mx = 0.0;
    my = 0.0;
	#if defined WIN32
    monalisa = loadTexture("..\\monalisa.bmp");
    wall = loadTexture("..\\wall.bmp");
	#else
	monalisa = loadTexture("monalisa.bmp");
	wall = loadTexture("wall.bmp");
	#endif
    
    background = new TexRect(-1, 1, 2, 2);
    painting = new TexRect(0, 0.67, 0.5, 0.67);
	stopMove = false;
	


	speed = 500;


	count = 0;
	// END TESTING
}

void App::idle() {
	redraw();
	
}

void App::draw() {

	count++;
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// TEST YOUR CODE HERE:
	
	
	switch (game.currentMode())
	{
	case Menu: game.displayMenu(); break;																// Display menu
	case ScoreDisplayEasy: game.displayScoreboard(); break;		// Display scoreboard
	case ScoreDisplayInt: game.displayScoreboard(); break;		// Display scoreboard
	case ScoreDisplayHard: game.displayScoreboard(); break;		// Display scoreboard
	default: game.run(); break;																			// Run/continue the game
	}
	// check end condition
	if (game.currentStatus() == GameOver)
		game.end();
	

	

    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::keyPress(unsigned char key) {
   
	if (key == 27) // Exit the app when Esc key is pressed
		exit(0);
	else
	{
		game.receiveInput(key);
		game.setTurn(Player1);
		game.changeDirection();
	}

	redraw();
	
}

void App::specialKeyPress(int key) {
	// Accepts special keys only in TwoPlayerMode/AIMode
	
	if (game.currentMode() == TwoPlayerMode || game.currentMode() == AIMode)
	{
		game.receiveSpecialInput(key);
		game.setTurn(Player2);
		game.changeDirection();
	}
	
}

// IGNORE THE FOLLOWING (Still being tested):

GLuint App::loadTexture(const char *filename) {
	GLuint texture_id;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);

	RgbImage theTexMap(filename);

	// Pixel alignment: each row is word aligned (aligned to a 4 byte boundary)
	//    Therefore, no need to call glPixelStore( GL_UNPACK_ALIGNMENT, ... );

	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(),
		GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());

	return texture_id;
}

// IGNORE THE FOLLOWING (Will not be used):

void App::mouseDown(float x, float y) {
	// Update app state
	mx = x;
	my = y;
}

void App::mouseDrag(float x, float y) {
	// Update app state
	mx = x;
	my = y;
}