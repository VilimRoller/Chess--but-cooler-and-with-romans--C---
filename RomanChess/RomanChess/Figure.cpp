#include "Figure.h"

void Figure::InitializeFigure(
	figureColour figure_colour,
	figureType figure_type,
	BoardCoordinates initial_position,
	int figure_number) {
	SetFigureColour(figure_colour);
	SetFigureType(figure_type);
	SetPosition(initial_position);
	SetFigureNumber(figure_number);
	InitializeFigureLambdas();
}

inline FigureImage Figure::GetImage() const {
	return figure_image_;
}

BoardCoordinates Figure::GetPosition() const {
	return position_;
}

inline figureType Figure::GetType() const {
	return figure_image_.first;
}

inline int Figure::GetID() const {
	return figureID_;
}

inline void Figure::SetPosition(const BoardCoordinates& new_poistion) {
	position_ = new_poistion;
}

inline void Figure::SetFigureType(const figureType& figure_type) {
	figure_image_.first = figure_type;
}

inline void Figure::SetFigureColour(const figureColour& figure_colour) {
	figure_image_.second = figure_colour;
}

inline void Figure::SetFigureNumber(const int new_number) {
	figureID_ = new_number;
}

void Figure::InitializeFigureLambdas()
{
	IsPlaceEmptyLambda = [&](const BoardImage& board_layout, const BoardCoordinates& position) {return IsPlaceEmpty(board_layout, position); };
	IsPlaceRedLambda = [&](const BoardImage& board_layout, const BoardCoordinates& position) {return IsPlaceRed(board_layout, position); };
	IsPlacePurpleLambda = [&](const BoardImage& board_layout, const BoardCoordinates& position) {return IsPlacePurple(board_layout, position); };
}

inline FigureImage Figure::GetEmptyFigure() const {
	return FigureImage(figureType::no_type, figureColour::no_colour);
}

inline bool Figure::IsRed(const FigureImage& figure_image) const {
	return figure_image.second == figureColour::Red;
}

inline bool Figure::IsPurple(const FigureImage& figure_image) const {
	return figure_image.second == figureColour::Purple;
}

inline bool Figure::IsEmpty(const FigureImage& figure_image) const {
	return figure_image == GetEmptyFigure();
}

inline bool Figure::IsStillOnBoard(const BoardCoordinates& coordinates) const {
	return  (coordinates.x >= 0) && (coordinates.x <= Constants::boardSize - 1) &&
		(coordinates.y >= 0) && (coordinates.y <= Constants::boardSize - 1);
}

bool Figure::IsMoveLegal(const BoardCoordinates& new_position, const BoardImage& board_layout) {
	std::vector<BoardCoordinates> legal_moves = GetLegalMoves(board_layout);
	return std::any_of(	legal_moves.begin(), 
						legal_moves.end(), 
						[&new_position](const auto& legal_move) {return new_position == legal_move; });
}

inline bool Figure::IsPlaceEmpty(const BoardImage& board_layout, const BoardCoordinates& position) {
	if (IsStillOnBoard(position)) {
		return IsEmpty(board_layout[position.x][position.y]);
	}
	return false;
}
inline bool Figure::IsPlaceRed(const BoardImage& board_layout, const BoardCoordinates& position) {
	if (IsStillOnBoard(position)) {
		return IsRed(board_layout[position.x][position.y]);
	}
	return false;
}
inline bool Figure::IsPlacePurple(const BoardImage& board_layout, const BoardCoordinates& position) {
	if (IsStillOnBoard(position)) {
		return IsPurple(board_layout[position.x][position.y]);
	}
	return false;
}
