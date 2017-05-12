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
enum GameMode { SinglePlayerMode, TwoPlayerMode, AIMode, Menu, ScoreDisplayEasy, ScoreDisplayInt, ScoreDisplayHard };

// Game status
enum GameStatus { StandBy, InProgress, GameOver };

// Player type
enum Player { Player1, Player2, AI };

// Game Difficulty (SinglePlayerMode only)
enum GameDifficulty { NotInitialized, Easy, Intermediate, Hard };

// Square side
#define SQUARE_SIDE 0.1

// Background side
#define BACKGROUND_SIDE 2.0

#endif //_CONFIG_H