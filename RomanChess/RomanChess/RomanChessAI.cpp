#include "RomanChessAI.h"
#include <algorithm>
#include "BadInputException.h"


RomanChessAI::RomanChessAI(const AIType AI_type_red, const AIStrategy AI_strategy_red,
	const AIType AI_type_purple, const AIStrategy AI_strategy_purple,
	RomanChessGameEngine* game_engine, const figureColour AI_colour) {
	InitializeRomanChessAI(AI_type_red, AI_strategy_red, AI_type_purple, AI_strategy_purple, game_engine, AI_colour);
}


/*---------------------------------------------------------------------------------------------------*/
/*										  INITIALIZERS												 */
/*---------------------------------------------------------------------------------------------------*/

#pragma region INITIALIZERS

void RomanChessAI::InitializeRomanChessAI(const AIType AI_type_red, const AIStrategy AI_strategy_red,
	const AIType AI_type_purple, const AIStrategy AI_strategy_purple,
	RomanChessGameEngine* game_engine, const figureColour AI_colour) {
	SetAITypeRed(AI_type_red);
	SetAIStrategyRed(AI_strategy_red);
	SetAITypePurple(AI_type_purple);
	SetAIStrategyPurple(AI_strategy_purple);
	SetGameEnginePtr(game_engine);
	SetAIPlayerColour(AI_colour);

	InitializeRomanChessAIMaps();
}

void RomanChessAI::InitializeRomanChessAIMaps() {
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
	default:
		throw BadInputException(ExceptionMessages::InitializeFigureEvaluationValuesMap);
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
	default:
		throw BadInputException(ExceptionMessages::InitializeFigureEvaluationMultiplierMap);
		break;
	}
}

#pragma endregion

/*---------------------------------------------------------------------------------------------------*/
/*											GETTERS													 */
/*---------------------------------------------------------------------------------------------------*/

#pragma region GETTERS

inline const figureColour& RomanChessAI::GetAIPlayerColour() const {
	return AI_player_colour_;
}

inline const AIType& RomanChessAI::GetAITypeRed() const {
	return AI_type_red_;
}

inline const AIType& RomanChessAI::GetAITypePurple() const {
	return AI_type_purple_;
}

inline const AIStrategy& RomanChessAI::GetAIStrategyRed() const {
	return AI_strategy_red_;
}

inline const AIStrategy& RomanChessAI::GetAIStrategyPurple() const {
	return AI_strategy_purple_;
}

#pragma endregion

/*---------------------------------------------------------------------------------------------------*/
/*											SETTERS													 */
/*---------------------------------------------------------------------------------------------------*/

#pragma region SETTERS

inline void RomanChessAI::SetAIPlayerColour(const figureColour& figure_colour) {
	AI_player_colour_ = figure_colour;
}

inline void RomanChessAI::SetGameEnginePtr(RomanChessGameEngine* game_engine) {
	game_engine_ = game_engine;
}

inline void RomanChessAI::SetAITypeRed(const AIType& AI_type_red) {
	AI_type_red_ = AI_type_red;
}

inline void RomanChessAI::SetAITypePurple(const AIType& AI_type_purple) {
	AI_type_purple_ = AI_type_purple;
}

inline void RomanChessAI::SetAIStrategyRed(const AIStrategy& AI_strategy_red) {
	AI_strategy_red_ = AI_strategy_red;
}

inline void RomanChessAI::SetAIStrategyPurple(const AIStrategy& AI_strategy_purple) {
	AI_strategy_purple_ = AI_strategy_purple;
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
	default:
		throw BadInputException(ExceptionMessages::SetFigureEvaluationMap);
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
	default:
		throw BadInputException(ExceptionMessages::SetFigureEvaluationMultiplierMap);
		break;
	}
}

#pragma endregion

/*---------------------------------------------------------------------------------------------------*/
/*										BOARD EVALUATION											 */
/*---------------------------------------------------------------------------------------------------*/

#pragma region BOARD EVALUATION

const int16 RomanChessAI::GetEvaluatedBoardStrenght(const BoardImage board_image) const noexcept {
	int16 result = int16(0);

	for (int8 row = int8(0); row < Constants::boardSize; ++row)
		for (int8 collumn = int8(0); collumn < Constants::boardSize; ++collumn)
			result += GetFigureStrengh(board_image[row][collumn], BoardCoordinates(collumn, row));

	return result;
}

const int16 RomanChessAI::GetEvaluatedBoardStrenght() const noexcept {
	return GetEvaluatedBoardStrenght(game_engine_->GetBoardImage());
}

const int16 RomanChessAI::GetFigureStrengh(const FigureImage figure_image, const BoardCoordinates coordinates) const noexcept {
	if (!IsFigureImageEmpty(figure_image))
		return figure_evaluation_values_map_red_[figure_image] * GetFigureEvaluationMultiplier(figure_image, coordinates);

	else
		return 0;
}

inline const int16 RomanChessAI::GetFigureEvaluationMultiplier(const FigureImage figure_image, const BoardCoordinates coordinates) const {
	switch (figure_image.colour) {
	case figureColour::Red:
		return GetFigureEvaluationMultiplierRed(figure_image, coordinates);
		break;
	case figureColour::Purple:
		return GetFigureEvaluationMultiplierPurple(figure_image, coordinates);
		break;
	default:
		throw BadInputException(ExceptionMessages::GetFigureEvaluationMultiplier);
		break;
	}
}

inline const int16 RomanChessAI::GetFigureEvaluationMultiplierRed(const FigureImage figure_image, const BoardCoordinates coordinates) const {
	return figure_evaluation_multplier_map_red_[figure_image.type][coordinates.y][coordinates.x];
}

inline const int16 RomanChessAI::GetFigureEvaluationMultiplierPurple(const FigureImage figure_image, const BoardCoordinates coordinates) const {
	auto row = Constants::lastBoardElement - coordinates.y;
	auto collumn = Constants::lastBoardElement - coordinates.x;

	return figure_evaluation_multplier_map_purple_[figure_image.type][row][collumn];
}





#pragma endregion



/*---------------------------------------------------------------------------------------------------*/
/*										EVALUATING FIGURE MOVES										 */
/*---------------------------------------------------------------------------------------------------*/

#pragma region EVALUATING FIGURE MOVES



void RomanChessAI::FillAllFigurePositionsVector() noexcept {
	all_figure_positions_.clear();
	auto& board = game_engine_->GetBoardImage();

	for (int8 row = int8(0); row < Constants::boardSize; ++row)
		for (int8 collumn = int8(0); collumn < Constants::boardSize; ++collumn)
			if (board[row][collumn].colour == AI_player_colour_)
				all_figure_positions_.emplace_back(BoardCoordinates(collumn, row));
}

void RomanChessAI::CalculateBestMoveForEveryFigure() noexcept {
	FillAllFigurePositionsVector();

	for (const auto coordinate : all_figure_positions_)
		GetBestMoveForFigureAsync(coordinate);
}



std::optional<int16> RomanChessAI::GetBestMoveForFigureAsync(const BoardCoordinates coordinate) noexcept {
	auto game_engine_copy_ptr = MakeGameEngineCopy();
	const auto& figure_moves = game_engine_copy_ptr->GetLegalMoves(coordinate);

	if (figure_moves.empty())
		return std::nullopt;

	std::vector<int16> figure_moves_values;

	for (const auto move : figure_moves)
		figure_moves_values.emplace_back(GetValueForFigureMove(move));

	return FilterBestMove(std::move(figure_moves_values));
}

int16 RomanChessAI::GetValueForFigureMove(const BoardCoordinates coordinate) {



}

int16 RomanChessAI::FilterBestMove(std::vector<int16>&& moves_vector) const {
	if (AI_player_colour_ == figureColour::Red)
		return *std::max_element(moves_vector.begin(), moves_vector.end());
	else
		return *std::min_element(moves_vector.begin(), moves_vector.end());
}

#pragma endregion













/*---------------------------------------------------------------------------------------------------*/
/*										PICKING BEST FIGURE MOVE									 */
/*---------------------------------------------------------------------------------------------------*/

#pragma region PICKING BEST FIGURE MOVE

RomanChessMove RomanChessAI::GetBestMove() {
	ClearBestNodeValuesFutureVector();
	FillBestNodeValuesFutureVector();
	return GetBestMoveNode()->first;
}

const std::vector<EvaluatedRomanChessMove>::iterator RomanChessAI::GetBestMoveNode() {
	switch (AI_player_colour_) {
	case figureColour::Red:
		return GetMinMoveNodeValue();
		break;

	case figureColour::Purple:
		return GetMaxMoveNodeValue();
		break;
	}
}

const std::vector<EvaluatedRomanChessMove>::iterator RomanChessAI::GetMinMoveNodeValue() {
	return std::min_element(best_move_for_figures_.begin(), best_move_for_figures_.end(),
		[](auto& left, auto& right) {return left.second < right.second; });
}

const std::vector<EvaluatedRomanChessMove>::iterator RomanChessAI::GetMaxMoveNodeValue() {
	return std::max_element(best_move_for_figures_.begin(), best_move_for_figures_.end(),
		[](auto& left, auto& right) {return left.second < right.second; });
}

#pragma endregion









inline void RomanChessAI::ClearBestNodeValuesFutureVector() {
	best_node_values_future_.clear();
}

inline void RomanChessAI::FillBestNodeValuesFutureVector() {
	auto all_figures = GetFigurePtrs();
	for (const auto& figure : all_figures) {
		best_node_values_future_.emplace_back(std::async(std::launch::async,
			[&figure, this]() {return GetBestMoveForFigure(figure); }));
	}
}



inline void RomanChessAI::ClearBestMoveForFiguresVector() {
	best_move_for_figures_.clear();
}

void RomanChessAI::FillBestMoveForFiguresVector() {
	for (auto& future_node : best_node_values_future_) {
		if (future_node.get()) {
			best_move_for_figures_.emplace_back(*future_node.get());
		}
	}
}



std::vector<std::shared_ptr<Figure>>&& RomanChessAI::GetFigurePtrs() const {
	std::vector<std::shared_ptr<Figure>> result;

	for (int row = 0; row < Constants::boardSize; ++row) {
		for (int collumn = 0; collumn < Constants::boardSize; ++collumn) {
			if (IsFigureAIColour((*game_figures_)[row][collumn])) {
				result.emplace_back((*game_figures_)[row][collumn]);
			}
		}
	}
	return std::move(result);
}



/*---------------------------------------------------------------------------------------------------*/
/*										AUXILIARY FUNCTIONS											 */
/*---------------------------------------------------------------------------------------------------*/




inline std::shared_ptr<RomanChessGameEngine> RomanChessAI::MakeGameEngineCopy() const {
	return std::make_shared<RomanChessGameEngine>(*game_engine_);
}









const std::optional<NodeValue> RomanChessAI::GetBestMoveForFigure(const std::shared_ptr<Figure>& figure) {
	auto legal_moves = game_engine_->GetLegalMoves(figure);
	std::vector<std::future<NodeValue>> node_values_future; // result of best values for every move

	//put second board coordinate into initial node value
	 //both coordinates of this figure									 

	if (legal_moves.size() > std::size_t(0)) {
		//async minimax
		for (auto& move : legal_moves) {
			node_values_future.emplace_back(std::async(std::launch::async,
				[&figure, &move, this]() {return EvaluateFigureMove(figure, move); }));
		}



		//get best value out of future
	}

	//async call minimax for every legal move
	//implement handling removing PontifexMaximus
	//create first node out of figure
	//implement minimax





	return std::nullopt;
	return std::make_pair(std::make_pair(BoardCoordinates(0, 0), BoardCoordinates(0, 0)), 0);
}




const NodeValue RomanChessAI::EvaluateFigureMove(const std::shared_ptr<Figure>& figure, const BoardCoordinates& move_coordinates) {
	//this goes under mutex
	RomanChessNode initial_node(GetInitialNodeValue(figure, move_coordinates));
	RomanChessGameEngine temp_game_engine(*game_figures_);

	figureColour figure_colour = figure->GetFigureColour();
	auto initial_alpha_beta = Constants::AI::InitialAlphaBeta;


	//end mutex

	return Minimax(initial_node, figure_colour, initial_alpha_beta, temp_game_engine);
}

int RomanChessAI::Minimax(RomanChessNode& node, const figureColour& player,
	std::pair<int, int>& alpha_beta,
	RomanChessGameEngine& chess_engine) {

	if (IsMaxDepth(node.GetDepth())) //return evaluated board
		return GetEvaluatedBoardStrenght(chess_engine.GetBoardImage());

	if (!AreChildrenNodesGenerated(node)) {

		//if no legal moves can be created, return

		//get legal moves
		//make node value for every move
		//create children nodes with node values
		node.MakeChildrenNode()
	}

	//check if children nodes are generated
	//generate children nodes if not already generated
	//if no nodes could be generated, return



}

inline const NodeValue RomanChessAI::GetAlphaBetaNodeValue(std::pair<NodeValue, NodeValue>& alpha_beta) const {
	return AI_player_colour_ == figureColour::Red ? alpha_beta.second : alpha_beta.first;
}

inline bool RomanChessAI::AreChildrenNodesGenerated(const RomanChessNode& node) {
	return node.GetChildrenNodesNumber() > std::size_t(0);
}

bool RomanChessAI::GenerateChildrenNodes(RomanChessNode& node, RomanChessGameEngine& chess_engine) {

	chess_engine.CalculateLegalMoves(node.GetFigurePosition());

	if (chess_engine.LegalMovesExist()) {
		for (const auto& move : chess_engine.GetLegalMoves()) {
			//create node value
			//
			RomanChessMove children_move(node.GetMoveCoordinates(), move);
			GetEvaluatedBoardStrenght();

			node.MakeChildrenNode()
		}
	}

	else
		return false;


}

NodeValue&& RomanChessAI::MakeNodeValue(const RomanChessNode& node, const BoardCoordinates& move_coordinates) {




}

inline bool RomanChessAI::IsMaxDepth(const int depth) const {
	return depth == Constants::AI::MaxDepth;
}

inline bool RomanChessAI::IsLastLevelNode(const int depth) const {
	return depth == Constants::AI::MaxDepth - 1;
}



inline bool RomanChessAI::IsFigureAIColour(const std::shared_ptr<Figure>& figure) const {
	if (IsFigureOnTile(figure)) {
		return figure->GetFigureColour() == AI_player_colour_;
	}
	return false;
}

inline const NodeValue RomanChessAI::GetInitialNodeValue(const std::shared_ptr<Figure>& figure, const BoardCoordinates& move_coordinates) const {
	return NodeValue(std::make_pair(figure->GetPosition(), move_coordinates), GetInitialBoardStrenght(figure));
}

inline const int RomanChessAI::GetInitialBoardStrenght(const std::shared_ptr<Figure>& figure) const {
	return figure->GetFigureColour() == figureColour::Red ? Constants::AI::MaxValue : Constants::AI::MinValue;
}


inline bool RomanChessAI::IsFigureOnTile(const std::shared_ptr<Figure> figure) const {
	return figure != nullptr;
}

inline bool RomanChessAI::IsFigureImageEmpty(const FigureImage figure_image) const {
	return figure_image == FigureImage();
}
