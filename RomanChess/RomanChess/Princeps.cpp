#include "Princeps.h"

Princeps::Princeps(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::Princeps, initial_position, figure_number);
	
}

Princeps::~Princeps() {
}

void Princeps::CalculateLegalMoves(const BoardImage& board_layout) {
	ValidateMove(board_layout, MoveFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveBack(),  IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveLeft(),  IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveRight(), IsPlaceEmptyLambda);

	ValidateMoveInDirection(board_layout, [&](int num_of_spaces) {return MoveDiagonalLeftFront(num_of_spaces); });
	ValidateMoveInDirection(board_layout, [&](int num_of_spaces) {return MoveDiagonalRightFront(num_of_spaces); });
	ValidateMoveInDirection(board_layout, [&](int num_of_spaces) {return MoveDiagonalLeftBack(num_of_spaces); });
	ValidateMoveInDirection(board_layout, [&](int num_of_spaces) {return MoveDiagonalRightBack(num_of_spaces); });
}

