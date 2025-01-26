#pragma once
#include <iostream>
#include "Minesweeper.h"
#include "Box.h"

using namespace std;

class EmptyBox :public Box
{
private:

public:
	EmptyBox()
	{
		state = 0;
	}

	EmptyBox(int x, int y, int value) :Box(x, y, value)
	{
		state = 0;
	}

	void Draw(int xPixelConstant, int yPixelConstant)
	{
		if (state == 0)
		{
			myBoxRect(xPixelConstant + (j * 42), yPixelConstant + (i * 42), xPixelConstant + 40 + (j * 42), yPixelConstant + 40 + (i * 42), 211, 211, 211);
		}
		else if (state == 1)
		{
			myBoxRect(xPixelConstant + (j * 42), yPixelConstant + (i * 42), xPixelConstant + 40 + (j * 42), yPixelConstant + 40 + (i * 42), 150, 150, 150);
		}
		else if (state == 2)
		{
			myBoxRect(xPixelConstant + (j * 42), yPixelConstant + (i * 42), xPixelConstant + 40 + (j * 42), yPixelConstant + 40 + (i * 42), 211, 211, 211);
			myColouredLine(xPixelConstant + (j * 42) + 22, yPixelConstant + (i * 42) + 5, xPixelConstant + (j * 42) + 22, yPixelConstant + (i * 42) + 35, 0, 0, 0);
			myColouredLine(xPixelConstant + (j * 42) + 22, yPixelConstant + (i * 42) + 5, xPixelConstant + (j * 42) + 7, yPixelConstant + (i * 42) + 19, 255, 0, 0);
			myColouredLine(xPixelConstant + (j * 42) + 7, yPixelConstant + (i * 42) + 19, xPixelConstant + (j * 42) + 22, yPixelConstant + (i * 42) + 19, 255, 0, 0);
			myColouredLine(xPixelConstant + (j * 42) + 15, yPixelConstant + (i * 42) + 35, xPixelConstant + (j * 42) + 28, yPixelConstant + (i * 42) + 35, 0, 0, 0);
			myColouredLine(xPixelConstant + (j * 42) + 18, yPixelConstant + (i * 42) + 34, xPixelConstant + (j * 42) + 18, yPixelConstant + (i * 42) + 33, 0, 0, 0);
			myColouredLine(xPixelConstant + (j * 42) + 18, yPixelConstant + (i * 42) + 33, xPixelConstant + (j * 42) + 25, yPixelConstant + (i * 42) + 33, 0, 0, 0);
			myColouredLine(xPixelConstant + (j * 42) + 25, yPixelConstant + (i * 42) + 34, xPixelConstant + (j * 42) + 18, yPixelConstant + (i * 42) + 34, 0, 0, 0);
		}
	}

};