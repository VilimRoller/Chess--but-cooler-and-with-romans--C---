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
#include "TypeAliases.h"

using BoardRow = std::array<FigureImage, Constants::boardSize>;
using BoardImage = std::array<BoardRow, Constants::boardSize>;
using RomanChessFigures = std::array<std::array<std::shared_ptr<Figure>, Constants::boardSize>, Constants::boardSize>;

class BoardCanvas final :
    public wxSfmlCanvas
{
public:
    BoardCanvas(wxWindow* Parent,
        wxWindowID Id,
        wxPoint& Position,
        wxSize& Size,
        long Style = 0);

    /*-------------------------------------------------------------------------------------------------------------*/
    /*                                              INITIALIZATION                                                 */
    /*-------------------------------------------------------------------------------------------------------------*/

    void LoadTextures() noexcept;
    void InitializeBoardSprite() noexcept;
    void InitializeRectangleSprites() noexcept;

    void SetRectangleSpriteTexturesAndPositions(const BoardCoordinates coordinates) noexcept;
    void SetRectangleSpriteTextures(const BoardCoordinates coordinates) noexcept;
    void SetRectangleSpritePositions(const BoardCoordinates coordinates) noexcept;

    void InitializeRomanChessFigures() noexcept;
    void SetFigure(BoardCoordinates position) noexcept;
    void CreateFigure(BoardCoordinates position) noexcept;
    void CreateEmptyFigure(std::shared_ptr<Figure>& figure) noexcept;
    void MakeFigureSprite(BoardCoordinates coordinates) noexcept;

    /*-------------------------------------------------------------------------------------------------------------*/
    /*                                         RENDERING FUNCTIONS                                                 */
    /*-------------------------------------------------------------------------------------------------------------*/
protected:
	void OnUpdate() override;

public:
    void DrawSprites() noexcept;
    void ClearCanvas() noexcept;

    void DrawRectanglesIfEnabled() noexcept;
    void DrawRectangles() noexcept;
    void DrawYellowRectangles() noexcept;
    void DrawRedRectangles() noexcept;
    
    void DrawAllFigures() noexcept;
    void DrawFigure(const std::shared_ptr<Figure>& figure_ptr) noexcept;
    void DrawBoard() noexcept;
    
    /*-------------------------------------------------------------------------------------------------------------*/
    /*                                           HANDLING EVENTS                                                   */
    /*-------------------------------------------------------------------------------------------------------------*/

    void HandleCanvasEvent() noexcept;
    void HandleCanvasEventType(const sf::Event& mouse_event) noexcept;

    void HandleMouseButtonPressedEvent(const sf::Event& mouse_event) noexcept;

    void HandleMouseMovedIfDraggingEnabled(const sf::Event& mouse_event) noexcept;
    void HandleMouseMovedEvent(const sf::Event& mouse_event) noexcept;

    void HandleMouseButtonReleasedEvent(const sf::Event& mouse_event) noexcept;
    

	/*-------------------------------------------------------------------------------------------------------------*/
    /*                                        EVENT FIGURE FUNCTIONS                                               */
    /*-------------------------------------------------------------------------------------------------------------*/

    void SetEventFigureIfEligible(const sf::Event& mouse_event) noexcept;
    void SetEventFigure(const sf::Event& mouse_event) noexcept;

    void SetEventFigurePtr(const BoardCoordinates coordinates) noexcept;
    void ResetEventFigurePtr() noexcept;

    void SetEventFigureSpriteOffset(const sf::Vector2f& mouse_vector_coordinates) noexcept;
    void ResetEventFigureSpriteOffset() noexcept;

    void MoveEventFigureSpriteIfEligible(const sf::Vector2f& mouse_position) noexcept;
    void MoveEventFigureSprite(const sf::Vector2f& mouse_position) noexcept;

    void SetEventFigurePositionIfEligible(const sf::Event& mouse_event) noexcept;
    void SetEventFigurePosition(const sf::Event& mouse_event) noexcept;

    void ManageMovingEventFigureIfEligible(const BoardCoordinates coordinates) noexcept;
    void ManageMovingEventFigure(const BoardCoordinates coordinates) noexcept;
    void MoveEventFigure(const BoardCoordinates coordinates) noexcept;

	void ResetOldEventFigurePosition() noexcept;
	void SetEventFigureCoordinates(const BoardCoordinates coordinates) noexcept;
	void RefreshEventFigureSpritePosition() noexcept;

    void SetFigurePtrToEventPtr(const BoardCoordinates coordinates) noexcept;

	/*-------------------------------------------------------------------------------------------------------------*/
	/*                                        RECTANGLE FUNCTIONS                                                  */
	/*-------------------------------------------------------------------------------------------------------------*/

    void SetRectangleCoordinates() noexcept;
    void EmplaceRectangleCoordinate(const BoardCoordinates coordinate) noexcept;
    void ResetRectangleCoordinates() noexcept;
    void ClearRectangleVectors() noexcept;

	void EnableDrawingRectangles() noexcept;
	void DisableDrawingRectangles() noexcept;
    
	/*-------------------------------------------------------------------------------------------------------------*/
    /*                                         BOOLEAN FUNCTIONS                                                   */
    /*-------------------------------------------------------------------------------------------------------------*/

    [[nodiscard]] bool GameIsNotOver() const noexcept;

	[[nodiscard]] bool IsFigureOnTile(const BoardCoordinates coordinates) const noexcept;
    [[nodiscard]] bool IsFigureOnTile(const std::shared_ptr<Figure>& figure) const noexcept;
    [[nodiscard]] bool IsEventFigureEqualToSelectedFigure(const BoardCoordinates coordinates) const noexcept;
    [[nodiscard]] bool IsEventFigureMoveLegal(const BoardCoordinates coordinates) const noexcept;
    [[nodiscard]] bool IsEventFigureMovable(const BoardCoordinates board_coordinates) const noexcept;
    [[nodiscard]] bool IsEventFigureRightColour() const noexcept;
    [[nodiscard]] bool IsEventFigureColourEqualToCurrentPlayerColour() const noexcept;

    [[nodiscard]] bool IsOnCanvas(const BoardCoordinates coordinates) const noexcept;
    [[nodiscard]] bool IsOnCanvas(sf::Vector2f coordinates) const noexcept;


	/*-------------------------------------------------------------------------------------------------------------*/
    /*                                              GETTERS                                                        */
    /*-------------------------------------------------------------------------------------------------------------*/

    [[nodiscard]] BoardCoordinates GetBoardCoordinatesFromSfVector(const sf::Vector2f coordinates) const noexcept;
    [[nodiscard]] sf::Vector2f GetSfVectorFromBoardCoordinates(const BoardCoordinates coordinates) const noexcept;

    [[nodiscard]] sf::Vector2f GetMouseButtonVectorCoordinates(const sf::Event& mouse_event) const noexcept;
    [[nodiscard]] sf::Vector2f GetMouseMoveVectorCoordinates(const sf::Event& mouse_event) const noexcept;

    [[nodiscard]] BoardCoordinates GetMouseButtonBoardCoordinates(const sf::Event& mouse_event) const noexcept;
    [[nodiscard]] BoardCoordinates GetMouseMoveBoardCoordinates(const sf::Event& mouse_event) const noexcept;

    [[nodiscard]] const sf::Vector2f GetEventSpritePosition() const noexcept;
    [[nodiscard]] const sf::Vector2f GetEventSpriteOffset() const noexcept;

	/*-------------------------------------------------------------------------------------------------------------*/
	/*                                            MISCELLANEOUS                                                    */
	/*-------------------------------------------------------------------------------------------------------------*/

	void EnableDragging() noexcept;
	void DisableDragging() noexcept;

    void ManageEndOfMove() noexcept;
    void SetMoveMadeBoolean() noexcept;
    void ResetMoveMadeBoolean() noexcept;

    void ResetTemporaryValues() noexcept;

    void ManageEndOfGameIfGameIsOver() noexcept;
    void DisplayGameOverMessageBox() noexcept;

    /*-------------------------------------------------------------------------------------------------------------*/
    /*                                            CLASS MEMBERS                                                    */
    /*-------------------------------------------------------------------------------------------------------------*/

private:
    RomanChessGameEngine chess_engine_;
    RomanChessFigures figures_;

    //Pointer to figure modified by event handler functions
    std::shared_ptr<Figure> event_figure_ptr_;
    
    // Distance from top left corner of sprite to mouse position
    sf::Vector2f event_figure_offset_; 
    
    sf::Event canvas_event_;

    bool is_dragging_enabled_ = false;
    bool is_drawing_rectangles_enabled_ = false;
    bool is_move_made_ = false;

    std::vector<BoardCoordinates> yellow_rectangle_positions_;
    std::vector<BoardCoordinates> red_rectangle_positions_;

	sf::Texture board_texture_;
	sf::Texture figure_textures_;
    sf::Texture yellow_rectangle_texture_;
    sf::Texture red_rectangle_texture_;

    sf::Sprite board_sprite_;
    std::array<std::array<sf::Sprite, Constants::boardSize>, Constants::boardSize> yellow_rectangles_;
    std::array<std::array<sf::Sprite, Constants::boardSize>, Constants::boardSize> red_rectangles_;
};


