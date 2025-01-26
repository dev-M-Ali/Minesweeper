#pragma once
#include <iostream>
#include <windows.h>
#include <ctime>
#include <thread>
#include <math.h>
#include <fstream>
#include "help.h"
#include "Box.h"
#include "MineBox.h"
#include "NumberBox.h"
#include "EmptyBox.h"

using namespace std;

class Minesweeper
{
private:
	long long int score;
	Box*** grid;
	int rows;
	int cols;
	int numOfMines;		//10 mines in beginner, 40 mines in intermediate and 99 mines in the expert level
	int xPixelConstant;	//770 for beginner, 625 for intermediate and 330 for the expert level
	int yPixelConstant;	//275 for beginner, 275 for intermediate and 275 for the expert level
	int blocksRevealed;
	int usableFlags;	//Same as the numOfMines
	bool firstLeftClick;
	time_t startTime;
	int totalTime;
	bool gameEnded;
	thread timerThread;

public:
	Minesweeper()
	{
		score = 0;
		grid = nullptr;
		rows = cols = numOfMines = xPixelConstant = yPixelConstant = 0;
		blocksRevealed = 0;
		usableFlags = 0;
		firstLeftClick = 0;
		gameEnded = 0;
	}

	Minesweeper(int r, int c, int Mines, int xSkips, int ySkips)
	{
		score = 0;
		grid = nullptr;
		rows = r;
		cols = c;
		numOfMines = Mines;
		xPixelConstant = xSkips;
		yPixelConstant = ySkips;
		blocksRevealed = 0;
		usableFlags = Mines;
		firstLeftClick = 0;
		gameEnded = 0;
	}

	~Minesweeper()
	{
		if (grid != nullptr)
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					delete grid[i][j];
				}
				delete[] grid[i];
			}

			delete[] grid;
		}
	}

	void startGame()
	{
		ShowConsoleCursor(false);
		int x_coord = 0, y_coord = 0, r = -1, c = -1, whichKey = 0;
		Sleep(500);
	
		while (1)
		{
			DrawFakeArray();

			if (getXAndYbyClick(x_coord, y_coord, whichKey))
			{
				if (ConvertxyIntoij(x_coord, y_coord, r, c) && whichKey == 1 && r != -1 && c != -1)
					break;
			}
		}

		initializeGridArray(r, c);
		while (1)
		{
			DrawGridArray();

			if (getXAndYbyClick(x_coord, y_coord, whichKey))
			{
				if (ConvertxyIntoij(x_coord, y_coord, r, c))
				{
					if (whichKey == 1)
					{
						if (LeftClickBlock(r, c))
						{
							gameEnded = 1;
							//For timer
							timerThread.join();
							GameOverScreen();
						}
						if (isFullyRevealed())
						{
							gameEnded = 1;
							//For timer
							timerThread.join();
							DrawGridArray();
							GameWonScreen();
							StoreScore();
							break;
						}
					}
					else if (whichKey == 9)
					{
						RightClickBlock(r, c);
					}
				}
			}
		}
	}

	void fullscreen()
	{
		keybd_event(VK_MENU, 0x38, 0, 0);
		keybd_event(VK_RETURN, 0x1c, 0, 0);
		keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
	}

	int timePassedSince(clock_t Earlier)
	{
		clock_t end = clock();

		int secondsPassed = (end - Earlier) / CLOCKS_PER_SEC;

		return secondsPassed;
	}

	void printHUD(clock_t Earlier)
	{
		while (gameEnded == 0)
		{
			//Showing timer
			gotoxy(82, 2);
			cout << "Time:";
			gotoxy(90, 2);
			cout << timePassedSince(Earlier) << "     ";
			
			//Showing number of usable flags
			printUsableFlags();
		}
	}

	void printUsableFlags()
	{
		//Showing number of usable flags
		gotoxy(0, 4);
		cout << "  Flags Usable:\n    " << usableFlags << "     ";
	}

	void DrawFakeArray()
	{
		//Showing timer
		gotoxy(82, 2);
		cout << "Time:";
		gotoxy(90, 2);
		cout << "0     ";

		//Showing number of usable flags
		printUsableFlags();

		//Drawing a border around the board
		for (int i = 1; i <= 50; i++)
		{
			if(i<=25)
				myHollowRect(xPixelConstant - i, yPixelConstant - i, xPixelConstant + i + cols * 42, yPixelConstant + i + rows * 42, 255, 200, 255);
			else
				myHollowRect(xPixelConstant - i, yPixelConstant - i, xPixelConstant + i + cols * 42, yPixelConstant + i + rows * 42, 175, 175, 255);
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				myBoxRect(xPixelConstant + (j * 42), yPixelConstant + (i * 42), xPixelConstant + 40 + (j * 42), yPixelConstant + 40 + (i * 42), 211, 211, 211);
			}
		}
	}

	void DrawGridArray()	//Will draw the Boxes on console
	{
		//Drawing a border around the board
		for (int i = 1; i <= 50; i++)
		{
			if (i <= 25)
				myHollowRect(xPixelConstant - i, yPixelConstant - i, xPixelConstant + i + cols * 42, yPixelConstant + i + rows * 42, 255, 200, 255);
			else
				myHollowRect(xPixelConstant - i, yPixelConstant - i, xPixelConstant + i + cols * 42, yPixelConstant + i + rows * 42, 175, 175, 255);
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				grid[i][j]->Draw(xPixelConstant, yPixelConstant);
			}
		}
		Sleep(100);
	}

	bool ConvertxyIntoij(int x_coord, int y_coord, int& row, int& col)	//Returns 1 if valid row, col values are found
	{
		int flag = 0;

		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (xPixelConstant + (j * 42) <= x_coord && xPixelConstant + 40 + (j * 42) > x_coord && yPixelConstant + (i * 42) <= y_coord && yPixelConstant + 40 + (i * 42) > y_coord)
				{
					row = i; col = j;
					flag = 1;
				}

		return flag;
	}

	void CreateSampleIntegerArray(int**& ContentArr, int x, int y)
	{
		//Assigning -1 to various indices of that integer array
		srand(time(NULL));
		int randomRow = 0, randomCol = 0;
		for (int i = 1; i <= numOfMines; i++)
		{
			randomRow = rand() % rows;
			randomCol = rand() % cols;

			if (randomRow != x && randomCol != y && ContentArr[randomRow][randomCol] != -1)	//If a mine was not already present at the block, represented by a -1, then assign it a mine.
			{
				ContentArr[randomRow][randomCol] = -1;
			}
			else	//If a mine was present at the block, run the loop once again without making any change in this iteration.
			{
				i--;
			}
		}

		//Checks for the number of mines in each box's adjacent boxes and stores it in the box itself.
		int count = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (ContentArr[i][j] != -1)	//If a mine is present at the block with index i, j then we will not change its value.
				{
					count = 0;
					for (int k = i - 1; k < i + 2; k++)	//k and l loops will be used to scan the adjacent blocks of the block with index i, j.
					{
						for (int l = j - 1; l < j + 2; l++)
						{
							if (k >= 0 && k < rows && l >= 0 && l < cols)	//if statement to assure that the loop does not go out of bounds.
							{
								if (k != i || l != j)	//if statement to exclude the block with index i, j because it does not count towards the amount of adjacent mines.
								{
									if (ContentArr[k][l] == -1)
										count++;
								}
							}
						}
					}

					ContentArr[i][j] = count;
				}
			}
		}

		/*for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				cout << ContentArr[i][j] << "\t";
			}
			cout << endl;
		}*/
	}

	void initializeGridArray(int r, int c)	//Needs modification
	{
		//Making an integer array that will be used to help initialize our grid array
		int** ContentArr = new int*[rows];
		for (int i = 0; i < rows; i++)
		{
			ContentArr[i] = new int[cols];
		}

		CreateSampleIntegerArray(ContentArr, r, c);

		//Initializing our grid array with boxes
		grid = new Box * *[rows];
		for (int i = 0; i < rows; i++)
		{
			grid[i] = new Box * [cols];
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (ContentArr[i][j] == -1)	//If -1 is present at the i, jth index of the integer array, then assign a MineBox to the same index of the grid array
				{
					grid[i][j] = new MineBox(i, j, -1);
				}
				else if (ContentArr[i][j] == 0)	//If 0 is present at the i, jth index of the integer array, then assign an EmptyBox to the same index of the grid array
				{
					grid[i][j] = new EmptyBox(i, j, 0);
				}
				else if (ContentArr[i][j] > 0 && ContentArr[i][j] < 9)	//If a number from 1 - 8 is present at the i, jth index of the integer array, then assign a NumberBox to the same index of the grid array
				{
					grid[i][j] = new NumberBox(i, j, ContentArr[i][j]);
				}
				else
				{
					cout << "An error occurred in initializing the grid array\n";
				}
			}
		}

		//Deleting the integer array since it will not be used any longer
		if (ContentArr != nullptr)
		{
			for (int i = 0; i < rows; i++)
				delete[] ContentArr[i];
			delete[] ContentArr;
		}

		LeftClickBlock(r, c);
	}

	bool RevealAdjacentBlocks()	//Will reveal all adjacent boxes around an empty box
	{
		int flag = 0;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (grid[i][j]->value == 0 && grid[i][j]->state == 1)
				{
					for (int k = i - 1; k < i + 2; k++)	//k and l loops will be used to scan the adjacent blocks of the block with index i, j.
					{
						for (int l = j - 1; l < j + 2; l++)
						{
							if (k >= 0 && k < rows && l >= 0 && l < cols)	//if statement to assure that the loop does not go out of bounds.
							{
								if (grid[k][l]->state == 0)
								{
									grid[k][l]->state = 1;
									blocksRevealed++;
									flag = 1;
								}
							}
						}
					}
				}
			}
		}
		return flag;
	}

	bool LeftClickBlock(int row, int col)	//Will return true if a mine is left-clicked, false otherwise
	{
		//Initiate the timer on the first left click
		if (firstLeftClick == 0)
		{
			startTime = clock();
			timerThread = std::thread{ &Minesweeper::printHUD, this, startTime };	//(&ClassName::MemberFunction, CallerObject, parameters);
			firstLeftClick = 1;
		}

		if (grid[row][col]->state == 0)
		{
			if (grid[row][col]->value == 0)	//If an empty box was left-clicked, then reveal it and the adjacent blocks
			{
				grid[row][col]->state = 1;
				blocksRevealed++;
				while (RevealAdjacentBlocks());
			}
			else if (grid[row][col]->value > 0 && grid[row][col]->value < 9)	//If a number box was left-clicked, then reveal it
			{
				grid[row][col]->state = 1;
				blocksRevealed++;
			}
			else if (grid[row][col]->value == -1)	//Return true if a mine was left-clicked
			{
				grid[row][col]->state = 1;
				return true;
			}
		}
		return false;
	}

	void RightClickBlock(int row, int col)
	{
		if (grid[row][col]->state == 0)
		{
			grid[row][col]->state = 2;
			usableFlags--;
		}
		else if (grid[row][col]->state == 2)
		{
			grid[row][col]->state = 0;
			usableFlags++;
		}
	}

	bool getXAndYbyClick(int& xpos, int& ypos, int &whichKey)	//Will return 1 if LMB is pressed, 9 if RMG is pressed
	{

		HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
		DWORD Events;
		INPUT_RECORD InputRecord;
		SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
		do
		{
			ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		
			//Checking if left key is pressed
			if (GetAsyncKeyState(VK_LBUTTON) & 1)
			{
				POINT p;
				HWND hwnd = GetConsoleWindow();
				GetCursorPos(&p);

				if (ScreenToClient(hwnd, &p))
				{
					xpos = p.x * 1.25 + 2;
					ypos = p.y * 1.25 + 2;
					//cout << "Left click\n";
					whichKey = 1;
					return 1;
				}
			}
			
			//Checking if right key is pressed
			if (GetAsyncKeyState(VK_RBUTTON) & 1)
			{
				POINT p;
				HWND hwnd = GetConsoleWindow();
				GetCursorPos(&p);

				if (ScreenToClient(hwnd, &p))
				{
					xpos = p.x * 1.25 + 2;
					ypos = p.y * 1.25 + 2;
					//cout << "Right click\n";
					whichKey = 9;
					return 1;
				}
			}
		} while (true);

		return 0;
	}

	void revealMines()
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (grid[i][j]->value == -1)
					grid[i][j]->state = 1;
			}
		}
	}

	void GameOverScreen()
	{
		revealMines();

		for (int i = 1; i <= 5; i++)
		{
			DrawGridArray();
			gotoxy(81, i);
			cout << "Game   Over";
			Sleep(200);
			system("CLS");
			DrawGridArray();

			//Showing timer
			gotoxy(82, 2);
			cout << "Time:";
			gotoxy(90, 2);
			cout << timePassedSince(startTime) << "     ";

			//Showing number of usable flags
			printUsableFlags();
		}

		gotoxy(81, 5);
		cout << "Game   Over\n";
		DrawGridArray();
		Sleep(1000);
	}

	bool isFullyRevealed()
	{
		int flag = 1;
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (grid[i][j]->value != -1)
				{
					if (grid[i][j]->state == 0 || grid[i][j]->state == 2)
						flag = 0;
				}
			}
		}

		if (blocksRevealed == (rows * cols) - numOfMines && flag == 1)
		{
			return true;
		}
		return false;
	}

	void GameWonScreen()
	{
		/*long long int divisor = 0;
		divisor = pow(1.01, timePassedSince(startTime));

		double temp = 0;
		temp = (float) 1 / divisor;*/

		score = 100000 / timePassedSince(startTime);
		
		for (int i = 1; i <= 5; i++)
		{
			DrawGridArray();
			gotoxy(65, i);
			cout << "Congratulations! You won and scored " << score << " points!";
			Sleep(250);
			system("CLS");
			DrawGridArray();

			//Showing timer
			gotoxy(82, 2);
			cout << "Time:";
			gotoxy(90, 2);
			cout << timePassedSince(startTime) << "     ";

			//Showing number of usable flags
			printUsableFlags();
		}

		totalTime = timePassedSince(startTime);
		gotoxy(65, 5);
		cout << "Congratulations! You won and scored " << score << " points!";
		DrawGridArray();
		Sleep(1000);
	}

	void StoreScore()
	{
		string n[5];
		if (rows == cols && rows == 9 && numOfMines == 10)
		{
			ifstream fin("Easy.txt");

			char names[5][100];
			int time[5];
			int flag = 0;

			//Inputting from file
			for (int i = 0; i < 5; i++)
			{
				fin.getline(names[i], 100);
				fin >> time[i];
				fin.ignore();
			}

			//Comparing user's time
			int index = 0;
			for (int i = 0; i < 5; i++)
			{
				if (totalTime <= time[i])
				{
					index = i;
					flag = 1;
					break;
				}
			}

			if (flag == 1)
			{
				//Converting char array into string
				for (int i = 0; i < 5; i++)
				{
					n[i] = names[i];
				}

				//Moving data
				for (int i = 4; i >= index; i--)
				{
					if (i != 0)
					{
						time[i] = time[i - 1];
						n[i] = n[i - 1];
					}
				}

				char temp[100];

				gotoxy(0, 8);
				cout << "Enter username\n";
				cin.getline(temp, 100);
				n[index] = temp;
				time[index] = totalTime;

				//Outputting to file
				ofstream fout("Easy.txt");

				for (int i = 0; i < 5; i++)
				{
					fout << n[i] << endl;
					fout << time[i] << endl;
				}
				fout.close();
			}

			cout << "\nLeaderboard:\n";
			for (int i = 0; i < 5; i++)
			{
				cout << n[i] << " " << time[i] << endl;
			}

			fin.close();
		}

		else if (rows == cols && rows == 16 && numOfMines == 40)
		{
			ifstream fin("Medium.txt");

			char names[5][100];
			int time[5];
			int flag = 0;

			//Inputting from file
			for (int i = 0; i < 5; i++)
			{
				fin.getline(names[i], 100);
				fin >> time[i];
				fin.ignore();
			}

			//Comparing user's time
			int index = 0;
			for (int i = 0; i < 5; i++)
			{
				if (totalTime <= time[i])
				{
					index = i;
					flag = 1;
					break;
				}
			}

			if (flag == 1)
			{
				//Converting char array into string
				for (int i = 0; i < 5; i++)
				{
					n[i] = names[i];
				}

				//Moving data
				for (int i = 4; i >= index; i--)
				{
					if (i != 0)
					{
						time[i] = time[i - 1];
						n[i] = n[i - 1];
					}
				}

				char temp[100];

				gotoxy(0, 8);
				cout << "Enter username\n";
				cin.getline(temp, 100);
				n[index] = temp;
				time[index] = totalTime;

				//Outputting to file
				ofstream fout("Medium.txt");

				for (int i = 0; i < 5; i++)
				{
					fout << n[i] << endl;
					fout << time[i] << endl;
				}
				fout.close();
			}

			cout << "\nLeaderboard:\n";
			for (int i = 0; i < 5; i++)
			{
				cout << n[i] << " " << time[i] << endl;
			}

			fin.close();
		}

		else if (rows == 16 && cols == 30 && numOfMines == 99)
		{
			ifstream fin("Hard.txt");

			char names[5][100];
			int time[5];
			int flag = 0;

			//Inputting from file
			for (int i = 0; i < 5; i++)
			{
				fin.getline(names[i], 100);
				fin >> time[i];
				fin.ignore();
			}

			//Comparing user's time
			int index = 0;
			for (int i = 0; i < 5; i++)
			{
				if (totalTime <= time[i])
				{
					index = i;
					flag = 1;
					break;
				}
			}

			if (flag == 1)
			{
				//Converting char array into string
				for (int i = 0; i < 5; i++)
				{
					n[i] = names[i];
				}

				//Moving data
				for (int i = 4; i >= index; i--)
				{
					if (i != 0)
					{
						time[i] = time[i - 1];
						n[i] = n[i - 1];
					}
				}

				char temp[100];

				gotoxy(0, 8);
				cout << "Enter username\n";
				cin.getline(temp, 100);
				n[index] = temp;
				time[index] = totalTime;
				//Outputting to file
				ofstream fout("Hard.txt");

				for (int i = 0; i < 5; i++)
				{
					fout << n[i] << endl;
					fout << time[i] << endl;
				}
				fout.close();
			}

			cout << "\nLeaderboard:\n";
			for (int i = 0; i < 5; i++)
			{
				cout << n[i] << " " << time[i] << endl;
			}

			fin.close();
		}
	}

	void ShowConsoleCursor(bool showFlag)
	{
		HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

		CONSOLE_CURSOR_INFO     cursorInfo;

		GetConsoleCursorInfo(out, &cursorInfo);
		cursorInfo.bVisible = showFlag; // set the cursor visibility
		SetConsoleCursorInfo(out, &cursorInfo);
	}
};