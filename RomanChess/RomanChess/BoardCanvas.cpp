#include "BoardCanvas.h"
#include "Veles.h"


BoardCanvas::BoardCanvas(wxWindow* Parent,
    wxWindowID Id,
    wxPoint& Position,
    wxSize& Size,
    long Style): wxSfmlCanvas(Parent, Id, Position, Size, Style) {
    InitializeBoard();

    InitializeFigures();
}

void BoardCanvas::InitializeFigures() {
    for (auto& texture : ImagePaths::FigureTextures) {
        MakeFigureTexture(texture.first, texture.second);
    }
}

void BoardCanvas::MakeFigureTexture(const FigureImage& image, const std::string& texture_path) {
    auto figure_texture = std::make_shared<sf::Texture>();
    figure_texture->loadFromFile(texture_path);
    figure_textures_.emplace(image, figure_texture);
}

void BoardCanvas::MakeFigureSprite(const spriteID& ID) {

    
}

void BoardCanvas::OnUpdate() {
    clear(sf::Color(128, 128, 128));
    DrawAllElements();
}

void BoardCanvas::InitializeBoard() {
    board_texture_.loadFromFile(ImagePaths::Board);

    //board_sprite_ = std::make_unique<sf::Sprite>();
    board_sprite_.setTexture(board_texture_);
}

void BoardCanvas::DrawAllElements() {
    draw(board_sprite_);
    
}

void BoardCanvas::DrawFigure(std::shared_ptr<Figure> figure) {

    


}


