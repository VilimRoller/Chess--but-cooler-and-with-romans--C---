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

	void CalculateLegalMoves(const BoardImage& board_layout) override;

};

