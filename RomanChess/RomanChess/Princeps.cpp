#include "Princeps.h"

Princeps::Princeps(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::Princeps, initial_position, figure_number);
	
}

Princeps::~Princeps() {
}



