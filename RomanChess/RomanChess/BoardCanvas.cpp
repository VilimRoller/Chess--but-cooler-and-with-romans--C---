#include "BoardCanvas.h"
#include "Veles.h"


BoardCanvas::BoardCanvas(wxWindow* Parent,
    wxWindowID Id,
    wxPoint& Position,
    wxSize& Size,
    long Style) : wxSfmlCanvas(Parent, Id, Position, Size, Style) {
}

void BoardCanvas::OnUpdate() {
    clear(sf::Color(128, 128, 128));
    DrawAllElements();
}

void BoardCanvas::DrawAllElements() {
    for (const auto& element : *sprites_) {
        draw(*element);
    }
}



