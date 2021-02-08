#pragma once
#include "Figure.h"
class Consul final:
    public Figure
{
public:
	Consul(figureColour figure_colour = figureColour::Red,
		BoardCoordinates initial_position = BoardCoordinates{ 0,0 },
		int figure_number = 0);

	~Consul();

    std::vector<BoardCoordinates> GetLegalMoves(const BoardImage& board_layout) const override;

};

