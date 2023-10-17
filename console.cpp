#pragma warning(disable:4996)

#include "console.h"

Console::Console() {
	this->box = getBox();
}

bool Console::isFlush() {
	return _kbhit() != 0;
}

int Console::getKey() {
	return _getch();
}

void Console::showConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Console::HideBlink() {
	showConsoleCursor(false);
}

void Console::ShowBlink() {
	showConsoleCursor(true);
}

void Console::HideEcho() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
}

void Console::ShowEcho() {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode | ENABLE_ECHO_INPUT);
}

::Box Console::getBox() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	::Box box{};
	box.rows = rows;
	box.columns = columns;
	return box;
}