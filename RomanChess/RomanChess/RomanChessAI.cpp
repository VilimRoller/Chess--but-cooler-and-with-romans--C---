#include "RomanChessAI.h"
#include <numeric>

RomanChessAI::RomanChessAI(const AIType& AI_type_red, const AIStrategy& AI_strategy_red,
						   const AIType& AI_type_purple, const AIStrategy& AI_strategy_purple,
						   const RomanChessFigures& game_figures, const figureColour AI_colour) :
	AI_type_red_{ AI_type_red }, AI_strategy_red_{ AI_strategy_red },
	AI_type_purple_{ AI_type_purple }, AI_strategy_purple_{ AI_strategy_purple },
	game_figures_{ &game_figures }, AI_player_colour_{ AI_colour }{
	InitializeRomanChessAI();

}

void RomanChessAI::InitializeRomanChessAI() {
	InitializeFigureEvaluationValuesMap(AI_type_red_, figureColour::Red);
	InitializeFigureEvaluationMultiplierMap(AI_strategy_red_, figureColour::Red);

	InitializeFigureEvaluationValuesMap(AI_type_purple_, figureColour::Purple);
	InitializeFigureEvaluationMultiplierMap(AI_strategy_purple_, figureColour::Purple);
}

void RomanChessAI::InitializeFigureEvaluationValuesMap(const AIType& AI_type, const figureColour& colour) {
	switch (AI_type) {
	case AIType::CaesarAI:
		SetFigureEvaluationMap(Constants::AI::FigureEvaluation::CaesarAIFiguresMap, colour);
		break;
	case AIType::AgrippaAI:
		SetFigureEvaluationMap(Constants::AI::FigureEvaluation::AgrippaAIFiguresMap, colour);
		break;
	case AIType::ScipioAI:
		SetFigureEvaluationMap(Constants::AI::FigureEvaluation::ScipioAIFiguresMap, colour);
		break;
	case AIType::CrassusAI:
		SetFigureEvaluationMap(Constants::AI::FigureEvaluation::CrassusAIFiguresMap, colour);
		break;
	case AIType::VarroAI:
		SetFigureEvaluationMap(Constants::AI::FigureEvaluation::VarroAIFiguresMap, colour);
		break;
	}
}

void RomanChessAI::InitializeFigureEvaluationMultiplierMap(const AIStrategy& AI_strategy,
														   const figureColour& colour) {
	switch (AI_strategy) {
	case AIStrategy::Standard:
		SetFigureEvaluationMultiplierMap(Constants::AI::EvaluationMultiplier::EvaluationMultiplierMap_Standard, colour);
		break;
	case AIStrategy::Fabian:
		SetFigureEvaluationMultiplierMap(Constants::AI::EvaluationMultiplier::EvaluationMultiplierMap_FabianStrategy, colour);
	}
}

void RomanChessAI::SetFigureEvaluationMap(const std::map<FigureImage, int>& evaluation_map,
										  const figureColour& colour) {
	switch (colour) {
	case figureColour::Red:
		figure_evaluation_values_map_red_ = evaluation_map;
		break;
	case figureColour::Purple:
		figure_evaluation_values_map_purple_ = evaluation_map;
		break;
	}
}

void RomanChessAI::SetFigureEvaluationMultiplierMap(const std::map<figureType, IntegerMap2D>& multiplier_map,
													const figureColour& colour) {
	switch (colour) {
	case figureColour::Red:
		figure_evaluation_multplier_map_red_ = multiplier_map;
		break;
	case figureColour::Purple:
		figure_evaluation_multplier_map_purple_ = multiplier_map;
		break;
	}
}

BoardImage RomanChessAI::GetBoardImage(const RomanChessFigures& figures) {
	BoardImage result;
	for (int row = 0; row < Constants::boardSize;++row) {
		for (int collumn = 0; collumn < Constants::boardSize; ++collumn) {
			if (IsFigureOnTile(figures[row][collumn])) {
				result[row][collumn] = figures[row][collumn]->GetFigureImage();
			}
		}
	}
	return result;
}

bool RomanChessAI::IsFigureOnTile(std::shared_ptr<Figure> tile) {
	return tile != nullptr;
}

inline bool RomanChessAI::IsFigureImageEmpty(const FigureImage& figure_image) {
	return figure_image == FigureImage(figureType::no_type, figureColour::no_colour);
}

int RomanChessAI::GetEvaluatedBoardStrenght(const BoardImage& board) {
	int result = 0;
	for (int row = 0; row < Constants::boardSize; ++row) {
		for (int collumn = 0; collumn < Constants::boardSize; ++collumn) {
			if (!IsFigureImageEmpty(board[row][collumn])) {
				result += GetFigureStrengh(board, BoardCoordinates(collumn, row));
			}
		}
	}
	return result;
}

int RomanChessAI::GetFigureStrengh(const BoardImage& board, const BoardCoordinates& coordinates) {

	return 0;
}
