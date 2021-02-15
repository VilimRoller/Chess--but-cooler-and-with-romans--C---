#include "Triarius.h"

Triarius::Triarius(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::Triarius, initial_position, figure_number);
}

Triarius::~Triarius(){
}


