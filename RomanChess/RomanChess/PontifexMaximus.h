#pragma once
#include "Figure.h"
class PontifexMaximus :
    public Figure
{
public:
	PontifexMaximus(figureColour figure_colour = figureColour::Red,
		BoardCoordinates initial_position = BoardCoordinates{ 0,0 },
		int figure_number = 0);

	~PontifexMaximus();

	std::vector<BoardCoordinates> GetLegalMoves(const BoardImage& board_layout) override;

};

