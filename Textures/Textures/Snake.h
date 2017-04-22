/*
	Author: Yun Chul Chang
	Editor(s): Yun Chul Chang, Jose Sandoval, Edwin Ramirez
	Purpose: Represent a snake object
*/

#ifndef _SNAKE_H
#define _SNAKE_H

#include "Square.h"
#include <vector>

using namespace std;

class Snake
{
private:
	// Private instance variables:

	// Snake's body (head is at index 0)
	vector<Square> snake;

	// Color of the snake
	double r, g, b;

public:
	// Constructor:

	// Insert a square into the vector (Represents the head).
	// The square (with side length 0.1) should be at the starting position.
	// Default color for snake would be white (1.0, 1.0, 1.0)
	Snake() 
	{
		// code here...
	}

	// Same except that color is specified
	Snake(double r, double g, double b)
	{
		// code here...
	}

	// Public methods:

	// Insert a square into the vector...
	// First, get the location of the last square of the vector (size-1).
	// Second, create a square offsetted by 0.1 from the last square (Make sure that
	// the location is valid). Then, push back into the vector
	void grow()
	{
		// code here...
	}

	// Move the snake by 0.1 in a specified direction...
	// First, store the head's (index = 0) location (There is a method called getLocation(...)).
	// Second, move the head to the new location and have its body/tail move to its 
	// previous location (the coordinates that just got stored). Remember that there is
	// a method that makes the head/body/tail move called move(...).
	// Third, repeat this process until all snake parts have moved to the new location.
	// Read Square.h for more details about the given methods.
	void move(Direction direction)
	{
		// code here...
	}

	// Draw the snake...
	// For each square in the vector and call draw function. Read Square.h for more details
	void draw()
	{
		// code here...
	}
};

#endif // _SNAKE_H