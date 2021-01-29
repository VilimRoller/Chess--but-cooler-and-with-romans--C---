#include "RomanChessGame.h"

RomanChessGame::RomanChessGame(const BoardImage board_image, 
	const figureColour player_turn) {
	SetPlayerTurn(player_turn);
}

RomanChessGame::~RomanChessGame() {

}

void RomanChessGame::SetFigure(FigureImage figure, BoardCoordinates position){
	switch (figure.first) {
	case figureType::Veles:
		figures_[position.y][position.x] = std::make_unique<Veles>(figure.second, position);
		break;
	case figureType::Hastatus:
		figures_[position.y][position.x] = std::make_unique<Hastatus>(figure.second, position);
		break;
	case figureType::Princeps:
		figures_[position.y][position.x] = std::make_unique<Princeps>(figure.second, position);
		break;
	case figureType::Triarius:
		figures_[position.y][position.x] = std::make_unique<Triarius>(figure.second, position);
		break;
	case figureType::Eques:
		figures_[position.y][position.x] = std::make_unique<Eques>(figure.second, position);
		break;
	case figureType::Consul:
		figures_[position.y][position.x] = std::make_unique<Consul>(figure.second, position);
		break;
	case figureType::PontifexMaximus:
		figures_[position.y][position.x] = std::make_unique<PontifexMaximus>(figure.second, position);
		break;
	}
}


void RomanChessGame::InitializeFigures(const BoardImage& board_image) {
	for (int figure_pos_y = 0; figure_pos_y < Constants::boardSize; ++figure_pos_y) {
		for (int figure_pos_x = 0; figure_pos_x < Constants::boardSize; ++figure_pos_x) {
			SetFigure(board_image[figure_pos_y][figure_pos_x], BoardCoordinates(figure_pos_x, figure_pos_y));
		}
	}
}
