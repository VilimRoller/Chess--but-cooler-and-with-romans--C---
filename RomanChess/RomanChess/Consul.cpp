#include "Consul.h"

Consul::Consul(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::Consul, initial_position, figure_number);
}

Consul::~Consul() {

}

std::vector<BoardCoordinates> Consul::GetLegalMoves(const BoardImage& board_layout) {
	std::vector<BoardCoordinates> result;

	ValidateMove(board_layout, result, MoveFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveLeft(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveRight(), IsPlaceEmptyLambda);

	ValidateMove(board_layout, result, MoveDiagonalLeftFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveDiagonalRightFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveDiagonalLeftBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveDiagonalRightBack(), IsPlaceEmptyLambda);

	return result;
}

