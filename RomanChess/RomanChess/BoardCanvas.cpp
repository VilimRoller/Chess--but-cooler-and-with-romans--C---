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
}

void BoardCanvas::LoadTextures() {
	board_texture_.loadFromFile(ImagePaths::Board);
	figure_textures_.loadFromFile(ImagePaths::Figures);
}

void BoardCanvas::InitializeBoardSprite() {
	board_sprite_ = std::make_shared<sf::Sprite>();
	board_sprite_->setTexture(board_texture_);
}

void BoardCanvas::InitializeRomanChessFigures(const BoardImage& board_image) {
	for (int figure_pos_y = 0; figure_pos_y < Constants::boardSize; ++figure_pos_y) {
		for (int figure_pos_x = 0; figure_pos_x < Constants::boardSize; ++figure_pos_x) {
			SetFigure(board_image[figure_pos_y][figure_pos_x], BoardCoordinates(figure_pos_x, figure_pos_y));
		}
	}
}

void BoardCanvas::SetFigure(const FigureImage& figure, const BoardCoordinates& position) {

	switch (figure.first) {
	case figureType::Veles:
		figures_[position.y][position.x] = std::make_shared<Veles>(figure.second, position);
		break;
	case figureType::Hastatus:
		figures_[position.y][position.x] = std::make_shared<Hastatus>(figure.second, position);
		break;
	case figureType::Princeps:
		figures_[position.y][position.x] = std::make_shared<Princeps>(figure.second, position);
		break;
	case figureType::Triarius:
		figures_[position.y][position.x] = std::make_shared<Triarius>(figure.second, position);
		break;
	case figureType::Eques:
		figures_[position.y][position.x] = std::make_shared<Eques>(figure.second, position);
		break;
	case figureType::Consul:
		figures_[position.y][position.x] = std::make_shared<Consul>(figure.second, position);
		break;
	case figureType::PontifexMaximus:
		figures_[position.y][position.x] = std::make_shared<PontifexMaximus>(figure.second, position);
		break;
	default:
		figures_[position.y][position.x] = nullptr;
	}
	if (figures_[position.y][position.x] != nullptr) {
		figures_[position.y][position.x]->InitializeFigureSprite(figure_textures_);
	}
}

void BoardCanvas::OnUpdate() {
    HandleCanvasEvent();
    DrawSprites();
    
}

void BoardCanvas::DrawAllFigures() {
    for (const auto& row : figures_) {
        for (const auto& figure_ptr : row) {
            if (figure_ptr != nullptr) {
                draw(*(figure_ptr->GetFigureSprite()));
            }
        }
    }
}

void BoardCanvas::DrawBoard() {
    if (board_sprite_ != nullptr) {
        draw(*board_sprite_);
    }
}

void BoardCanvas::ClearCanvas() {
	clear(sf::Color(128, 128, 128));
}

void BoardCanvas::DrawSprites() {
	ClearCanvas();
	DrawBoard();
	DrawAllFigures();
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
    EnableDragging();
    SetEventFigureSpritePtr(mouse_event);
}

void BoardCanvas::HandleMouseButtonReleasedEvent(sf::Event& mouse_event) {
    SetEventFigurePosition(mouse_event);
    DisableDragging();
    ResetEventFigurePtr();
    ResetEventFigureOffset();
	RefreshBoardImage();
}

void BoardCanvas::HandleMouseMovedEvent(sf::Event& mouse_event) {
    if (IsDraggingEnabled()) {
		sf::Vector2f mouse_position = GetMouseVectorCoordinates(mouse_event.mouseMove.x, mouse_event.mouseMove.y);
        
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

inline bool BoardCanvas::IsDraggingEnabled() {
	return is_dragging_enabled_;
}

void BoardCanvas::SetEventFigureSpritePtr(sf::Event& mouse_event) {
    int x_coordinate = mouse_event.mouseButton.x / Constants::PixelMultiplier;
    int y_coordinate = mouse_event.mouseButton.y / Constants::PixelMultiplier;

	sf::Vector2f mouse_vector_coordinates = GetMouseVectorCoordinates(mouse_event.mouseButton.x, mouse_event.mouseButton.y);

    if(IsOnCanvas(x_coordinate, y_coordinate) && IsFigurePtrInitialized(figures_[y_coordinate][x_coordinate])) {
		SetEventFigurePtr(x_coordinate, y_coordinate);
        sf::Vector2f event_figure_coordinates = event_figure_ptr_->GetFigureSprite()->getPosition();
        event_figure_offset_ = mouse_vector_coordinates - event_figure_coordinates;
    }
}

inline void BoardCanvas::SetEventFigurePtr(const int x_coordinate, const int y_coordinate) {
	event_figure_ptr_ = figures_[y_coordinate][x_coordinate];
}

inline void BoardCanvas::ResetEventFigurePtr() {
	event_figure_ptr_ = nullptr;
}

inline void BoardCanvas::ResetEventFigureOffset() {
	event_figure_offset_ = sf::Vector2f(0, 0);
}

inline bool BoardCanvas::IsOnCanvas(const int x_coordinate, const int y_coordinate) const {
	return (x_coordinate < Constants::boardSize) && (y_coordinate < Constants::boardSize)
		&& (x_coordinate >= 0) && (y_coordinate >= 0);
}

inline bool BoardCanvas::IsOnCanvas(sf::Vector2f coordinates) {
	int x_coordinate = static_cast<int>(std::round(coordinates.x)) / Constants::PixelMultiplier;
	int y_coordinate = static_cast<int>(std::round(coordinates.y)) / Constants::PixelMultiplier;

	return IsOnCanvas(x_coordinate, y_coordinate);
}

void BoardCanvas::MoveEventSprite(const sf::Vector2f& mouse_position) {
	if (IsFigurePtrInitialized(event_figure_ptr_)) {
		sf::Vector2f current_position = event_figure_ptr_->GetFigureSprite()->getPosition();
		sf::Vector2f position_offset = mouse_position - current_position - event_figure_offset_;
		event_figure_ptr_->GetFigureSprite()->move(position_offset);
	}
}

void BoardCanvas::SetEventFigurePosition(sf::Event& mouse_event) {
    if (IsFigurePtrInitialized(event_figure_ptr_)) {
		auto mouse_coordinates = GetMouseIntegerCoordinates(std::make_pair(mouse_event.mouseButton.x, mouse_event.mouseButton.y));
		
		MoveEventFigure(mouse_coordinates.first, mouse_coordinates.second);
		CheckGameOver();
		NextPlayerTurn();
		RefreshEventFigureSpritePosition();
    }
}

inline bool BoardCanvas::IsFigurePtrInitialized(std::shared_ptr<Figure> figure_ptr) const{
	return figure_ptr != nullptr;
}

inline sf::Vector2f BoardCanvas::GetMouseVectorCoordinates(const int x_coordinate, const int y_coordinate) const {
	return sf::Vector2f(static_cast<float>(x_coordinate), static_cast<float>(y_coordinate));
}

std::pair<int, int> BoardCanvas::GetMouseIntegerCoordinates(const std::pair<int, int>& mouse_coordinates) const {
	std::pair<int, int> result;
	result.first  = mouse_coordinates.first / Constants::PixelMultiplier;
	result.second = mouse_coordinates.second/ Constants::PixelMultiplier;

	return result;
}

std::pair<int, int> BoardCanvas::GetOffsettedMouseIntegerCoordinates(const std::pair<int, int>& mouse_coordinates) const {
	std::pair<int, int> result;
	result.first = (mouse_coordinates.first - static_cast<int>(event_figure_offset_.x)) / Constants::PixelMultiplier;
	result.second = (mouse_coordinates.second - static_cast<int>(event_figure_offset_.x)) / Constants::PixelMultiplier;

	return result;
}


inline void BoardCanvas::RefreshBoardImage() {
	board_image_ = MakeBoardImage(figures_);
}

BoardImage BoardCanvas::MakeBoardImage(const RomanChessFigures& figures) {
	BoardImage result;

	for (int y_coordinate = 0; y_coordinate < Constants::boardSize; ++y_coordinate) {
		for (int x_coordinate = 0; x_coordinate < Constants::boardSize; ++x_coordinate) {
			if (IsFigurePtrInitialized(figures[y_coordinate][x_coordinate])) {
				result[y_coordinate][x_coordinate] = figures[y_coordinate][x_coordinate]->GetFigureImage();
			}
		}
	}
	return result;
}

inline figureColour BoardCanvas::GetPlayerTurnColour() const{
	return player_turn_;
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

void BoardCanvas::NextPlayerTurn() {
	player_turn_ = (player_turn_ == figureColour::Red ? figureColour::Purple : figureColour::Red);
}

inline bool BoardCanvas::IsGameOver() const {
	return is_game_over_;
}

std::pair<int, int> BoardCanvas::GetNumberOfConsuls() {
	std::pair<int, int> result(0, 0);
	for (const auto& line : figures_) {
		for (const auto& figure_ptr : line) {
			if (IsFigurePtrInitialized(figure_ptr)) {
				if (figure_ptr->GetType() == figureType::Consul) {
					if (figure_ptr->IsFigureRed()) {
						++result.first;
					}
					else if (figure_ptr->IsFigurePurple()) {
						++result.second;
					}
				}
			}
		}
	}
	return result;
}

bool BoardCanvas::BothSidesHaveConsul(const std::pair<int, int>& consuls) {
	return consuls.first && consuls.second;
}

void BoardCanvas::DisplayGameOverMessageBox() {
	player_turn_ == figureColour::Red? wxMessageBox(wxConstantStrings::GameOverWinnerRedMessage) :
									   wxMessageBox(wxConstantStrings::GameOverWinnerPurpleMessage);
}

bool BoardCanvas::IsEventFigureRightColour() const {
	if (IsFigurePtrInitialized(event_figure_ptr_)) {
		return event_figure_ptr_->GetFigureColour() == GetPlayerTurnColour();
	}
	return false;
}

inline void BoardCanvas::SetBoardImage(BoardImage new_image) {
	board_image_ = new_image;
}

void BoardCanvas::MoveEventFigure(const int x_coordinate, const int y_coordinate) {
	if (IsEventMovable(x_coordinate, y_coordinate)) {
		SetFigurePtr(x_coordinate, y_coordinate);
		ResetOldEventFigurePosition();
		SetEventFigurePosition(x_coordinate, y_coordinate);
	}
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

inline void BoardCanvas::SetFigurePtr(const int x_coordinate, const int y_coordinate) {
	figures_[y_coordinate][x_coordinate] = event_figure_ptr_;
}

inline void BoardCanvas::ResetOldEventFigurePosition() {
	figures_[event_figure_ptr_->GetPosition().y][event_figure_ptr_->GetPosition().x] = nullptr;
}

inline void BoardCanvas::RefreshEventFigureSpritePosition() {
	event_figure_ptr_->SetFigureSpritePosition();
}

inline void BoardCanvas::SetEventFigurePosition(const int x_coordinate, const int y_coordinate) {
	event_figure_ptr_->SetPosition(x_coordinate, y_coordinate);
}