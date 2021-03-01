#pragma once
#include <utility>
#include <array>
#include <vector>
#include <string>
#include <map>
#include <future>
#include <mutex>
#include <optional>
#include "ID.h"
#include "Constants.h"
#include "BoardCoordinates.h"
#include "FigureIncludes.h"
#include "RomanChessNode.h"
#include "RomanChessGameEngine.h"

#include "TypeAliases.h"


using IntegerMap2D = std::array<std::array<int16, Constants::boardSize>, Constants::boardSize>;
using RomanChessMove = std::pair<BoardCoordinates, BoardCoordinates>;
using EvaluatedRomanChessMove = std::pair<RomanChessMove, int16>;

class RomanChessAI
{
public:
	RomanChessAI(const AIType AI_type_red = AIType::CaesarAI,
		const AIStrategy AI_strategy_red = AIStrategy::Standard,
		const AIType AI_type_purple = AIType::CaesarAI,
		const AIStrategy AI_strategy_purple = AIStrategy::Standard,
		RomanChessGameEngine* game_engine = nullptr,
		const figureColour AI_colour = figureColour::Red);

	~RomanChessAI() {}

	/*---------------------------------------------------------------------------------------------------*/
	/*										INITIALIZERS												 */
	/*---------------------------------------------------------------------------------------------------*/

	void InitializeRomanChessAI(const AIType AI_type_red, const AIStrategy AI_strategy_red,
		const AIType AI_type_purple, const AIStrategy AI_strategy_purple,
		RomanChessGameEngine* game_engine, const figureColour AI_colour);

	void InitializeRomanChessAIMaps();
	void InitializeFigureEvaluationValuesMap(const AIType& AI_type, const figureColour& colour);
	void InitializeFigureEvaluationMultiplierMap(const AIStrategy& AI_strategy, const figureColour& colour);

	/*---------------------------------------------------------------------------------------------------*/
	/*										GETTERS														 */
	/*---------------------------------------------------------------------------------------------------*/


	[[nodiscard]] const figureColour& GetAIPlayerColour() const;
	[[nodiscard]] const AIType& GetAITypeRed() const;
	[[nodiscard]] const AIType& GetAITypePurple() const;
	[[nodiscard]] const AIStrategy& GetAIStrategyRed() const;
	[[nodiscard]] const AIStrategy& GetAIStrategyPurple() const;


	/*---------------------------------------------------------------------------------------------------*/
	/*										SETTERS														 */
	/*---------------------------------------------------------------------------------------------------*/

	void SetAIPlayerColour(const figureColour& figure_colour);
	void SetGameEnginePtr(RomanChessGameEngine* game_engine);
	void SetAITypeRed(const AIType& AI_type_red);
	void SetAITypePurple(const AIType& AI_type_purple);
	void SetAIStrategyRed(const AIStrategy& AI_strategy_red);
	void SetAIStrategyPurple(const AIStrategy& AI_strategy_purple);

	void SetFigureEvaluationMap(const std::map<FigureImage, int>& evaluation_map, const figureColour& colour);
	void SetFigureEvaluationMultiplierMap(const std::map<figureType, IntegerMap2D>& multiplier_map, const figureColour& colour);



	/*---------------------------------------------------------------------------------------------------*/
	/*										BOARD EVALUATION											 */
	/*---------------------------------------------------------------------------------------------------*/


	[[nodiscard]] const int16 GetEvaluatedBoardStrenght() const noexcept;
	[[nodiscard]] const int16 GetEvaluatedBoardStrenght(const BoardImage board_image) const noexcept;
	[[nodiscard]] const int16 GetFigureStrengh(const FigureImage figure_image, const BoardCoordinates coordinates) const noexcept;

	[[nodiscard]] const int16 GetFigureEvaluationMultiplier(const FigureImage figure_image, const BoardCoordinates coordinates) const;
	[[nodiscard]] const int16 GetFigureEvaluationMultiplierRed(const FigureImage figure_image, const BoardCoordinates coordinates) const;
	[[nodiscard]] const int16 GetFigureEvaluationMultiplierPurple(const FigureImage figure_image, const BoardCoordinates coordinates) const;



	/*---------------------------------------------------------------------------------------------------*/
	/*										EVALUATING FIGURE MOVES										 */
	/*---------------------------------------------------------------------------------------------------*/

	void FillAllFigurePositionsVector() noexcept;

	void CalculateBestMoveForEveryFigure() noexcept;

	std::optional<int16> GetBestMoveForFigureAsync(const BoardCoordinates coordinate) noexcept;

	int16 GetValueForFigureMove(const BoardCoordinates coordinate);


	int16 FilterBestMove(std::vector<int16>&& moves_vector) const;







	[[nodiscard]] const std::optional<NodeValue> GetBestMoveForFigure(const std::shared_ptr<Figure>& figure);
	[[nodiscard]] const RomanChessFigures& GetFigureBoardCopy();

	[[nodiscard]] const NodeValue GetInitialNodeValue(const std::shared_ptr<Figure>& figure, const BoardCoordinates& move_coordinates) const;
	[[nodiscard]] const int GetInitialBoardStrenght(const std::shared_ptr<Figure>& figure) const;










	/*---------------------------------------------------------------------------------------------------*/
	/*										PICKING BEST FIGURE MOVE									 */
	/*---------------------------------------------------------------------------------------------------*/



	[[nodiscard]] RomanChessMove GetBestMove();

	[[nodiscard]] const std::vector<EvaluatedRomanChessMove>::iterator GetBestMoveNode();
	[[nodiscard]] const std::vector<EvaluatedRomanChessMove>::iterator GetMinMoveNodeValue();
	[[nodiscard]] const std::vector<EvaluatedRomanChessMove>::iterator GetMaxMoveNodeValue();











	[[nodiscard]] std::vector<std::shared_ptr<Figure>>&& GetFigurePtrs() const;

	/*---------------------------------------------------------------------------------------------------*/
	/*										AUXILIARY FUNCTIONS											 */
	/*---------------------------------------------------------------------------------------------------*/

	std::shared_ptr<RomanChessGameEngine> MakeGameEngineCopy() const;



	[[nodiscard]] bool IsFigureOnTile(const std::shared_ptr<Figure>& tile) const;
	[[nodiscard]] bool IsFigureImageEmpty(const FigureImage& figure_image) const;

	[[nodiscard]] bool IsFigureAIColour(const std::shared_ptr<Figure>& figure) const;

	[[nodiscard]] bool IsMaxDepth(const int depth) const;
	[[nodiscard]] bool IsLastLevelNode(const int depth) const;

	[[nodiscard]] bool AreChildrenNodesGenerated(const RomanChessNode& node) const;
	[[nodiscard]] bool GenerateChildrenNodes(RomanChessNode& node, RomanChessGameEngine& chess_engine) const;

	[[nodiscard]] const NodeValue GetAlphaBetaNodeValue(std::pair<NodeValue, NodeValue>& alpha_beta) const;


	void ClearBestNodeValuesFutureVector();
	void FillBestNodeValuesFutureVector();
	void ClearBestMoveForFiguresVector();
	void FillBestMoveForFiguresVector();

	NodeValue&& MakeNodeValue(const RomanChessNode& node, const BoardCoordinates& move_coordinates);

	const RomanChessNode MakeRomanChessNode(const BoardCoordinates& board_coordinates);


	/*-------------------------------------------------------------------------------------------------------------*/
	/*                                         EVALUATING MOVE                                                     */
	/*-------------------------------------------------------------------------------------------------------------*/






	const NodeValue EvaluateFigureMove(const std::shared_ptr<Figure>& figure, const BoardCoordinates& move_coordinates);

	int Minimax(RomanChessNode& node, const figureColour& player,
		std::pair<int, int>& alpha_beta,
		RomanChessGameEngine& chess_engine);






	/*-------------------------------------------------------------------------------------------------------------*/
	/*												CLASS MEMBERS                                                  */
	/*-------------------------------------------------------------------------------------------------------------*/

#pragma region CLASS MEMBERS

private:

	figureColour AI_player_colour_;

	RomanChessGameEngine* game_engine_;

	AIType AI_type_red_;
	AIStrategy AI_strategy_red_;
	AIType AI_type_purple_;
	AIStrategy AI_strategy_purple_;

	mutable std::map<FigureImage, int16> figure_evaluation_values_map_red_;
	mutable std::map<figureType, IntegerMap2D> figure_evaluation_multplier_map_red_;

	mutable std::map<FigureImage, int16> figure_evaluation_values_map_purple_;
	mutable std::map<figureType, IntegerMap2D> figure_evaluation_multplier_map_purple_;

	std::vector<BoardCoordinates> all_figure_positions_;

	std::vector<std::future<std::optional<EvaluatedRomanChessMove>>> best_node_values_future_;
	std::vector<EvaluatedRomanChessMove> best_move_for_figures_;

#pragma endregion
};
