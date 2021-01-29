#pragma once
#include <utility>
#include <memory>
#include <array>
#include <vector>
#include <algorithm>
#include <functional>
#include <optional>
#include "Constants.h"
#include "ID.h"
#include "BoardCoordinates.h"
#include "BadColourException.h"

using FigureImage = std::pair<figureType, figureColour>;
using BoardImage = std::array<std::array<FigureImage, Constants::boardSize>, Constants::boardSize>;
using ConditionLambdaType = std::function<bool(const BoardImage& board_layout, const BoardCoordinates& position)>;
using MoveFigureLambdaType = std::function<const BoardCoordinates(const int number_of_spaces)>;

class Figure
{
public:
	//Getters
	FigureImage GetImage() const;
	BoardCoordinates GetPosition() const;
	figureType GetType() const;
	figureColour GetFigureColour() const {
		return figure_image_.second;
	}
	int GetID() const;
	auto GetEnemyColourLambda() {
		return GetFigureColour() == figureColour::Red ? IsPlacePurpleLambda : IsPlaceRedLambda;
	}

	//Setters
	void SetPosition(const BoardCoordinates& new_poistion);
	void SetFigureType(const figureType& figure_type);
	void SetFigureColour(const figureColour& figure_colour);
	void SetFigureNumber(const int new_number);
	void InitializeFigureLambdas();

	FigureImage GetEmptyFigure() const;
	bool IsRed(const FigureImage& figure_image) const;
	bool IsPurple(const FigureImage& figure_image) const;
	bool IsEmpty(const FigureImage& figure_image) const;
	
	void InitializeFigure(
		figureColour figure_colour,
		figureType figure_type,
		BoardCoordinates initial_position,
		int figure_number = 0);

	bool IsStillOnBoard(const BoardCoordinates& coordinates) const;
	bool IsMoveLegal(const BoardCoordinates& new_position, const BoardImage& board_layout);

	//Methods for checking tiles around the figure
	//Surrounding is analyzed from figure's point of view
	bool IsPlaceEmpty(const BoardImage& board_layout, const BoardCoordinates& position);
	bool IsPlaceRed(const BoardImage& board_layout, const BoardCoordinates& position);
	bool IsPlacePurple(const BoardImage& board_layout, const BoardCoordinates& position);


	const BoardCoordinates MoveFront(const int number_of_spaces = 1) const {
		return position_ + (GetFigureColour() == figureColour::Red?	BoardCoordinates(0, -number_of_spaces) :
																BoardCoordinates(0, number_of_spaces));
	}

	const BoardCoordinates MoveBack(const int number_of_spaces = 1) const {
		return position_ + (GetFigureColour() == figureColour::Red ?	BoardCoordinates(0, number_of_spaces) :
																BoardCoordinates(0, -number_of_spaces));
	}

	const BoardCoordinates MoveLeft(const int number_of_spaces = 1) const {
		return position_ + (GetFigureColour() == figureColour::Red ?	BoardCoordinates(-number_of_spaces, 0) :
																BoardCoordinates(number_of_spaces, 0));
	}

	const BoardCoordinates MoveRight(const int number_of_spaces = 1) const {
		return position_ + (GetFigureColour() == figureColour::Red ?	BoardCoordinates(number_of_spaces, 0) :
																BoardCoordinates(-number_of_spaces, 0));
	}

	const BoardCoordinates MoveDiagonalLeftFront(const int number_of_spaces = 1) const {
		return position_ + (GetFigureColour() == figureColour::Red ?	BoardCoordinates(-number_of_spaces, -number_of_spaces) :
																BoardCoordinates(number_of_spaces, number_of_spaces));
	}



	const BoardCoordinates MoveDiagonalLeftBack(const int number_of_spaces = 1) const {
		return position_ + (GetFigureColour() == figureColour::Red ?	BoardCoordinates(-number_of_spaces, number_of_spaces) :
																BoardCoordinates(number_of_spaces, -number_of_spaces));
	}

	const BoardCoordinates MoveDiagonalRightFront(const int number_of_spaces = 1) const {
		return position_ + (GetFigureColour() == figureColour::Red ?	BoardCoordinates(number_of_spaces, -number_of_spaces) :
																BoardCoordinates(-number_of_spaces, number_of_spaces));
	}

	const BoardCoordinates MoveDiagonalRightBack(const int number_of_spaces = 1) const {
		return position_ + (GetFigureColour() == figureColour::Red ?	BoardCoordinates(number_of_spaces, number_of_spaces) :
																BoardCoordinates(-number_of_spaces, -number_of_spaces));
	}

	//Validate figure's move to position
	template <class T>
	bool ValidateMove(const BoardImage& board_layout,
		std::vector<BoardCoordinates>& res,
		const BoardCoordinates& position,
		T&& ConditionLambda) {
		if (ConditionLambda(board_layout, position)) {
			res.emplace_back(position);
			return true;
		}
		return false;
	}

	//Validate figure's moves in direction defined by DirectionLambda
	template <class T1>
	void ValidateMoveInDirection(const BoardImage& board_layout,
		std::vector<BoardCoordinates>& res,
		T1&& DirectionLambda) {
		for (int num_of_spaces = 1; IsStillOnBoard(DirectionLambda(num_of_spaces)); ++num_of_spaces) {
			if (!ValidateMove(board_layout, res, DirectionLambda(num_of_spaces), IsPlaceEmptyLambda)) {
				ValidateMove(board_layout, res, DirectionLambda(num_of_spaces), GetEnemyColourLambda());
				break; //Avoid skipping over figures
			}
		}
	}

	//Specific for every figure
	virtual std::vector<BoardCoordinates> GetLegalMoves(const BoardImage& board_layout) = 0;
	
	
	ConditionLambdaType IsPlaceEmptyLambda;
	ConditionLambdaType IsPlaceRedLambda;
	ConditionLambdaType IsPlacePurpleLambda;



private:
	BoardCoordinates position_;
	FigureImage figure_image_;
	int figureID_;

};