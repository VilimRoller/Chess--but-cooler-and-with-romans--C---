#include "Hastatus.h"

Hastatus::Hastatus(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number)
	: number_of_kills_{ 0 } {
	InitializeFigure(figure_colour, figureType::Hastatus, initial_position, figure_number);
}

Hastatus::~Hastatus() {

}

std::vector<BoardCoordinates> Hastatus::GetLegalMoves(const BoardImage& board_layout){
	std::vector<BoardCoordinates> result;

	CheckFront(board_layout, result);
	ValidateMove(board_layout, result, MoveBack(), IsPlaceEmptyLambda);
	ValidateMove(board_layout, result, MoveDiagonalLeftFront(), GetEnemyColourLambda());
	ValidateMove(board_layout, result, MoveDiagonalRightFront(), GetEnemyColourLambda());

	return result;
}

void Hastatus::CheckFront(const BoardImage& board_layout, std::vector<BoardCoordinates>& res) {
	for (int num_of_moves = 1; num_of_moves < 3; ++num_of_moves) {
		if (!ValidateMove(board_layout, res, MoveFront(num_of_moves), IsPlaceEmptyLambda)) {
			break;
		}
	}
}
