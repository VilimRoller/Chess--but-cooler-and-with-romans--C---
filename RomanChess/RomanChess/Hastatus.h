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

    std::vector<BoardCoordinates> GetLegalMoves(const BoardImage& board_layout) override;

    void CheckFront(const BoardImage& board_layout, std::vector<BoardCoordinates>& res);

    void AddKill() {
        ++number_of_kills_;
    }

    bool IsToBePromoted() {
        return number_of_kills_ > 2;
    }

private:
    int number_of_kills_;

public: 
    //Illegal methods for this figure
	const BoardCoordinates MoveLeftSide(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveRightSide(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveDiagonalLeftBack(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveDiagonalRightBack(const int number_of_spaces = 1) const = delete;
};



