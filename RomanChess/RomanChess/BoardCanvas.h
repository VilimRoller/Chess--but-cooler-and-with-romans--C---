#pragma once
#include "wxSfmlCanvas.h"
#include <map>
#include <vector>
#include <array>
#include <utility>
#include <deque>
#include "ID.h"
#include "Constants.h"
#include "FigureIncludes.h"

using RomanChessFigures = std::array<std::array<std::shared_ptr<Figure>, Constants::boardSize>, Constants::boardSize>;
using FigureImage = std::pair<figureType, figureColour>;
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
    void InitializeRectangleSprites();
    void SetRectangleSpriteTexture(const int row, const int collumn);
    void SetRectangleSpritePosition(const int row, const int collumn);

    void InitializeRomanChessFigures(const BoardImage& board_image);
    void SetFigure(const FigureImage& figure, const BoardCoordinates& position);
    void MakeFigureSprite(const BoardCoordinates& position);

    void DrawRedRectangles();
    void DrawYellowRectangles();
    void DrawRectangles();
    void DrawAllFigures();
    void DrawBoard();

    void ClearCanvas();

    void DrawSprites();
    void HandleCanvasEvent();
    
    void HandleMouseButtonPressedEvent(sf::Event& mouse_event);
    void HandleMouseButtonReleasedEvent(sf::Event& mouse_event);
    void HandleMouseMovedEvent(sf::Event& mouse_event);

    void EnableDragging();
    void DisableDragging();
    void EnableDrawingRectangles();
    void DisableDrawingRectangles();

    void SetEventFigureSpritePtr(sf::Event& mouse_event);
    void SetEventFigurePtr(const int x_coordinate, const int y_coordinate);
    void ResetEventFigurePtr();
    void SetEventFigureOffset(const sf::Vector2f& mouse_vector_coordinates);
    void ResetEventFigureOffset();
    void SetRectangleCoordinates(const int x_coordinate, const int  y_coordinate);
    void EmplaceRectangleCoordinate(const BoardCoordinates& coordinate);
    void ResetRectangleCoordinates();
    void ClearRectangleVectors();

    bool IsOnCanvas(const int x_coordinate, const int y_coordinate) const;
    bool IsOnCanvas(sf::Vector2f coordinates);

    void MoveEventSprite(const sf::Vector2f& mouse_position);

    void SetEventFigurePosition(sf::Event& mouse_event);
    void SetBoardImage(BoardImage new_image = Constants::initialBoardImage);

    void MoveEventFigure(const int x_coordinate, const int y_coordinate);

    bool IsEventFigure(const int x_coordinate, const int y_coordinate) const;
    bool IsEventMoveLegal(const int x_coordinate, const int y_coordinate) const;
    bool IsEventMovable(const int x_coordinate, const int y_coordinate) const;
    bool IsEventFigureRightColour() const;

    void SetFigurePtr(const int x_coordinate, const int y_coordinate);

    void ResetOldEventFigurePosition();
    void RefreshEventFigureSpritePosition();

    void SetEventFigurePosition(const int x_coordinate, const int y_coordinate);

    bool IsFigureOnTile(const std::shared_ptr<Figure>& figure_ptr) const;

    sf::Vector2f GetVectorCoordinates(const int x_coordinate, const int y_coordinate) const;
    std::pair<int, int> GetMouseIntegerCoordinates(const std::pair<int, int>& mouse_coordinates) const;
    std::pair<int, int> GetOffsettedMouseIntegerCoordinates(const std::pair<int, int>& mouse_coordinates) const;

    void RefreshBoardImage();

    BoardImage MakeBoardImage(const RomanChessFigures& figures);
    figureColour GetPlayerTurnColour() const;
    void CheckGameOver();
    void SetGameOver();
    void NextPlayerTurn();
    bool IsGameOver() const;
    std::pair<int, int> GetNumberOfConsuls();
    void AddNumberOfConsuls(const std::shared_ptr<Figure>& figure , std::pair<int, int>& consul_number);

    bool BothSidesHaveConsul(const std::pair<int, int>& consuls);
    void DisplayGameOverMessageBox();
    void SaveBoardImage();
    void ClearBoardImageDeque();
    void RemovePontifexMaximus(const figureColour& figure_colour);
    void RemoveIfPontifexMaximus(const figureColour& figure_colour, std::shared_ptr<Figure>& figure);
    void RemoveFigure(std::shared_ptr<Figure>& figure);
    bool CheckIfPontifexMaximus(std::shared_ptr<Figure>& figure);
    void RewindBoard(const figureColour& pontifex_colour);
    

protected:
    void OnUpdate() override;

private:
    //Pointer to figure modified by events
    std::shared_ptr<Figure> event_figure_ptr_;
    
    // Distance from top left corner of sprite to mouse position
    sf::Vector2f event_figure_offset_; 
    
    sf::Event canvas_event_;

    bool is_dragging_enabled_ = false;
    bool is_drawing_rectangles_enabled_ = false;

    std::vector<BoardCoordinates> yellow_rectangle_positions_;
    std::vector<BoardCoordinates> red_rectangle_positions_;

	sf::Texture board_texture_;
	sf::Texture figure_textures_;
    sf::Texture yellow_rectangle_texture_;
    sf::Texture red_rectangle_texture_;

    
    sf::Sprite board_sprite_;
    std::array<std::array<sf::Sprite, Constants::boardSize>, Constants::boardSize> yellow_rectangles_;
    std::array<std::array<sf::Sprite, Constants::boardSize>, Constants::boardSize> red_rectangles_;

    RomanChessFigures figures_;

    BoardImage board_image_;

	bool is_game_over_ = false;
	figureColour player_turn_ = figureColour::Red;

    std::deque<BoardImage> board_image_deque_;

};


