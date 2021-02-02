#include "RomanChessGame.h"

RomanChessGame::RomanChessGame(const BoardImage board_image, 
	const figureColour player_turn) {
	SetPlayerTurn(player_turn);

}

RomanChessGame::~RomanChessGame() {

}





void RomanChessGame::MakeNewBoardCanvas(wxWindow* ParentWindow) {
	wxPoint board_canvas_point{ wxConstants::BoardCanvasPoint };
	wxSize board_canvas_size{ wxConstants::BoardCanvasSize };

	board_canvas_ = std::make_shared<BoardCanvas>(ParentWindow, Canvas::ID::BOARD_CANVAS, board_canvas_point, board_canvas_size, 0);
	
}


