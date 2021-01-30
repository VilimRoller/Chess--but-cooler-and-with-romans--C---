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
#include <SFML/Graphics.hpp>

using FigureImage = std::pair<figureType, figureColour>;
using BoardImage = std::array<std::array<FigureImage, Constants::boardSize>, Constants::boardSize>;
using ConditionLambdaType = std::function<bool(const BoardImage& board_layout, const BoardCoordinates& position)>;
using MoveFigureLambdaType = std::function<const BoardCoordinates(const int number_of_spaces)>;

class Figure
{
public:
	//Getters

	FigureImage GetImage() const {
		return figure_image_;
	}

	BoardCoordinates GetPosition() const {
		return position_;
	}

	figureType GetType() const {
		return figure_image_.first;
	}

	figureColour GetFigureColour() const {
		return figure_image_.second;
	}

	std::shared_ptr<sf::Sprite> GetFigureSprite() {
		return figure_sprite_;
	}
		


	int GetID() const {
		return figureID_;
	}

	auto GetEnemyColourLambda() {
		return GetFigureColour() == figureColour::Red ? IsPlacePurpleLambda : IsPlaceRedLambda;
	}

	//Setters
	void SetPosition(const BoardCoordinates& new_poistion) {
		position_ = new_poistion;
	}


	void SetFigureType(const figureType& figure_type) {
		figure_image_.first = figure_type;
	}

	void SetFigureColour(const figureColour& figure_colour) {
		figure_image_.second = figure_colour;
	}

	void SetFigureNumber(const int new_number) {
		figureID_ = new_number;
	}

	void InitializeFigureLambdas() {
		IsPlaceEmptyLambda = [&](const BoardImage& board_layout, const BoardCoordinates& position) {return IsPlaceEmpty(board_layout, position); };
		IsPlaceRedLambda = [&](const BoardImage& board_layout, const BoardCoordinates& position) {return IsPlaceRed(board_layout, position); };
		IsPlacePurpleLambda = [&](const BoardImage& board_layout, const BoardCoordinates& position) {return IsPlacePurple(board_layout, position); };
	}

	FigureImage GetEmptyFigure() const {
		return FigureImage(figureType::no_type, figureColour::no_colour);
	}

	bool IsRed(const FigureImage& figure_image) const {
		return figure_image.second == figureColour::Red;
	}

	bool IsPurple(const FigureImage& figure_image) const {
		return figure_image.second == figureColour::Purple;
	}

	bool IsEmpty(const FigureImage& figure_image) const {
		return figure_image == GetEmptyFigure();
	}
	
	void InitializeFigure(
		figureColour figure_colour, figureType figure_type, BoardCoordinates initial_position, int figure_number) {

		SetFigureColour(figure_colour);
		SetFigureType(figure_type);
		SetPosition(initial_position);
		InitializeFigureLambdas();
	}

	void InitializeFigureSprite(const sf::Texture& figure_texture) {
		figure_sprite_ = std::make_shared<sf::Sprite>();
		SetFigureTextureRect();
		figure_sprite_->setPosition(static_cast<float>(GetPosition().x * Constants::PixelMultiplier),
									static_cast<float>(GetPosition().y * Constants::PixelMultiplier));
		figure_sprite_->setTexture(figure_texture);
	}

	void SetTextureRect(const std::pair<sf::Vector2i, sf::Vector2i>& figure_sprite_rect_pos) {
		GetFigureColour() == figureColour::Red ?
			figure_sprite_->setTextureRect(sf::IntRect(figure_sprite_rect_pos.first, SFMLConstants::FigureSpriteRectSize)) :
			figure_sprite_->setTextureRect(sf::IntRect(figure_sprite_rect_pos.second, SFMLConstants::FigureSpriteRectSize));
	}

	void SetFigureTextureRect() {
		switch (GetType()) {
		case figureType::Veles:
			SetTextureRect(SFMLConstants::FigureSpriteRectPos_Veles);
			break;
		case figureType::Hastatus:
			SetTextureRect(SFMLConstants::FigureSpriteRectPos_Hastatus);
			break;
		case figureType::Princeps:
			SetTextureRect(SFMLConstants::FigureSpriteRectPos_Princeps);
			break;
		case figureType::Triarius:
			SetTextureRect(SFMLConstants::FigureSpriteRectPos_Triarius);
			break;
		case figureType::Eques:
			SetTextureRect(SFMLConstants::FigureSpriteRectPos_Eques);
			break;
		case figureType::Consul:
			SetTextureRect(SFMLConstants::FigureSpriteRectPos_Consul);
			break;
		case figureType::PontifexMaximus:
			SetTextureRect(SFMLConstants::FigureSpriteRectPos_PontifexMaximus);
			break;
		}
	}

	bool IsStillOnBoard(const BoardCoordinates& coordinates) const {
		return  (coordinates.x >= 0) && (coordinates.x <= Constants::boardSize - 1) &&
			(coordinates.y >= 0) && (coordinates.y <= Constants::boardSize - 1);
	}

	bool IsMoveLegal(const BoardCoordinates& new_position, const BoardImage& board_layout) {
		std::vector<BoardCoordinates> legal_moves = GetLegalMoves(board_layout);
		return std::any_of(legal_moves.begin(),
						   legal_moves.end(),
						   [&new_position](const auto& legal_move) {return new_position == legal_move; });
	}

	//Methods for checking tiles around the figure
	//Surrounding is analyzed from figure's point of view
	bool IsPlaceEmpty(const BoardImage& board_layout, const BoardCoordinates& position) {
		if (IsStillOnBoard(position)) {
			return IsEmpty(board_layout[position.x][position.y]);
		}
		return false;
	}

	bool IsPlaceRed(const BoardImage& board_layout, const BoardCoordinates& position) {
		if (IsStillOnBoard(position)) {
			return IsRed(board_layout[position.x][position.y]);
		}
		return false;
	}

	bool IsPlacePurple(const BoardImage& board_layout, const BoardCoordinates& position) {
		if (IsStillOnBoard(position)) {
			return IsPurple(board_layout[position.x][position.y]);
		}
		return false;
	}


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


	std::shared_ptr<sf::Sprite> figure_sprite_;

private:
	BoardCoordinates position_;
	FigureImage figure_image_;
	int figureID_;
	
};