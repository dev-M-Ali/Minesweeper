#pragma once
#include <iostream>
#include "Minesweeper.h"
#include "Box.h"

using namespace std;

class NumberBox :public Box
{
private:

public:
	NumberBox()
	{
		state = 0;
	}

	NumberBox(int x, int y, int adjacentMines):Box(x, y, adjacentMines)
	{
		state = 0;
	}

	void Draw(int xPixelConstant, int yPixelConstant)
	{
		if (state == 0)
		{
			myBoxRect(xPixelConstant + (j * 42), yPixelConstant + (i * 42), xPixelConstant + 40 + (j * 42), yPixelConstant + 40 + (i * 42), 211, 211, 211);	//Adding (j * 2) and (i * 2) allows us to avoid overwriting, which causes flickering on the screen. Ending values are the RGB code for the fill colour.
		}
		else if (state == 1)
		{
			myBoxRect(xPixelConstant + (j * 42), yPixelConstant + (i * 42), xPixelConstant + 40 + (j * 42), yPixelConstant + 40 + (i * 42), 150, 150, 150);	//Adding (j * 2) and (i * 2) allows us to avoid overwriting, which causes flickering on the screen. Ending values are the RGB code for the fill colour.
			if (value == 1)
			{
				myColouredLine(xPixelConstant + (j * 42) + 18, yPixelConstant + (i * 42) + 10, xPixelConstant + (j * 42) + 18, yPixelConstant + (i * 42) + 30, 0, 0, 128);
				myColouredLine(xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 30, xPixelConstant + (j * 42) + 23, yPixelConstant + (i * 42) + 30, 0, 0, 128);
				myColouredLine(xPixelConstant + (j * 42) + 18, yPixelConstant + (i * 42) + 10, xPixelConstant + (j * 42) + 14, yPixelConstant + (i * 42) + 17, 0, 0, 128);
			}
			else if (value == 2)
			{
				myColouredLine(xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 14, xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 14, 0, 255, 0);
				myColouredLine(xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 14, xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 21, 0, 255, 0);
				myColouredLine(xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 21, xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 21, 0, 255, 0);
				myColouredLine(xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 21, xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 28, 0, 255, 0);
				myColouredLine(xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 28, xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 28, 0, 255, 0);
			}
			else if (value == 3)
			{
				myColouredLine(xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 10, xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 10, 255, 0, 0);
				myColouredLine(xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 10, xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 18, 255, 0, 0);
				myColouredLine(xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 18, xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 18, 255, 0, 0);
				myColouredLine(xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 18, xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 26, 255, 0, 0);
				myColouredLine(xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 26, xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 26, 255, 0, 0);
			}
			else if (value == 4)
			{
				myColouredLine(xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 10, xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 36, 0, 0, 255);
				myColouredLine(xPixelConstant + (j * 42) + 14, yPixelConstant + (i * 42) + 10, xPixelConstant + (j * 42) + 14, yPixelConstant + (i * 42) + 22, 0, 0, 255);
				myColouredLine(xPixelConstant + (j * 42) + 14, yPixelConstant + (i * 42) + 22, xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 22, 0, 0, 255);
			}
			else if (value == 5)
			{
				myColouredLine(xPixelConstant + (j * 42) + 29, yPixelConstant + (i * 42) + 9, xPixelConstant + (j * 42) + 11, yPixelConstant + (i * 42) + 9, 128, 0, 0);
				myColouredLine(xPixelConstant + (j * 42) + 11, yPixelConstant + (i * 42) + 9, xPixelConstant + (j * 42) + 11, yPixelConstant + (i * 42) + 19, 128, 0, 0);
				myColouredLine(xPixelConstant + (j * 42) + 11, yPixelConstant + (i * 42) + 19, xPixelConstant + (j * 42) + 29, yPixelConstant + (i * 42) + 19, 128, 0, 0);
				myColouredLine(xPixelConstant + (j * 42) + 29, yPixelConstant + (i * 42) + 19, xPixelConstant + (j * 42) + 29, yPixelConstant + (i * 42) + 30, 128, 0, 0);
				myColouredLine(xPixelConstant + (j * 42) + 29, yPixelConstant + (i * 42) + 30, xPixelConstant + (j * 42) + 11, yPixelConstant + (i * 42) + 30, 128, 0, 0);
			}
			else if (value == 6)
			{
				myColouredLine(xPixelConstant + (j * 42) + 29, yPixelConstant + (i * 42) + 8, xPixelConstant + (j * 42) + 29, yPixelConstant + (i * 42) + 6, 32, 178, 170);
				myColouredLine(xPixelConstant + (j * 42) + 29, yPixelConstant + (i * 42) + 6, xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 6, 32, 178, 170);
				myColouredLine(xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 6, xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 32, 32, 178, 170);
				myColouredLine(xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 32, xPixelConstant + (j * 42) + 29, yPixelConstant + (i * 42) + 32, 32, 178, 170);
				myColouredLine(xPixelConstant + (j * 42) + 29, yPixelConstant + (i * 42) + 32, xPixelConstant + (j * 42) + 29, yPixelConstant + (i * 42) + 19, 32, 178, 170);
				myColouredLine(xPixelConstant + (j * 42) + 29, yPixelConstant + (i * 42) + 19, xPixelConstant + (j * 42) + 13, yPixelConstant + (i * 42) + 19, 32, 178, 170);
			}
			else if (value == 7)
			{
				myColouredLine(xPixelConstant + (j * 42) + 15, yPixelConstant + (i * 42) + 9, xPixelConstant + (j * 42) + 15, yPixelConstant + (i * 42) + 6, 0, 0, 0);
				myColouredLine(xPixelConstant + (j * 42) + 15, yPixelConstant + (i * 42) + 6, xPixelConstant + (j * 42) + 30, yPixelConstant + (i * 42) + 6, 0, 0, 0);
				myColouredLine(xPixelConstant + (j * 42) + 30, yPixelConstant + (i * 42) + 6, xPixelConstant + (j * 42) + 16, yPixelConstant + (i * 42) + 35, 0, 0, 0);
				myColouredLine(xPixelConstant + (j * 42) + 17, yPixelConstant + (i * 42) + 21, xPixelConstant + (j * 42) + 29, yPixelConstant + (i * 42) + 21, 0, 0, 0);
			}
			else if (value == 8)
			{
				myEllipse(xPixelConstant + (j * 42) + 12, yPixelConstant + (i * 42) + 6, xPixelConstant + (j * 42) + 27, yPixelConstant + (i * 42) + 17, 105, 105, 105);
				myEllipse(xPixelConstant + (j * 42) + 12, yPixelConstant + (i * 42) + 17, xPixelConstant + (j * 42) + 28, yPixelConstant + (i * 42) + 33, 105, 105, 105);
			}
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