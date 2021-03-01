#pragma once
#include "Figure.h"
class Triarius final :
    public Figure
{
public:
	Triarius(figureColour figure_colour = figureColour::Red,
		BoardCoordinates initial_position = BoardCoordinates{ 0,0 },
		int figure_number = 0) {
		InitializeFigure(figure_colour, figureType::Triarius, initial_position, figure_number);
	}

	void SetFigureTextureRect() override {
		SetTextureRect(SFMLConstants::FigureSpriteRectPos_Triarius);
	}
};