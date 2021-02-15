#include "PontifexMaximus.h"

PontifexMaximus::PontifexMaximus(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::PontifexMaximus, initial_position, figure_number);
}

PontifexMaximus::~PontifexMaximus() {
}



