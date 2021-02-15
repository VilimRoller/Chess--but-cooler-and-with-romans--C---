#pragma once
#include "Figure.h"

class Eques :
    public Figure
{
public:
	Eques(figureColour figure_colour = figureColour::Red,
		BoardCoordinates initial_position = BoardCoordinates{0,0},
		int figure_number = 0);

	~Eques();

};

