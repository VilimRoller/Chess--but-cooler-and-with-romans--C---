#pragma once
#include <SFML/Graphics.hpp>

#include "ID.h"
#include "Constants.h"
#include "BoardCoordinates.h"
#include "FigureImage.h"

class Figure
{
public:

	/*---------------------------------------------------------------------------------------------------------*/
	/*												INITIALIZERS		                                       */
	/*---------------------------------------------------------------------------------------------------------*/

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

	/*---------------------------------------------------------------------------------------------------------*/
	/*												GETTERS                                                    */
	/*---------------------------------------------------------------------------------------------------------*/

	[[nodiscard]] const FigureImage GetFigureImage() const noexcept {
		return figure_image_;
	}

	[[nodiscard]] const BoardCoordinates GetPosition() const noexcept {
		return position_;
	}

	[[nodiscard]] const figureType GetType() const noexcept {
		return figure_image_.type;
	}

	[[nodiscard]] const figureColour GetFigureColour() const noexcept {
		return figure_image_.colour;
	}

	[[nodiscard]] sf::Sprite& GetFigureSprite() noexcept {
		return figure_sprite_;
	}

	/*---------------------------------------------------------------------------------------------------------*/
	/*												SETTERS                                                    */
	/*---------------------------------------------------------------------------------------------------------*/

	void SetPosition(const BoardCoordinates new_poistion) noexcept {
		position_ = new_poistion;
	}

	void SetPosition(const int x_coordinate, const int y_coordinate) noexcept {
		SetPosition(BoardCoordinates(x_coordinate, y_coordinate));
	}

	void SetFigureType(const figureType& figure_type) noexcept {
		figure_image_.type = figure_type;
	}

	void SetFigureColour(const figureColour& figure_colour) noexcept {
		figure_image_.colour = figure_colour;
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

	virtual void SetFigureTextureRect() = 0;

	/*---------------------------------------------------------------------------------------------------------*/
	/*												BOOLEANS                                                   */
	/*---------------------------------------------------------------------------------------------------------*/

	[[nodiscard]] bool IsRed(const FigureImage& figure_image) const {
		return figure_image.colour == figureColour::Red;
	}

	[[nodiscard]] bool IsPurple(const FigureImage& figure_image) const {
		return figure_image.colour == figureColour::Purple;
	}

	[[nodiscard]] bool IsEmpty(const FigureImage& figure_image) const {
		return figure_image == FigureImage();
	}

	[[nodiscard]] bool IsFigureRed() const{
		return figure_image_.colour == figureColour::Red;
	}

	[[nodiscard]] bool IsFigurePurple() const{
		return figure_image_.colour == figureColour::Purple;
	}
	
	[[nodiscard]] bool IsFigureType(figureType type) const {
		return type == GetType();
	}

private:
	sf::Sprite figure_sprite_;

	BoardCoordinates position_;
	FigureImage figure_image_;
};