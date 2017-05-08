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
	// Constructor:
	//	- Define some private variables to default (other variables are defined later):
	//	- mode: Initially on Menu mode
	//	- status: Initially on StandBy mode
	//	- keyboard: Initially '\0'
	//	- special_keyboard: Initially -1
	GameManager();

private:
	// Private method(s):


	// Return the type of collision that the player is facing:
	//	- NONE: No collision
	//	- FRUIT: Collision with Fruit
	//	- WALL: Collision with the boundary
	//	- SNAKE: Collision with a snake
	//	- For example, check:
	//		* Would the current location collide with itself?
	//		* Would the current location collide with another snake? (Only in TwoPlayerMode and AIMode)
	//		* Would the current location collide with the boundary?
	//		* Would the current location collide with a fruit?
	Collision checkCollision(const Player player);


	// Setter...
	// Reset the user input
	void resetInput() { keyboard = '\0'; special_keyboard = -1; }

	
	// Initialization ("Constructor")...

	
	// "Constructor" for SinglePlayerMode:
	//	- snake1: Call constructor that specifies location and color (green)
	//	- fruit: Call constructor that specifies location and color (orange)
	//	- score: Call default constructor
	//	- turn: Player1
	//	- snake1_direction: Initially is North
	//	- difficulty: NotInitialized
	// Note: Spread out the objects so that they don't collide right away the game starts.
	void setupSingle();

	// "Constructor" for TwoPlayerMode:
	//	- snake1: Call constructor that specifies location and color (green)
	//	- fruit: Call constructor that specifies location and color (orange)
	//	- snake2: Call constructor that specifies location and color (red)
	//	- snake1_direction: Initially is North
	//	- snake2_direction: Initially is South
	// Note: Spread out the objects so that they don't collide right away the game starts.
	void setupTwoPlayer();

	// "Constructor" for AIMode:
	//	- same as setupTwoPlayer()
	// Note: Spread out the objects so that they don't collide right away the game starts.
	void setupAI();


	// run() helpers...
	

	// Run in SinglePlayerMode:
	//	1) Make snake1 move
	//	2) Check collision:
	//		* NONE: Does nothing
	//		* FRUIT: snake1 grows. score is incremented. fruit respawns in a next avaiable location. Then check for collision again.
	//		* WALL: set status to GameOver
	//		* SNAKE: set status to GameOver
	void runSingle();

	// Run in TwoPlayerMode:
	//	1) Make snake1 move
	//	2) Check collision:
	//		* NONE: Does nothing
	//		* FRUIT: snake1 grows. fruit respawns in a next avaiable location. Then check for collision again.
	//		* WALL: set status to GameOver
	//		* SNAKE: set status to GameOver and set victory to Player2
	//	3) Make snake2 move
	//	4) Check collision:
	//		* NONE: Does nothing
	//		* FRUIT: snake2 grows. fruit respawns in a next avaiable location. Then check for collision again.
	//		* WALL: set status to GameOver
	//		* SNAKE: set status to GameOver and set victory to Player1
	void runTwoPlayer();

	// Run in AIMode:
	//	1) Make snake1 move
	//	2) Check collision:
	//		* NONE: Does nothing
	//		* FRUIT: snake1 grows. fruit respawns in a next avaiable location. Then check for collision again.
	//		* WALL: set status to GameOver
	//		* SNAKE: set status to GameOver and set victory to AI
	//	3) Make snake2 move
	//	4) Check collision:
	//		* NONE: Does nothing
	//		* FRUIT: snake2 grows. fruit respawns in a next avaiable location. Then check for collision again.
	//		* WALL: set status to GameOver
	//		* SNAKE: set status to GameOver and set victory to Player1
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


	// Main Game Loop:
	//	- In SinglePlayerMode: User must set the difficulty: 1 = Easy, 2 = Intermediate, 3 = Hard (Then waits for space bar key to start)
	//	- In StandBy mode, the game would not start until space bar has been pressed (Objects are displayed but does not move).
	//	- In InProgress mode, the game would continue until an end condition is met
	//	- In GameOver mode, the game stops running
	void run();

	// End Game Loop:
	//	- Is only called when status = GameOver
	//	- In SinglePlayerMode:
	//		* If the score belongs in top 10, user input will be asked and saved into the score.txt.
	//		* (Testing purposes): For now, terminal interface is used.
	//	- In TwoPlayerMode/AIMode:
	//		* Display whose victory it is (assume victory is already initialized).
	//		* (Testing purposes): For now, terminal interface is used.
	//	- The program ends with ESC button.
	void end();

	// Game Menu Display:
	//	- Provide 4 options (to set the game mode): Single, TwoPlayer, AI, ScoreDisplay
	//	- Option will be chosen depending on the keyboard input
	//	- Options can be displayed with an already-made texture
	//	- (Testing purposes): For now, terminal interface is used
	void displayMenu();

	// Scoreboard Display:
	//	- Pressing space bar switches to menu display
	//	- Output depends on user's display option
	void displayScoreboard();

	// Change snake's direction:
	//	- Set the direction depending on the user input
	//	- Player1: 'w' = North; 's' = South; 'a' = West; 'd' = East
	//	- Player2: up arrow = North; down arrow = South; left arrow = West; right arrow = East
	//	- No option for AI (It's called somewhere else)
	void changeDirection();

	// AI's input:
	//	- Used in AI mode
	//	- Decide and set AI's direction (Maybe avoiding wall collision?)
	//	- Choose between North, South, West, East
	//	- Remember that AI = snake2 in AIMode
	void AIDecision();

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