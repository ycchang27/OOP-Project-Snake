/*
	Author: Yun Chul Chang
	Editor(s): Yun Chul Chang, Jose Sandoval, David Cabral, Edwin Ramirez
	Purpose: Represent a game manager
*/

#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "Snake.h"
#include "Fruit.h"
#include "ScoreKeeper.h"
#include "GlutApp.h"
#include <iomanip>
#include <random>
#include <time.h>
#include <string>
#include <iostream>

// Sound Engine
// Download page: http://www.ambiera.com/irrklang/downloads.html
// Set up tutorial: http://www.dreamincode.net/forums/topic/185301-playing-audio-files-with-irrklang/
#include <Windows.h>
#include "include/irrKlang.h"

// Set up for sound engine
using namespace std;
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")

class GameManager
{
private:
	// Private instance variables:


	// Game display mode
	GameMode mode;

	// Status of the game
	GameStatus status;

	// Scorekeeper
	//	- Only used in SinglePlayerMode
	ScoreKeeper score;

	// GameDifficulty
	//	- Only used in SinglePlayerMode
	GameDifficulty difficulty;

	// Sound controls
	ISoundEngine* sound_effect;
	ISoundEngine* background_music;

	// Game speed
	//	- Only used in SinglePlayerMode
	double game_speed;

	// Victory/Turn
	Player victory, turn;

	// Snakes
	Snake snake1, snake2;

	// Fruit ("Power-up" item)
	Fruit fruit;

	// Snake's direction
	Direction snake1_direction, snake2_direction;

	// User keyboard input
	unsigned char keyboard;				// handles general input
	int special_keyboard;				// handles special input

	// Speed of the game
	int speed = 5;
	int count = 0;
	clock_t t;

	// Background
	Square background;
	GLuint texture;

	// Player name
	string player_name = "";

public:
	
	GameManager();

private:

	// Setter...
	// Reset the user input
	void resetInput() { keyboard = '\0'; special_keyboard = -1; }

	

	void setupSingle();

	
	void setupTwoPlayer();

	
	void setupAI();


	
	void runSingle();

	
	void runTwoPlayer();

	
	void runAI();

	// Test (User input)
	void receiveName();

	// Load texture
	GLuint loadTexture(const char *filename) {
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

public:
	// Public methods:


	
	void run();

	
	void end();

	
	void displayMenu();

	
	void displayScoreboard();

	
	void changeDirection();


	// Setters:
	// Receive general user input
	void receiveInput(unsigned char input) { keyboard = input; }
	// Receive special user input
	void receiveSpecialInput(int input) { special_keyboard = input; }
	// Set turn
	void setTurn(Player turn)
	{
		if(mode == SinglePlayerMode)							// SinglePlayerMode
			return ;											// Turn is fixed
		else
		{
			if (mode == TwoPlayerMode)							// TwoPlayerMode
				this->turn = turn;
			else												// AIMode
				this->turn = (turn == Player1) ? Player1 : AI;	// AI's turn implementation is... special
		}
	}

	// Getters:
	// Display current game status
	GameStatus currentStatus() { return status; }
	// Display current game mode
	GameMode currentMode() { return mode; }
};

#endif // _GAMEMANAGER_H