#include "PontifexMaximus.h"

PontifexMaximus::PontifexMaximus(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::PontifexMaximus, initial_position, figure_number);
}

PontifexMaximus::~PontifexMaximus() {
}

std::vector<BoardCoordinates> PontifexMaximus::GetLegalMoves(const BoardImage& board_layout) const{
	std::vector<BoardCoordinates> result;

	ValidateMove(board_layout, result, MoveFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveFront(), GetEnemyColourLambda());
	ValidateMove(board_layout, result, MoveBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveBack(), GetEnemyColourLambda());
	ValidateMove(board_layout, result, MoveLeft(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveLeft(), GetEnemyColourLambda());
	ValidateMove(board_layout, result, MoveRight(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveRight(), GetEnemyColourLambda());

	ValidateMove(board_layout, result, MoveDiagonalLeftFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveDiagonalLeftFront(), GetEnemyColourLambda());
	ValidateMove(board_layout, result, MoveDiagonalRightFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveDiagonalRightFront(), GetEnemyColourLambda());
	ValidateMove(board_layout, result, MoveDiagonalLeftBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveDiagonalLeftBack(), GetEnemyColourLambda());
	ValidateMove(board_layout, result, MoveDiagonalRightBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveDiagonalRightBack(), GetEnemyColourLambda());

	return result;
}

