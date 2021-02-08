#pragma once
#include "Figure.h"
class Triarius final :
    public Figure
{
public:
	Triarius(figureColour figure_colour = figureColour::Red,
		BoardCoordinates initial_position = BoardCoordinates{ 0,0 },
		int figure_number = 0);
	~Triarius();

	std::vector<BoardCoordinates> GetLegalMoves(const BoardImage& board_layout) const override;

};

