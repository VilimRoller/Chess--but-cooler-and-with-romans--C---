#pragma once
#include "Figure.h"
class Consul final:
    public Figure
{
public:
	Consul(figureColour figure_colour = figureColour::Red,
		BoardCoordinates initial_position = BoardCoordinates{ 0,0 },
		int figure_number = 0) {
		InitializeFigure(figure_colour, figureType::Consul, initial_position, figure_number);
	}

	void SetFigureTextureRect() override {
		SetTextureRect(SFMLConstants::FigureSpriteRectPos_Consul);
	}
};