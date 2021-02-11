#include "Eques.h"

Eques::Eques(figureColour figure_colour,
	BoardCoordinates initial_position,
	int figure_number) {
	InitializeFigure(figure_colour, figureType::Eques, initial_position, figure_number);
}

Eques::~Eques() {
}

void Eques::CalculateLegalMoves(const BoardImage& board_layout) {
	ValidateEquesMove(board_layout, [&](int num_of_spaces) {return MoveFront(num_of_spaces); });
	ValidateEquesMove(board_layout, [&](int num_of_spaces) {return MoveBack(num_of_spaces); });
	ValidateEquesMove(board_layout, [&](int num_of_spaces) {return MoveLeft(num_of_spaces); });
	ValidateEquesMove(board_layout, [&](int num_of_spaces) {return MoveRight(num_of_spaces); });
}