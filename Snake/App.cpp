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
	test = Square(-0.05, 0.05);						// center
	double temp_x = 0, temp_y = 0;
	test.getLocation(temp_x, temp_y);
	for (int i = 0; i <= 3; ++i)
		tests.push_back(Square(temp_x, temp_y));	// surrounding squares
	tests[0].move(North, 0.3);
	tests[1].move(South, 0.3);
	tests[2].move(West, 0.3);
	tests[3].move(East, 0.3);

	time(&timerBegin);
	time(&timerEnd);
	speed = 3000;
	count = 0;
	// END TESTING
}

void App::idle() {
	// Check whether it is the time to "run" or not
	if (game.currentStatus() == GameOver || game.currentStatus() == StandBy || game.currentMode() == Menu || game.currentMode() == ScoreDisplay)
		return;
	else
	{
		if(game.currentMode() == AIMode)			// AI feature: AI always makes decide to turn each "run" (can face the same direction as previous one)
			game.AIDecision();
		redraw();									// run
	}
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
	test.draw(1.0, 1.0, 1.0);
	for (int i = 0; i <= 3; ++i)
		tests[i].draw(0.0, 1.0, 1.0);

<<<<<<< HEAD
	time(&timerEnd);
	snake1.draw();
	if (count >= speed)
	{
		snake1.move(snake1.getDirection());
		time(&timerBegin);
		time(&timerEnd);
		count = 0;
	}
=======
	// GameManager (Actual Run):
	// game mode check
	switch (game.currentMode())
	{
	case Menu: game.displayMenu(); break;						// Display menu
	case ScoreDisplay: game.displayScoreboard(); break;			// Display scoreboard
	default: game.run(); break;									// Run/continue the game
	}
	// check end condition
	if (game.currentStatus() == GameOver)
		game.end();

>>>>>>> origin/master
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
void App::idle()
{
	redraw();
}
void App::keyPress(unsigned char key) {
<<<<<<< HEAD
    if (key == 27){
        // Exit the app when Esc key is pressed
        exit(0);
    }

	if (!snake1.checkBounds())
	return;

	switch (key)
	{
	case 27: exit(0);
	case 'w': snake1.setDirection(North); break;
	case 'a': snake1.setDirection(West); break;
	case 'd': snake1.setDirection(East); break;
	case 's': snake1.setDirection(South); break;
	default: std::cout << "No support for this key\n";
=======
	if (key == 27) // Exit the app when Esc key is pressed
		exit(0);
	else
	{
		game.receiveInput(key);
		game.setTurn(Player1);
		game.changeDirection();
	}
}

void App::specialKeyPress(int key) {
	// Accepts special keys only in TwoPlayerMode/AIMode
	if (game.currentMode() == TwoPlayerMode || game.currentMode() == AIMode)
	{
		game.receiveSpecialInput(key);
		game.setTurn(Player2);
		game.changeDirection();
>>>>>>> origin/master
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