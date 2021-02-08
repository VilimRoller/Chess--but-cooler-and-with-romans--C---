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

    std::vector<BoardCoordinates> GetLegalMoves(const BoardImage& board_layout) const override;

    void CheckFront(const BoardImage& board_layout, std::vector<BoardCoordinates>& res) const;


    //Illegal methods for this figure
	const BoardCoordinates MoveLeftSide(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveRightSide(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveDiagonalLeftBack(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveDiagonalRightBack(const int number_of_spaces = 1) const = delete;
};



