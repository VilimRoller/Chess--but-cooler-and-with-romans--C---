#include "Veles.h"

Veles::Veles(figureColour figure_colour, BoardCoordinates initial_position, int figure_number) {
	InitializeFigure(figure_colour, figureType::Veles, initial_position, figure_number);
}

Veles::~Veles() {
}

void Veles::CalculateLegalMoves(const BoardImage& board_layout) {
	ValidateMove(board_layout, MoveFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveDiagonalLeftFront(), GetEnemyColourLambda());
	ValidateMove(board_layout, MoveDiagonalRightFront(), GetEnemyColourLambda());
}


