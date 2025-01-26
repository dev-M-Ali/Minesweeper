#include <iostream>
#include <windows.h>
#include <ctime>
#include <thread>
#include "Minesweeper.h"

using namespace std;

//GameWon(), score, storing high score
//Beginner 9*9, intermediate 16*16 and expert 16*30

void fullscreen()
{
	keybd_event(VK_MENU, 0x38, 0, 0);
	keybd_event(VK_RETURN, 0x1c, 0, 0);
	keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
	keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}
void draw_easy(int x, int y)
{
	//while (1)   
	{
		myThickRect(x + 106, y + 111, x + 522, y + 346, 0, 255, 0);
		// Draw E //	
		myThickLine(x + 218, y + 157, x + 155, y + 157, 255, 255, 255);
		myThickLine(x + 155, y + 157, x + 155, y + 305, 255, 255, 255);
		myThickLine(x + 155, y + 305, x + 218, y + 305, 255, 255, 255);
		myThickLine(x + 199, y + 233, x + 155, y + 233, 255, 255, 255);
		// Draw A //
		myThickLine(x + 265, y + 157, x + 232, y + 302, 255, 255, 255);
		myThickLine(x + 265, y + 157, x + 303, y + 302, 255, 255, 255);
		myThickLine(x + 250, y + 246, x + 287, y + 246, 255, 255, 255);
		// Draw S //
		myThickLine(x + 396, y + 175, x + 396, y + 157, 255, 255, 255);
		myThickLine(x + 396, y + 157, x + 314, y + 157, 255, 255, 255);
		myThickLine(x + 314, y + 157, x + 314, y + 233, 255, 255, 255);
		myThickLine(x + 314, y + 233, x + 396, y + 233, 255, 255, 255);
		myThickLine(x + 396, y + 233, x + 396, y + 302, 255, 255, 255);
		myThickLine(x + 396, y + 302, x + 318, y + 302, 255, 255, 255);
		myThickLine(x + 318, y + 302, x + 318, y + 285, 255, 255, 255);
		// Draw Y //
		myThickLine(x + 488, y + 157, x + 436, y + 302, 255, 255, 255);
		myThickLine(x + 422, y + 157, x + 461, y + 227, 255, 255, 255);
		Sleep(100);
	}
}
void draw_med(int x, int y)
{
	//while (1)
	{
		myThickRect(x + 106, y + 111, x + 522, y + 346, 0, 0, 255);
		// Draw M //
		myThickLine(x + 140, y + 157, x + 140, y + 302, 255, 255, 255);
		myThickLine(x + 140, y + 157, x + 180, y + 216, 255, 255, 255);
		myThickLine(x + 180, y + 216, x + 220, y + 157, 255, 255, 255);
		myThickLine(x + 220, y + 157, x + 220, y + 302, 255, 255, 255);

		// Draw E //
		myThickLine(x + 365, y + 157, x + 284, y + 157, 255, 255, 255);
		myThickLine(x + 284, y + 157, x + 284, y + 302, 255, 255, 255);
		myThickLine(x + 284, y + 302, x + 365, y + 302, 255, 255, 255);
		myThickLine(x + 287, y + 228, x + 339, y + 228, 255, 255, 255);
		// Draw D //
		myThickLine(x + 403, y + 157, x + 502, y + 157, 255, 255, 255);
		myThickLine(x + 502, y + 157, x + 502, y + 302, 255, 255, 255);
		myThickLine(x + 502, y + 302, x + 403, y + 302, 255, 255, 255);
		myThickLine(x + 422, y + 157, x + 422, y + 302, 255, 255, 255);
		Sleep(100);
	}
}
void draw_hard(int x, int y)
{
	//while (1)
	{
		myThickRect(x + 106, y + 111, x + 522, y + 346, 255, 0, 0);
		// Draw H  //  
		myThickLine(x + 140, y + 157, x + 140, y + 302, 255, 255, 255);
		myThickLine(x + 214, y + 157, x + 214, y + 302, 255, 255, 255);
		myThickLine(x + 213, y + 223, x + 140, y + 223, 255, 255, 255);
		//  Draw A  //
		myThickLine(x + 265, y + 157, x + 232, y + 302, 255, 255, 255);
		myThickLine(x + 265, y + 157, x + 303, y + 302, 255, 255, 255);
		myThickLine(x + 250, y + 246, x + 287, y + 246, 255, 255, 255);
		//   Draw R  //
		myThickLine(x + 320, y + 157, x + 320, y + 302, 255, 255, 255);
		myThickLine(x + 320, y + 157, x + 385, y + 157, 255, 255, 255);
		myThickLine(x + 385, y + 157, x + 385, y + 226, 255, 255, 255);
		myThickLine(x + 385, y + 226, x + 320, y + 226, 255, 255, 255);
		myThickLine(x + 320, y + 226, x + 390, y + 302, 255, 255, 255);
		//  Draw D  //
		myThickLine(x + 403, y + 157, x + 502, y + 157, 255, 255, 255);
		myThickLine(x + 502, y + 157, x + 502, y + 302, 255, 255, 255);
		myThickLine(x + 502, y + 302, x + 403, y + 302, 255, 255, 255);
		myThickLine(x + 422, y + 157, x + 422, y + 302, 255, 255, 255);
		Sleep(100);
	}
}
bool getXAndYbyClick(int& xpos, int& ypos, int& whichKey)	//Will return 1 if LMB is pressed, 9 if RMG is pressed
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

int main()
{
	int  x = 0, y = 0, whichKey = 0;
	//system("color 9F");
	system("color E0");
	fullscreen();
	Sleep(500);

	//Drawing menu screen
	while (1)
	{
		int temp1 = 650, temp2 = -25;
		draw_easy(temp1, temp2);
		draw_med(temp1, temp2 + 300);
		draw_hard(temp1, temp2 + 600);

		//Taking input
		if (getXAndYbyClick(x, y, whichKey))
		{
			if (whichKey == 1)
				//If easy was left-clicked
				if (x >= temp1 + 106 && y >= temp2 + 111 && x <= temp1 + 522 && y <= temp2 + 346)
				{
					system("CLS");
					//system("color 9F");
					Minesweeper Game(9, 9, 10, 770, 275);
					Game.startGame();
					break;
				}
				//if medium was left-clicked
				else if(x >= temp1 + 106 && y >= temp2 + 300 + 111 && x <= temp1 + 522 && y <= temp2 + 300 + 346)
				{
					system("CLS");
					//system("color 9F");
					Minesweeper Game(16, 16, 40, 625, 275);
					Game.startGame();
					break;
				}
				//if hard was left-clicked
				else if (x >= temp1 + 106 && y >= temp2 + 600 + 111 && x <= temp1 + 522 && y <= temp2 + 600 + 346)
				{
					system("CLS");
					//system("color 9F");
					Minesweeper Game(16, 30, 99, 330, 275);
					Game.startGame();
					break;
				}
		}
	}

	system("pause");
	return 0;
}