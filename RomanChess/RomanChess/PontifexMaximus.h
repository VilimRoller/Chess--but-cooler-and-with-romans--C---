#pragma once
#include "Figure.h"
class PontifexMaximus :
    public Figure
{
public:
	PontifexMaximus(figureColour figure_colour = figureColour::Red,
		BoardCoordinates initial_position = BoardCoordinates{ 0,0 },
		int figure_number = 0) {
		InitializeFigure(figure_colour, figureType::PontifexMaximus, initial_position, figure_number);
	}

	void SetFigureTextureRect() override {
		SetTextureRect(SFMLConstants::FigureSpriteRectPos_PontifexMaximus);
	}
};