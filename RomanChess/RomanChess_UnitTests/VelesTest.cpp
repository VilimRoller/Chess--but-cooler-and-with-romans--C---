#include "Veles.h"
#include "gtest/gtest.h"
#include "TestFunctions.h"

class VelesFigure : public ::testing::Test {
protected:
	void SetUp() override {
		test_board = TestFunctions::GetEmptyBoardImage();
		std::vector<std::pair<FigureImage, BoardCoordinates>> board_figures;
		std::vector<BoardCoordinates> red_figure_coordinates;
		std::vector<BoardCoordinates> purple_figure_coordinates;
		FigureImage red_veles_figure(figureType::Veles, figureColour::Red);
		FigureImage purple_veles_figure(figureType::Veles, figureColour::Purple);
		
		red_figure_coordinates.emplace_back(BoardCoordinates(0, 0));
		red_figure_coordinates.emplace_back(BoardCoordinates(1, 4));
		red_figure_coordinates.emplace_back(BoardCoordinates(2, 5));
		red_figure_coordinates.emplace_back(BoardCoordinates(3, 4));
		red_figure_coordinates.emplace_back(BoardCoordinates(5, 4));
		red_figure_coordinates.emplace_back(BoardCoordinates(7, 0));
		red_figure_coordinates.emplace_back(BoardCoordinates(7, 1));

		purple_figure_coordinates.emplace_back(BoardCoordinates(0, 7));
		purple_figure_coordinates.emplace_back(BoardCoordinates(1, 3));
		purple_figure_coordinates.emplace_back(BoardCoordinates(4, 3));
		purple_figure_coordinates.emplace_back(BoardCoordinates(5, 2));
		purple_figure_coordinates.emplace_back(BoardCoordinates(6, 3));
		purple_figure_coordinates.emplace_back(BoardCoordinates(7, 6));
		purple_figure_coordinates.emplace_back(BoardCoordinates(7, 7));

		for (int i = 0; i < red_figure_coordinates.size(); ++i) {
			red_veles_figures.emplace_back(Veles(figureColour::Red));
			purple_veles_figures.emplace_back(Veles(figureColour::Purple));

			red_veles_figures[i].SetPosition(red_figure_coordinates[i]);
			purple_veles_figures[i].SetPosition(purple_figure_coordinates[i]);
		}

		TestFunctions::MakeMultipleFigureImages(red_veles_figure, red_figure_coordinates, board_figures);
		TestFunctions::MakeMultipleFigureImages(purple_veles_figure, purple_figure_coordinates, board_figures);
		TestFunctions::SetMultipleFigureImages(test_board, board_figures);

	}
	void TearDown() override {}
	BoardImage test_board;
	std::vector<Veles> red_veles_figures;
	std::vector<Veles> purple_veles_figures;
};

TEST_F(VelesFigure, NumberOfLegalMoves_Red) {
	EXPECT_EQ(red_veles_figures[0].GetLegalMoves(test_board).size(), 0);
	EXPECT_EQ(red_veles_figures[1].GetLegalMoves(test_board).size(), 0);
	EXPECT_EQ(red_veles_figures[2].GetLegalMoves(test_board).size(), 1);
	EXPECT_EQ(red_veles_figures[3].GetLegalMoves(test_board).size(), 2);
	EXPECT_EQ(red_veles_figures[4].GetLegalMoves(test_board).size(), 3);
	EXPECT_EQ(red_veles_figures[5].GetLegalMoves(test_board).size(), 0);
	EXPECT_EQ(red_veles_figures[6].GetLegalMoves(test_board).size(), 0);
}

TEST_F(VelesFigure, NumberOfLegalMoves_Purple) {
	EXPECT_EQ(purple_veles_figures[0].GetLegalMoves(test_board).size(), 0);
	EXPECT_EQ(purple_veles_figures[1].GetLegalMoves(test_board).size(), 0);
	EXPECT_EQ(purple_veles_figures[2].GetLegalMoves(test_board).size(), 3);
	EXPECT_EQ(purple_veles_figures[3].GetLegalMoves(test_board).size(), 1);
	EXPECT_EQ(purple_veles_figures[4].GetLegalMoves(test_board).size(), 2);
	EXPECT_EQ(purple_veles_figures[5].GetLegalMoves(test_board).size(), 0);
	EXPECT_EQ(purple_veles_figures[6].GetLegalMoves(test_board).size(), 0);
}


TEST_F(VelesFigure, IsMoveLegal_StayingOnSamePlace_Red) {
	EXPECT_FALSE(red_veles_figures[0].IsMoveLegal(BoardCoordinates(0, 0), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_StayingOnSamePlace_Purple) {
	EXPECT_FALSE(purple_veles_figures[0].IsMoveLegal(BoardCoordinates(0, 7), test_board));
}

//------------------------------------------------------------------------------------------------------------------------\\
//MOVING FORWARD
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(VelesFigure, GetCoordinates_Front_Red) {
	EXPECT_EQ(red_veles_figures[0].MoveFront(), BoardCoordinates(0, -1));
	EXPECT_EQ(red_veles_figures[1].MoveFront(), BoardCoordinates(1, 3));
}

TEST_F(VelesFigure, GetCoordinates_Front_Purple) {
	EXPECT_EQ(purple_veles_figures[0].MoveFront(), BoardCoordinates(0, 8));
	EXPECT_EQ(purple_veles_figures[1].MoveFront(), BoardCoordinates(1, 4));
}

TEST_F(VelesFigure, IsMoveLegal_Front_OutOfBoard_Red) {
	EXPECT_FALSE(red_veles_figures[0].IsMoveLegal(red_veles_figures[0].MoveFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_Front_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_veles_figures[0].IsMoveLegal(purple_veles_figures[0].MoveFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_Front_Empty_Red) {
	EXPECT_TRUE(red_veles_figures[3].IsMoveLegal(red_veles_figures[3].MoveFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_Front_Empty_Purple) {
	EXPECT_TRUE(purple_veles_figures[2].IsMoveLegal(purple_veles_figures[2].MoveFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_Front_Enemy_Red) {
	EXPECT_FALSE(red_veles_figures[1].IsMoveLegal(red_veles_figures[1].MoveFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_Front_Enemy_Purple) {
	EXPECT_FALSE(purple_veles_figures[1].IsMoveLegal(purple_veles_figures[1].MoveFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_Front_Ally_Red) {
	EXPECT_FALSE(red_veles_figures[6].IsMoveLegal(red_veles_figures[6].MoveFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_Front_Ally_Purple) {
	EXPECT_FALSE(purple_veles_figures[5].IsMoveLegal(purple_veles_figures[5].MoveFront(), test_board));
}

//------------------------------------------------------------------------------------------------------------------------\\
//MOVING DIAGONAL LEFT
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(VelesFigure, GetCoordinates_DiagonalLeft_Red) {
	EXPECT_EQ(red_veles_figures[0].MoveDiagonalLeftFront(), BoardCoordinates(-1, -1));
	EXPECT_EQ(red_veles_figures[1].MoveDiagonalLeftFront(), BoardCoordinates(0, 3));
}

TEST_F(VelesFigure, GetCoordinates_DiagonalLeft_Purple) {
	EXPECT_EQ(purple_veles_figures[1].MoveDiagonalLeftFront(), BoardCoordinates(2, 4));
	EXPECT_EQ(purple_veles_figures[6].MoveDiagonalLeftFront(), BoardCoordinates(8, 8));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalLeft_OutOfBoard_Red) {
	EXPECT_FALSE(red_veles_figures[0].IsMoveLegal(red_veles_figures[0].MoveDiagonalLeftFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalLeft_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_veles_figures[0].IsMoveLegal(purple_veles_figures[0].MoveDiagonalLeftFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalLeft_Empty_Red) {
	EXPECT_FALSE(red_veles_figures[1].IsMoveLegal(red_veles_figures[1].MoveDiagonalLeftFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalLeft_Empty_Purple) {
	EXPECT_FALSE(purple_veles_figures[1].IsMoveLegal(purple_veles_figures[1].MoveDiagonalLeftFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalLeft_Enemy_Red) {
	EXPECT_TRUE(red_veles_figures[4].IsMoveLegal(red_veles_figures[4].MoveDiagonalLeftFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalLeft_Enemy_Purple) {
	EXPECT_TRUE(purple_veles_figures[2].IsMoveLegal(purple_veles_figures[2].MoveDiagonalLeftFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalLeft_Ally_Red) {
	EXPECT_FALSE(red_veles_figures[2].IsMoveLegal(red_veles_figures[2].MoveDiagonalLeftFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalLeft_Ally_Purple) {
	EXPECT_FALSE(purple_veles_figures[3].IsMoveLegal(purple_veles_figures[1].MoveDiagonalLeftFront(), test_board));
}


//------------------------------------------------------------------------------------------------------------------------\\
//MOVING DIAGONAL RIGHT
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(VelesFigure, GetCoordinates_DiagonalRight_Red) {
	EXPECT_EQ(red_veles_figures[0].MoveDiagonalRightFront(), BoardCoordinates(1, -1));
	EXPECT_EQ(red_veles_figures[5].MoveDiagonalRightFront(), BoardCoordinates(8, -1));
}

TEST_F(VelesFigure, GetCoordinates_DiagonalRight_Purple) {
	EXPECT_EQ(purple_veles_figures[0].MoveDiagonalRightFront(), BoardCoordinates(-1, 8));
	EXPECT_EQ(purple_veles_figures[2].MoveDiagonalRightFront(), BoardCoordinates(3, 4));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalRight_OutOfBoard_Red) {
	EXPECT_FALSE(red_veles_figures[0].IsMoveLegal(red_veles_figures[0].MoveDiagonalRightFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalRight_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_veles_figures[0].IsMoveLegal(purple_veles_figures[0].MoveDiagonalRightFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalRight_Empty_Red) {
	EXPECT_FALSE(red_veles_figures[1].IsMoveLegal(red_veles_figures[1].MoveDiagonalRightFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalRight_Empty_Purple) {
	EXPECT_FALSE(purple_veles_figures[1].IsMoveLegal(purple_veles_figures[1].MoveDiagonalRightFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalRight_Enemy_Red) {
	EXPECT_TRUE(red_veles_figures[3].IsMoveLegal(red_veles_figures[3].MoveDiagonalRightFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalRight_Enemy_Purple) {
	EXPECT_TRUE(purple_veles_figures[2].IsMoveLegal(purple_veles_figures[2].MoveDiagonalRightFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalRight_Ally_Red) {
	EXPECT_FALSE(red_veles_figures[2].IsMoveLegal(red_veles_figures[2].MoveDiagonalRightFront(), test_board));
}

TEST_F(VelesFigure, IsMoveLegal_DiagonalRight_Ally_Purple) {
	EXPECT_FALSE(purple_veles_figures[3].IsMoveLegal(purple_veles_figures[3].MoveDiagonalRightFront(), test_board));
}
