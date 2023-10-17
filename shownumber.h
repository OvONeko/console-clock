#pragma once

#ifndef SHOWNUMBER_H
#define SHOWNUMBER_H

#include <iostream>

const std::string block = "\u2588";

int numbers[10][5][3] = {
	{
		{1, 1, 1},
		{1, 0, 1},
		{1, 0, 1},
		{1, 0, 1},
		{1, 1, 1}
	},
	{
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1}
	},
	{
		{1, 1, 1},
		{0, 0, 1},
		{1, 1, 1},
		{1, 0, 0},
		{1, 1, 1}
	},
	{
		{1, 1, 1},
		{0, 0, 1},
		{1, 1, 1},
		{0, 0, 1},
		{1, 1, 1}
	},
	{
		{1, 0, 1},
		{1, 0, 1},
		{1, 1, 1},
		{0, 0, 1},
		{0, 0, 1}
	},
	{
		{1, 1, 1},
		{1, 0, 0},
		{1, 1, 1},
		{0, 0, 1},
		{1, 1, 1}
	},
	{
		{1, 1, 1},
		{1, 0, 0},
		{1, 1, 1},
		{1, 0, 1},
		{1, 1, 1}
	},
	{
		{1, 1, 1},
		{1, 0, 1},
		{0, 0, 1},
		{0, 0, 1},
		{0, 0, 1}
	},
	{
		{1, 1, 1},
		{1, 0, 1},
		{1, 1, 1},
		{1, 0, 1},
		{1, 1, 1}
	},
	{
		{1, 1, 1},
		{1, 0, 1},
		{1, 1, 1},
		{0, 0, 1},
		{1, 1, 1}
	}
};

inline void showNumber(int num, int line, std::string showing) {
	for (int i = 0; i < 3; ++i) {
		if (numbers[num][line][i])
			std::cout << showing + "  " << std::flush;
		else
			std::cout << "\033[0m  " << std::flush;
	}
}

#endif