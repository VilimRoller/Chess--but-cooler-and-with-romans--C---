#pragma once
#include "Figure.h"

class Veles final :
    public Figure
{
public:
	Veles(figureColour figure_colour = figureColour::Red,
		BoardCoordinates initial_position = BoardCoordinates(0,0),
		int figure_number = 0);
	
	~Veles();

	std::vector<BoardCoordinates> GetLegalMoves(const BoardImage& board_layout) const override;


	//Illegal moves for this figure
	const BoardCoordinates MoveBack(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveLeftSide(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveRightSide(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveDiagonalLeftBack(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveDiagonalRightBack(const int number_of_spaces = 1) const = delete;
};

