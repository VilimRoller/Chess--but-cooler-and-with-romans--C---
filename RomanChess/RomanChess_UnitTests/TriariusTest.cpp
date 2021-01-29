#include "gtest/gtest.h"
#include "Triarius.h"
#include "TestFunctions.h"

class TriariusFigure : public ::testing::Test {
protected:
	void SetUp() override {
		test_board1 = TestFunctions::GetEmptyBoardImage();
		test_board2 = TestFunctions::GetEmptyBoardImage();

		std::vector<std::pair<FigureImage, BoardCoordinates>> board_figures;
		std::vector<BoardCoordinates> red_figure_coordinates;
		std::vector<BoardCoordinates> purple_figure_coordinates;

		FigureImage red_triarius_figure(figureType::Triarius, figureColour::Red);
		FigureImage purple_triarius_figure(figureType::Triarius, figureColour::Purple);

		//First set; Diagonal, front, back, left, right to empty tiles and out of board
		red_figure_coordinates.emplace_back(BoardCoordinates(1, 1));
		red_figure_coordinates.emplace_back(BoardCoordinates(3, 3));
		red_figure_coordinates.emplace_back(BoardCoordinates(4, 2));
		red_figure_coordinates.emplace_back(BoardCoordinates(4, 4));
		red_figure_coordinates.emplace_back(BoardCoordinates(5, 3));


		purple_figure_coordinates.emplace_back(BoardCoordinates(2, 3));
		purple_figure_coordinates.emplace_back(BoardCoordinates(3, 2));
		purple_figure_coordinates.emplace_back(BoardCoordinates(3, 4));
		purple_figure_coordinates.emplace_back(BoardCoordinates(4, 3));
		purple_figure_coordinates.emplace_back(BoardCoordinates(6, 6));


		for (int i = 0; i < red_figure_coordinates.size(); ++i) {
			red_triarius_figures1.emplace_back(Triarius(figureColour::Red));
			purple_triarius_figures1.emplace_back(Triarius(figureColour::Purple));

			red_triarius_figures1[i].SetPosition(red_figure_coordinates[i]);
			purple_triarius_figures1[i].SetPosition(purple_figure_coordinates[i]);
		}

		TestFunctions::MakeMultipleFigureImages(red_triarius_figure, red_figure_coordinates, board_figures);
		TestFunctions::MakeMultipleFigureImages(purple_triarius_figure, purple_figure_coordinates, board_figures);
		TestFunctions::SetMultipleFigureImages(test_board1, board_figures);

		board_figures.clear();
		red_figure_coordinates.clear();
		purple_figure_coordinates.clear();

		//Second set; 

		red_figure_coordinates.emplace_back(BoardCoordinates(1, 4));
		red_figure_coordinates.emplace_back(BoardCoordinates(2, 3));
		red_figure_coordinates.emplace_back(BoardCoordinates(2, 5));
		red_figure_coordinates.emplace_back(BoardCoordinates(3, 6));
		red_figure_coordinates.emplace_back(BoardCoordinates(4, 0));
		red_figure_coordinates.emplace_back(BoardCoordinates(4, 3));
		red_figure_coordinates.emplace_back(BoardCoordinates(4, 5));
		red_figure_coordinates.emplace_back(BoardCoordinates(5, 0));
		red_figure_coordinates.emplace_back(BoardCoordinates(7, 2));
		red_figure_coordinates.emplace_back(BoardCoordinates(7, 3));

		purple_figure_coordinates.emplace_back(BoardCoordinates(3, 2));
		purple_figure_coordinates.emplace_back(BoardCoordinates(3, 4));
		purple_figure_coordinates.emplace_back(BoardCoordinates(5, 2));
		purple_figure_coordinates.emplace_back(BoardCoordinates(5, 4));
		purple_figure_coordinates.emplace_back(BoardCoordinates(5, 6));
		purple_figure_coordinates.emplace_back(BoardCoordinates(6, 5));
		purple_figure_coordinates.emplace_back(BoardCoordinates(7, 4));
		purple_figure_coordinates.emplace_back(BoardCoordinates(7, 6));
		
		for (int i = 0; i < red_figure_coordinates.size(); ++i) {
			red_triarius_figures2.emplace_back(Triarius(figureColour::Red));
			red_triarius_figures2[i].SetPosition(red_figure_coordinates[i]);
		}

		for (int i = 0; i < purple_figure_coordinates.size(); ++i) {
			purple_triarius_figures2.emplace_back(Triarius(figureColour::Purple));
			purple_triarius_figures2[i].SetPosition(purple_figure_coordinates[i]);
		}

		TestFunctions::MakeMultipleFigureImages(red_triarius_figure, red_figure_coordinates, board_figures);
		TestFunctions::MakeMultipleFigureImages(purple_triarius_figure, purple_figure_coordinates, board_figures);
		TestFunctions::SetMultipleFigureImages(test_board2, board_figures);

	}

	void TearDown() override {}
	BoardImage test_board1;
	BoardImage test_board2;

	std::vector<Triarius> red_triarius_figures1;
	std::vector<Triarius> purple_triarius_figures1;
	std::vector<Triarius> red_triarius_figures2;
	std::vector<Triarius> purple_triarius_figures2;
};

TEST_F(TriariusFigure, NumberOfLegalMoves_Red) {
	EXPECT_EQ(red_triarius_figures2[0].GetLegalMoves(test_board2).size(), 12);
	EXPECT_EQ(red_triarius_figures2[3].GetLegalMoves(test_board2).size(), 10);
	EXPECT_EQ(red_triarius_figures2[5].GetLegalMoves(test_board2).size(), 6);
	EXPECT_EQ(red_triarius_figures2[9].GetLegalMoves(test_board2).size(), 5);
}

TEST_F(TriariusFigure, NumberOfLegalMoves_Purple) {
	EXPECT_EQ(purple_triarius_figures2[0].GetLegalMoves(test_board2).size(), 9);
	EXPECT_EQ(purple_triarius_figures2[1].GetLegalMoves(test_board2).size(), 6);
	EXPECT_EQ(purple_triarius_figures2[2].GetLegalMoves(test_board2).size(), 9);
	EXPECT_EQ(purple_triarius_figures2[3].GetLegalMoves(test_board2).size(), 5);
}


//------------------------------------------------------------------------------------------------------------------------\\
//MOVING FRONT
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(TriariusFigure, MoveFront_OutOfBoard_Red) {
	EXPECT_FALSE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveFront(2), test_board1));
}

TEST_F(TriariusFigure, MoveFront_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveFront(2), test_board1));
}

TEST_F(TriariusFigure, MoveFront_Empty_Red) {
	EXPECT_TRUE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveFront(1), test_board1));
}

TEST_F(TriariusFigure, MoveFront_Empty_Purple) {
	EXPECT_TRUE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveFront(1), test_board1));
}

TEST_F(TriariusFigure, MoveFront_Enemy_Red) {
	EXPECT_TRUE(red_triarius_figures2[3].IsMoveLegal(red_triarius_figures2[3].MoveFront(2), test_board2));
}

TEST_F(TriariusFigure, MoveFront_Enemy_Purple) {
	EXPECT_TRUE(purple_triarius_figures2[1].IsMoveLegal(purple_triarius_figures2[1].MoveFront(2), test_board2));
}

TEST_F(TriariusFigure, MoveFront_Ally_Red) {
	EXPECT_FALSE(red_triarius_figures2[5].IsMoveLegal(red_triarius_figures2[2].MoveFront(3), test_board2));
}

TEST_F(TriariusFigure, MoveFront_Ally_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[0].IsMoveLegal(purple_triarius_figures2[0].MoveFront(2), test_board2));
}

TEST_F(TriariusFigure, MoveFront_SkipOverFigures_Red) {
	EXPECT_FALSE(red_triarius_figures2[3].IsMoveLegal(red_triarius_figures2[3].MoveFront(3), test_board2));
}

TEST_F(TriariusFigure, MoveFront_SkipOverFigures_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[1].IsMoveLegal(purple_triarius_figures2[1].MoveFront(3), test_board2));
}



//------------------------------------------------------------------------------------------------------------------------\\
//MOVING BACK
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(TriariusFigure, MoveBack_OutOfBoard_Red) {
	EXPECT_FALSE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveBack(7), test_board1));
}

TEST_F(TriariusFigure, MoveBack_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveBack(7), test_board1));
}

TEST_F(TriariusFigure, MoveBack_Empty_Red) {
	EXPECT_TRUE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveBack(6), test_board1));
}

TEST_F(TriariusFigure, MoveBack_Empty_Purple) {
	EXPECT_TRUE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveBack(6), test_board1));
}

TEST_F(TriariusFigure, MoveBack_Enemy_Red) {
	EXPECT_TRUE(red_triarius_figures2[7].IsMoveLegal(red_triarius_figures2[7].MoveBack(2), test_board2));
}

TEST_F(TriariusFigure, MoveBack_Enemy_Purple) {
	EXPECT_TRUE(purple_triarius_figures2[2].IsMoveLegal(purple_triarius_figures2[2].MoveBack(2), test_board2));
}

TEST_F(TriariusFigure, MoveBack_Ally_Red) {
	EXPECT_FALSE(red_triarius_figures2[5].IsMoveLegal(red_triarius_figures2[1].MoveBack(2), test_board2));
}

TEST_F(TriariusFigure, MoveBack_Ally_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[1].IsMoveLegal(purple_triarius_figures2[1].MoveBack(2), test_board2));
}

TEST_F(TriariusFigure, MoveBack_SkipOverFigures_Red) {
	EXPECT_FALSE(red_triarius_figures2[1].IsMoveLegal(red_triarius_figures2[1].MoveBack(3), test_board2));
}

TEST_F(TriariusFigure, MoveBack_SkipOverFigures_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[1].IsMoveLegal(purple_triarius_figures2[1].MoveBack(3), test_board2));
}


//------------------------------------------------------------------------------------------------------------------------\\
//MOVING LEFT
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(TriariusFigure, MoveLeft_OutOfBoard_Red) {
	EXPECT_FALSE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveLeft(2), test_board1));
}

TEST_F(TriariusFigure, MoveLeft_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveLeft(2), test_board1));
}

TEST_F(TriariusFigure, MoveLeft_Empty_Red) {
	EXPECT_TRUE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveLeft(1), test_board1));
}

TEST_F(TriariusFigure, MoveLeft_Empty_Purple) {
	EXPECT_TRUE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveLeft(1), test_board1));
}

TEST_F(TriariusFigure, MoveLeft_Enemy_Red) {
	EXPECT_TRUE(red_triarius_figures2[8].IsMoveLegal(red_triarius_figures2[8].MoveLeft(2), test_board2));
}

TEST_F(TriariusFigure, MoveLeft_Enemy_Purple) {
	EXPECT_TRUE(purple_triarius_figures2[2].IsMoveLegal(purple_triarius_figures2[2].MoveLeft(2), test_board2));
}

TEST_F(TriariusFigure, MoveLeft_Ally_Red) {
	EXPECT_FALSE(red_triarius_figures2[5].IsMoveLegal(red_triarius_figures2[5].MoveLeft(2), test_board2));
}

TEST_F(TriariusFigure, MoveLeft_Ally_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[0].IsMoveLegal(purple_triarius_figures2[0].MoveLeft(2), test_board2));
}

TEST_F(TriariusFigure, MoveLeft_SkipOverFigures_Red) {
	EXPECT_FALSE(red_triarius_figures2[5].IsMoveLegal(red_triarius_figures2[0].MoveLeft(3), test_board2));
}

TEST_F(TriariusFigure, MoveLeft_SkipOverFigures_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[0].IsMoveLegal(purple_triarius_figures2[0].MoveLeft(4), test_board2));
}



//------------------------------------------------------------------------------------------------------------------------\\
//MOVING RIGHT
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(TriariusFigure, MoveRight_OutOfBoard_Red) {
	EXPECT_FALSE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveRight(7), test_board1));
}

TEST_F(TriariusFigure, MoveRight_OutOfBoard_Purple) {
	EXPECT_FALSE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveRight(7), test_board1));
}

TEST_F(TriariusFigure, MoveRight_Empty_Red) {
	EXPECT_TRUE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveRight(6), test_board1));
}

TEST_F(TriariusFigure, MoveRight_Empty_Purple) {
	EXPECT_TRUE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveRight(6), test_board1));
}

TEST_F(TriariusFigure, MoveRight_Enemy_Red) {
	EXPECT_TRUE(red_triarius_figures2[0].IsMoveLegal(red_triarius_figures2[0].MoveRight(2), test_board2));
}

TEST_F(TriariusFigure, MoveRight_Enemy_Purple) {
	EXPECT_TRUE(purple_triarius_figures2[1].IsMoveLegal(purple_triarius_figures2[1].MoveRight(2), test_board2));
}

TEST_F(TriariusFigure, MoveRight_Ally_Red) {
	EXPECT_FALSE(red_triarius_figures2[1].IsMoveLegal(red_triarius_figures2[1].MoveRight(2), test_board2));
}

TEST_F(TriariusFigure, MoveRight_Ally_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[2].IsMoveLegal(purple_triarius_figures2[2].MoveRight(2), test_board2));
}

TEST_F(TriariusFigure, MoveRight_SkipOverFigures_Red) {
	EXPECT_FALSE(red_triarius_figures2[0].IsMoveLegal(red_triarius_figures2[0].MoveRight(3), test_board2));
}

TEST_F(TriariusFigure, MoveRight_SkipOverFigures_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[1].IsMoveLegal(purple_triarius_figures2[1].MoveRight(3), test_board2));
}



//------------------------------------------------------------------------------------------------------------------------\\
//MOVING DIAGONAL LEFT FRONT
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(TriariusFigure, MoveDiagonalLeftFront_Empty_Red) {
	EXPECT_TRUE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveDiagonalLeftFront(), test_board1));
}

TEST_F(TriariusFigure, MoveDiagonalLeftFront_Empty_Purple) {
	EXPECT_TRUE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveDiagonalLeftFront(), test_board1));
}

TEST_F(TriariusFigure, MoveDiagonalLeftFront_Enemy_Red) {
	EXPECT_FALSE(red_triarius_figures2[5].IsMoveLegal(red_triarius_figures2[5].MoveDiagonalLeftFront(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalLeftFront_Enemy_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[1].IsMoveLegal(purple_triarius_figures2[1].MoveDiagonalLeftFront(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalLeftFront_Ally_Red) {
	EXPECT_FALSE(red_triarius_figures2[2].IsMoveLegal(red_triarius_figures2[2].MoveDiagonalLeftFront(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalLeftFront_Ally_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[5].IsMoveLegal(purple_triarius_figures2[5].MoveDiagonalLeftFront(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalLeftFront_MultipleTiles) {
	EXPECT_FALSE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveDiagonalLeftFront(2), test_board1));
	EXPECT_FALSE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveDiagonalLeftFront(2), test_board1));
}

//------------------------------------------------------------------------------------------------------------------------\\
//MOVING DIAGONAL RIGHT FRONT
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(TriariusFigure, MoveDiagonalRightFront_Empty_Red) {
	EXPECT_TRUE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveDiagonalRightFront(), test_board1));
}

TEST_F(TriariusFigure, MoveDiagonalRightFront_Empty_Purple) {
	EXPECT_TRUE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveDiagonalRightFront(), test_board1));
}

TEST_F(TriariusFigure, MoveDiagonalRightFront_Enemy_Red) {
	EXPECT_FALSE(red_triarius_figures2[5].IsMoveLegal(red_triarius_figures2[5].MoveDiagonalRightFront(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalRightFront_Enemy_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[1].IsMoveLegal(purple_triarius_figures2[1].MoveDiagonalRightFront(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalRightFront_Ally_Red) {
	EXPECT_FALSE(red_triarius_figures2[0].IsMoveLegal(red_triarius_figures2[0].MoveDiagonalRightFront(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalRightFront_Ally_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[5].IsMoveLegal(purple_triarius_figures2[5].MoveDiagonalRightFront(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalRightFront_MultipleTiles) {
	EXPECT_FALSE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveDiagonalRightFront(2), test_board1));
	EXPECT_FALSE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveDiagonalRightFront(2), test_board1));
}

//------------------------------------------------------------------------------------------------------------------------\\
//MOVING DIAGONAL LEFT BACK
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(TriariusFigure, MoveDiagonalLeftBack_Empty_Red) {
	EXPECT_TRUE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveDiagonalLeftBack(), test_board1));
}

TEST_F(TriariusFigure, MoveDiagonalLeftBack_Empty_Purple) {
	EXPECT_TRUE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveDiagonalLeftBack(), test_board1));
}

TEST_F(TriariusFigure, MoveDiagonalLeftBack_Enemy_Red) {
	EXPECT_FALSE(red_triarius_figures2[5].IsMoveLegal(red_triarius_figures2[5].MoveDiagonalLeftBack(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalLeftBack_Enemy_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[1].IsMoveLegal(purple_triarius_figures2[1].MoveDiagonalLeftBack(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalLeftBack_Ally_Red) {
	EXPECT_FALSE(red_triarius_figures2[1].IsMoveLegal(red_triarius_figures2[1].MoveDiagonalLeftBack(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalLeftBack_Ally_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[5].IsMoveLegal(purple_triarius_figures2[5].MoveDiagonalLeftBack(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalLeftBack_MultipleTiles) {
	EXPECT_FALSE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveDiagonalLeftBack(2), test_board1));
	EXPECT_FALSE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveDiagonalLeftBack(2), test_board1));
}


//------------------------------------------------------------------------------------------------------------------------\\
//MOVING DIAGONAL RIGHT BACK
//------------------------------------------------------------------------------------------------------------------------\\

TEST_F(TriariusFigure, MoveDiagonalRightBack_Empty_Red) {
	EXPECT_TRUE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveDiagonalRightBack(), test_board1));
}

TEST_F(TriariusFigure, MoveDiagonalRightBack_Empty_Purple) {
	EXPECT_TRUE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveDiagonalRightBack(), test_board1));
}

TEST_F(TriariusFigure, MoveDiagonalRightBack_Enemy_Red) {
	EXPECT_FALSE(red_triarius_figures2[5].IsMoveLegal(red_triarius_figures2[5].MoveDiagonalRightBack(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalRightBack_Enemy_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[1].IsMoveLegal(purple_triarius_figures2[1].MoveDiagonalRightBack(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalRightBack_Ally_Red) {
	EXPECT_FALSE(red_triarius_figures2[2].IsMoveLegal(red_triarius_figures2[2].MoveDiagonalRightBack(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalRightBack_Ally_Purple) {
	EXPECT_FALSE(purple_triarius_figures2[5].IsMoveLegal(purple_triarius_figures2[5].MoveDiagonalRightBack(), test_board2));
}

TEST_F(TriariusFigure, MoveDiagonalRightBack_MultipleTiles) {
	EXPECT_FALSE(red_triarius_figures1[0].IsMoveLegal(red_triarius_figures1[0].MoveDiagonalRightBack(2), test_board1));
	EXPECT_FALSE(purple_triarius_figures1[4].IsMoveLegal(purple_triarius_figures1[4].MoveDiagonalRightBack(2), test_board1));
}
