#pragma once
#include "wxSfmlCanvas.h"
#include <map>
#include <vector>
#include <array>
#include <utility>
#include "ID.h"
#include "Constants.h"
#include "FigureIncludes.h"

using RomanChessFigures = std::array<std::array<std::shared_ptr<Figure>, Constants::boardSize>, Constants::boardSize>;
using BoardImage = std::array<std::array<FigureImage, Constants::boardSize>, Constants::boardSize>;

class BoardCanvas final :
    public wxSfmlCanvas
{
public:
    BoardCanvas(wxWindow* Parent,
        wxWindowID Id,
        wxPoint& Position,
        wxSize& Size,
        long Style = 0);

    void LoadTextures();
    void InitializeBoardSprite();
    void InitializeRomanChessFigures(const BoardImage& board_image);
    void SetFigure(const FigureImage& figure, const BoardCoordinates& position);

    void DrawAllFigures();
    void DrawBoard();

    void ClearCanvas() {
        clear(sf::Color(128, 128, 128));
    }

    void DrawSprites();
    void HandleCanvasEvent();
    
    void HandleMouseButtonPressedEvent(sf::Event& mouse_event);
    void HandleMouseButtonReleasedEvent(sf::Event& mouse_event);
    void HandleMouseMovedEvent(sf::Event& mouse_event);

    void EnableDragging() {
        is_dragging_enabled_ = true;
    }
    void DisableDragging() {
        is_dragging_enabled_ = false;
    }

    bool IsDraggingEnabled() {
        return is_dragging_enabled_;
    }

    void SetFigureEventSpritePtr(sf::Event& mouse_event);

    void ResetEventFigurePtrPtr() {
        event_figure_ptr_ = nullptr;
    }

    void ResetEventFigureOffset() {
        event_figure_offset_ = sf::Vector2f(0, 0);
    }

    bool IsOnCanvas(int x_coordinate, int y_coordinate) {
        return (x_coordinate < Constants::boardSize) && (y_coordinate < Constants::boardSize)
            && (x_coordinate >= 0)                   && (y_coordinate >= 0);
    }

    bool IsOnCanvas(sf::Vector2f coordinates) {
        int x_coordinate = static_cast<int>(std::round(coordinates.x)) / Constants::PixelMultiplier;
        int y_coordinate = static_cast<int>(std::round(coordinates.y)) / Constants::PixelMultiplier;

        return IsOnCanvas(x_coordinate, y_coordinate);
    }

    void MoveEventSprite(const sf::Vector2f& mouse_position) {
        if (event_figure_ptr_ != nullptr) {
            auto current_position = event_figure_ptr_->GetFigureSprite()->getPosition();
            auto position_offset = mouse_position - current_position - event_figure_offset_;
            event_figure_ptr_->GetFigureSprite()->move(position_offset);
        }
    }

    void SetEventFigurePosition(sf::Event& mouse_event);
    void SetBoardImage(BoardImage new_image = Constants::initialBoardImage) {
        board_image = new_image;
    }

protected:
    void OnUpdate() override;

private:
    //Pointer to figure modified by events
    std::shared_ptr<Figure> event_figure_ptr_;
    sf::Vector2f event_figure_offset_;

    sf::Event canvas_event_;

    bool is_dragging_enabled_ = false;


	sf::Texture board_texture_;
	sf::Texture figure_textures_;

    std::shared_ptr<sf::Sprite> board_sprite_;
    RomanChessFigures figures_;

    BoardImage board_image;

};


