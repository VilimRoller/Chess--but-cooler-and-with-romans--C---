#pragma once
#include "Figure.h"
#include "BoardCoordinates.h"

using FigureImage = std::pair<figureType, figureColour>;
using BoardImage = std::array<std::array<FigureImage, Constants::boardSize>, Constants::boardSize>;

namespace TestFunctions {

	inline FigureImage GetEmptyFigureImage() {
		return FigureImage(figureType::no_type, figureColour::no_colour);
	}

	inline BoardImage GetEmptyBoardImage() {
		BoardImage result;
		for (int row = 0; row < Constants::boardSize; ++row) {
			for (int collumn = 0; collumn < Constants::boardSize; ++collumn) {
				result[row][collumn] = GetEmptyFigureImage();
			}
		}
		return result;
	}

	inline void SetFigureImage(BoardImage& board, const FigureImage& figure, const BoardCoordinates& coordinates) {
		board[coordinates.y][coordinates.x] = figure;
	}

	inline void MakeMultipleFigureImages (FigureImage image, 
										  std::vector<BoardCoordinates> coordinates,
										  std::vector<std::pair<FigureImage, BoardCoordinates>>& result) {
		for (auto& position : coordinates) {
			result.emplace_back(std::make_pair(image, position));
		}
	}

	inline void SetMultipleFigureImages(BoardImage& board, const std::vector<std::pair<FigureImage, BoardCoordinates>>& figures) {
		for (auto figure : figures) {
			SetFigureImage(board, figure.first, figure.second);
		}
	}

}


/*
#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>

class Timer
{
public:
	void start()
	{
		m_StartTime = std::chrono::system_clock::now();
		m_bRunning = true;
	}

	void stop()
	{
		m_EndTime = std::chrono::system_clock::now();
		m_bRunning = false;
	}

	double elapsedMilliseconds()
	{
		std::chrono::time_point<std::chrono::system_clock> endTime;

		if (m_bRunning)
		{
			endTime = std::chrono::system_clock::now();
		}
		else
		{
			endTime = m_EndTime;
		}

		return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
	}

	double elapsedSeconds()
	{
		return elapsedMilliseconds() / 1000.0;
	}

private:
	std::chrono::time_point<std::chrono::system_clock> m_StartTime;
	std::chrono::time_point<std::chrono::system_clock> m_EndTime;
	bool                                               m_bRunning = false;
};
*/

