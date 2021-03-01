#include "gtest/gtest.h"
#include "RomanChessGameEngine.h"

#include <algorithm>
#include <vector>
	/*------------------------------------------------------------------------------------------------------------*/
	/*											CALCULATING LEGAL MOVES		 							          */
	/*------------------------------------------------------------------------------------------------------------*/

class LegalMovesTest : public ::testing::Test {
protected:
	void SetUp() override {

	}
	void TearDown() override {}

	RomanChessGameEngine test_engine_;
};

/*---------------------------------------------------VELES---------------------------------------------------------*/

TEST_F(LegalMovesTest, Veles_MovingFront_Empty) {
	test_engine_.CalculateLegalMoves(BoardCoordinates(0,6));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(0, 5)));
}

TEST_F(LegalMovesTest, Veles_AttackMoves_Empty) {
	test_engine_.CalculateLegalMoves(BoardCoordinates(1, 6));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(0, 5)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(2, 5)));
}

TEST_F(LegalMovesTest, Veles_MovingOutOfBoard_Red) {
	test_engine_.CalculateLegalMoves(std::make_shared<Veles>(figureColour::Red, BoardCoordinates(1, 0)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(1, -1)));
}

TEST_F(LegalMovesTest, Veles_MovingOutOfBoard_Purple) {
	test_engine_.CalculateLegalMoves(std::make_shared<Veles>(figureColour::Purple, BoardCoordinates(1, 7)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(1, 8)));
}

TEST_F(LegalMovesTest, Veles_AttackMoves_Enemy) {
	test_engine_.CalculateLegalMoves(std::make_shared<Veles>(figureColour::Purple, BoardCoordinates(1,5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(0, 6)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 6)));
}

TEST_F(LegalMovesTest, Veles_MovingFront_Enemy) {
	test_engine_.CalculateLegalMoves(std::make_shared<Veles>(figureColour::Purple, BoardCoordinates(0, 5)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(0, 6)));
}

/*-----------------------------------------------HASTATUS---------------------------------------------------------*/

TEST_F(LegalMovesTest, Hastatus_AttackMoves_Empty) {
	test_engine_.CalculateLegalMoves(BoardCoordinates(2, 6));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(1, 5)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(3, 5)));
}

TEST_F(LegalMovesTest, Hastatus_MovingFront_Empty) {
	test_engine_.CalculateLegalMoves(BoardCoordinates(2, 6));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 4)));
}

TEST_F(LegalMovesTest, Hastatus_MovingBack_Ally) {
	test_engine_.CalculateLegalMoves(BoardCoordinates(2, 6));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(2, 7)));
}

TEST_F(LegalMovesTest, Hastatus_AttackMoves_Enemy) {
	test_engine_.CalculateLegalMoves(std::make_shared<Hastatus>(figureColour::Purple, BoardCoordinates(3, 5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 6)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 6)));
}

TEST_F(LegalMovesTest, Hastatus_MovingBack_Empty) {
	test_engine_.CalculateLegalMoves(std::make_shared<Hastatus>(figureColour::Purple, BoardCoordinates(3, 5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(3, 4)));
}

TEST_F(LegalMovesTest, Hastatus_MovingFornt_Enemy) {
	test_engine_.CalculateLegalMoves(std::make_shared<Hastatus>(figureColour::Purple, BoardCoordinates(3, 5)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(3, 6)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(3, 7)));
}

/*-----------------------------------------------PRINCEPS---------------------------------------------------------*/

TEST_F(LegalMovesTest, Princeps_MovingAround_AllyFigures) {
	test_engine_.CalculateLegalMoves(BoardCoordinates(1, 7));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(1, 7)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(0, 7)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(2, 7)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(1, 6)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(0, 6)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(2, 6)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(3, 5)));
}

TEST_F(LegalMovesTest, Princeps_MovingAround_Straight_EmptyTiles) {
	test_engine_.CalculateLegalMoves(std::make_shared<Princeps>(figureColour::Purple, BoardCoordinates(3, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(3, 3)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(3, 5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 4)));
}

TEST_F(LegalMovesTest, Princeps_MovingAround_Diagonal_EmptyTiles) {
	test_engine_.CalculateLegalMoves(std::make_shared<Princeps>(figureColour::Purple, BoardCoordinates(3, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(1, 2)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(5, 2)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 5)));
}

TEST_F(LegalMovesTest, Princeps_MoveDiagonalBack_AllyFigures) {
	test_engine_.CalculateLegalMoves(std::make_shared<Princeps>(figureColour::Purple, BoardCoordinates(3, 4)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(0, 1)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(6, 1)));
}

TEST_F(LegalMovesTest, Princeps_MoveDiagonalFront_EnemyFigures) {
	test_engine_.CalculateLegalMoves(std::make_shared<Princeps>(figureColour::Purple, BoardCoordinates(3, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(1, 6)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(5, 6)));
}

TEST_F(LegalMovesTest, Princeps_MoveDiagonal_JumpOverFigures) {
	test_engine_.CalculateLegalMoves(std::make_shared<Princeps>(figureColour::Purple, BoardCoordinates(3, 4)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(0, 1)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(6, 1)));
}

/*-----------------------------------------------TRIARIUS---------------------------------------------------------*/

TEST_F(LegalMovesTest, Triarius_MovingAround_AllyFigures) {
	test_engine_.CalculateLegalMoves(BoardCoordinates(0, 7));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(0, 6)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(1, 7)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(1, 6)));
}

TEST_F(LegalMovesTest, Triarius_MovingAround_Straight_EmptyTiles) {
	test_engine_.CalculateLegalMoves(std::make_shared<Triarius>(figureColour::Purple, BoardCoordinates(3, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(3, 2)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(0, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(7, 4)));
}

TEST_F(LegalMovesTest, Triarius_MovingAround_Diagonal_EmptyTiles) {
	test_engine_.CalculateLegalMoves(std::make_shared<Triarius>(figureColour::Purple, BoardCoordinates(3, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 3)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 3)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 5)));
}

TEST_F(LegalMovesTest, Triarius_AttackMoves_Enemy) {
	test_engine_.CalculateLegalMoves(std::make_shared<Triarius>(figureColour::Purple, BoardCoordinates(3, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(3, 6)));
}

TEST_F(LegalMovesTest, Triarius_JumpOverFigures) {
	test_engine_.CalculateLegalMoves(std::make_shared<Triarius>(figureColour::Purple, BoardCoordinates(3, 4)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(3, 7)));
}

/*-----------------------------------------------EQUES---------------------------------------------------------*/

TEST_F(LegalMovesTest, Eques_FrontJumps) {
	test_engine_.CalculateLegalMoves(std::make_shared<Eques>(figureColour::Purple, BoardCoordinates(3, 5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 7)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 7)));
}

TEST_F(LegalMovesTest, Eques_RightJumps) {
	test_engine_.CalculateLegalMoves(std::make_shared<Eques>(figureColour::Purple, BoardCoordinates(3, 5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(5, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(5, 6)));
}

TEST_F(LegalMovesTest, Eques_LeftJumps) {
	test_engine_.CalculateLegalMoves(std::make_shared<Eques>(figureColour::Purple, BoardCoordinates(3, 5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(1, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(1, 6)));
}

TEST_F(LegalMovesTest, Eques_BackJumps) {
	test_engine_.CalculateLegalMoves(std::make_shared<Eques>(figureColour::Purple, BoardCoordinates(3, 5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 3)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 3)));
}

TEST_F(LegalMovesTest, Eques_JumpOutOfBoard) {
	test_engine_.CalculateLegalMoves(std::make_shared<Eques>(figureColour::Purple, BoardCoordinates(1, 6)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(-1, 5)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(-1, 7)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(0, 8)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(2, 8)));
}

/*-----------------------------------------------CONSUL---------------------------------------------------------*/

TEST_F(LegalMovesTest, Consul_MovingAround_AllyFigures) {
	test_engine_.CalculateLegalMoves(BoardCoordinates(3, 7));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(2, 7)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(2, 6)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(3, 6)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(4, 6)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(4, 7)));
}

TEST_F(LegalMovesTest, Consul_MovingAround_EmptyTiles) {
	test_engine_.CalculateLegalMoves(std::make_shared<Consul>(figureColour::Purple, BoardCoordinates(3, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 3)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(3, 3)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 3)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 5)));
}

TEST_F(LegalMovesTest, Consul_MovingAround_EnemyFigures) {
	test_engine_.CalculateLegalMoves(std::make_shared<Consul>(figureColour::Red, BoardCoordinates(3, 1)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(2, 1)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(2, 0)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(3, 0)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(4, 0)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(4, 1)));
}

/*-----------------------------------------------PONTIFEX MAXIMUS--------------------------------------------------*/

TEST_F(LegalMovesTest, PontifexMaximus_MovingAround_AllyFigures) {
	test_engine_.CalculateLegalMoves(std::make_shared<PontifexMaximus>(figureColour::Red, BoardCoordinates(3, 7)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(2, 7)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(2, 6)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(3, 6)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(4, 6)));
	EXPECT_FALSE(test_engine_.IsMoveLegal(BoardCoordinates(4, 7)));
}

TEST_F(LegalMovesTest, PontifexMaximus_MovingAround_EmptyTiles) {
	test_engine_.CalculateLegalMoves(std::make_shared<PontifexMaximus>(figureColour::Red, BoardCoordinates(3, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 3)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(3, 3)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 3)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 4)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(3, 5)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 5)));
}

TEST_F(LegalMovesTest, PontifexMaximus_MovingAround_EnemyFigures) {
	test_engine_.CalculateLegalMoves(std::make_shared<PontifexMaximus>(figureColour::Red, BoardCoordinates(3, 2)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(2, 1)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(3, 1)));
	EXPECT_TRUE(test_engine_.IsMoveLegal(BoardCoordinates(4, 1)));
}

TEST_F(LegalMovesTest, GetLegalMovesTest) {
	EXPECT_EQ(test_engine_.GetLegalMoves(std::make_shared<Hastatus>(figureColour::Red, BoardCoordinates(0, 4))).size(), 3);
}

/*------------------------------------------------------------------------------------------------------------*/
/*												 GAME MECHANICS									              */
/*------------------------------------------------------------------------------------------------------------*/

class GameMechanicsTest : public ::testing::Test {
protected:
	void SetUp() override {
		for (int i = 0; i < 20; ++i) {
			player_turns_.emplace_back(test_engine_.GetPlayerTurn());
			test_engine_.NextPlayerTurn();
		}
	}
	void TearDown() override {}

	RomanChessGameEngine test_engine_;
	std::vector<figureColour> player_turns_;

};

TEST_F(GameMechanicsTest, PlayerTurnTest) {
	auto result_iterator = std::adjacent_find(player_turns_.begin(), player_turns_.end());
	EXPECT_TRUE(result_iterator == player_turns_.end());
}

