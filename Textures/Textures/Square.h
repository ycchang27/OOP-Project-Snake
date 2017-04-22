/*
	Author: Yun Chul Chang
	Editor(s): Yun Chul Chang, 
	Purpose: Represent a Square object
*/

#ifndef _SQUARE_H
#define _SQUARE_H

#include "Shape.h"
#include "freeglut.h"

class Square : public Shape						// Extends Shape
{
private:
	// Private instance variables
	double side;								// Side of a square (defined in Config.h)

public:
	// Constructors:
	// Square's point represents the point at the top left corner
	Square() : side(SQUARE_SIDE) { x = 0.0; y = 0.0; }
	Square(double x, double y) : side(SQUARE_SIDE) { this->x = x; this->y = y; }
	
	// Public methods
	void draw(double r, double g, double b)		// Override draw method
	{
		glColor3d(r, g, b);						// Set the Color to white
		glBegin(GL_QUADS);						// Start drawing
		
		glVertex2f(x, y);
		glVertex2f(x + side, y);
		glVertex2f(x + side, y - side);
		glVertex2f(x, y - side);

		glEnd();								// Stop drawing
	}

	// Note: Square also has Shape's void getLocation(double& x, double& y) method
	// Read Shape.h for details 
};

#endif // _SQUARE_H