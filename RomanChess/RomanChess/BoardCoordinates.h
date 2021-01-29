#pragma once
struct BoardCoordinates
{
	int x;
	int y;
	
	BoardCoordinates() : x{0}, y{0} {}
	BoardCoordinates(int x_variable, int y_variable) : x{x_variable}, y{y_variable} {}

	friend BoardCoordinates operator+(const BoardCoordinates& left, const BoardCoordinates& right) {
		return BoardCoordinates(left.x + right.x, left.y + right.y);
	}

	bool operator==(const BoardCoordinates& right) const {
		return (x == right.x) && (y == right.y);
	}
};