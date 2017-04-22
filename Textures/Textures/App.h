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

// Texture purposes (Still being tested):
#include "RgbImage.h"
#include "TexRect.hpp"

class App: public GlutApp {
    // Maintain app state here
    float mx;
    float my;

	// TEST YOUR CODE HERE:
	Square test;
	std::vector<Square> tests;

	// END TESTING
public:
    // Constructor, to initialize state
    App(const char* label, int x, int y, int w, int h);
    
    // These are the events we want to handle
    void draw();
    void keyPress(unsigned char key);

	// NOTE: DO NOT ADD ANY METHODS WITHOUT ANY PERMISSION
    
	// IGNORE THE FOLLOWING (Still being tested):
    GLuint loadTexture(const char* filename);
    
    GLuint monalisa;
    GLuint wall;
    
    TexRect* painting;
    TexRect* background;

	// IGNORE THE FOLLOWING (Will not be used):
	void mouseDown(float x, float y);
	void mouseDrag(float x, float y);
};

#endif
