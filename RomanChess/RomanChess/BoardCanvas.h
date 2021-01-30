#pragma once
#include "wxSfmlCanvas.h"
#include <map>
#include <vector>
#include <array>
#include <utility>
#include "Figure.h"
#include "ID.h"
#include "Constants.h"



class BoardCanvas final :
    public wxSfmlCanvas
{
public:
    BoardCanvas(wxWindow* Parent,
        wxWindowID Id,
        wxPoint& Position,
        wxSize& Size,
        long Style = 0);

    void DrawAllElements();
    void SetSpritesVector(std::vector<std::shared_ptr<sf::Sprite>>& sprites_vector) {
        sprites_ = &sprites_vector;
    }

protected:
    void OnUpdate() override;

private:
    std::vector<std::shared_ptr<sf::Sprite>>* sprites_ = nullptr;

};

