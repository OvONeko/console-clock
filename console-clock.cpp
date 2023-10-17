
#pragma warning(disable:4996)

#include <iostream>
#include "console.h"
#include "datetime.h"
#include "shownumber.h"

bool showSecond = false;
int transcount = 0;
int tick = 1000;
std::string transcolor[5] = {
	"\033[38;2;85;205;253m\033[48;2;85;205;253m",
	"\033[38;2;246;170;183m\033[48;2;246;170;183m",
	"\033[38;2;255;255;255m\033[48;2;255;255;255m",
	"\033[38;2;246;170;183m\033[48;2;246;170;183m",
	"\033[38;2;85;205;253m\033[48;2;85;205;253m"
};
std::string transdatecolor[3] = {
	"\033[38;2;85;205;253m",
	"\033[38;2;246;170;183m",
	"\033[38;2;255;255;255m"
};
std::string normalColor = "\033[92;102m";
std::string dateColor = "\033[0m\033[92m";
int spaceCount = 0;
int returnCount = 0;
bool showonce = false;
bool screensaver = false;
bool blinking = false;

bool setColor(char t) {
	if ((t >= '0') && (t <= '7')) {
		normalColor = "\033[" + std::to_string(((int)t) - 0x30 + 40) + ";" + std::to_string(((int)t) - 0x30 + 30) + "m";
		dateColor = "\033[0m\033[" + std::to_string(((int)t) - 0x30 + 30) + "m";
	}
	else if (t == '8') {
		normalColor = "\033[90;100m";
		dateColor = "\033[0m\033[90m";
	}
	else if (t == '9') {
		normalColor = "\033[91;101m";
		dateColor = "\033[0m\033[91m";
	}
	else if ((std::tolower(t) >= 'a') && (std::tolower(t) <= 'f')) {
		normalColor = "\033[" + std::to_string(((int)std::tolower(t)) - 0x61 + 92) + ";" + std::to_string(((int)std::tolower(t)) - 0x61 + 102) + "m";
		dateColor = "\033[0m\033[" + std::to_string(((int)std::tolower(t)) - 0x61 + 92) + "m";
	}
	else {
		return false;
	}
	return true;
}

int hexCharToInt(char c) {
	if ((c >= '0') && (c <= '9'))
		return (c - '0');
	if ((c >= 'A') && (c <= 'F'))
		return (c - 'A' + 10);
	if ((c >= 'a') && (c <= 'f'))
		return (c - 'a' + 10);
	return -1;
}

bool setRGBColor(char* color) {
	unsigned int r = 0, g = 0, b = 0;
	unsigned long rgb = 0;
	while (*(++color)) {
		rgb <<= 4;
		rgb += hexCharToInt(*color);
		if (hexCharToInt(*color) == -1)
			return false;
	}
	r = (rgb >> 16) & 0xFF;
	g = (rgb >> 8) & 0xFF;
	b = rgb & 0xFF;
	normalColor = "\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m\033[48;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
	dateColor = "\033[0m\033[38;2;" + std::to_string(r) + ";" + std::to_string(g) + ";" + std::to_string(b) + "m";
	return true;
}


int main()
{
	Console console;
	DateTime dt;
	Box b = console.getBox();
	while (true) {
		if (!showonce)
			system("cls");
		if (returnCount) {
			for (int r = 0; r < returnCount; ++r)
				std::cout << std::endl;
		}
		for (int j = 0; j < 5; ++j) {
			if (spaceCount) {
				for (int space = 0; space < spaceCount; ++space)
					std::cout << ' ' << std::flush;
			}
			showNumber(dt.getTime().hour / 10, j, (transcount != 5) ? normalColor : transcolor[j]);
			std::cout << "\033[0m  " << std::flush;
			showNumber(dt.getTime().hour % 10, j, (transcount != 5) ? normalColor : transcolor[j]);
			std::cout << (((j == 1) || (j == 3)) ? (((!blinking) || (dt.getTime().second % 2 == 0)) ? ("\033[0m  " + ((transcount != 5) ? normalColor : transcolor[j]) + "  \033[0m  ") : ("\033[0m      ")) : ("\033[0m      ")) << std::flush;
			showNumber(dt.getTime().minute / 10, j, (transcount != 5) ? normalColor : transcolor[j]);
			std::cout << "\033[0m  " << std::flush;
			showNumber(dt.getTime().minute % 10, j, (transcount != 5) ? normalColor : transcolor[j]);
			if (showSecond) {
				std::cout << (((j == 1) || (j == 3)) ? (((!blinking) || (dt.getTime().second % 2 == 0)) ? ("\033[0m  " + ((transcount != 5) ? normalColor : transcolor[j]) + "  \033[0m  ") : ("\033[0m      ")) : ("\033[0m      ")) << std::flush;
				showNumber(dt.getTime().second / 10, j, (transcount != 5) ? normalColor : transcolor[j]);
				std::cout << "\033[0m  " << std::flush;
				showNumber(dt.getTime().second % 10, j, (transcount != 5) ? normalColor : transcolor[j]);
				std::cout << "\033[0m  " << std::flush;
			}
			std::cout << "\033[0m" << std::endl;
		}
		if (spaceCount) {
			for (int space = 0; space < spaceCount; ++space)
				std::cout << ' ' << std::flush;
		}
		for (int i = 0; i < (showSecond ? 22 : 12); ++i)
			std::cout << " " << std::flush;
		std::cout << (((transcount != 5) ? dateColor : (transdatecolor[dt.getTime().second % 3])) + std::to_string(dt.getDate().year) + "/" + (((dt.getDate().month + 1 >= 10) ? "" : "0") + std::to_string(dt.getDate().month + 1)) + "/" + (((dt.getDate().day >= 10) ? "" : "0") + std::to_string(dt.getDate().day)) + "\033[0m") << std::endl;
		if (console.isFlush()) {
			if (screensaver)
				return 0;
			char c = console.getKey();
			switch (c) {
			case 'a':
				if (transcount == 2) ++transcount;
				break;
			case 'c': {
				b = console.getBox();
				int clockwidth = showSecond ? 54 : 38;
				spaceCount = (b.columns - clockwidth) / 2;
				returnCount = (b.rows - 6) / 2;
				break;
			}
			case 'm':
				spaceCount = 0;
				returnCount = 0;
				break;
			case 'n':
				if (transcount == 3) ++transcount;
				break;
			case 'r':
				if (transcount == 1) ++transcount;
				break;
			case 's':
				showSecond = !showSecond;
				if (transcount == 4) ++transcount;
				break;
			case 't':
				if (transcount == 0) ++transcount;
				break;
			case 'q':
				return 0;
			default:
				;
			}
		}
		if (showonce) break;
		dt.Now();
		Sleep(tick);
	}
	return 0;
}
