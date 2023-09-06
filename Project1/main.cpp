#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
enum eDirection {STOP = 0, LEFT, UP, RIGHT, DOWN};
// eDirection is a type define by myself, not a variable
eDirection dir;

// position of the snake head
int x, y;

// position of the fruit
int fruitX, fruitY;

// use two arrays to record tails and an int to record length
int bodyLength = 0;
int gufX[50], gufY[50];

// why the game ends
string causeOfDeath = " ";
// score board
int score = 0;

// set up the positions and direction
void Setup()
{
	gameOver = false;
	dir = STOP;
	// the head of snake appears in the middle of the screen
	x = width / 2;
	y = height / 2;
	// the fruit appears in a random location
	fruitX = rand() % width;
	fruitY = rand() % height;
}

// draw the map (like output a matrux)
// use '#' to indicate the border
void Draw()
{
	// clear the screen
	system("cls");
	// the top border
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width + 2; j++)
		{
			if (j == 0 || j == 21)
				cout << "#";
			else if (i == y and j == x)
				cout << 'O';
			else if (i == fruitY and j == fruitX)
				cout << 'F';
			else // body or space
			{
				boolean body = false;
				for (int k = 0; k < bodyLength; k++)
				{
					if (i == gufY[k] && j == gufX[k])
					{
						cout << 'o';
						body = true;
						break;
					}
				}
				if (!body)
					cout << ' ';
			}
		}
		cout << endl; // finish one row
	}
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << " score: " << score << endl;
	cout << causeOfDeath << endl;
}

// user types one of 'awsd' to change direction
void Input()
{
	if(_kbhit())
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		}
}
void MoveHead()
{
	// the origins is in the top left corner
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case UP:
		y--;
		break;
	case RIGHT:
		x++;
		break;
	case DOWN:
		y++;
		break;
	}
	// go out of the borders
	if (x < 1 || x > 20 || y < 0 || y >19)
	{
		gameOver = true;
		cout << "you hit the wall! " << endl;
	}
	// eat the fruit
	if (x == fruitX && y == fruitY)
	{
		bodyLength++;
		score += 10;
		// store the position in gufX, gufY
		// gufX[bodyLength - 1] = x;
		// gufY[bodyLength - 1] = y;
		// add a new fruit
		fruitX = rand() % width;
		fruitY = rand() % height;
}
}

void MoveBody()
{
	if (bodyLength == 0)
		return;
	for (int i = bodyLength - 1; i > 0; i--)
	{
		// xi, yi = xi-1, yi-1 
		gufX[i] = gufX[i - 1];
		gufY[i] = gufY[i - 1];
	}
	gufX[0] = x;
	gufY[0] = y;
}

void Suicide()
{
	for (int i = 0; i < bodyLength; i++)
	{
		if (x == gufX[i] && y == gufY[i])
		{
			gameOver = true;
			cout << "you bite yourself!" << endl;
			return; // no need for subsequent loops
		}
	}
}
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		// move the body before move the head, or else it will overlap
		MoveBody();
		MoveHead();
		Suicide();
		Sleep(200);
	}
	return 0;
}