#pragma once
#include "Figure.h"

class Hastatus final :
    public Figure
{
public:
    Hastatus(figureColour figure_colour = figureColour::Red,
        BoardCoordinates initial_position = BoardCoordinates{ 0,0 },
        int figure_number = 0) {
        InitializeFigure(figure_colour, figureType::Hastatus, initial_position, figure_number);
    }
    
    void SetFigureTextureRect() override {
        SetTextureRect(SFMLConstants::FigureSpriteRectPos_Hastatus);
    }
};