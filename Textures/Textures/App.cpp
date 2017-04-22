#include "App.h"

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

	// TEST YOUR CODE HERE:
	test = Square(-0.05, 0.05, 0.1);					// center
	double temp_x = 0, temp_y = 0;
	test.getLocation(temp_x, temp_y);
	for (int i = 0; i <= 7; ++i)
		tests.push_back(Square(temp_x, temp_y, 0.1));	// surrounding squares
	tests[0].move(North, 0.3);
	tests[1].move(South, 0.3);
	tests[2].move(West, 0.3);
	tests[3].move(East, 0.3);
	tests[4].move(NorthWest, 0.3);
	tests[5].move(NorthEast, 0.3);
	tests[6].move(SouthWest, 0.3);
	tests[7].move(SouthEast, 0.3);
	// END TESTING
}

void App::draw() {

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // Set background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    
    // Set up the transformations stack
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	// TEST YOUR CODE HERE:
	test.draw(1.0, 1.0, 1.0);
	for (int i = 0; i <= 7; ++i)
		tests[i].draw(0.0, 1.0, 1.0);
	// END TESTING

	/*
	// IGNORE THE FOLLOWING (Still being tested):
	// Set Color
	glColor3d(1.0, 1.0, 1.0);


	glBindTexture( GL_TEXTURE_2D, monalisa );
	painting->draw();


	glBindTexture( GL_TEXTURE_2D, wall );
	background->draw();


	glDisable(GL_TEXTURE_2D);
	*/

    // We have been drawing everything to the back buffer
    // Swap the buffers to see the result of what we drew
    glFlush();
    glutSwapBuffers();
}

void App::keyPress(unsigned char key) {
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
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

	// Redraw the scene
	redraw();
}

void App::mouseDrag(float x, float y) {
	// Update app state
	mx = x;
	my = y;

	// Redraw the scene
	redraw();
}