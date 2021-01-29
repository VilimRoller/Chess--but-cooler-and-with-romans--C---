#include "gtest/gtest.h"
#include "Eques.h"
#include "TestFunctions.h"

class EquesFigure : public ::testing::Test {
protected:
	void SetUp() override {
		test_board = TestFunctions::GetEmptyBoardImage();

		std::vector<std::pair<FigureImage, BoardCoordinates>> board_figures;
		std::vector<BoardCoordinates> red_figure_coordinates;
		std::vector<BoardCoordinates> purple_figure_coordinates;

		FigureImage red_eques_figure(figureType::Eques, figureColour::Red);
		FigureImage purple_eques_figure(figureType::Eques, figureColour::Purple);


		red_figure_coordinates.emplace_back(BoardCoordinates(1, 6));
		red_figure_coordinates.emplace_back(BoardCoordinates(3, 2));
		red_figure_coordinates.emplace_back(BoardCoordinates(4, 6));
		red_figure_coordinates.emplace_back(BoardCoordinates(4, 7));
		red_figure_coordinates.emplace_back(BoardCoordinates(5, 4));
		red_figure_coordinates.emplace_back(BoardCoordinates(6, 1));

		purple_figure_coordinates.emplace_back(BoardCoordinates(0, 3));
		purple_figure_coordinates.emplace_back(BoardCoordinates(1, 1));
		purple_figure_coordinates.emplace_back(BoardCoordinates(2, 4));
		purple_figure_coordinates.emplace_back(BoardCoordinates(4, 2));
		purple_figure_coordinates.emplace_back(BoardCoordinates(5, 0));
		purple_figure_coordinates.emplace_back(BoardCoordinates(6, 6));


		for (int i = 0; i < red_figure_coordinates.size(); ++i) {
			red_eques_figures.emplace_back(Eques(figureColour::Red));
			purple_eques_figures.emplace_back(Eques(figureColour::Purple));

			red_eques_figures[i].SetPosition(red_figure_coordinates[i]);
			purple_eques_figures[i].SetPosition(purple_figure_coordinates[i]);
		}

		TestFunctions::MakeMultipleFigureImages(red_eques_figure, red_figure_coordinates, board_figures);
		TestFunctions::MakeMultipleFigureImages(purple_eques_figure, purple_figure_coordinates, board_figures);
		TestFunctions::SetMultipleFigureImages(test_board, board_figures);

	}

	void TearDown() override {}
	BoardImage test_board;

	std::vector<Eques> red_eques_figures;
	std::vector<Eques> purple_eques_figures;
};

TEST_F(EquesFigure, NumberOfLegalMoves_Red) {
	EXPECT_EQ(red_eques_figures[0].GetLegalMoves(test_board).size(), 4);
	EXPECT_EQ(red_eques_figures[1].GetLegalMoves(test_board).size(), 8);
	EXPECT_EQ(red_eques_figures[2].GetLegalMoves(test_board).size(), 5);
	EXPECT_EQ(red_eques_figures[3].GetLegalMoves(test_board).size(), 4);
	EXPECT_EQ(red_eques_figures[4].GetLegalMoves(test_board).size(), 7);
	EXPECT_EQ(red_eques_figures[5].GetLegalMoves(test_board).size(), 4);
}

TEST_F(EquesFigure, NumberOfLegalMoves_Purple) {
	EXPECT_EQ(purple_eques_figures[0].GetLegalMoves(test_board).size(), 2);
	EXPECT_EQ(purple_eques_figures[1].GetLegalMoves(test_board).size(), 3);
	EXPECT_EQ(purple_eques_figures[2].GetLegalMoves(test_board).size(), 7);
	EXPECT_EQ(purple_eques_figures[3].GetLegalMoves(test_board).size(), 7);
	EXPECT_EQ(purple_eques_figures[4].GetLegalMoves(test_board).size(), 3);
	EXPECT_EQ(purple_eques_figures[5].GetLegalMoves(test_board).size(), 4);
}

//------------------------------------------------------------------------------------------------------------------------\\
//JUMPING OUT OF BOARD
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(EquesFigure, OutOfBoard_Left_Red) {
	EXPECT_FALSE(red_eques_figures[0].IsMoveLegal(BoardCoordinates(-1,7), test_board));
}

TEST_F(EquesFigure, Jump_OutOfBoard_Left_Purple) {
	EXPECT_FALSE(purple_eques_figures[0].IsMoveLegal(BoardCoordinates(-2, 2), test_board));
}

TEST_F(EquesFigure, Jump_OutOfBoard_Right_Red) {
	EXPECT_FALSE(red_eques_figures[5].IsMoveLegal(BoardCoordinates(8, 2), test_board));
}

TEST_F(EquesFigure, Jump_OutOfBoard_Right_Purple) {
	EXPECT_FALSE(purple_eques_figures[5].IsMoveLegal(BoardCoordinates(8, 7), test_board));
}

TEST_F(EquesFigure, Jump_OutOfBoard_Up_Red) {
	EXPECT_FALSE(red_eques_figures[5].IsMoveLegal(BoardCoordinates(5, -1), test_board));
}

TEST_F(EquesFigure, Jump_OutOfBoard_Up_Purple) {
	EXPECT_FALSE(purple_eques_figures[1].IsMoveLegal(BoardCoordinates(0, -1), test_board));
}

TEST_F(EquesFigure, Jump_OutOfBoard_Down_Red) {
	EXPECT_FALSE(red_eques_figures[3].IsMoveLegal(BoardCoordinates(5, 9), test_board));
}

TEST_F(EquesFigure, Jump_OutOfBoard_Down_Purple) {
	EXPECT_FALSE(purple_eques_figures[5].IsMoveLegal(BoardCoordinates(7, 8), test_board));
}

//------------------------------------------------------------------------------------------------------------------------\\
//JUMPING TO EMPTY
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(EquesFigure, Jump_Empty_Red) {
	EXPECT_TRUE(red_eques_figures[0].IsMoveLegal(BoardCoordinates(0, 4), test_board));
	EXPECT_TRUE(red_eques_figures[4].IsMoveLegal(BoardCoordinates(7, 3), test_board));
}

TEST_F(EquesFigure, Jump_Empty_Purple) {
	EXPECT_TRUE(purple_eques_figures[0].IsMoveLegal(BoardCoordinates(1, 5), test_board));
	EXPECT_TRUE(purple_eques_figures[5].IsMoveLegal(BoardCoordinates(7, 4), test_board));
}

TEST_F(EquesFigure, JumpOverFigure_Red) {
	EXPECT_TRUE(red_eques_figures[1].IsMoveLegal(BoardCoordinates(5, 1), test_board));
	EXPECT_TRUE(red_eques_figures[3].IsMoveLegal(BoardCoordinates(3, 5), test_board));
}

TEST_F(EquesFigure, JumpOverFigure_Purple) {
	EXPECT_TRUE(purple_eques_figures[3].IsMoveLegal(BoardCoordinates(2, 3), test_board));
}

//------------------------------------------------------------------------------------------------------------------------\\
//JUMPING TO ENEMY
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(EquesFigure, Jump_Enemy_Red) {
	EXPECT_TRUE(red_eques_figures[0].IsMoveLegal(BoardCoordinates(2, 4), test_board));
	EXPECT_TRUE(red_eques_figures[5].IsMoveLegal(BoardCoordinates(4, 2), test_board));
}

TEST_F(EquesFigure, Jump_Enemy_Purple) {
	EXPECT_TRUE(purple_eques_figures[1].IsMoveLegal(BoardCoordinates(3, 2), test_board));
	EXPECT_TRUE(purple_eques_figures[3].IsMoveLegal(BoardCoordinates(5, 4), test_board));
}

//------------------------------------------------------------------------------------------------------------------------\\
//JUMPING TO ALLY
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(EquesFigure, Jump_Ally_Red) {
	EXPECT_FALSE(red_eques_figures[4].IsMoveLegal(BoardCoordinates(4, 6), test_board));
}

TEST_F(EquesFigure, Jump_Ally_Purple) {
	EXPECT_FALSE(purple_eques_figures[0].IsMoveLegal(BoardCoordinates(1, 1), test_board));
}

