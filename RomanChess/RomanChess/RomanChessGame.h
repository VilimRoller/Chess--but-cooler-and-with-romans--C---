#pragma once
#include <memory>

#include "Board.h"
#include "FigureIncludes.h"
#include "Constants.h"

using BoardLayout = std::array<std::array<std::shared_ptr<Figure>, Constants::boardSize>, Constants::boardSize>;

class RomanChessGame
{

public:
	RomanChessGame(const BoardImage board_image = Constants::initialBoardImage,
		const figureColour player_turn = figureColour::Red);

	~RomanChessGame();

	void SetPlayerTurn(figureColour player_colour) {
		player_turn_ = player_colour;
	}

	void NextPlayerTurn() {
		player_turn_ = (player_turn_ == figureColour::Red ? figureColour::Purple : figureColour::Red);
	}

	bool IsGameOver();
	void EndGame();
	void SetFigure(FigureImage figure, BoardCoordinates position);
	void InitializeFigures(const BoardImage& board_image);
	bool MoveFigure();

private:
	Board game_board_;
	bool is_game_over_ = false;
	figureColour player_turn_;
	BoardLayout figures_;
};

