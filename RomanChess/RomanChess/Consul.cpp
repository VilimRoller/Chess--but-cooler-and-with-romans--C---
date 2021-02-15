#include "Consul.h"

Consul::Consul(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::Consul, initial_position, figure_number);
}

Consul::~Consul() {
}


