#include "PontifexMaximus.h"

PontifexMaximus::PontifexMaximus(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::PontifexMaximus, initial_position, figure_number);
}

PontifexMaximus::~PontifexMaximus() {
}

void PontifexMaximus::CalculateLegalMoves(const BoardImage& board_layout){
	ValidateMove(board_layout, MoveFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveFront(), GetEnemyColourLambda());
	ValidateMove(board_layout, MoveBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveBack(), GetEnemyColourLambda());
	ValidateMove(board_layout, MoveLeft(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveLeft(), GetEnemyColourLambda());
	ValidateMove(board_layout, MoveRight(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveRight(), GetEnemyColourLambda());

	ValidateMove(board_layout, MoveDiagonalLeftFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveDiagonalLeftFront(), GetEnemyColourLambda());
	ValidateMove(board_layout, MoveDiagonalRightFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveDiagonalRightFront(), GetEnemyColourLambda());
	ValidateMove(board_layout, MoveDiagonalLeftBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveDiagonalLeftBack(), GetEnemyColourLambda());
	ValidateMove(board_layout, MoveDiagonalRightBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveDiagonalRightBack(), GetEnemyColourLambda());
}

