/*
	Author: Yun Chul Chang
	Editor(s): Yun Chul Chang, David Cabral, Edwin Ramirez, Jose Sandoval
	Purpose: Represent a snake object
*/

#ifndef _SNAKE_H
#define _SNAKE_H

#include "Square.h"
#include "RgbImage.h"
#include <vector>
#include <algorithm>

using namespace std;

class Snake
{
private:
	// Private instance variables:

	// Snake's body (head is at index 0)
	vector<Square> snake;

	// Color of the snake
	double r, g, b;

	Direction direct;

	bool changedDirection;

	GLuint texture;

	void checkBounds()
	{
		double x;
		double y;

		snake[0].getLocation(x, y);

		if (x > 0.9 || x < -1.0)
		{
			if (x > 0.9)
			{
				x = -1.0;
				snake[0].setLocation(x, y);
				//direct = East;
			}
			else
			{
				x = 0.9;
				snake[0].setLocation(x, y);
				//direct = West;
			}

		}
		else if (y > 1.0 || y < -0.9)
		{
			if (y > 1.0)
			{
				y = -0.9;
				snake[0].setLocation(x, y);
				//direct = North;
			}
			else
			{
				y = 1.0;
				snake[0].setLocation(x, y);
				//direct = South;
			}

		}

	}

public:
	// Constructors:
	Snake() 
	{
		snake.push_back(Square());
		snake.push_back(Square(0.0, -0.1));
		snake.push_back(Square(0.0, -0.2));
		direct = North;
		r = 1;
		g = 1;
		b = 1;
		changedDirection = false;
	}

	// Insert 3 squares into the vector (head, body, and tail)
	// The square has already-defined side length 0.1
	Snake(double x, double y, double r, double g, double b, GLuint head)
	{
		// code here...
		snake.push_back(Square(x,y));
		snake.push_back(Square(x,y-0.1));
		snake.push_back(Square(x, y-0.2));
		direct = North;
		this->r = r;
		this->g = g;
		this->b = b;
		changedDirection = false;

		texture = head;
	}

	// Public methods:

	// Insert a square into the vector...
	// First, get the location of the last square of the vector (size-1).
	// Second, create a square offsetted by 0.1 from the last square (Make sure that
	// the location is valid). Then, push back into the vector
	void grow()
	{
		// code here...
		double lastX;
		double lastY;
		double slastX;
		double slastY;
		double xOffset;
		double yOffset;
		double x;
		double y;

		snake[snake.size() - 1].getLocation(lastX, lastY);
		snake[snake.size() - 2].getLocation(slastX, slastY);
		x = lastX;
		y = lastY;

		// decide what direction location should be shifted towards based on what current direction the last tail is currently in

		xOffset = slastX - lastX;
		yOffset = slastY - lastY;

		if (xOffset > 0)
			x -= 0.1;
		else if (xOffset < 0)
			x += 0.1;
		else if (yOffset > 0)
			y -= 0.1;
		else if (yOffset < 0)
			y += 0.1;
		
		/*if (x >= 1.0)
		{
			x -= 0.1;
			y -= 0.1;
		}
		else if (x <= -1)
		{
			x += 0.1;
			y -= 0.1;
		}

		if (y >= 1.0)
		{
			x -= 0.1;
			y -= 0.1;
		}
		else if (y <= -1)
		{
			x += 0.1;
			y += 0.1;
		}*/
		// check if location is valid first before putting in
		snake.push_back(Square(x, y));

	//	cout << "Snake growing with (" << x << ", " << y << ")\n";

		for (int i = 0; i < snake.size(); i++)
		{
			snake[i].getLocation(x, y);
		//	cout << "Body part at (" << x << ", " << y << ")\n";
		}
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
		Direction myDirection = direction;
		
		double x;
		double y;
		double newX;
		double newY;
		double offset = 0.1;
		
		snake[0].getLocation(x, y);

		//checkBounds();

		if ((direct == North && direction == South) || (direct == South && direction == North)
			|| (direct == West && direction == East) || (direct == East && direction == West))
			myDirection = direct;


		
		snake[0].move(myDirection, offset);
		checkBounds();
		snake[0].getLocation(newX, newY);

	/*	cout << "Head Position (" << newX << ", " << newY << ")\n";
		cout << "Offset = " << offset << "\n";
		if (myDirection == East)
			std::cout << "Direction = East\n";
		else if (myDirection == West)
			std::cout << "Direction = West\n";
		else if (myDirection == North)
			std::cout << "Direction = North\n";
		else if (myDirection == South)
			std::cout << "Direction = South\n";
		std::cout << "---------------------------------------------------\n";*/

		for (int i = 1; i < snake.size(); i++)
		{
			snake[i].getLocation(newX, newY);
			snake[i].setLocation(x, y);

			x = newX;
			y = newY;
		}
		changedDirection = false;
	}
	Square getHead()
	{
		return snake[0];
	}
	
	Direction getDirection()
	{
		return direct;
	}
	void setDirection(Direction d)
	{
		if (changedDirection)
			return;

		//checkBounds();

		if ((direct == North && d == South) || (direct == South && d == North)
			|| (direct == West && d == East) || (direct == East && d == West))
			return;
		direct = d;
		changedDirection = true;
	}
	
	// Traverse through the vector and see if any of them contains the square
	// If it's the same snake, don't check the first index (since head == head)
	bool isThereCollision(Square checkMe, bool same_snake)
	{
		// code here...

		if (same_snake)
		{
			for (int i = 1; i < snake.size(); i++)
			{
				if (snake[i].contains(checkMe))
				{
					cout << "Collision with body\n";
					return true;
				}
			}
		}
		else
		{
			for (int i = 0; i < snake.size(); i++)
			{
				if (snake[i].contains(checkMe))
				{
					return true;
				}
			}
		}

		return false;

	}

	// Draw the snake...
	// For each square in the vector and call draw function. Read Square.h for more details
	void draw()
	{
		snake[0].textureDraw(texture);
		for (int i = 1; i < snake.size(); i++)
			snake[i].draw(r, g, b);
	}
};

#endif // _SNAKE_H