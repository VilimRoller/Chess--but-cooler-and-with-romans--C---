#include "Veles.h"

Veles::Veles(figureColour figure_colour, BoardCoordinates initial_position, int figure_number) {
	InitializeFigure(figure_colour, figureType::Veles, initial_position, figure_number);
}

Veles::~Veles() {
}

std::vector<BoardCoordinates> Veles::GetLegalMoves(const BoardImage& board_layout) const {
	std::vector<BoardCoordinates> result;
	
	ValidateMove(board_layout, result, MoveFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveDiagonalLeftFront(), GetEnemyColourLambda());
	ValidateMove(board_layout, result, MoveDiagonalRightFront(), GetEnemyColourLambda());

	return result;
}


