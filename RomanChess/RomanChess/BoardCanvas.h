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
#include "RomanChessGameEngine.h"

using RomanChessFigures = std::array<std::array<std::shared_ptr<Figure>, Constants::boardSize>, Constants::boardSize>;
using FigureImage = std::pair<figureType, figureColour>;
using BoardImage = std::array<std::array<FigureImage, Constants::boardSize>, Constants::boardSize>;


//Add comments

class BoardCanvas final :
    public wxSfmlCanvas
{
public:
    BoardCanvas(wxWindow* Parent,
        wxWindowID Id,
        wxPoint& Position,
        wxSize& Size,
        long Style = 0);

    /*--------------------------------------------------------------------------------------------*/
    /*                                INITIALIZATION                                              */
    /*--------------------------------------------------------------------------------------------*/
    void LoadTextures();
    void InitializeBoardSprite();
    void InitializeRectangleSprites();
    void SetRectangleSpriteTexture(const int row, const int collumn);
    void SetRectangleSpritePosition(const int row, const int collumn);

    void InitializeRomanChessFigures();
    void SetFigure(BoardCoordinates&& position);
    void MakeFigureSprite(BoardCoordinates&& coordinates);

	/*--------------------------------------------------------------------------------------------*/
    /*                                RENDERING FUNCTIONS                                         */
    /*--------------------------------------------------------------------------------------------*/

    void DrawSprites();
    void ClearCanvas();

    void DrawRectangles();
    void DrawYellowRectangles();
    void DrawRedRectangles();
    
    void DrawAllFigures();
    void DrawBoard();
    
	/*--------------------------------------------------------------------------------------------*/
    /*                                HANDLING EVENTS                                             */
    /*--------------------------------------------------------------------------------------------*/

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
    bool IsOnCanvas(sf::Vector2f coordinates) const;

    void MoveEventSprite(const sf::Vector2f& mouse_position);
    const sf::Vector2f GetEventSpritePosition() const;
    const sf::Vector2f GetEventSpriteOffset() const;

    void SetEventFigurePosition(sf::Event& mouse_event);

    void MoveEventFigure(const int x_coordinate, const int y_coordinate);

    void SetFigurePtr(const int x_coordinate, const int y_coordinate);
	void ResetOldEventFigurePosition();
    void SetEventFigureCoordinates(const int x_coordinate, const int y_coordinate);
	void RefreshEventFigureSpritePosition();

	sf::Vector2f GetVectorCoordinates(const int x_coordinate, const int y_coordinate) const;
	std::pair<int, int> GetMouseIntegerCoordinates(const std::pair<int, int>& mouse_coordinates) const;
	std::pair<int, int> GetOffsettedMouseIntegerCoordinates(const std::pair<int, int>& mouse_coordinates) const;

    void DisplayGameOverMessageBox();

	/*--------------------------------------------------------------------------------------------*/
    /*                                HELPER BOOLEAN FUNCTIONS                                    */
    /*--------------------------------------------------------------------------------------------*/

	bool IsFigureOnTile(const BoardCoordinates& coordinates) const;
    bool IsFigureOnTile(const std::shared_ptr<Figure>& figure) const;
	bool IsEventFigure(const int x_coordinate, const int y_coordinate) const;
	bool IsEventMoveLegal(const int x_coordinate, const int y_coordinate) const;
	bool IsEventMovable(const int x_coordinate, const int y_coordinate) const;
	bool IsEventFigureRightColour() const;


protected:
    void OnUpdate() override;

private:
    RomanChessGameEngine chess_engine_;

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
};


