#pragma once
#include <iostream>
#include "Minesweeper.h"
#include "help.h"

using namespace std;

//Values of x co-relate with columns while values of y co-relate with rows

class Box
{
private:
	friend class Minesweeper;

protected:
	int i;
	int j;
	int value;

	int state;	//0 state will indicate that the box is hidden, 1 will indicate that it has been revealed and 2 will indicate that it has been flagged

public:
	Box()
	{
		i = j = state = value = 0;
	}
	
	Box(int iNew, int jNew, int val)
	{
		i = iNew;
		j = jNew;
		state = 0;
		value = val;
	}

	friend class Easy;

	virtual void Draw(int xPixelConstant, int yPixelConstant) = 0;
};