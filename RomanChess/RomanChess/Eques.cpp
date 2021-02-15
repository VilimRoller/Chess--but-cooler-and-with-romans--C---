#include "Eques.h"

Eques::Eques(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::Eques, initial_position, figure_number);
}

Eques::~Eques() {
}
