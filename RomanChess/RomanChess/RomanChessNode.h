#pragma once
#include <vector>
#include <memory>
#include <utility>
#include "BoardCoordinates.h"

using RomanChessMove = std::pair<BoardCoordinates, BoardCoordinates>;
using NodeValue = std::pair<RomanChessMove, int>;

class RomanChessNode
{
public:
	RomanChessNode(const NodeValue& node_value, const int node_depth = 1)
		: node_value_{ node_value }, depth_{ node_depth } {

	}
	~RomanChessNode() {}

	const NodeValue& GetNodeValue() const {
		return node_value_;
	}

	const int GetNodeStrenght() const {
		return node_value_.second;
	}

	const BoardCoordinates& GetMoveCoordinates() const {
		return node_value_.first.second;
	}

	const int GetDepth() const {
		return depth_;
	}

	const std::size_t GetChildrenNodesNumber() const {
		return children_nodes_.size();
	}

	auto* GetChildrenNodesPtr() const {
		return &children_nodes_;
	}

	void MakeChildrenNode(const NodeValue& node_value) {
		children_nodes_.emplace_back(std::make_shared<RomanChessNode>(node_value, depth_ + 1));
	}

	void SetMoveCoordinate(const BoardCoordinates& board_coordinates) {
		node_value_.first.second = board_coordinates;
	}

	void SetNodeStrenght(const int strenght) {
		node_value_.second = strenght;
	}

private:
	NodeValue node_value_;
	int depth_;
	std::vector<std::shared_ptr<RomanChessNode>> children_nodes_;

};

