#pragma once
#include <array>
#include <memory>
#include "Constants.h"
#include "Figure.h"

struct BoardLayout {
    BoardLayout() {
        ResetBoardLayout();
    }
    void ResetBoardLayout() {
        for (auto& line : Elements) {
            for (auto& element : line) {
                element = nullptr;
            }
        }
    }
    std::array<std::array<std::shared_ptr<Figure>, Constants::boardSize>, Constants::boardSize> Elements;
};