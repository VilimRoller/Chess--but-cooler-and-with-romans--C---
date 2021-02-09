#pragma once
#include <vector>
#include <memory>
class RomanChessNode
{
public:
	RomanChessNode(const int node_value = 0, const int node_depth = 1)
		: node_value_{ node_value }, depth_{ node_depth } {

	}
	~RomanChessNode() {}

	const int GetNodeValue() const {
		return node_value_;
	}

	const int GetDepth() const {
		return depth_;
	}

	const int GetChildrenNodesNumber() const {
		return children_nodes_.size();
	}

	auto* GetChildrenNodesPtr() const {
		return &children_nodes_;
	}

	void MakeChildrenNode(const int node_value) {
		children_nodes_.emplace_back(std::make_shared<RomanChessNode>(node_value, depth_ + 1));
	}

private:
	int node_value_;
	int depth_;
	std::vector<std::shared_ptr<RomanChessNode>> children_nodes_;

};

