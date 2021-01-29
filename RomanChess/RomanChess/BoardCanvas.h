#pragma once
#include "wxSfmlCanvas.h"
#include <map>
#include <vector>
#include <array>
#include <utility>
#include "Figure.h"
#include "ID.h"
#include "Constants.h"
#include "BoardLayout.h"


class BoardCanvas final :
    public wxSfmlCanvas
{
public:
    BoardCanvas(wxWindow* Parent,
        wxWindowID Id,
        wxPoint& Position,
        wxSize& Size,
        long Style = 0);

    void InitializeFigures();
    void MakeFigureTexture(const FigureImage& image, const std::string& texture_path);
    void MakeFigureSprite(const spriteID& ID);

    void InitializeBoard();
    
    void InitializeLayoutPtr(const BoardLayout& layout) {
        layout_ptr = &layout;
    }

    void DrawAllElements();

    void DrawFigure(std::shared_ptr<Figure> figure);

protected:
    void OnUpdate() override;

private:
    sf::Texture board_texture_;
    sf::Sprite board_sprite_;
    
    std::map<FigureImage, std::shared_ptr<sf::Texture>> figure_textures_;
    std::map<spriteID, sf::Sprite> figure_sprites_;

    const BoardLayout* layout_ptr;
};

