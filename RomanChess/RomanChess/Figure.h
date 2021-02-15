#pragma once
#include <utility>
#include <memory>
#include <array>
#include <vector>
#include <algorithm>
#include <functional>
#include <optional>
#include <cmath>
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

	const FigureImage& GetFigureImage() const {
		return figure_image_;
	}

	const BoardCoordinates& GetPosition() const {
		return position_;
	}

	const figureType& GetType() const {
		return figure_image_.first;
	}

	const figureColour& GetFigureColour() const {
		return figure_image_.second;
	}

	sf::Sprite& GetFigureSprite() {
		return figure_sprite_;
	}



	//Setters
	void SetPosition(const BoardCoordinates& new_poistion) {
		position_ = new_poistion;
	}

	void SetPosition(const int x_coordinate, const int y_coordinate) {
		SetPosition(BoardCoordinates(x_coordinate, y_coordinate));
	}

	void SetScaledPosition(const sf::Vector2f& new_position) {
		SetPosition(BoardCoordinates(static_cast<int>(std::round(new_position.x) / Constants::PixelMultiplier), 
									 static_cast<int>(std::round(new_position.y) / Constants::PixelMultiplier)));
	}

	void SetFigureType(const figureType& figure_type) {
		figure_image_.first = figure_type;
	}

	void SetFigureColour(const figureColour& figure_colour) {
		figure_image_.second = figure_colour;
	}



	const FigureImage GetEmptyFigure() const {
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

	bool IsFigureRed() const{
		return IsFigureColour(figureColour::Red);
	}

	bool IsFigurePurple() const{
		return IsFigureColour(figureColour::Purple);
	}
	
	bool IsFigureColour(figureColour colour) const {
		return colour == GetFigureColour();
	}

	bool IsFigureType(figureType type) const {
		return type == GetType();
	}

	void InitializeFigure(
		figureColour figure_colour, figureType figure_type, BoardCoordinates initial_position, int figure_number) {
		SetFigureColour(figure_colour);
		SetFigureType(figure_type);
		SetPosition(initial_position);
	}

	void InitializeFigureSprite(const sf::Texture& figure_texture) {
		SetFigureTextureRect();
		SetFigureSpritePosition();

		figure_sprite_.setTexture(figure_texture);
	}

	void SetFigureSpritePosition() {
		figure_sprite_.setPosition(static_cast<float>(GetPosition().x * Constants::PixelMultiplier),
								   static_cast<float>(GetPosition().y * Constants::PixelMultiplier));
	}

	void SetTextureRect(const std::pair<sf::Vector2i, sf::Vector2i>& figure_sprite_rect_pos) {
		IsFigureRed() ?
			figure_sprite_.setTextureRect(sf::IntRect(figure_sprite_rect_pos.first, SFMLConstants::FigureSpriteRectSize)) :
			figure_sprite_.setTextureRect(sf::IntRect(figure_sprite_rect_pos.second, SFMLConstants::FigureSpriteRectSize));
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






	sf::Sprite figure_sprite_;

private:
	BoardCoordinates position_;
	FigureImage figure_image_;
};