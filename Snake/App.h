#ifndef App_hpp
#define App_hpp

// Handles OpenGL events
#include "GlutApp.h"

// General testing purposes:
#include "Square.h"
#include "GameManager.h"
#include "Fruit.h"
#include "Snake.h"
#include <vector>
#include <time.h>

// Actual Run header(s)
#include "ScoreKeeper.h"

// Texture purposes (Still being tested):
#include "RgbImage.h"
#include "TexRect.hpp"

class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;
	int count;

	// TEST YOUR CODE HERE:
	Square test;
	std::vector<Square> tests;
	
	Snake snake1;
	time_t timerBegin;
	time_t timerEnd;
	int speed;
	// GameManager (Actual Run):
	 GameManager game;
	

	// END TESTING
public:
	// WARNING: DO NOT ADD ANY METHODS WITHOUT ANY PERMISSION

	// Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    // These are the events we want to handle
    void draw();
	void idle();
    void keyPress(unsigned char key);
	void specialKeyPress(int key);

    
	// IGNORE THE FOLLOWING (Still being tested):
    GLuint loadTexture(const char* filename);

	// IGNORE THE FOLLOWING (Will not be used):
	void mouseDown(float x, float y);
	void mouseDrag(float x, float y);
	GLuint monalisa;
	GLuint wall;
	TexRect* painting;
	TexRect* background;
};

#endif
