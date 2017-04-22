/*
	Author: Yun Chul Chang
	Purpose: Build an interface/template of all shapes
*/

#ifndef _SHAPE_H
#define _SHAPE_H

#include "Config.h"

#include <iostream>

class Shape
{
protected:
	// Accessible by all Shapes and its derived classes
	// Provides distinguishable location of the shape
	// For example, Square's point would represent the point at the top left corner
	double x, y;

public:
	// Constructors:
	Shape() : x(0.0), y(0.0) {}
	Shape(double x, double y) : x(x), y(y) {}

	// Virtual function(s):
	// Draws the shape with given color r, g, b
	virtual void draw(double r, double g, double b) {}
	
	// Gives the shape's location by passing values to the parameters
	virtual void getLocation(double& x, double& y) { x = this->x, y = this->y; }
	
	// Move the shape to specified direction by given amount
	virtual void move(Direction direction, double offset)
	{
		switch (direction)
		{
		case North: y += offset; break;
		case South: y -= offset; break;
		case West: x -= offset; break;
		case East: x += offset; break;
		default: std::cout << "Error: invalid direction.\n";				// Error message
		}
	}
};

#endif // _SHAPE_H