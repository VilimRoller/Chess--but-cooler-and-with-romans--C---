#include "Board.h"
#include "Veles.h"

using FigureImage = std::pair<figureType, figureColour>;

Board::Board() {
	InitializeBoard();
}

void Board::InitializeBoard() {
	board_layout_.Elements[0][0] = std::make_shared<Veles>();
}

void Board::setBoardLayout(const BoardImage& new_board_layout) {
	//Transform board image into board layout
}

BoardImage Board::GetBoardImage() {
	BoardImage image;

	return image;
}

void Board::SetBoardImage(BoardImage& image) {

}

void Board::SetFigure(FigureImage figure, BoardCoordinates coordinates) {
	switch (figure.first) {
	case figureType::Veles:
		board_layout_.Elements[coordinates.x][coordinates.y] = std::make_shared<Veles>(figure.second, coordinates);
		break;
	}
}

void Board::RemoveFigure() {

}


bool Board::Move(BoardCoordinates old_location, BoardCoordinates new_location) {
	bool is_succesful = false;


	return is_succesful;
}

void Board::MakeNewBoardCanvas(wxWindow* ParentWindow) {
	wxPoint board_canvas_point{ wxConstants::BoardCanvasPoint };
	wxSize board_canvas_size{ wxConstants::BoardCanvasSize };

	board_canvas_ = std::make_shared<BoardCanvas>(ParentWindow, Canvas::ID::BOARD_CANVAS, board_canvas_point, board_canvas_size);
}

bool Board::CheckBoardLayout() {
	bool is_layout_correct = false;

	//Use std::unordered_map
	short int velesWhiteNum = 0;
	short int hastatusWhiteNum = 0;
	short int princepsWhiteNum = 0;
	short int triariusWhiteNum = 0;
	short int equesWhiteNum = 0;
	short int consulWhiteNum = 0;
	short int pontifexmaxWhiteNum = 0;

	short int velesBlackNum = 0;
	short int hastatusBlackNum = 0;
	short int princepsBlackNum = 0;
	short int triariusBlackNum = 0;
	short int equesBlackNum = 0;
	short int consulBlackNum = 0;
	short int pontifexmaxBlackNum = 0;

	//go through board layout 
	//for (auto& figure: board...

	return is_layout_correct;
}

void Board::DrawFigure(BoardCoordinates coordinates) {
	board_canvas_->DrawFigure(board_layout_.Elements[coordinates.x][coordinates.y]);
}
