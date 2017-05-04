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
		glColor3d(r, g, b);						// Set the color
		glBegin(GL_QUADS);						// Start drawing
		
		glVertex2f(x, y);
		glVertex2f(x + side, y);
		glVertex2f(x + side, y - side);
		glVertex2f(x, y - side);

		glEnd();								// Stop drawing
	}

	// Note: Square also has Shape's void getLocation(double& x, double& y) method
	// Read Shape.h for details 

	// Checks for collision
	bool contains(Square& checkMe)
	{
		double temp_x, temp_y;					// temp x, y to get location of the parameter square
		checkMe.getLocation(temp_x, temp_y);
		temp_x += side / 2;
		temp_y -= side / 2;

	
		if (temp_x > x && temp_x < (x + side) && temp_y < y && temp_y >(y - side))
			return true;
		else
			return false;
		// Case #1: The parameter square is on top of the square
	///*	if (x == temp_x && y == temp_y)
	//		return true;*/
	//	// Case #2: Top left point is in the square
	//	if ((x < temp_x && temp_x < x + side) && (y - side < temp_y && temp_y < y))
	//		return true;
	//	// Case #3: Top right point is in the square
	//	else if ((x < temp_x + side && temp_x + side < x + side) && (y - side < temp_y && temp_y < y))
	//		return true;
	//	// Case #4: Bot left point is in the square
	//	else if ((x < temp_x && temp_x < x + side) && (y - side < temp_y - side && temp_y - side < y))
	//		return true;
	//	// Case #5: Bot right point is in the square
	//	else if ((x < temp_x + side && temp_x + side < x + side) && (y - side < temp_y - side && temp_y - side < y))
	//		return true;
	//	//// Case #6: None (no collision)
	//	else
	//		return false;
	}
};

#endif // _SQUARE_H