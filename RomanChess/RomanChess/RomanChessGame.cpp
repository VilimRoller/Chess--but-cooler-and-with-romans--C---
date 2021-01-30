#include "RomanChessGame.h"

RomanChessGame::RomanChessGame(const BoardImage board_image, 
	const figureColour player_turn) {
	SetPlayerTurn(player_turn);
	LoadTextures();
	InitializeBoardSprite();
	InitializeRomanChessFigures(board_image);
	GetAllSprites();
}

RomanChessGame::~RomanChessGame() {

}

void RomanChessGame::SetFigure(FigureImage figure, BoardCoordinates position){

	switch (figure.first) {
	case figureType::Veles:
		figures_[position.y][position.x] = std::make_shared<Veles>(figure.second, position);
		break;
	case figureType::Hastatus:
		figures_[position.y][position.x] = std::make_shared<Hastatus>(figure.second, position);
		break;
	case figureType::Princeps:
		figures_[position.y][position.x] = std::make_shared<Princeps>(figure.second, position);
		break;
	case figureType::Triarius:
		figures_[position.y][position.x] = std::make_shared<Triarius>(figure.second, position);
		break;
	case figureType::Eques:
		figures_[position.y][position.x] = std::make_shared<Eques>(figure.second, position);
		break;
	case figureType::Consul:
		figures_[position.y][position.x] = std::make_shared<Consul>(figure.second, position);
		break;
	case figureType::PontifexMaximus:
		figures_[position.y][position.x] = std::make_shared<PontifexMaximus>(figure.second, position);
		break;
	default:
		figures_[position.y][position.x] = nullptr;
	}
	if (figures_[position.y][position.x] != nullptr) {
		figures_[position.y][position.x]->InitializeFigureSprite(figure_textures_);
	}
}

void RomanChessGame::InitializeRomanChessFigures(const BoardImage& board_image) {
	for (int figure_pos_y = 0; figure_pos_y < Constants::boardSize; ++figure_pos_y) {
		for (int figure_pos_x = 0; figure_pos_x < Constants::boardSize; ++figure_pos_x) {
			SetFigure(board_image[figure_pos_y][figure_pos_x], BoardCoordinates(figure_pos_x, figure_pos_y));
		}
	}
}

void RomanChessGame::LoadTextures() {
	board_texture_.loadFromFile(ImagePaths::Board);
	figure_textures_.loadFromFile(ImagePaths::Figures);
}

void RomanChessGame::MakeNewBoardCanvas(wxWindow* ParentWindow) {
	wxPoint board_canvas_point{ wxConstants::BoardCanvasPoint };
	wxSize board_canvas_size{ wxConstants::BoardCanvasSize };
	board_canvas_ = std::make_shared<BoardCanvas>(ParentWindow, Canvas::ID::BOARD_CANVAS, board_canvas_point, board_canvas_size, 0);
	board_canvas_->SetSpritesVector(all_sprites_);
}

void RomanChessGame::GetAllSprites() {
	all_sprites_.emplace_back(board_sprite_);
	for ( auto& figure_line : figures_) {
		for (auto& figure : figure_line) {
			if (figure != nullptr) {
				all_sprites_.emplace_back(figure->GetFigureSprite());
			}
		}
	}
}

void RomanChessGame::InitializeBoardSprite() {
	board_sprite_ = std::make_shared<sf::Sprite>();
	board_sprite_->setTexture(board_texture_);
}
