/*
	Author: Yun Chul Chang
	Editor(s): Yun Chul Chang, Edwin Ramirez
	Purpose: Represent a fruit object
*/

#ifndef _FRUIT_H
#define _FRUIT_H

#include "Square.h"
#include "freeglut.h"
#include <stdlib.h>     


class Fruit
{
private:
	// Private instance variables:
	
	// Represents fruit
	Square fruit;
	
	// Color
	double r, g, b;

public:
	// Constructors:
	Fruit() {}			// does nothing (must call the other constructor)
	
	// Initialize the square (side is already defined)
	Fruit(double x, double y, double r, double g, double b) 
	{
	

		fruit = Square(x, y);
		this -> r = r;
		this -> g = g;
		this -> b = b;
	}

	// Public method:

	// Draw the fruit (just call the square's draw function)
	void draw()
	{
		fruit.draw(r,g,b);
	}

	// check if fruit contains the square
	bool isThereCollision(Square& checkMe)
	{
		return fruit.contains(checkMe);
	}
};

#endif // _FRUIT_H