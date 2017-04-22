#ifndef _CONFIG_H
#define _CONFIG_H

/*
	Author: Yun Chul Chang
	Purpose: List global definitions used throughout the project.
*/

// Direction
enum Direction { North, South, West, East};

// Collision types
enum Collision { NONE, FRUIT, WALL, SNAKE };

// Game mode
enum GameMode { SINGLE, TWOPLAYER, AI };

// Player type
enum Player { Player1, Player2 };

// Square side
#define SQUARE_SIDE 0.1

#endif //_CONFIG_H