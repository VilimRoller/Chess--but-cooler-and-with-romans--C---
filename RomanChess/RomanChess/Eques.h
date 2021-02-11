#pragma once
#include "Figure.h"

class Eques :
    public Figure
{
public:
	Eques(figureColour figure_colour = figureColour::Red,
		BoardCoordinates initial_position = BoardCoordinates{0,0},
		int figure_number = 0);

	~Eques();


	void CalculateLegalMoves(const BoardImage& board_layout) override;

	template <class T1>
	void ValidateEquesMove(const BoardImage& board_layout,
		T1&& DirectionLambda) {

		BoardCoordinates evaluated_position = DirectionLambda(2);
		if (GetPosition().x == evaluated_position.x) { //moving vertically 
			ValidateMove(board_layout, evaluated_position + BoardCoordinates(1,0), IsPlaceEmptyLambda);
			ValidateMove(board_layout, evaluated_position + BoardCoordinates(1, 0), GetEnemyColourLambda());
			ValidateMove(board_layout, evaluated_position + BoardCoordinates(-1, 0), IsPlaceEmptyLambda);
			ValidateMove(board_layout, evaluated_position + BoardCoordinates(-1, 0), GetEnemyColourLambda());
		}
		else if (GetPosition().y == evaluated_position.y){ //moving horizontally 
			ValidateMove(board_layout, evaluated_position + BoardCoordinates(0, 1), IsPlaceEmptyLambda);
			ValidateMove(board_layout, evaluated_position + BoardCoordinates(0, 1), GetEnemyColourLambda());
			ValidateMove(board_layout, evaluated_position + BoardCoordinates(0, -1), IsPlaceEmptyLambda);
			ValidateMove(board_layout, evaluated_position + BoardCoordinates(0, -1), GetEnemyColourLambda());
		}
	}

	//Not used by this figure
	const BoardCoordinates MoveDiagonalLeftFront(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveDiagonalLeftBack(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveDiagonalRightFront(const int number_of_spaces = 1) const = delete;
	const BoardCoordinates MoveDiagonalRightBack(const int number_of_spaces = 1) const = delete;
};

