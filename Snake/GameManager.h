/*
	Author: Yun Chul Chang
	Editor(s): Yun Chul Chang, David Cabral
	Purpose: Represent a game manager
*/

#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include "Snake.h"
#include "Fruit.h"

class GameManager
{
private:
	// Private instance variables:

	// Game mode
	GameMode mode;

	// Snake(s) would not move until a user makes a move, so
	// snake(s) would not take any actions until this variable is true.
	bool game_start;

	// Game score
	// The score will be saved when the game is over (will be implemented later)
	unsigned int game_score;

	// Victory
	Player victory;

	// Snakes (snake2 will not be used for single player mode)
	// Also, snake2 can be either another player or AI
	Snake snake1, snake2;

	// Fruit
	// It will respawn every x seconds (will be implemented later)
	Fruit fruit;

	// Represents the direction that snake1 is facing.
	// There are 4 possible values that this object may use: 
	// North, South, West, East
	Direction snake1_direction;

	// Represents the direction that snake2 is facing.
	// There are 4 possible values that this object may use: 
	// North, South, West, East
	Direction snake2_direction;

public:
	// Constructor:

	// Determine the game mode and initialize variables as fit.
	// For example, if the mode is SINGLEPLAYER, then only snake1 and fruit 
	// would be initialized.
	// game_start is initially false.
	GameManager(GameMode mode) 
	{
		// code here...	
	}

private:
	// Private method(s):
	
	// AI can decide whether to change direction or not
	void AIDecision()
	{
		// code here...
	}

	// Return the type of collision
	// Player is defined in Config.h
	Collision checkCollision(const Player player)
	{
		// code here...
	}

public:
	// Public methods:

	// Change snake1's or snake2's direction
	// Player is defined in Config.h
	void changeDirection(Direction new_direction, Player type)
	{
		// code here...	
	}

	// Update the game accordingly to the game mode...
	// snake1 will move according to its direction.
	// snake2 will either act like snake1 or will decide its next action if it's AI mode.
	// Watch out for the collision for each move.
	// If the collision type (look at Config.h) is WALL or SNAKE, whichever snake loses,
	// and the game ends.
	// If the collision type is FRUIT, then the snake powers up
	void updateGame()
	{
		// code here...
	}
};

#endif // _GAMEMANAGER_H