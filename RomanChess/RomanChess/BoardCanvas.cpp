#include "BoardCanvas.h"
#include <cmath>
#include "Veles.h"
#include "wxConstants.h"

BoardCanvas::BoardCanvas(wxWindow* Parent,
    wxWindowID Id,
    wxPoint& Position,
    wxSize& Size,
    long Style) : wxSfmlCanvas(Parent, Id, Position, Size, Style) {
    SetBoardImage();
	LoadTextures();
	InitializeBoardSprite();
	InitializeRomanChessFigures(board_image_);
	InitializeRectangleSprites();
}

void BoardCanvas::LoadTextures() {
	board_texture_.loadFromFile(ImagePaths::Board);
	figure_textures_.loadFromFile(ImagePaths::Figures);
	yellow_rectangle_texture_.loadFromFile(ImagePaths::Yellow_Rectangle);
	red_rectangle_texture_.loadFromFile(ImagePaths::Red_Rectangle);
}

void BoardCanvas::InitializeBoardSprite() {
	board_sprite_.setTexture(board_texture_);
}

void BoardCanvas::InitializeRectangleSprites() {
	for (int row = 0; row < Constants::boardSize; ++row) {
		for (int collumn = 0; collumn < Constants::boardSize; ++collumn) {
			SetRectangleSpriteTexture(row, collumn);
			SetRectangleSpritePosition(row, collumn);
		}
	}
}

void BoardCanvas::SetRectangleSpriteTexture(const int row, const int collumn) {
	yellow_rectangles_[row][collumn].setTexture(yellow_rectangle_texture_);
	red_rectangles_[row][collumn].setTexture(red_rectangle_texture_);
}

void BoardCanvas::SetRectangleSpritePosition(const int row, const int collumn) {
	yellow_rectangles_[row][collumn].setPosition(GetVectorCoordinates(collumn * Constants::PixelMultiplier,
																	  row	  * Constants::PixelMultiplier));
	red_rectangles_[row][collumn].setPosition(GetVectorCoordinates(collumn * Constants::PixelMultiplier, 
																   row	   * Constants::PixelMultiplier));
}

void BoardCanvas::InitializeRomanChessFigures(const BoardImage& board_image) {
	for (int row = 0; row < Constants::boardSize; ++row) {
		for (int collumn = 0; collumn < Constants::boardSize; ++collumn) {
			SetFigure(board_image, BoardCoordinates(collumn, row));
		}
	}
}

void BoardCanvas::SetFigure(const BoardImage& board, const BoardCoordinates& position) {
	auto figure_type = board[position.y][position.x].first;
	auto figure_colour = board[position.y][position.x].second;
	auto* selected_figure = &figures_[position.y][position.x];

	switch (figure_type) {
	case figureType::Veles:
		*selected_figure = std::make_shared<Veles>(figure_colour, position);
		break;
	case figureType::Hastatus:
		*selected_figure = std::make_shared<Hastatus>(figure_colour, position);
		break;
	case figureType::Princeps:
		*selected_figure = std::make_shared<Princeps>(figure_colour, position);
		break;
	case figureType::Triarius:
		*selected_figure = std::make_shared<Triarius>(figure_colour, position);
		break;
	case figureType::Eques:
		*selected_figure = std::make_shared<Eques>(figure_colour, position);
		break;
	case figureType::Consul:
		*selected_figure = std::make_shared<Consul>(figure_colour, position);
		break;
	case figureType::PontifexMaximus:
		*selected_figure = std::make_shared<PontifexMaximus>(figure_colour, position);
		break;
	default:
		*selected_figure = nullptr;
	}
	InitializeLegalMoves(*selected_figure, board);
	MakeFigureSprite(*selected_figure);
}

inline void BoardCanvas::MakeFigureSprite(const std::shared_ptr<Figure>& figure) {
	if (IsFigureOnTile(figure)) {
		figure->InitializeFigureSprite(figure_textures_);
	}
}

inline void BoardCanvas::InitializeLegalMoves(const std::shared_ptr<Figure>& figure, const BoardImage& board) {
	if (IsFigureOnTile(figure)) {
		figure->RefreshLegalMoves(board);
	}
}

void BoardCanvas::OnUpdate() {
    HandleCanvasEvent();
    DrawSprites();
}

inline void BoardCanvas::DrawSprites() {
	ClearCanvas();
	DrawBoard();
	DrawAllFigures();
	DrawRectangles();
}

inline void BoardCanvas::ClearCanvas() {
	clear(sf::Color(128, 128, 128));
}

inline void BoardCanvas::DrawRectangles() {
	if (is_drawing_rectangles_enabled_) {
		DrawYellowRectangles();
		DrawRedRectangles();
	}
}

inline void BoardCanvas::DrawYellowRectangles() {
	for (const auto& coordinate : yellow_rectangle_positions_) {
		draw(yellow_rectangles_[coordinate.y][coordinate.x]);
	}
}

inline void BoardCanvas::DrawRedRectangles() {
	for (const auto& coordinate : red_rectangle_positions_) {
		draw(red_rectangles_[coordinate.y][coordinate.x]);
	}
}

inline void BoardCanvas::DrawAllFigures() {
    for (const auto& row : figures_) {
        for (const auto& figure_ptr : row) {
            if (IsFigureOnTile(figure_ptr)) {
                draw(figure_ptr->GetFigureSprite());
            }
        }
    }
}

inline void BoardCanvas::DrawBoard() {
        draw(board_sprite_);
}

void BoardCanvas::HandleCanvasEvent() {
    while (this->pollEvent(canvas_event_)) {
        switch (canvas_event_.type) {
        case sf::Event::MouseMoved:
            HandleMouseMovedEvent(canvas_event_);
            break;
        case sf::Event::MouseButtonPressed:
            HandleMouseButtonPressedEvent(canvas_event_);
            break;
        case sf::Event::MouseButtonReleased:
            HandleMouseButtonReleasedEvent(canvas_event_);
            break;
        }
    }
}

void BoardCanvas::HandleMouseButtonPressedEvent(sf::Event& mouse_event) {
	if (!IsGameOver()) {
		EnableDragging();
		SetEventFigureSpritePtr(mouse_event);
	}
}

void BoardCanvas::HandleMouseButtonReleasedEvent(sf::Event& mouse_event) {
    SetEventFigurePosition(mouse_event);
	RefreshBoardImage();
    DisableDragging();
    ResetEventFigurePtr();
    ResetEventFigureOffset();
	ResetRectangleCoordinates();
}

void BoardCanvas::HandleMouseMovedEvent(sf::Event& mouse_event) {
    if (is_dragging_enabled_) {
		sf::Vector2f mouse_position = GetVectorCoordinates(mouse_event.mouseMove.x, mouse_event.mouseMove.y);
        
        if (IsOnCanvas(mouse_position)) {
            MoveEventSprite(mouse_position);
        }
    }
}

inline void BoardCanvas::EnableDragging() {
	is_dragging_enabled_ = true;
}

inline void BoardCanvas::DisableDragging() {
	is_dragging_enabled_ = false;
}

inline void BoardCanvas::EnableDrawingRectangles() {
	is_drawing_rectangles_enabled_ = true;
}

inline void BoardCanvas::DisableDrawingRectangles() {
	is_drawing_rectangles_enabled_ = false;
}

void BoardCanvas::SetEventFigureSpritePtr(sf::Event& mouse_event) {
    int x_coordinate = mouse_event.mouseButton.x / Constants::PixelMultiplier;
    int y_coordinate = mouse_event.mouseButton.y / Constants::PixelMultiplier;
	sf::Vector2f mouse_vector_coordinates = GetVectorCoordinates(mouse_event.mouseButton.x, 
																 mouse_event.mouseButton.y);

    if(IsOnCanvas(x_coordinate, y_coordinate) && IsFigureOnTile(figures_[y_coordinate][x_coordinate])) {
		SetEventFigurePtr(x_coordinate, y_coordinate);
		SetEventFigureOffset(mouse_vector_coordinates);
		RefreshEventFigureLegalMoves();
		SetRectangleCoordinates(x_coordinate, y_coordinate);

    }
}

inline void BoardCanvas::SetEventFigurePtr(const int x_coordinate, const int y_coordinate) {
	event_figure_ptr_ = figures_[y_coordinate][x_coordinate];
}

inline void BoardCanvas::ResetEventFigurePtr() {
	event_figure_ptr_ = nullptr;
}

inline void BoardCanvas::SetEventFigureOffset(const sf::Vector2f& mouse_vector_coordinates) {
	sf::Vector2f event_figure_coordinates = event_figure_ptr_->GetFigureSprite().getPosition();
	event_figure_offset_ = mouse_vector_coordinates - event_figure_coordinates;
}

inline void BoardCanvas::ResetEventFigureOffset() {
	event_figure_offset_ = sf::Vector2f(0, 0);
}

void BoardCanvas::SetRectangleCoordinates(const int x_coordinate, const int y_coordinate) {
	EnableDrawingRectangles();
	RefreshBoardImage();
	std::vector<BoardCoordinates> all_rectangle_coordinates = figures_[y_coordinate][x_coordinate]->GetLegalMoves();

	for (const auto& coordinate : all_rectangle_coordinates) {
		EmplaceRectangleCoordinate(coordinate);
	}
}

inline void BoardCanvas::EmplaceRectangleCoordinate(const BoardCoordinates& coordinate) {
	if (IsFigureOnTile(figures_[coordinate.y][coordinate.x])) {
		red_rectangle_positions_.emplace_back(coordinate);
	}
	else {
		yellow_rectangle_positions_.emplace_back(coordinate);
	}
}

inline void BoardCanvas::ResetRectangleCoordinates() {
	DisableDrawingRectangles();
	ClearRectangleVectors();
}

inline void BoardCanvas::ClearRectangleVectors() {
	yellow_rectangle_positions_.clear();
	red_rectangle_positions_.clear();
}

inline bool BoardCanvas::IsOnCanvas(const int x_coordinate, const int y_coordinate) const {
	return (x_coordinate < Constants::boardSize) && (y_coordinate < Constants::boardSize)
		&& (x_coordinate >= 0) && (y_coordinate >= 0);
}

inline bool BoardCanvas::IsOnCanvas(sf::Vector2f coordinates) const {
	int x_coordinate = static_cast<int>(std::round(coordinates.x)) / Constants::PixelMultiplier;
	int y_coordinate = static_cast<int>(std::round(coordinates.y)) / Constants::PixelMultiplier;

	return IsOnCanvas(x_coordinate, y_coordinate);
}

void BoardCanvas::MoveEventSprite(const sf::Vector2f& mouse_position) {
	if (IsFigureOnTile(event_figure_ptr_)) {
		sf::Vector2f position_offset = mouse_position - GetEventSpritePosition() - GetEventSpriteOffset();
		event_figure_ptr_->GetFigureSprite().move(position_offset);
	}
}

inline const sf::Vector2f BoardCanvas::GetEventSpritePosition() const {
	return event_figure_ptr_->GetFigureSprite().getPosition();
}

inline const sf::Vector2f BoardCanvas::GetEventSpriteOffset() const {
	return event_figure_offset_;
}

void BoardCanvas::SetEventFigurePosition(sf::Event& mouse_event) {
    if (IsFigureOnTile(event_figure_ptr_)) {
		auto mouse_coordinates = GetMouseIntegerCoordinates(std::make_pair(mouse_event.mouseButton.x,
																		   mouse_event.mouseButton.y));
		
		MoveEventFigure(mouse_coordinates.first, mouse_coordinates.second);
		CheckGameOver();
		RefreshEventFigureSpritePosition();
    }
}

void BoardCanvas::MoveEventFigure(const int x_coordinate, const int y_coordinate) {
	if (IsEventMovable(x_coordinate, y_coordinate)) {
		if (!CheckIfPontifexMaximus(figures_[y_coordinate][x_coordinate])) {
			SetFigurePtr(x_coordinate, y_coordinate);
			ResetOldEventFigurePosition();
			SetEventFigureCoordinates(x_coordinate, y_coordinate);
		}
		SaveBoardImageToDeque();
		NextPlayerTurn();
	}
}

inline void BoardCanvas::SetFigurePtr(const int x_coordinate, const int y_coordinate) {
	figures_[y_coordinate][x_coordinate] = event_figure_ptr_;
}

inline void BoardCanvas::ResetOldEventFigurePosition() {
	figures_[event_figure_ptr_->GetPosition().y][event_figure_ptr_->GetPosition().x] = nullptr;
}

inline void BoardCanvas::SetEventFigureCoordinates(const int x_coordinate, const int y_coordinate) {
	event_figure_ptr_->SetPosition(x_coordinate, y_coordinate);
}

inline void BoardCanvas::RefreshEventFigureSpritePosition() {
	event_figure_ptr_->SetFigureSpritePosition();
}

inline void BoardCanvas::RefreshEventFigureLegalMoves() {
	if (IsFigureOnTile(event_figure_ptr_)) {
		event_figure_ptr_->RefreshLegalMoves(board_image_);
	}
}

inline sf::Vector2f BoardCanvas::GetVectorCoordinates(const int x_coordinate, const int y_coordinate) const {
	return sf::Vector2f(static_cast<float>(x_coordinate), static_cast<float>(y_coordinate));
}

std::pair<int, int> BoardCanvas::GetMouseIntegerCoordinates(const std::pair<int, int>& mouse_coordinates) const {
	std::pair<int, int> result;
	result.first = mouse_coordinates.first / Constants::PixelMultiplier;
	result.second = mouse_coordinates.second / Constants::PixelMultiplier;

	return result;
}

std::pair<int, int> BoardCanvas::GetOffsettedMouseIntegerCoordinates(const std::pair<int, int>& mouse_coordinates) const {
	std::pair<int, int> result;
	result.first = (mouse_coordinates.first - static_cast<int>(event_figure_offset_.x)) / Constants::PixelMultiplier;
	result.second = (mouse_coordinates.second - static_cast<int>(event_figure_offset_.x)) / Constants::PixelMultiplier;

	return result;
}

const BoardImage BoardCanvas::MakeBoardImage(const RomanChessFigures& figures) const {
	BoardImage result;

	for (int row = 0; row < Constants::boardSize; ++row) {
		for (int collumn = 0; collumn < Constants::boardSize; ++collumn) {
			if (IsFigureOnTile(figures[row][collumn])) {
				result[row][collumn] = figures[row][collumn]->GetFigureImage();
			}
		}
	}
	return result;
}

inline void BoardCanvas::SetBoardImage(BoardImage new_image) {
	board_image_ = new_image;
}

inline void BoardCanvas::RefreshBoardImage() {
	board_image_ = MakeBoardImage(figures_);
}

void BoardCanvas::SaveBoardImageToDeque() {
	board_image_deque_.emplace_back(MakeBoardImage(figures_));
	if (IsDequeOverflowed()) {
		board_image_deque_.pop_front();
	}
}

inline bool BoardCanvas::IsDequeOverflowed() const {
	return board_image_deque_.size() > Constants::dequeMovesNumber;
}

void BoardCanvas::NextPlayerTurn() {
	player_turn_ = (player_turn_ == figureColour::Red ? figureColour::Purple : figureColour::Red);
	++move_counter_;
}


void BoardCanvas::CheckGameOver() {
	auto number_of_consuls = GetNumberOfConsuls();
	if (!BothSidesHaveConsul(number_of_consuls)) {
		SetGameOver();
	}
}

inline void BoardCanvas::SetGameOver() {
	is_game_over_ = true;
	DisplayGameOverMessageBox();
}

inline void BoardCanvas::DisplayGameOverMessageBox() {
	player_turn_ == figureColour::Purple ? wxMessageBox(wxConstantStrings::GameOverWinnerRedMessage) :
		wxMessageBox(wxConstantStrings::GameOverWinnerPurpleMessage);
}

inline bool BoardCanvas::IsGameOver() const {
	return is_game_over_;
}

std::pair<int, int> BoardCanvas::GetNumberOfConsuls() {
	std::pair<int, int> result(0, 0);
	for (const auto& row : figures_) {
		for (const auto& figure_ptr : row) {
			if (IsFigureOnTile(figure_ptr)) {
				AddNumberOfConsuls(figure_ptr, result);
			}
		}
	}
	return result;
}

void BoardCanvas::AddNumberOfConsuls(const std::shared_ptr<Figure>& figure, std::pair<int, int>& consul_number) {
	if (figure->GetType() == figureType::Consul) {
		if (figure->IsFigureRed()) {
			++consul_number.first;
		}
		else if (figure->IsFigurePurple()) {
			++consul_number.second;
		}
	}
}

inline bool BoardCanvas::BothSidesHaveConsul(const std::pair<int, int>& consuls) const {
	return consuls.first && consuls.second;
}




inline void BoardCanvas::ClearBoardImageDeque() {
	board_image_deque_.clear();
}

bool BoardCanvas::CheckIfPontifexMaximus(const std::shared_ptr<Figure>& figure) {
	if (IsFigureOnTile(figure)) {
		if (figure->IsFigureType(figureType::PontifexMaximus)) {
			RewindBoard(figure->GetFigureColour());
			return true;
		}
	}
	return false;
}

void BoardCanvas::RemovePontifexMaximus(const figureColour& figure_colour) {
	for (auto& row : figures_) {
		for (auto& figure_ptr : row) {
			RemoveIfPontifexMaximus(figure_colour, figure_ptr);
		}
	}
}

inline void BoardCanvas::RemoveFigure(std::shared_ptr<Figure>& figure) {
	figure = nullptr;
}

inline void BoardCanvas::RemoveIfPontifexMaximus(const figureColour& figure_colour, std::shared_ptr<Figure>& figure) {
	if (IsFigureOnTile(figure)) {
		if (figure->IsFigureColour(figure_colour) && figure->IsFigureType(figureType::PontifexMaximus)) {
			RemoveFigure(figure);
		}
	}
}

void BoardCanvas::RewindBoard(const figureColour pontifex_colour) {
	InitializeRomanChessFigures(board_image_deque_[0]);
	RemovePontifexMaximus(pontifex_colour);
	ClearBoardImageDeque();
}


inline bool BoardCanvas::IsFigureOnTile(const std::shared_ptr<Figure>& figure_ptr) const {
	return figure_ptr != nullptr;
}

inline bool BoardCanvas::IsEventFigure(const int x_coordinate, const int y_coordinate) const {
	return figures_[y_coordinate][x_coordinate] == event_figure_ptr_;
}

inline bool BoardCanvas::IsEventMoveLegal(const int x_coordinate, const int y_coordinate) const {
	return event_figure_ptr_->IsMoveLegal(BoardCoordinates(x_coordinate, y_coordinate), board_image_);
}

bool BoardCanvas::IsEventMovable(const int x_coordinate, const int y_coordinate) const {
	if (IsOnCanvas(x_coordinate, y_coordinate)) {
		return !IsEventFigure(x_coordinate, y_coordinate) &&
				IsEventFigureRightColour() &&
				IsEventMoveLegal(x_coordinate, y_coordinate);
	}
	return false;
}

inline bool BoardCanvas::IsEventFigureRightColour() const {
	if (IsFigureOnTile(event_figure_ptr_)) {
		return event_figure_ptr_->GetFigureColour() == GetPlayerTurnColour();
	}
	return false;
}

inline const figureColour& BoardCanvas::GetPlayerTurnColour() const {
	return player_turn_;
}

