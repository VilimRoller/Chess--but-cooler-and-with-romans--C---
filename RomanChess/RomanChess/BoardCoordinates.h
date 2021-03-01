#pragma once
#include "TypeAliases.h"

struct BoardCoordinates
{
	int8 x;
	int8 y;
	
	constexpr BoardCoordinates(const int8 input_x = 0, const int8 input_y = 0) :
		x{ input_x }, y{ input_y } {}

	friend BoardCoordinates operator+(const BoardCoordinates left, const BoardCoordinates right) {
		return BoardCoordinates(left.x + right.x, left.y + right.y);
	}

	bool operator==(const BoardCoordinates right) const {
		return (x == right.x) && (y == right.y);
	}
};