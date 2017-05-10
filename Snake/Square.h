/*
	Author: Yun Chul Chang
	Editor(s): Yun Chul Chang, David Cabral
	Purpose: Represent a Square object (currently represent snake's head/body, fruit, and background)
*/

#ifndef _SQUARE_H
#define _SQUARE_H

#include "Shape.h"

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
	void draw(double r, double g, double b)		// Implement draw method
	{
		glColor3d(r, g, b);						// Set the color
		glBegin(GL_QUADS);						// Start drawing
		
		glVertex2f(x, y);
		glVertex2f(x + side, y);
		glVertex2f(x + side, y - side);
		glVertex2f(x, y - side);

		glEnd();								// Stop drawing
	}

	void setToBackgroundSize()					// Set square's side to background one
	{
		side = BACKGROUND_SIDE;
	}

	void textureDraw(GLuint& texture)			// Implement textured draw method
	{				
		// Set Texture
		glColor3d(1.0, 1.0, 1.0);				// Set the color
		glBindTexture(GL_TEXTURE_2D, texture);
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// Start drawing
		glBegin(GL_QUADS);

		glTexCoord2f(0.0, 0.0);
		glVertex2f(x, y - side);

		glTexCoord2f(0.0, 1.0);
		glVertex2f(x, y);

		glTexCoord2f(1.0, 1.0);
		glVertex2f(x + side, y);

		glTexCoord2f(1.0, 0.0);
		glVertex2f(x + side, y - side);

		// Stop drawing
		glEnd();
		glDisable(GL_TEXTURE_2D);
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
		
	}
};

#endif // _SQUARE_H