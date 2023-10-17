#pragma once
#pragma warning(disable:4996)

#ifndef CONSOLE_H
#define CONSOLE_H

#include <iostream>
#include <conio.h>
#include <Windows.h>

typedef struct {
	unsigned int rows;
	unsigned int columns;
} Box;

class Console
{
public:
	Console();
	bool isFlush();
	int getKey();
	void showConsoleCursor(bool showFlag);
	void HideBlink();
	void ShowBlink();
	void HideEcho();
	void ShowEcho();
	Box getBox();
private:
	Box box;
};


#endif // !1
