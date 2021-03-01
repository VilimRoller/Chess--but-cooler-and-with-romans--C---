#include "BoardCanvas.h"
#include <cmath>
#include "Veles.h"
#include "wxConstants.h"

BoardCanvas::BoardCanvas(wxWindow* Parent,
    wxWindowID Id,
    wxPoint& Position,
    wxSize& Size,
    long Style) : wxSfmlCanvas(Parent, Id, Position, Size, Style) {
	LoadTextures();
	InitializeBoardSprite();
	InitializeRomanChessFigures();
	InitializeRectangleSprites();
}

	/*-------------------------------------------------------------------------------------------------------------*/
	/*                                              INITIALIZATION                                                 */
	/*-------------------------------------------------------------------------------------------------------------*/

#pragma region INITIALIZATION

void BoardCanvas::LoadTextures()  noexcept {
	board_texture_.loadFromFile(ImagePaths::Board);
	figure_textures_.loadFromFile(ImagePaths::Figures);
	yellow_rectangle_texture_.loadFromFile(ImagePaths::Yellow_Rectangle);
	red_rectangle_texture_.loadFromFile(ImagePaths::Red_Rectangle);
}

void BoardCanvas::InitializeBoardSprite()  noexcept {
	board_sprite_.setTexture(board_texture_);
}

void BoardCanvas::InitializeRectangleSprites()  noexcept {
	for (int8 row = int8(0); row < Constants::boardSize; ++row)
		for (int8 collumn = int8(0); collumn < Constants::boardSize; ++collumn)
			SetRectangleSpriteTexturesAndPositions(BoardCoordinates(collumn, row));
}

inline void BoardCanvas::SetRectangleSpriteTexturesAndPositions(const BoardCoordinates coordinates) noexcept {
	SetRectangleSpriteTextures(coordinates);
	SetRectangleSpritePositions(coordinates);
}

inline void BoardCanvas::SetRectangleSpriteTextures(const BoardCoordinates coordinates)  noexcept {
	yellow_rectangles_[coordinates.y][coordinates.x].setTexture(yellow_rectangle_texture_);
	red_rectangles_[coordinates.y][coordinates.x].setTexture(red_rectangle_texture_);
}

inline void BoardCanvas::SetRectangleSpritePositions(const BoardCoordinates coordinates)  noexcept {
	yellow_rectangles_[coordinates.y][coordinates.x].setPosition(GetSfVectorFromBoardCoordinates(coordinates));

	red_rectangles_[coordinates.y][coordinates.x].setPosition(GetSfVectorFromBoardCoordinates(coordinates));
}

void BoardCanvas::InitializeRomanChessFigures()  noexcept {
	for (int8 row = int8(0); row < Constants::boardSize; ++row)
		for (int8 collumn = int8(0); collumn < Constants::boardSize; ++collumn)
			SetFigure(BoardCoordinates(collumn, row));
}

inline void BoardCanvas::SetFigure(BoardCoordinates position)  noexcept {
	CreateFigure(position);
	MakeFigureSprite(position);
}

inline void BoardCanvas::CreateFigure(BoardCoordinates position)  noexcept {
	auto figure_type = chess_engine_.GetBoardImage()[position.y][position.x].type;
	auto figure_colour = chess_engine_.GetBoardImage()[position.y][position.x].colour;
	auto& selected_figure = figures_[position.y][position.x];

	switch (figure_type) {
	case figureType::Veles:
		selected_figure = std::make_shared<Veles>(figure_colour, position);
		break;
	case figureType::Hastatus:
		selected_figure = std::make_shared<Hastatus>(figure_colour, position);
		break;
	case figureType::Princeps:
		selected_figure = std::make_shared<Princeps>(figure_colour, position);
		break;
	case figureType::Triarius:
		selected_figure = std::make_shared<Triarius>(figure_colour, position);
		break;
	case figureType::Eques:
		selected_figure = std::make_shared<Eques>(figure_colour, position);
		break;
	case figureType::Consul:
		selected_figure = std::make_shared<Consul>(figure_colour, position);
		break;
	case figureType::PontifexMaximus:
		selected_figure = std::make_shared<PontifexMaximus>(figure_colour, position);
		break;
	default:
		CreateEmptyFigure(selected_figure);
		break;
	}
}

inline void BoardCanvas::CreateEmptyFigure(std::shared_ptr<Figure>& figure)  noexcept {
	figure = nullptr;
}

inline void BoardCanvas::MakeFigureSprite(BoardCoordinates coordinates)  noexcept {
	if (IsFigureOnTile(coordinates))
		figures_[coordinates.y][coordinates.x]->InitializeFigureSprite(figure_textures_);
}

#pragma endregion

	/*-------------------------------------------------------------------------------------------------------------*/
	/*                                            RENDERING FUNCTIONS                                              */
	/*-------------------------------------------------------------------------------------------------------------*/

#pragma region RENDERING FUNCTIONS

void BoardCanvas::OnUpdate() {
	HandleCanvasEvent();
	DrawSprites();
}

inline void BoardCanvas::DrawSprites() noexcept {
	ClearCanvas();
	DrawBoard();
	DrawAllFigures();
	DrawRectanglesIfEnabled();
}

inline void BoardCanvas::ClearCanvas() noexcept {
	clear(sf::Color(128, 128, 128));
}

inline void BoardCanvas::DrawRectanglesIfEnabled() noexcept {
	if (is_drawing_rectangles_enabled_)
		DrawRectangles();
}

inline void BoardCanvas::DrawRectangles() noexcept {
	DrawYellowRectangles();
	DrawRedRectangles();
}

void BoardCanvas::DrawYellowRectangles() noexcept {
	for (const auto& coordinate : yellow_rectangle_positions_)
		draw(yellow_rectangles_[coordinate.y][coordinate.x]);
}

void BoardCanvas::DrawRedRectangles() noexcept {
	for (const auto& coordinate : red_rectangle_positions_)
		draw(red_rectangles_[coordinate.y][coordinate.x]);
}

void BoardCanvas::DrawAllFigures() noexcept {
    for (const auto& row : figures_)
        for (const auto& figure_ptr : row)
            if (IsFigureOnTile(figure_ptr))
				DrawFigure(figure_ptr);
}

inline void BoardCanvas::DrawFigure(const std::shared_ptr<Figure>& figure_ptr) noexcept {
	draw(figure_ptr->GetFigureSprite());
}

inline void BoardCanvas::DrawBoard() noexcept {
	draw(board_sprite_);
}

#pragma endregion

	/*-------------------------------------------------------------------------------------------------------------*/
	/*                                              HANDLING EVENTS                                                */
	/*-------------------------------------------------------------------------------------------------------------*/

#pragma region HANDLING EVENTS

void BoardCanvas::HandleCanvasEvent() noexcept {
	while (this->pollEvent(canvas_event_))
		HandleCanvasEventType(canvas_event_);
}

void BoardCanvas::HandleCanvasEventType(const sf::Event& mouse_event) noexcept {
	if (GameIsNotOver())
		switch (mouse_event.type) {
		case sf::Event::MouseButtonPressed:
			HandleMouseButtonPressedEvent(mouse_event);
			break;
		case sf::Event::MouseMoved:
			HandleMouseMovedIfDraggingEnabled(mouse_event);
			break;
		case sf::Event::MouseButtonReleased:
			HandleMouseButtonReleasedEvent(mouse_event);
			break;
		default:
			break;
		}
}

inline void BoardCanvas::HandleMouseButtonPressedEvent(const sf::Event& mouse_event) noexcept {
	EnableDragging();
	EnableDrawingRectangles();
	SetEventFigureIfEligible(mouse_event);
	SetRectangleCoordinates();
}

inline void BoardCanvas::HandleMouseMovedIfDraggingEnabled(const sf::Event& mouse_event) noexcept {
	if (is_dragging_enabled_)
		HandleMouseMovedEvent(mouse_event);
}

inline void BoardCanvas::HandleMouseMovedEvent(const sf::Event& mouse_event) noexcept {
	sf::Vector2f mouse_position = GetMouseMoveVectorCoordinates(mouse_event);
	if (IsOnCanvas(mouse_position))
		MoveEventFigureSpriteIfEligible(mouse_position);
}

inline void BoardCanvas::HandleMouseButtonReleasedEvent(const sf::Event& mouse_event) noexcept {
	SetEventFigurePositionIfEligible(mouse_event);
	if (is_move_made_)
		ManageEndOfMove();
	ManageEndOfGameIfGameIsOver();
    DisableDragging();
	ResetTemporaryValues();
}

#pragma endregion

	/*-------------------------------------------------------------------------------------------------------------*/
	/*											EVENT FIGURE FUNCTIONS                                             */
	/*-------------------------------------------------------------------------------------------------------------*/

#pragma region EVENT FIGURE FUNCTIONS

void BoardCanvas::SetEventFigureIfEligible(const sf::Event& mouse_event) noexcept {
	if (IsOnCanvas(GetMouseButtonBoardCoordinates(mouse_event)))
		if (IsFigureOnTile(GetMouseButtonBoardCoordinates(mouse_event)))
			SetEventFigure(mouse_event);
}

void BoardCanvas::SetEventFigure(const sf::Event& mouse_event) noexcept {
	SetEventFigurePtr(GetMouseButtonBoardCoordinates(mouse_event));
	SetEventFigureSpriteOffset(GetMouseButtonVectorCoordinates(mouse_event));
}

inline void BoardCanvas::SetEventFigurePtr(const BoardCoordinates coordinates) noexcept {
	event_figure_ptr_ = figures_[coordinates.y][coordinates.x];
}

inline void BoardCanvas::ResetEventFigurePtr() noexcept {
	event_figure_ptr_ = nullptr;
}

inline void BoardCanvas::SetEventFigureSpriteOffset(const sf::Vector2f& mouse_vector_coordinates) noexcept {
	event_figure_offset_ = mouse_vector_coordinates - GetEventSpritePosition();
}

inline void BoardCanvas::ResetEventFigureSpriteOffset() noexcept {
	event_figure_offset_ = sf::Vector2f(0, 0);
}

inline void BoardCanvas::MoveEventFigureSpriteIfEligible(const sf::Vector2f& mouse_position) noexcept {
	if (IsFigureOnTile(event_figure_ptr_))
		MoveEventFigureSprite(mouse_position);
}

inline void BoardCanvas::MoveEventFigureSprite(const sf::Vector2f& mouse_position) noexcept {
	sf::Vector2f position_offset = mouse_position - GetEventSpritePosition() - GetEventSpriteOffset();
	event_figure_ptr_->GetFigureSprite().move(position_offset);
}

inline void BoardCanvas::SetEventFigurePositionIfEligible(const sf::Event& mouse_event) noexcept {
	if (IsFigureOnTile(event_figure_ptr_))
		SetEventFigurePosition(mouse_event);
}

inline void BoardCanvas::SetEventFigurePosition(const sf::Event& mouse_event) noexcept {
	ManageMovingEventFigureIfEligible(GetMouseButtonBoardCoordinates(mouse_event));
	RefreshEventFigureSpritePosition();
}

inline void BoardCanvas::ManageMovingEventFigureIfEligible(const BoardCoordinates coordinates) noexcept {
	if (IsEventFigureMovable(coordinates))
		ManageMovingEventFigure(coordinates);
}

inline void BoardCanvas::ManageMovingEventFigure(const BoardCoordinates coordinates) noexcept {
	if (!chess_engine_.CheckIfPontifexMaximus(coordinates))
		MoveEventFigure(coordinates);
	else
		InitializeRomanChessFigures();
}

inline void BoardCanvas::MoveEventFigure(const BoardCoordinates coordinates) noexcept {
	chess_engine_.CheckIfConsul(coordinates);

	chess_engine_.MoveFigure(event_figure_ptr_->GetPosition(), coordinates);
	SetFigurePtrToEventPtr(coordinates);
	ResetOldEventFigurePosition();
	SetEventFigureCoordinates(coordinates);

	SetMoveMadeBoolean();
}

inline void BoardCanvas::ResetOldEventFigurePosition() noexcept {
	figures_[event_figure_ptr_->GetPosition().y][event_figure_ptr_->GetPosition().x] = nullptr;
}

inline void BoardCanvas::SetEventFigureCoordinates(const BoardCoordinates coordinates) noexcept {
	event_figure_ptr_->SetPosition(coordinates);
}

inline void BoardCanvas::RefreshEventFigureSpritePosition() noexcept {
	event_figure_ptr_->SetFigureSpritePosition();
}

inline void BoardCanvas::SetFigurePtrToEventPtr(const BoardCoordinates coordinates) noexcept {
	figures_[coordinates.y][coordinates.x] = event_figure_ptr_;
}

#pragma endregion

	/*-------------------------------------------------------------------------------------------------------------*/
	/*											  RECTANGLE FUNCTIONS                                              */
	/*-------------------------------------------------------------------------------------------------------------*/

#pragma region RECTANGLE FUNCTIONS

void BoardCanvas::SetRectangleCoordinates() noexcept {
	chess_engine_.CalculateLegalMoves(event_figure_ptr_);
	auto var = chess_engine_.GetLegalMoves();
	for (const auto& coordinate : chess_engine_.GetLegalMoves())
		EmplaceRectangleCoordinate(coordinate);
}

inline void BoardCanvas::EmplaceRectangleCoordinate(const BoardCoordinates coordinate) noexcept {
	if (IsFigureOnTile(coordinate))
		red_rectangle_positions_.emplace_back(coordinate);

	else 
		yellow_rectangle_positions_.emplace_back(coordinate);
}

inline void BoardCanvas::ResetRectangleCoordinates() noexcept {
	DisableDrawingRectangles();
	ClearRectangleVectors();
}

inline void BoardCanvas::ClearRectangleVectors() noexcept {
	yellow_rectangle_positions_.clear();
	red_rectangle_positions_.clear();
}

inline void BoardCanvas::EnableDrawingRectangles() noexcept {
	is_drawing_rectangles_enabled_ = true;
}

inline void BoardCanvas::DisableDrawingRectangles() noexcept {
	is_drawing_rectangles_enabled_ = false;
}

inline bool BoardCanvas::GameIsNotOver() const noexcept {
	return !chess_engine_.IsGameOver();
}

#pragma endregion

	/*-------------------------------------------------------------------------------------------------------------*/
	/*											  BOOLEAN FUNCTIONS                                                */
	/*-------------------------------------------------------------------------------------------------------------*/

#pragma region BOOLEAN FUNCTIONS

inline bool BoardCanvas::IsFigureOnTile(BoardCoordinates coordinates) const noexcept {
	return figures_[coordinates.y][coordinates.x] != nullptr;
}

inline bool BoardCanvas::IsFigureOnTile(const std::shared_ptr<Figure>& figure) const noexcept {
	return figure != nullptr;
}

inline bool BoardCanvas::IsEventFigureEqualToSelectedFigure(const BoardCoordinates coordinates) const noexcept {
	return figures_[coordinates.y][coordinates.x] == event_figure_ptr_;
}

inline bool BoardCanvas::IsEventFigureMoveLegal(const BoardCoordinates coordinates) const noexcept {
	return chess_engine_.IsMoveLegal(coordinates);
}

bool BoardCanvas::IsEventFigureMovable(const BoardCoordinates board_coordinates) const noexcept {
	if (IsOnCanvas(board_coordinates))
		return !IsEventFigureEqualToSelectedFigure(board_coordinates) && 
				IsEventFigureRightColour() && 
				IsEventFigureMoveLegal(board_coordinates);
	else
		return false;
}

inline bool BoardCanvas::IsEventFigureRightColour() const noexcept {
	if (IsFigureOnTile(event_figure_ptr_))
		return IsEventFigureColourEqualToCurrentPlayerColour();
	else
		return false;
}

inline bool BoardCanvas::IsEventFigureColourEqualToCurrentPlayerColour() const noexcept {
	return event_figure_ptr_->GetFigureColour() == chess_engine_.GetPlayerTurn();
}

inline bool BoardCanvas::IsOnCanvas(const BoardCoordinates coordinates) const noexcept {
	return (coordinates.x < Constants::boardSize) && (coordinates.y < Constants::boardSize)
		&& (coordinates.x >= 0)					  && (coordinates.y >= 0);
}

inline bool BoardCanvas::IsOnCanvas(sf::Vector2f coordinates) const noexcept {
	return IsOnCanvas(GetBoardCoordinatesFromSfVector(coordinates));
}

#pragma endregion

	/*-------------------------------------------------------------------------------------------------------------*/
	/*												  GETTERS                                                      */
	/*-------------------------------------------------------------------------------------------------------------*/

#pragma region GETTERS

BoardCoordinates BoardCanvas::GetBoardCoordinatesFromSfVector(const sf::Vector2f coordinates) const noexcept {
	return BoardCoordinates(static_cast<int8>(std::round(coordinates.x) / Constants::PixelMultiplier_float),
							static_cast<int8>(std::round(coordinates.y) / Constants::PixelMultiplier_float));
}

inline sf::Vector2f BoardCanvas::GetSfVectorFromBoardCoordinates(const BoardCoordinates coordinates) const noexcept {
	return sf::Vector2f(static_cast<float>(coordinates.x) * Constants::PixelMultiplier_float,
						static_cast<float>(coordinates.y) * Constants::PixelMultiplier_float);
}

inline sf::Vector2f BoardCanvas::GetMouseButtonVectorCoordinates(const sf::Event& mouse_event) const noexcept {
	return sf::Vector2f(static_cast<float>(mouse_event.mouseButton.x),
						static_cast<float>(mouse_event.mouseButton.y));
}

sf::Vector2f BoardCanvas::GetMouseMoveVectorCoordinates(const sf::Event& mouse_event) const noexcept {
	return sf::Vector2f(static_cast<float>(mouse_event.mouseMove.x),
						static_cast<float>(mouse_event.mouseMove.y));
}

inline BoardCoordinates BoardCanvas::GetMouseButtonBoardCoordinates(const sf::Event& mouse_event) const noexcept {
	return BoardCoordinates(static_cast<int8>(static_cast<int16>(mouse_event.mouseButton.x) / Constants::PixelMultiplier),
							static_cast<int8>(static_cast<int16>(mouse_event.mouseButton.y) / Constants::PixelMultiplier));
}

inline BoardCoordinates BoardCanvas::GetMouseMoveBoardCoordinates(const sf::Event& mouse_event) const noexcept {
	return BoardCoordinates(static_cast<int8>(static_cast<int16>(mouse_event.mouseMove.x) / Constants::PixelMultiplier),
							static_cast<int8>(static_cast<int16>(mouse_event.mouseMove.y) / Constants::PixelMultiplier));
}

inline const sf::Vector2f BoardCanvas::GetEventSpritePosition() const noexcept {
	auto var = event_figure_ptr_->GetFigureSprite().getPosition();
	return event_figure_ptr_->GetFigureSprite().getPosition();
}

inline const sf::Vector2f BoardCanvas::GetEventSpriteOffset() const noexcept {
	return event_figure_offset_;
}

#pragma endregion

	/*-------------------------------------------------------------------------------------------------------------*/
	/*												MISCELLANEOUS                                                  */
	/*-------------------------------------------------------------------------------------------------------------*/

#pragma region MISCELLANEOUS

inline void BoardCanvas::EnableDragging() noexcept {
	is_dragging_enabled_ = true;
}

inline void BoardCanvas::DisableDragging() noexcept {
	is_dragging_enabled_ = false;
}

inline void BoardCanvas::ManageEndOfMove() noexcept {
	chess_engine_.SaveBoardImageToDeque();
	chess_engine_.NextPlayerTurn();
	ResetMoveMadeBoolean();
}

inline void BoardCanvas::SetMoveMadeBoolean() noexcept {
	is_move_made_ = true;
}

inline void BoardCanvas::ResetMoveMadeBoolean() noexcept {
	is_move_made_ = false;
}

inline void BoardCanvas::ResetTemporaryValues() noexcept {
	ResetEventFigurePtr();
	ResetEventFigureSpriteOffset();
	ResetRectangleCoordinates();
}

void BoardCanvas::ManageEndOfGameIfGameIsOver() noexcept {
	chess_engine_.CheckGameOver();
	if (chess_engine_.IsGameOver()) 
		DisplayGameOverMessageBox();
}

inline void BoardCanvas::DisplayGameOverMessageBox() noexcept {
	chess_engine_.GetPlayerTurn() == figureColour::Purple ? wxMessageBox(wxConstantStrings::GameOverWinnerRedMessage) :
		wxMessageBox(wxConstantStrings::GameOverWinnerPurpleMessage);
}

#pragma endregion
