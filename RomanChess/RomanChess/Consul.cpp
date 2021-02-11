#include "Consul.h"

Consul::Consul(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::Consul, initial_position, figure_number);
}

Consul::~Consul() {
}

void Consul::CalculateLegalMoves(const BoardImage& board_layout) {
	ValidateMove(board_layout, MoveFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveLeft(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveRight(), IsPlaceEmptyLambda);

	ValidateMove(board_layout, MoveDiagonalLeftFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveDiagonalRightFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveDiagonalLeftBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, MoveDiagonalRightBack(), IsPlaceEmptyLambda);
}

