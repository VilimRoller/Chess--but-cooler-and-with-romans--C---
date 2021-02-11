#include "Hastatus.h"

Hastatus::Hastatus(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::Hastatus, initial_position, figure_number);
}

Hastatus::~Hastatus() {
}

void Hastatus::CalculateLegalMoves(const BoardImage& board_layout) {
	CheckFront(board_layout);
	ValidateMove(board_layout, MoveBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveDiagonalLeftFront(), GetEnemyColourLambda());
	ValidateMove(board_layout, MoveDiagonalRightFront(), GetEnemyColourLambda());
}

void Hastatus::CheckFront(const BoardImage& board_layout) {
	for (int num_of_moves = 1; num_of_moves < 3; ++num_of_moves) {
		if (!ValidateMove(board_layout, MoveFront(num_of_moves), IsPlaceEmptyLambda)) {
			break;
		}
	}
}
