#include "Triarius.h"

Triarius::Triarius(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::Triarius, initial_position, figure_number);
}

Triarius::~Triarius(){

}


std::vector<BoardCoordinates> Triarius::GetLegalMoves(const BoardImage& board_layout){
	std::vector<BoardCoordinates> result;

	ValidateMove(board_layout, result, MoveDiagonalLeftFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveDiagonalRightFront(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveDiagonalLeftBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveDiagonalRightBack(), IsPlaceEmptyLambda);

	ValidateMoveInDirection(board_layout, result, [&](int num_of_spaces) {return MoveFront(num_of_spaces); });
	ValidateMoveInDirection(board_layout, result, [&](int num_of_spaces) {return MoveBack(num_of_spaces); });
	ValidateMoveInDirection(board_layout, result, [&](int num_of_spaces) {return MoveLeft(num_of_spaces); });
	ValidateMoveInDirection(board_layout, result, [&](int num_of_spaces) {return MoveRight(num_of_spaces); });

	return result;
}

