/*
	Author: Yun Chul Chang
	Purpose: Build an interface/template of all shapes
*/

#ifndef _SHAPE_H
#define _SHAPE_H
#include <math.h>
#include <iostream>

enum Direction {North, South, West, East, NorthWest, NorthEast, SouthWest, SouthEast};

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
	// Beware of diagonal directions (Remember how hypotenuse != side)
	virtual void move(Direction direction, double offset)
	{
		switch (direction)
		{
		case North: y += offset; break;
		case South: y -= offset; break;
		case West: x -= offset; break;
		case East: x += offset; break;
		case NorthWest: offset /= sqrt(2); x -= offset; y += offset; break;
		case NorthEast: offset /= sqrt(2); x += offset; y += offset; break;
		case SouthWest: offset /= sqrt(2); x -= offset; y -= offset; break;
		case SouthEast: offset /= sqrt(2); x += offset; y -= offset; break;
		default: std::cout << "Error: invalid direction.\n";				// Error message
		}
	}
};

#endif // _SHAPE_H