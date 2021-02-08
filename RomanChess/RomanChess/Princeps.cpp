#include "Princeps.h"

Princeps::Princeps(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::Princeps, initial_position, figure_number);
	
}

Princeps::~Princeps() {
}

std::vector<BoardCoordinates> Princeps::GetLegalMoves(const BoardImage& board_layout) const {
	std::vector<BoardCoordinates> result;

	ValidateMove(board_layout, result, MoveFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveBack(),  IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveLeft(),  IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveRight(), IsPlaceEmptyLambda);

	ValidateMoveInDirection(board_layout, result, [&](int num_of_spaces) {return MoveDiagonalLeftFront(num_of_spaces); });
	ValidateMoveInDirection(board_layout, result, [&](int num_of_spaces) {return MoveDiagonalRightFront(num_of_spaces); });
	ValidateMoveInDirection(board_layout, result, [&](int num_of_spaces) {return MoveDiagonalLeftBack(num_of_spaces); });
	ValidateMoveInDirection(board_layout, result, [&](int num_of_spaces) {return MoveDiagonalRightBack(num_of_spaces); });

	return result;
}

