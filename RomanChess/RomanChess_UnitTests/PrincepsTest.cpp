#include "gtest/gtest.h"
#include "Princeps.h"
#include "TestFunctions.h"

class PrincepsFigure : public ::testing::Test {
protected:
	void SetUp() override {
		test_board1 = TestFunctions::GetEmptyBoardImage();
		test_board2 = TestFunctions::GetEmptyBoardImage();

		std::vector<std::pair<FigureImage, BoardCoordinates>> board_figures;
		std::vector<BoardCoordinates> red_figure_coordinates;
		std::vector<BoardCoordinates> purple_figure_coordinates;

		FigureImage red_princeps_figure(figureType::Princeps, figureColour::Red);
		FigureImage purple_princeps_figure(figureType::Princeps, figureColour::Purple);

		//First set; testing if figures go out of board and move left and right
		red_figure_coordinates.emplace_back(BoardCoordinates(0, 7));
		red_figure_coordinates.emplace_back(BoardCoordinates(1, 7));
		red_figure_coordinates.emplace_back(BoardCoordinates(2, 7));
		red_figure_coordinates.emplace_back(BoardCoordinates(3, 0));
		red_figure_coordinates.emplace_back(BoardCoordinates(4, 7));
		red_figure_coordinates.emplace_back(BoardCoordinates(7, 7));

		purple_figure_coordinates.emplace_back(BoardCoordinates(0, 0));
		purple_figure_coordinates.emplace_back(BoardCoordinates(1, 0));
		purple_figure_coordinates.emplace_back(BoardCoordinates(2, 0));
		purple_figure_coordinates.emplace_back(BoardCoordinates(3, 7));
		purple_figure_coordinates.emplace_back(BoardCoordinates(4, 0));
		purple_figure_coordinates.emplace_back(BoardCoordinates(7, 0));
	
		for (int i = 0; i < red_figure_coordinates.size(); ++i) {
			red_princeps_figures1.emplace_back(Princeps(figureColour::Red));
			purple_princeps_figures1.emplace_back(Princeps(figureColour::Purple));

			red_princeps_figures1[i].SetPosition(red_figure_coordinates[i]);
			purple_princeps_figures1[i].SetPosition(purple_figure_coordinates[i]);
		}

		TestFunctions::MakeMultipleFigureImages(red_princeps_figure, red_figure_coordinates, board_figures);
		TestFunctions::MakeMultipleFigureImages(purple_princeps_figure, purple_figure_coordinates, board_figures);
		TestFunctions::SetMultipleFigureImages(test_board1, board_figures);

		for (int i = 0; i < red_figure_coordinates.size(); ++i) {
			red_princeps_figures1[i].CalculateLegalMoves(test_board1);
			purple_princeps_figures1[i].CalculateLegalMoves(test_board1);
		}

		board_figures.clear();
		red_figure_coordinates.clear();
		purple_figure_coordinates.clear();

		//Second set; testing skipping over figures, moving to enemy and allied figures
		red_figure_coordinates.emplace_back(BoardCoordinates(0, 1));
		red_figure_coordinates.emplace_back(BoardCoordinates(0, 7));
		red_figure_coordinates.emplace_back(BoardCoordinates(3, 2));
		red_figure_coordinates.emplace_back(BoardCoordinates(3, 6));
		red_figure_coordinates.emplace_back(BoardCoordinates(4, 4));
		red_figure_coordinates.emplace_back(BoardCoordinates(5, 4));
		red_figure_coordinates.emplace_back(BoardCoordinates(6, 3));
		red_figure_coordinates.emplace_back(BoardCoordinates(6, 5));
		red_figure_coordinates.emplace_back(BoardCoordinates(6, 7));
		red_figure_coordinates.emplace_back(BoardCoordinates(7, 0));

		purple_figure_coordinates.emplace_back(BoardCoordinates(0, 0));
		purple_figure_coordinates.emplace_back(BoardCoordinates(1, 3));
		purple_figure_coordinates.emplace_back(BoardCoordinates(1, 5));
		purple_figure_coordinates.emplace_back(BoardCoordinates(1, 7));
		purple_figure_coordinates.emplace_back(BoardCoordinates(2, 4));
		purple_figure_coordinates.emplace_back(BoardCoordinates(3, 4));
		purple_figure_coordinates.emplace_back(BoardCoordinates(4, 2));
		purple_figure_coordinates.emplace_back(BoardCoordinates(4, 6));
		purple_figure_coordinates.emplace_back(BoardCoordinates(7, 1));
		purple_figure_coordinates.emplace_back(BoardCoordinates(7, 7));


		for (int i = 0; i < red_figure_coordinates.size(); ++i) {
			red_princeps_figures2.emplace_back(Princeps(figureColour::Red));
			purple_princeps_figures2.emplace_back(Princeps(figureColour::Purple));

			red_princeps_figures2[i].SetPosition(red_figure_coordinates[i]);
			purple_princeps_figures2[i].SetPosition(purple_figure_coordinates[i]);
		}

		TestFunctions::MakeMultipleFigureImages(red_princeps_figure, red_figure_coordinates, board_figures);
		TestFunctions::MakeMultipleFigureImages(purple_princeps_figure, purple_figure_coordinates, board_figures);
		TestFunctions::SetMultipleFigureImages(test_board2, board_figures);

		for (int i = 0; i < red_figure_coordinates.size(); ++i) {
			red_princeps_figures2[i].CalculateLegalMoves(test_board2);
			purple_princeps_figures2[i].CalculateLegalMoves(test_board2);
		}
	}
	void TearDown() override {}
	BoardImage test_board1; // testing moving out of map and left and right movement
	BoardImage test_board2; // testing diagonal movement

	std::vector<Princeps> red_princeps_figures1;
	std::vector<Princeps> purple_princeps_figures1;
	std::vector<Princeps> red_princeps_figures2;
	std::vector<Princeps> purple_princeps_figures2;
};

TEST_F(PrincepsFigure, NumberOfLegalMoves_Red) {
	EXPECT_EQ(red_princeps_figures2[4].GetLegalMoves().size(), 15);
	EXPECT_EQ(red_princeps_figures2[5].GetLegalMoves().size(), 5);
	EXPECT_EQ(red_princeps_figures2[6].GetLegalMoves().size(), 9);
}

TEST_F(PrincepsFigure, NumberOfLegalMoves_Purple) {
	EXPECT_EQ(purple_princeps_figures2[4].GetLegalMoves().size(), 5);
	EXPECT_EQ(purple_princeps_figures2[5].GetLegalMoves().size(), 15);
	EXPECT_EQ(purple_princeps_figures2[6].GetLegalMoves().size(), 11);
}

//------------------------------------------------------------------------------------------------------------------------\\
//MOVING LEFT
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(PrincepsFigure, GetCoordinates_Left_Red) {
	EXPECT_EQ(red_princeps_figures1[0].MoveLeft(), BoardCoordinates(-1, 7));
	EXPECT_EQ(red_princeps_figures1[5].MoveLeft(), BoardCoordinates(6, 7));
}

TEST_F(PrincepsFigure, GetCoordinates_Left_Purple) {
	EXPECT_EQ(purple_princeps_figures1[0].MoveLeft(), BoardCoordinates(1, 0));
	EXPECT_EQ(purple_princeps_figures1[5].MoveLeft(), BoardCoordinates(8, 0));
}

TEST_F(PrincepsFigure, IsMoveLegal_Left_Empty_Red) {
	EXPECT_TRUE(red_princeps_figures1[5].IsMoveLegal(red_princeps_figures1[5].MoveLeft(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Left_Empty_Purple) {
	EXPECT_TRUE(purple_princeps_figures1[4].IsMoveLegal(purple_princeps_figures1[4].MoveLeft(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Left_Enemy_Red) {
	EXPECT_FALSE(red_princeps_figures1[3].IsMoveLegal(red_princeps_figures1[3].MoveLeft(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Left_Enemy_Purple) {
	EXPECT_FALSE(purple_princeps_figures1[3].IsMoveLegal(purple_princeps_figures1[3].MoveLeft(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Left_Ally_Red) {
	EXPECT_FALSE(red_princeps_figures1[1].IsMoveLegal(red_princeps_figures1[5].MoveLeft(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Left_Ally_Purple) {
	EXPECT_FALSE(purple_princeps_figures1[1].IsMoveLegal(purple_princeps_figures1[4].MoveLeft(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Left_OutOfBoard_Red) {
	EXPECT_FALSE(red_princeps_figures1[0].IsMoveLegal(red_princeps_figures1[0].MoveLeft(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Left_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_princeps_figures1[5].IsMoveLegal(purple_princeps_figures1[5].MoveLeft(), test_board1));
}


//------------------------------------------------------------------------------------------------------------------------\\
//MOVING RIGHT
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(PrincepsFigure, GetCoordinates_Right_Red) {
	EXPECT_EQ(red_princeps_figures1[0].MoveRight(), BoardCoordinates(1, 7));
	EXPECT_EQ(red_princeps_figures1[5].MoveRight(), BoardCoordinates(8, 7));
}

TEST_F(PrincepsFigure, GetCoordinates_Right_Purple) {
	EXPECT_EQ(purple_princeps_figures1[0].MoveRight(), BoardCoordinates(-1, 0));
	EXPECT_EQ(purple_princeps_figures1[5].MoveRight(), BoardCoordinates(6, 0));
}

TEST_F(PrincepsFigure, IsMoveLegal_Right_Empty_Red) {
	EXPECT_TRUE(red_princeps_figures1[4].IsMoveLegal(red_princeps_figures1[4].MoveRight(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Right_Empty_Purple) {
	EXPECT_TRUE(purple_princeps_figures1[5].IsMoveLegal(purple_princeps_figures1[5].MoveRight(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Right_Enemy_Red) {
	EXPECT_FALSE(red_princeps_figures1[2].IsMoveLegal(red_princeps_figures1[2].MoveRight(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Right_Enemy_Purple) {
	EXPECT_FALSE(purple_princeps_figures1[4].IsMoveLegal(purple_princeps_figures1[4].MoveRight(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Right_Ally_Red) {
	EXPECT_FALSE(red_princeps_figures1[1].IsMoveLegal(red_princeps_figures1[1].MoveRight(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Right_Ally_Purple) {
	EXPECT_FALSE(purple_princeps_figures1[1].IsMoveLegal(purple_princeps_figures1[1].MoveRight(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Right_OutOfBoard_Red) {
	EXPECT_FALSE(red_princeps_figures1[5].IsMoveLegal(red_princeps_figures1[5].MoveRight(), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_Right_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_princeps_figures1[0].IsMoveLegal(purple_princeps_figures1[0].MoveRight(), test_board1));
}


//------------------------------------------------------------------------------------------------------------------------\\
//MOVING DIAGONAL LEFT FRONT
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftFront_OutOfBoard_Red) {
	EXPECT_FALSE(red_princeps_figures1[4].IsMoveLegal(red_princeps_figures1[4].MoveDiagonalLeftFront(5), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftFront_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_princeps_figures1[4].IsMoveLegal(purple_princeps_figures1[4].MoveDiagonalLeftFront(5), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftFront_Empty_Red) {
	EXPECT_TRUE(red_princeps_figures1[4].IsMoveLegal(red_princeps_figures1[4].MoveDiagonalLeftFront(3), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftFront_Empty_Purple) {
	EXPECT_TRUE(purple_princeps_figures1[4].IsMoveLegal(purple_princeps_figures1[4].MoveDiagonalLeftFront(3), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftFront_Enemy_Red) {
	EXPECT_TRUE(red_princeps_figures2[4].IsMoveLegal(red_princeps_figures2[4].MoveDiagonalLeftFront(4), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftFront_Enemy_Purple) {
	EXPECT_TRUE(purple_princeps_figures2[5].IsMoveLegal(purple_princeps_figures2[5].MoveDiagonalLeftFront(3), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftFront_Ally_Red) {
	EXPECT_FALSE(red_princeps_figures2[5].IsMoveLegal(red_princeps_figures2[4].MoveDiagonalLeftFront(2), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftFront_Ally_Purple) {
	EXPECT_FALSE(purple_princeps_figures2[4].IsMoveLegal(purple_princeps_figures2[5].MoveDiagonalLeftFront(2), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftFront_SkippingOverFigures_Red) {
	EXPECT_FALSE(red_princeps_figures2[5].IsMoveLegal(red_princeps_figures2[5].MoveDiagonalLeftFront(3), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftFront_SkippingOverFigures_Purple) {
	EXPECT_FALSE(purple_princeps_figures2[4].IsMoveLegal(purple_princeps_figures2[4].MoveDiagonalLeftFront(3), test_board2));
}


//------------------------------------------------------------------------------------------------------------------------\\
//MOVING DIAGONAL RIGHT FRONT
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightFront_OutOfBoard_Red) {
	EXPECT_FALSE(red_princeps_figures1[4].IsMoveLegal(red_princeps_figures1[4].MoveDiagonalRightFront(5), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightFront_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_princeps_figures1[4].IsMoveLegal(purple_princeps_figures1[4].MoveDiagonalRightFront(5), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightFront_Empty_Red) {
EXPECT_TRUE(red_princeps_figures1[4].IsMoveLegal(red_princeps_figures1[4].MoveDiagonalRightFront(3), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightFront_Empty_Purple) {
	EXPECT_TRUE(purple_princeps_figures1[4].IsMoveLegal(purple_princeps_figures1[4].MoveDiagonalRightFront(3), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightFront_Enemy_Red) {
	EXPECT_TRUE(red_princeps_figures2[4].IsMoveLegal(red_princeps_figures2[4].MoveDiagonalRightFront(3), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightFront_Enemy_Purple) {
	EXPECT_TRUE(purple_princeps_figures2[5].IsMoveLegal(purple_princeps_figures2[5].MoveDiagonalRightFront(3), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightFront_Ally_Red) {
	EXPECT_FALSE(red_princeps_figures2[5].IsMoveLegal(red_princeps_figures2[5].MoveDiagonalRightFront(1), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightFront_Ally_Purple) {
	EXPECT_FALSE(purple_princeps_figures2[4].IsMoveLegal(purple_princeps_figures2[4].MoveDiagonalRightFront(1), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightFront_SkippingOverFigures_Red) {
	EXPECT_FALSE(red_princeps_figures2[5].IsMoveLegal(red_princeps_figures2[5].MoveDiagonalRightFront(2), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightFront_SkippingOverFigures_Purple) {
	EXPECT_FALSE(purple_princeps_figures2[4].IsMoveLegal(purple_princeps_figures2[4].MoveDiagonalRightFront(2), test_board2));
}


//------------------------------------------------------------------------------------------------------------------------\\
//MOVING DIAGONAL LEFT BACK
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftBack_OutOfBoard_Red) {
	EXPECT_FALSE(red_princeps_figures1[3].IsMoveLegal(red_princeps_figures1[3].MoveDiagonalLeftBack(5), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftBack_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_princeps_figures1[3].IsMoveLegal(purple_princeps_figures1[3].MoveDiagonalLeftBack(5), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftBack_Empty_Red) {
EXPECT_TRUE(red_princeps_figures1[3].IsMoveLegal(red_princeps_figures1[3].MoveDiagonalLeftBack(3), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftBack_Empty_Purple) {
	EXPECT_TRUE(purple_princeps_figures1[3].IsMoveLegal(purple_princeps_figures1[3].MoveDiagonalLeftBack(3), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftBack_Enemy_Red) {
	EXPECT_TRUE(red_princeps_figures2[4].IsMoveLegal(red_princeps_figures2[4].MoveDiagonalLeftBack(3), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftBack_Enemy_Purple) {
	EXPECT_TRUE(purple_princeps_figures2[5].IsMoveLegal(purple_princeps_figures2[5].MoveDiagonalLeftBack(4), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftBack_Ally_Red) {
	EXPECT_FALSE(red_princeps_figures2[5].IsMoveLegal(red_princeps_figures2[5].MoveDiagonalLeftBack(2), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftBack_Ally_Purple) {
	EXPECT_FALSE(purple_princeps_figures2[4].IsMoveLegal(purple_princeps_figures2[4].MoveDiagonalLeftBack(2), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftBack_SkippingOverFigures_Red) {
	EXPECT_FALSE(red_princeps_figures2[5].IsMoveLegal(red_princeps_figures2[5].MoveDiagonalLeftBack(3), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalLeftBack_SkippingOverFigures_Purple) {
	EXPECT_FALSE(purple_princeps_figures2[4].IsMoveLegal(purple_princeps_figures2[4].MoveDiagonalLeftBack(3), test_board2));
}



//------------------------------------------------------------------------------------------------------------------------\\
//MOVING DIAGONAL RIGHT BACK
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightBack_OutOfBoard_Red) {
	EXPECT_FALSE(red_princeps_figures1[3].IsMoveLegal(red_princeps_figures1[3].MoveDiagonalRightBack(5), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightBack_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_princeps_figures1[3].IsMoveLegal(purple_princeps_figures1[3].MoveDiagonalRightBack(5), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightBack_Empty_Red) {
	EXPECT_TRUE(red_princeps_figures1[3].IsMoveLegal(red_princeps_figures1[3].MoveDiagonalRightBack(3), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightBack_Empty_Purple) {
	EXPECT_TRUE(purple_princeps_figures1[3].IsMoveLegal(purple_princeps_figures1[3].MoveDiagonalRightBack(3), test_board1));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightBack_Enemy_Red) {
	EXPECT_TRUE(red_princeps_figures2[4].IsMoveLegal(red_princeps_figures2[4].MoveDiagonalRightBack(3), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightBack_Enemy_Purple) {
	EXPECT_TRUE(purple_princeps_figures2[5].IsMoveLegal(purple_princeps_figures2[5].MoveDiagonalRightBack(3), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightBack_Ally_Red) {
	EXPECT_FALSE(red_princeps_figures2[5].IsMoveLegal(red_princeps_figures2[5].MoveDiagonalRightBack(1), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightBack_Ally_Purple) {
	EXPECT_FALSE(purple_princeps_figures2[4].IsMoveLegal(purple_princeps_figures2[4].MoveDiagonalRightBack(1), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightBack_SkippingOverFigures_Red) {
	EXPECT_FALSE(red_princeps_figures2[5].IsMoveLegal(red_princeps_figures2[5].MoveDiagonalRightBack(2), test_board2));
}

TEST_F(PrincepsFigure, IsMoveLegal_DiagonalRightBack_SkippingOverFigures_Purple) {
	EXPECT_FALSE(purple_princeps_figures2[4].IsMoveLegal(purple_princeps_figures2[4].MoveDiagonalRightBack(2), test_board2));
}

