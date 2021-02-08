#pragma once
#include "Figure.h"
#include <functional>

class Princeps final :
    public Figure
{
public:
	Princeps(figureColour figure_colour = figureColour::Red,
		BoardCoordinates initial_position = BoardCoordinates{ 0,0 },
		int figure_number = 0);

	~Princeps();

	std::vector<BoardCoordinates> GetLegalMoves(const BoardImage& board_layout) const override;
};

