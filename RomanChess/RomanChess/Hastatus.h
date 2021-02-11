#pragma once
#include "Figure.h"

class Hastatus final :
    public Figure
{
public:
    Hastatus(figureColour figure_colour = figureColour::Red,
            BoardCoordinates initial_position = BoardCoordinates{ 0,0 },
            int figure_number = 0);
    
    ~Hastatus();

    void CalculateLegalMoves(const BoardImage& board_layout) override;

    void CheckFront(const BoardImage& board_layout);


    //Illegal methods for this figure
	const BoardCoordinates MoveLeftSide(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveRightSide(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveDiagonalLeftBack(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveDiagonalRightBack(const int number_of_spaces = 1) const = delete;
};



