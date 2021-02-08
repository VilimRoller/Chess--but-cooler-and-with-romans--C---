#pragma once
#include <utility>
#include <array>
#include <vector>
#include <string>
#include <map>
#include "ID.h"
#include "Constants.h"
#include "BoardCoordinates.h"
#include "FigureIncludes.h"

using RomanChessFigures = std::array<std::array<std::shared_ptr<Figure>, Constants::boardSize>, Constants::boardSize>;
using FigureImage = std::pair<figureType, figureColour>;
using BoardImage = std::array<std::array<FigureImage, Constants::boardSize>, Constants::boardSize>;
using IntegerMap2D = std::array<std::array<int, Constants::boardSize>, Constants::boardSize>;


class RomanChessAI
{
public:
	RomanChessAI(const AIType& AI_type_red, const AIStrategy& AI_strategy_red,
				const AIType& AI_type_purple, const AIStrategy& AI_strategy_purple, 
				const RomanChessFigures& game_figures, const figureColour AI_colour);

	void InitializeRomanChessAI();
	void InitializeFigureEvaluationValuesMap(const AIType& AI_type, const figureColour& colour);
	void InitializeFigureEvaluationMultiplierMap(const AIStrategy& AI_strategy, const figureColour& colour);

	void SetFigureEvaluationMap(const std::map<FigureImage, int>& evaluation_map, const figureColour& colour);
	void SetFigureEvaluationMultiplierMap(const std::map<figureType, IntegerMap2D>& multiplier_map, const figureColour& colour);

	const BoardImage GetBoardImage() const;
	void RefreshCurrentBoardImage();
	const BoardImage& GetCurrentBoardImage() const;

	bool IsFigureOnTile(std::shared_ptr<Figure> tile) const;
	bool IsFigureImageEmpty(const FigureImage& figure_image) const;

	const int GetEvaluatedBoardStrenght();
	const int GetFigureStrengh(const FigureImage& figure_image, const BoardCoordinates& coordinates);

	int GetFigureEvaluationMultiplier(const figureType& figure_type, const figureColour& figure_colour, const BoardCoordinates& coordinates);

	//bool IsGameOver(); 
	BoardCoordinates GetBestMove(const BoardCoordinates& figure);



private:
	const figureColour AI_player_colour_;

	
	static int moves_counter_;

	//AI must track position of figures, but it is not allowed to move them
	const RomanChessFigures const* game_figures_;
	BoardImage current_board_image_;

	const AIType AI_type_red_;
	const AIStrategy AI_strategy_red_;
	const AIType AI_type_purple_;
	const AIStrategy AI_strategy_purple_;

	std::map<FigureImage, int> figure_evaluation_values_map_red_;
	std::map<figureType, IntegerMap2D> figure_evaluation_multplier_map_red_;

	std::map<FigureImage, int> figure_evaluation_values_map_purple_;
	std::map<figureType, IntegerMap2D> figure_evaluation_multplier_map_purple_;
	



};

