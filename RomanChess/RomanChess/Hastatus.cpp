#include "Hastatus.h"

Hastatus::Hastatus(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::Hastatus, initial_position, figure_number);
}

Hastatus::~Hastatus() {
}


