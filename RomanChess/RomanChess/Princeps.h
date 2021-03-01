#pragma once
#include "Figure.h"
#include <functional>

class Princeps final :
    public Figure
{
public:
	Princeps(figureColour figure_colour = figureColour::Red,
		BoardCoordinates initial_position = BoardCoordinates{ 0,0 },
		int figure_number = 0) {
		InitializeFigure(figure_colour, figureType::Princeps, initial_position, figure_number);
	}

	void SetFigureTextureRect() override {
		SetTextureRect(SFMLConstants::FigureSpriteRectPos_Princeps);
	}
};