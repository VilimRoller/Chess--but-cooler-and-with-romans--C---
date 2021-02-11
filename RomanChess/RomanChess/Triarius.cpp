#include "Triarius.h"

Triarius::Triarius(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::Triarius, initial_position, figure_number);
}

Triarius::~Triarius(){
}

void Triarius::CalculateLegalMoves(const BoardImage& board_layout) {
	ValidateMove(board_layout, MoveDiagonalLeftFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveDiagonalRightFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveDiagonalLeftBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveDiagonalRightBack(), IsPlaceEmptyLambda);

	ValidateMoveInDirection(board_layout, [&](int num_of_spaces) {return MoveFront(num_of_spaces); });
	ValidateMoveInDirection(board_layout, [&](int num_of_spaces) {return MoveBack(num_of_spaces); });
	ValidateMoveInDirection(board_layout, [&](int num_of_spaces) {return MoveLeft(num_of_spaces); });
	ValidateMoveInDirection(board_layout, [&](int num_of_spaces) {return MoveRight(num_of_spaces); });
}

