#include <conio.h>
#include <windows.h>
#include <iostream>
using namespace std;
#include "screen.h"

#define	FOREGROUND_WHITE	0x0007

short Screen::cursor_x, Screen::cursor_y;

void Screen::SetColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
	csbiInfo.wAttributes = color;
	SetConsoleTextAttribute(hConsole, csbiInfo.wAttributes);
}

void Screen::GoToXY(short x, short y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coordScreen = { x, y };
	SetConsoleCursorPosition(hConsole, coordScreen);
}

void Screen::ClrScr()
{
	COORD coordScreen = { 0, 0 };
	DWORD dwConSize, cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	csbi.wAttributes = FOREGROUND_WHITE;
	SetConsoleTextAttribute(hConsole, csbi.wAttributes);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, (TCHAR) ' ', dwConSize,
							   coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize,
							   coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}

void Screen::HideCursor()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	SetConsoleMode(hInput, 0);
	GetConsoleCursorInfo(hOutput, &ConsoleCursorInfo);
	ConsoleCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(hOutput, &ConsoleCursorInfo);
}

void Screen::ShowCursor()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	SetConsoleMode(hInput, 0);
	GetConsoleCursorInfo(hOutput, &ConsoleCursorInfo);
	ConsoleCursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(hOutput, &ConsoleCursorInfo);
}

void Screen::PutCursor()
{
	GoToXY(cursor_x, cursor_y);
}

void Screen::MoveCursor(short new_x, short new_y)
{
	cursor_x = new_x;
	cursor_y = new_y;
}

void Screen::Set(short x, short y, int fill)
{
	GoToXY(x, y);
	SetColor(BACKGROUND_BLUE | FOREGROUND_WHITE);
	_putch(fill);
}

void Screen::PrintText(short x, short y, const char *text)
{
	GoToXY(x, y);
	cout << text;
}

void Screen::PrintText(short x, short y, const char *text, short size)
{
	GoToXY(x, y);

	for (int i = 0; i < size; i++)
		if (!text[i]) break;
		else _putch(text[i]);
}

void Screen::PrintLeftArrow(short x, short y)
{
	GoToXY(x, y);
	_putch(27);
}

void Screen::PrintRightArrow(short x, short y)
{
	GoToXY(x, y);
	_putch(26);
}

void Screen::DeleteArrow(short x, short y)
{
	GoToXY(x, y);
	_putch(0xBA);
}
