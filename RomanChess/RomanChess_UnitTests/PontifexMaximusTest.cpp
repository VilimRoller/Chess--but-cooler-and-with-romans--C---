#include "gtest/gtest.h"
#include "PontifexMaximus.h"
#include "TestFunctions.h"

class PontifexMaximusFigure : public ::testing::Test {
protected:
	void SetUp() override {
		test_board = TestFunctions::GetEmptyBoardImage();

		std::vector<std::pair<FigureImage, BoardCoordinates>> board_figures;
		std::vector<BoardCoordinates> red_figure_coordinates;
		std::vector<BoardCoordinates> purple_figure_coordinates;

		FigureImage red_pontifex_maximus_figure(figureType::PontifexMaximus, figureColour::Red);
		FigureImage purple_pontifex_maximus_figure(figureType::PontifexMaximus, figureColour::Purple);

		red_figure_coordinates.emplace_back(BoardCoordinates(2, 5));
		red_figure_coordinates.emplace_back(BoardCoordinates(3, 5));
		red_figure_coordinates.emplace_back(BoardCoordinates(3, 6));
		red_figure_coordinates.emplace_back(BoardCoordinates(4, 7));
		red_figure_coordinates.emplace_back(BoardCoordinates(5, 7));
		red_figure_coordinates.emplace_back(BoardCoordinates(6, 5));
		red_figure_coordinates.emplace_back(BoardCoordinates(7, 7));

		purple_figure_coordinates.emplace_back(BoardCoordinates(1, 4));
		purple_figure_coordinates.emplace_back(BoardCoordinates(2, 6));
		purple_figure_coordinates.emplace_back(BoardCoordinates(2, 7));
		purple_figure_coordinates.emplace_back(BoardCoordinates(4, 4));
		purple_figure_coordinates.emplace_back(BoardCoordinates(4, 6));
		purple_figure_coordinates.emplace_back(BoardCoordinates(5, 5));
		purple_figure_coordinates.emplace_back(BoardCoordinates(6, 6));

		for (int i = 0; i < red_figure_coordinates.size(); ++i) {
			red_pontifex_maximus_figures.emplace_back(PontifexMaximus(figureColour::Red));
			purple_pontifex_maximus_figures.emplace_back(PontifexMaximus(figureColour::Purple));

			red_pontifex_maximus_figures[i].SetPosition(red_figure_coordinates[i]);
			purple_pontifex_maximus_figures[i].SetPosition(purple_figure_coordinates[i]);
		}
		TestFunctions::MakeMultipleFigureImages(red_pontifex_maximus_figure, red_figure_coordinates, board_figures);
		TestFunctions::MakeMultipleFigureImages(purple_pontifex_maximus_figure, purple_figure_coordinates, board_figures);
		TestFunctions::SetMultipleFigureImages(test_board, board_figures);
	}
	void TearDown() override {}
	BoardImage test_board;

	std::vector<PontifexMaximus> red_pontifex_maximus_figures;
	std::vector<PontifexMaximus> purple_pontifex_maximus_figures;
};

TEST_F(PontifexMaximusFigure, GetLegalMoves_Red) {
	EXPECT_EQ(red_pontifex_maximus_figures[0].GetLegalMoves(test_board).size(), 6);
	EXPECT_EQ(red_pontifex_maximus_figures[1].GetLegalMoves(test_board).size(), 6);
	EXPECT_EQ(red_pontifex_maximus_figures[2].GetLegalMoves(test_board).size(), 5);
	EXPECT_EQ(red_pontifex_maximus_figures[3].GetLegalMoves(test_board).size(), 3);
	EXPECT_EQ(red_pontifex_maximus_figures[4].GetLegalMoves(test_board).size(), 4);
	EXPECT_EQ(red_pontifex_maximus_figures[5].GetLegalMoves(test_board).size(), 8);
	EXPECT_EQ(red_pontifex_maximus_figures[6].GetLegalMoves(test_board).size(), 3);
}


TEST_F(PontifexMaximusFigure, GetLegalMoves_Purple) {
	EXPECT_EQ(purple_pontifex_maximus_figures[0].GetLegalMoves(test_board).size(), 8);
	EXPECT_EQ(purple_pontifex_maximus_figures[1].GetLegalMoves(test_board).size(), 7);
	EXPECT_EQ(purple_pontifex_maximus_figures[2].GetLegalMoves(test_board).size(), 4);
	EXPECT_EQ(purple_pontifex_maximus_figures[3].GetLegalMoves(test_board).size(), 7);
	EXPECT_EQ(purple_pontifex_maximus_figures[4].GetLegalMoves(test_board).size(), 7);
	EXPECT_EQ(purple_pontifex_maximus_figures[5].GetLegalMoves(test_board).size(), 5);
	EXPECT_EQ(purple_pontifex_maximus_figures[6].GetLegalMoves(test_board).size(), 7);

}