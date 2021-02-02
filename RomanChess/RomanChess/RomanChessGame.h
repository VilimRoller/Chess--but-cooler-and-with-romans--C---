#pragma once
#include <memory>
#include <array>
#include "Constants.h"
#include "wxConstants.h"
#include "wxID.h"
#include "FigureIncludes.h"
#include "BoardCanvas.h"

using RomanChessFigures = std::array<std::array<std::shared_ptr<Figure>, Constants::boardSize>, Constants::boardSize>;

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
	void InitializeRomanChessFigures(const BoardImage& board_image);
	bool MoveFigure();
	void LoadTextures();

	void MakeNewBoardCanvas(wxWindow* ParentWindow);

	

	void InitializeBoardSprite();
	void InitializeCanvasSpritePointers();

private:
	bool is_game_over_ = false;
	figureColour player_turn_ = figureColour::no_colour;

	RomanChessFigures figures_;

	sf::Texture board_texture_;
	sf::Texture figure_textures_;

	std::shared_ptr<sf::Sprite> board_sprite_;

	std::shared_ptr<BoardCanvas> board_canvas_;
	BoardImage board_image_;
};
