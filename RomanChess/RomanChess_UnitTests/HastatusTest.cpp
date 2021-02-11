#include "gtest/gtest.h"
#include "Hastatus.h"
#include "TestFunctions.h"

//TESTING FEATURES ADDED AFTER VELES

class HastatusFigure : public ::testing::Test {
protected:
	void SetUp() override {
		test_board = TestFunctions::GetEmptyBoardImage();
		std::vector<std::pair<FigureImage, BoardCoordinates>> board_figures;
		std::vector<BoardCoordinates> red_figure_coordinates;
		std::vector<BoardCoordinates> purple_figure_coordinates;
		FigureImage red_hastatus_figure(figureType::Hastatus, figureColour::Red);
		FigureImage purple_hastatus_figure(figureType::Hastatus, figureColour::Purple);

		red_figure_coordinates.emplace_back(BoardCoordinates(0, 7));
		red_figure_coordinates.emplace_back(BoardCoordinates(2, 5));
		red_figure_coordinates.emplace_back(BoardCoordinates(3, 5));
		red_figure_coordinates.emplace_back(BoardCoordinates(4, 5));
		red_figure_coordinates.emplace_back(BoardCoordinates(4, 6));
		red_figure_coordinates.emplace_back(BoardCoordinates(6, 5));
		red_figure_coordinates.emplace_back(BoardCoordinates(6, 6));
		red_figure_coordinates.emplace_back(BoardCoordinates(7, 3));

		purple_figure_coordinates.emplace_back(BoardCoordinates(0, 0));
		purple_figure_coordinates.emplace_back(BoardCoordinates(2, 4));
		purple_figure_coordinates.emplace_back(BoardCoordinates(3, 3));
		purple_figure_coordinates.emplace_back(BoardCoordinates(4, 1));
		purple_figure_coordinates.emplace_back(BoardCoordinates(4, 2));
		purple_figure_coordinates.emplace_back(BoardCoordinates(6, 3));
		purple_figure_coordinates.emplace_back(BoardCoordinates(6, 4));
		purple_figure_coordinates.emplace_back(BoardCoordinates(7, 4));


		for (int i = 0; i < red_figure_coordinates.size(); ++i) {
			red_hastatus_figures.emplace_back(Hastatus(figureColour::Red));
			purple_hastatus_figures.emplace_back(Hastatus(figureColour::Purple));

			red_hastatus_figures[i].SetPosition(red_figure_coordinates[i]);
			purple_hastatus_figures[i].SetPosition(purple_figure_coordinates[i]);
		}

		TestFunctions::MakeMultipleFigureImages(red_hastatus_figure, red_figure_coordinates, board_figures);
		TestFunctions::MakeMultipleFigureImages(purple_hastatus_figure, purple_figure_coordinates, board_figures);
		TestFunctions::SetMultipleFigureImages(test_board, board_figures);

		for (int i = 0; i < red_figure_coordinates.size(); ++i) {
			red_hastatus_figures[i].CalculateLegalMoves(test_board);
			purple_hastatus_figures[i].CalculateLegalMoves(test_board);
		}
	}
	void TearDown() override {}
	BoardImage test_board;
	std::vector<Hastatus> red_hastatus_figures;
	std::vector<Hastatus> purple_hastatus_figures;
};

TEST_F(HastatusFigure, NumberOfLegalMoves_Red) {
	EXPECT_EQ(red_hastatus_figures[0].GetLegalMoves().size(), 2);
	EXPECT_EQ(red_hastatus_figures[1].GetLegalMoves().size(), 1);
	EXPECT_EQ(red_hastatus_figures[2].GetLegalMoves().size(), 3);
	EXPECT_EQ(red_hastatus_figures[3].GetLegalMoves().size(), 2);
	EXPECT_EQ(red_hastatus_figures[4].GetLegalMoves().size(), 1);
	EXPECT_EQ(red_hastatus_figures[5].GetLegalMoves().size(), 1);
	EXPECT_EQ(red_hastatus_figures[6].GetLegalMoves().size(), 1);
	EXPECT_EQ(red_hastatus_figures[7].GetLegalMoves().size(), 2);
}

TEST_F(HastatusFigure, NumberOfLegalMoves_Purple) {
	EXPECT_EQ(purple_hastatus_figures[0].GetLegalMoves().size(), 2);
	EXPECT_EQ(purple_hastatus_figures[1].GetLegalMoves().size(), 2);
	EXPECT_EQ(purple_hastatus_figures[2].GetLegalMoves().size(), 2);
	EXPECT_EQ(purple_hastatus_figures[3].GetLegalMoves().size(), 1);
	EXPECT_EQ(purple_hastatus_figures[4].GetLegalMoves().size(), 2);
	EXPECT_EQ(purple_hastatus_figures[5].GetLegalMoves().size(), 1);
	EXPECT_EQ(purple_hastatus_figures[6].GetLegalMoves().size(), 0);
	EXPECT_EQ(purple_hastatus_figures[7].GetLegalMoves().size(), 3);
}

//------------------------------------------------------------------------------------------------------------------------\\
//MOVING BACKWARD
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(HastatusFigure, GetCoordinates_Back_Red) {
	EXPECT_EQ(red_hastatus_figures[0].MoveBack(), BoardCoordinates(0, 8));
	EXPECT_EQ(red_hastatus_figures[1].MoveBack(), BoardCoordinates(2, 6));
}

TEST_F(HastatusFigure, GetCoordinates_Back_Purple) {
	EXPECT_EQ(purple_hastatus_figures[0].MoveBack(), BoardCoordinates(0, -1));
	EXPECT_EQ(purple_hastatus_figures[1].MoveBack(), BoardCoordinates(2, 3));
}

TEST_F(HastatusFigure, IsMoveLegal_Back_OutOfBoard_Red) {
	EXPECT_FALSE(red_hastatus_figures[0].IsMoveLegal(red_hastatus_figures[0].MoveBack(), test_board));
}

TEST_F(HastatusFigure, IsMoveLegal_Back_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_hastatus_figures[0].IsMoveLegal(purple_hastatus_figures[0].MoveBack(), test_board));
}

TEST_F(HastatusFigure, IsMoveLegal_Back_Empty_Red) {
	EXPECT_TRUE(red_hastatus_figures[1].IsMoveLegal(red_hastatus_figures[1].MoveBack(), test_board));
}

TEST_F(HastatusFigure, IsMoveLegal_Back_Empty_Purple) {
	EXPECT_TRUE(purple_hastatus_figures[1].IsMoveLegal(purple_hastatus_figures[1].MoveBack(), test_board));
}

TEST_F(HastatusFigure, IsMoveLegal_Back_Enemy_Red) {
	EXPECT_FALSE(red_hastatus_figures[7].IsMoveLegal(red_hastatus_figures[7].MoveBack(), test_board));
}

TEST_F(HastatusFigure, IsMoveLegal_Back_Enemy_Purple) {
	EXPECT_FALSE(purple_hastatus_figures[6].IsMoveLegal(purple_hastatus_figures[6].MoveBack(), test_board));
}

TEST_F(HastatusFigure, IsMoveLegal_Back_Ally_Red) {
	EXPECT_FALSE(red_hastatus_figures[5].IsMoveLegal(red_hastatus_figures[5].MoveBack(), test_board));
}

TEST_F(HastatusFigure, IsMoveLegal_Back_Ally_Purple) {
	EXPECT_FALSE(purple_hastatus_figures[7].IsMoveLegal(purple_hastatus_figures[7].MoveBack(), test_board));
}

//------------------------------------------------------------------------------------------------------------------------\\
//MOVING DOUBLE FRONT
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(HastatusFigure, GetCoordinates_DoubleFront_Red) {
	EXPECT_EQ(red_hastatus_figures[0].MoveFront(2), BoardCoordinates(0, 5));
}

TEST_F(HastatusFigure, GetCoordinates_DoubleFront_Purple) {
	EXPECT_EQ(purple_hastatus_figures[0].MoveFront(2), BoardCoordinates(0, 2));
}

TEST_F(HastatusFigure, IsMoveLegal_DoubleFront_SkipOverEnemy_Red) {
	EXPECT_FALSE(red_hastatus_figures[1].IsMoveLegal(red_hastatus_figures[1].MoveFront(2), test_board));
}

TEST_F(HastatusFigure, IsMoveLegal_DoubleFront_SkipOverEnemy_Purple) {
	EXPECT_FALSE(purple_hastatus_figures[1].IsMoveLegal(purple_hastatus_figures[1].MoveFront(2), test_board));
}

TEST_F(HastatusFigure, IsMoveLegal_DoubleFront_SkipOverAlly_Red) {
	EXPECT_FALSE(red_hastatus_figures[4].IsMoveLegal(red_hastatus_figures[4].MoveFront(2), test_board));
}

TEST_F(HastatusFigure, IsMoveLegal_DoubleFront_SkipOverAlly_Purple) {
	EXPECT_FALSE(purple_hastatus_figures[3].IsMoveLegal(purple_hastatus_figures[3].MoveFront(2), test_board));
}

