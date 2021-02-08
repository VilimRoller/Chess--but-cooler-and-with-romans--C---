#include "gtest/gtest.h"
#include "Consul.h"
#include "TestFunctions.h"

class ConsulFigure : public ::testing::Test {
protected:
	void SetUp() override {
		test_board = TestFunctions::GetEmptyBoardImage();

		std::vector<std::pair<FigureImage, BoardCoordinates>> board_figures;
		std::vector<BoardCoordinates> red_figure_coordinates;
		std::vector<BoardCoordinates> purple_figure_coordinates;

		FigureImage red_consul_figure(figureType::Consul, figureColour::Red);
		FigureImage purple_consul_figure(figureType::Consul, figureColour::Purple);

		red_figure_coordinates.emplace_back(BoardCoordinates(0, 4));
		red_figure_coordinates.emplace_back(BoardCoordinates(1, 1));
		red_figure_coordinates.emplace_back(BoardCoordinates(1, 6));
		red_figure_coordinates.emplace_back(BoardCoordinates(2, 6));
		red_figure_coordinates.emplace_back(BoardCoordinates(3, 4));
		red_figure_coordinates.emplace_back(BoardCoordinates(3, 6));
		red_figure_coordinates.emplace_back(BoardCoordinates(5, 7));

		purple_figure_coordinates.emplace_back(BoardCoordinates(1, 5));
		purple_figure_coordinates.emplace_back(BoardCoordinates(2, 4));
		purple_figure_coordinates.emplace_back(BoardCoordinates(2, 5));
		purple_figure_coordinates.emplace_back(BoardCoordinates(3, 7));
		purple_figure_coordinates.emplace_back(BoardCoordinates(4, 5));
		purple_figure_coordinates.emplace_back(BoardCoordinates(4, 6));
		purple_figure_coordinates.emplace_back(BoardCoordinates(5, 1));

		for (int i = 0; i < red_figure_coordinates.size(); ++i) {
			red_consul_figures.emplace_back(Consul(figureColour::Red));
			purple_consul_figures.emplace_back(Consul(figureColour::Purple));

			red_consul_figures[i].SetPosition(red_figure_coordinates[i]);
			purple_consul_figures[i].SetPosition(purple_figure_coordinates[i]);
		}

		TestFunctions::MakeMultipleFigureImages(red_consul_figure, red_figure_coordinates, board_figures);
		TestFunctions::MakeMultipleFigureImages(purple_consul_figure, purple_figure_coordinates, board_figures);
		TestFunctions::SetMultipleFigureImages(test_board, board_figures);
	}
	void TearDown() override {}
	BoardImage test_board;

	std::vector<Consul> red_consul_figures;
	std::vector<Consul> purple_consul_figures;
};

TEST_F(ConsulFigure, GetLegalMoves_Red) {
	EXPECT_EQ(red_consul_figures[0].GetLegalMoves(test_board).size(), 4);
	EXPECT_EQ(red_consul_figures[1].GetLegalMoves(test_board).size(), 8);
	EXPECT_EQ(red_consul_figures[2].GetLegalMoves(test_board).size(), 5);
	EXPECT_EQ(red_consul_figures[3].GetLegalMoves(test_board).size(), 3);
	EXPECT_EQ(red_consul_figures[4].GetLegalMoves(test_board).size(), 5);
	EXPECT_EQ(red_consul_figures[5].GetLegalMoves(test_board).size(), 3);
	EXPECT_EQ(red_consul_figures[6].GetLegalMoves(test_board).size(), 4);
}

TEST_F(ConsulFigure, GetLegalMoves_Purple) {
	EXPECT_EQ(purple_consul_figures[0].GetLegalMoves(test_board).size(), 3);
	EXPECT_EQ(purple_consul_figures[1].GetLegalMoves(test_board).size(), 5);
	EXPECT_EQ(purple_consul_figures[2].GetLegalMoves(test_board).size(), 2);
	EXPECT_EQ(purple_consul_figures[3].GetLegalMoves(test_board).size(), 2);
	EXPECT_EQ(purple_consul_figures[4].GetLegalMoves(test_board).size(), 5);
	EXPECT_EQ(purple_consul_figures[5].GetLegalMoves(test_board).size(), 4);
	EXPECT_EQ(purple_consul_figures[6].GetLegalMoves(test_board).size(), 8);
}