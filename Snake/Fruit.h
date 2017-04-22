/*
	Author: Yun Chul Chang
	Editor(s): Yun Chul Chang, Edwin Ramirez
	Purpose: Represent a fruit object
*/

#ifndef _FRUIT_H
#define _FRUIT_H

#include "Square.h"
#include "freeglut.h"

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
	Fruit() {}			// Temporary default constructor (will be deleted later)

	// Initialize the square (side is already defined)
	Fruit(double x, double y, double r, double g, double b) 
	{
		fruit = Square(x, y);
		this -> r = r;
		this -> g = g;
		this-> b = b;

		// code here...	
	}

	// Public method:

	// Draw the fruit (just call the square's draw function)
	void draw()
	{
		fruit.draw(r,g,b);
	}
};

#endif // _FRUIT_H