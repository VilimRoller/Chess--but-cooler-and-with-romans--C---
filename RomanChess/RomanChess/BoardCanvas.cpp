#include "BoardCanvas.h"
#include <cmath>
#include "Veles.h"

BoardCanvas::BoardCanvas(wxWindow* Parent,
    wxWindowID Id,
    wxPoint& Position,
    wxSize& Size,
    long Style) : wxSfmlCanvas(Parent, Id, Position, Size, Style) {
    SetBoardImage();
	LoadTextures();
	InitializeBoardSprite();
	InitializeRomanChessFigures(board_image);
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
    SetFigureEventSpritePtr(mouse_event);

}

void BoardCanvas::HandleMouseButtonReleasedEvent(sf::Event& mouse_event) {
    SetEventFigurePosition(mouse_event);
    DisableDragging();
    ResetEventFigurePtrPtr();
    ResetEventFigureOffset();

}

void BoardCanvas::HandleMouseMovedEvent(sf::Event& mouse_event) {
    if (IsDraggingEnabled()) {
        sf::Vector2f mouse_position(static_cast<float>(mouse_event.mouseMove.x),
                                    static_cast<float>(mouse_event.mouseMove.y));
        
        if (IsOnCanvas(mouse_position)) {
            MoveEventSprite(mouse_position);
        }
    }
}

void BoardCanvas::SetFigureEventSpritePtr(sf::Event& mouse_event) {
    auto x_coordinate = mouse_event.mouseButton.x / Constants::PixelMultiplier;
    auto y_coordinate = mouse_event.mouseButton.y / Constants::PixelMultiplier;

	sf::Vector2f mouse_vector_coordinates = sf::Vector2f(static_cast<float>(mouse_event.mouseButton.x),
		                                                 static_cast<float>(mouse_event.mouseButton.y));

    if (IsOnCanvas(x_coordinate, y_coordinate)) {
        event_figure_ptr_ = (figures_)[y_coordinate][x_coordinate];
        if (event_figure_ptr_ != nullptr) {
            sf::Vector2f event_figure_coordinates = event_figure_ptr_->GetFigureSprite()->getPosition();
            event_figure_offset_ = mouse_vector_coordinates - event_figure_coordinates;
        }
    }
}

void BoardCanvas::SetEventFigurePosition(sf::Event& mouse_event) {
    if (event_figure_ptr_ != nullptr) {
        int x_coordinate = mouse_event.mouseButton.x / Constants::PixelMultiplier;
        int y_coordinate = mouse_event.mouseButton.y / Constants::PixelMultiplier;

        if (figures_[y_coordinate][x_coordinate] != event_figure_ptr_) {
            figures_[y_coordinate][x_coordinate] = event_figure_ptr_;
            figures_[event_figure_ptr_->GetPosition().y][event_figure_ptr_->GetPosition().x] = nullptr;
			event_figure_ptr_->SetPosition(x_coordinate, y_coordinate);
        }
        
        event_figure_ptr_->SetFigureSpritePosition();
        
    }
}

