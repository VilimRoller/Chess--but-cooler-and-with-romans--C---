#pragma once
#include <vector>
#include <memory>
#include <utility>
#include "TypeAliases.h"
#include "BoardCoordinates.h"

//deprecate node value
//replace with moves vector
class RomanChessNode
{
public:
	RomanChessNode(const std::vector<BoardCoordinates>& moves,
		const int16& evaluation_value,
		const int8 node_depth = 1)
		: moves_from_initial_node_{ moves }, board_evaluation_value_{evaluation_value}, depth_{ node_depth } {}

	RomanChessNode(std::vector<BoardCoordinates>&& moves,
		const int16& evaluation_value,
		const int8 node_depth = 1)
		: moves_from_initial_node_{ moves }, board_evaluation_value_{ evaluation_value }, depth_{ node_depth } {}

	~RomanChessNode() {}

	/*-----------------------------------------------------------------------------------------------------*/
	/*											GETTERS													   */
	/*-----------------------------------------------------------------------------------------------------*/

	const int8 GetDepth() const {
		return depth_;
	}

	const int16 GetBoardEvaluationValue() const {
		return board_evaluation_value_;
	}

	const BoardCoordinates GetInitialFigurePositionCoordinates() const {
		return *moves_from_initial_node_.begin();
	}

	const BoardCoordinates GetFigurePositionCoordinates() const {
		return *moves_from_initial_node_.end();
	}

	const auto& GetMovesVector() const {
		return moves_from_initial_node_;
	}

	const std::size_t GetChildrenNodesNumber() const {
		return children_node_ptrs_.size();
	}

	const auto& GetChildrenNodesVector() const {
		return children_node_ptrs_;
	}

	/*-----------------------------------------------------------------------------------------------------*/
	/*											SETTERS													   */
	/*-----------------------------------------------------------------------------------------------------*/

	void SetBoardEvaluationValue(const int16 evaluation_value) {
		board_evaluation_value_ = evaluation_value;
	}

	void SetMovesFromInitialNodeVector(const std::vector<BoardCoordinates>& moves_vector) {
		moves_from_initial_node_ = moves_vector;
	}

	void AddMoveToVector(const BoardCoordinates& move_coordinates) {
		moves_from_initial_node_.emplace_back(move_coordinates);
	}

	void MakeChildrenNode(const BoardCoordinates& move_coordinate, const int16 board_evaluation) {
		children_node_ptrs_.emplace_back(std::make_shared<RomanChessNode>(MakeChildrenMovesVector(move_coordinate),
																		  board_evaluation,
																		depth_ + int8(1)));
	}

	std::vector<BoardCoordinates>&& MakeChildrenMovesVector(const BoardCoordinates& board_coordinates) {
		std::vector<BoardCoordinates> result = moves_from_initial_node_;
		result.emplace_back(board_coordinates);
		return std::move(result);
	}


private:
	int8 depth_;
	int16 board_evaluation_value_;
	std::vector<std::unique_ptr<RomanChessNode>> children_node_ptrs_;
	std::vector<BoardCoordinates> moves_from_initial_node_;
};

