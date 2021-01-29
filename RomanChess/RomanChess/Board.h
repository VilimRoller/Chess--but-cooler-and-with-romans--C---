#pragma once
#include "BoardCanvas.h"
#include "Figure.h"
#include "Constants.h"
#include "wxConstants.h"
#include "wxID.h"
#include "BoardLayout.h"

class Board
{
public:
	Board();
	~Board() {}

	void InitializeBoard();

	BoardLayout GetBoardLayout() { 
		return board_layout_; 
	}
	void setBoardLayout(const BoardImage& new_BoardLayout);

	BoardImage GetBoardImage();
	void SetBoardImage(BoardImage& image);

	void SetFigure(FigureImage figure, BoardCoordinates coordinates);
	void RemoveFigure();

	bool Move(BoardCoordinates old_location, BoardCoordinates new_location);

	void MakeNewBoardCanvas(wxWindow* ParentWindow);

	void DrawFigure(BoardCoordinates coordinates);

	//Check if there is legal number of every figure
	bool CheckBoardLayout();

private:
	//BoardLayout_[0][0] is on the top left corner
	//white figures start on the bottom

	std::shared_ptr<BoardCanvas> board_canvas_;
	BoardLayout board_layout_;
};


