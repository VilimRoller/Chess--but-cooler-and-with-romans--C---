#include "gtest/gtest.h"
#include "RomanChessAI.h"

#include <memory>

class RomanChessAITest : public ::testing::Test {
protected:
	void SetUp() override {
		test_AI_.InitializeRomanChessAI(AIType::CaesarAI, AIStrategy::Standard,
										AIType::CaesarAI, AIStrategy::Standard,
										&game_figures_, figureColour::Red);

		board_image_ptr = &(test_AI_.GetCurrentBoardImage());

		
		game_figures_[6][1] = std::make_shared<Veles>(figureColour::Red);
		game_figures_[5][1] = std::make_shared<Veles>(figureColour::Red);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

		game_figures_[1][6] = std::make_shared<Veles>(figureColour::Purple);
		game_figures_[2][6] = std::make_shared<Veles>(figureColour::Purple);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

		game_figures_[6][3] = std::make_shared<Hastatus>(figureColour::Red);
		game_figures_[4][3] = std::make_shared<Hastatus>(figureColour::Red);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

		game_figures_[1][4] = std::make_shared<Hastatus>(figureColour::Purple);
		game_figures_[3][4] = std::make_shared<Hastatus>(figureColour::Purple);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

		game_figures_[7][1] = std::make_shared<Princeps>(figureColour::Red);
		game_figures_[4][4] = std::make_shared<Princeps>(figureColour::Red);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

		game_figures_[0][6] = std::make_shared<Princeps>(figureColour::Purple);
		game_figures_[3][3] = std::make_shared<Princeps>(figureColour::Purple);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

		game_figures_[7][7] = std::make_shared<Triarius>(figureColour::Red);
		game_figures_[5][6] = std::make_shared<Triarius>(figureColour::Red);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

		game_figures_[0][0] = std::make_shared<Triarius>(figureColour::Purple);
		game_figures_[2][1] = std::make_shared<Triarius>(figureColour::Purple);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

		game_figures_[7][5] = std::make_shared<Eques>(figureColour::Red);
		game_figures_[3][5] = std::make_shared<Eques>(figureColour::Red);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

		game_figures_[0][2] = std::make_shared<Eques>(figureColour::Purple);
		game_figures_[4][2] = std::make_shared<Eques>(figureColour::Purple);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

		game_figures_[7][4] = std::make_shared<Consul>(figureColour::Red);
		game_figures_[5][4] = std::make_shared<Consul>(figureColour::Red);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

		game_figures_[0][3] = std::make_shared<Consul>(figureColour::Purple);
		game_figures_[2][3] = std::make_shared<Consul>(figureColour::Purple);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

		game_figures_[7][2] = std::make_shared<PontifexMaximus>(figureColour::Red);
		game_figures_[5][2] = std::make_shared<PontifexMaximus>(figureColour::Red);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

		game_figures_[0][5] = std::make_shared<PontifexMaximus>(figureColour::Purple);
		game_figures_[2][5] = std::make_shared<PontifexMaximus>(figureColour::Purple);
		test_AI_.RefreshCurrentBoardImage();
		BoardStrenghtValues.emplace_back(test_AI_.GetEvaluatedBoardStrenght());

	}
	void TearDown() override {}

	RomanChessFigures game_figures_;
	RomanChessAI test_AI_;
	const BoardImage* board_image_ptr;
	std::vector<int> BoardStrenghtValues;
};

TEST_F(RomanChessAITest, GetFigureStrenght_Veles_Red) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[6][1], BoardCoordinates(1,6)), -15);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[5][1], BoardCoordinates(1,5)), -30);
}

TEST_F(RomanChessAITest, GetFigureStrenght_Veles_Purple) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[1][6], BoardCoordinates(6, 1)), 15);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[2][6], BoardCoordinates(6, 2)), 30);
}

TEST_F(RomanChessAITest, GetFigureStrenght_Hastatus_Red) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[6][3], BoardCoordinates(3, 6)), -25);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[4][3], BoardCoordinates(3, 4)), -50);
}

TEST_F(RomanChessAITest, GetFigureStrenght_Hastatus_Purple) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[1][4], BoardCoordinates(4, 1)), 25);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[3][4], BoardCoordinates(4, 3)), 50);
}

TEST_F(RomanChessAITest, GetFigureStrenght_Princeps_Red) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[7][1], BoardCoordinates(1, 7)), -80);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[4][4], BoardCoordinates(4, 4)), -160);
}

TEST_F(RomanChessAITest, GetFigureStrenght_Princeps_Purple) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[0][6], BoardCoordinates(6, 0)), 80);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[3][3], BoardCoordinates(3, 3)), 160);
}

TEST_F(RomanChessAITest, GetFigureStrenght_Triarius_Red) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[7][7], BoardCoordinates(7, 7)), -50);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[5][6], BoardCoordinates(6, 5)), -100);
}

TEST_F(RomanChessAITest, GetFigureStrenght_Triarius_Purple) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[0][0], BoardCoordinates(0, 0)), 50);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[2][1], BoardCoordinates(1, 2)), 100);
}

TEST_F(RomanChessAITest, GetFigureStrenght_Eques_Red) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[7][5], BoardCoordinates(5, 7)), -144);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[3][5], BoardCoordinates(5, 3)), -288);
}

TEST_F(RomanChessAITest, GetFigureStrenght_Eques_Purple) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[0][2], BoardCoordinates(2, 0)), 144);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[4][2], BoardCoordinates(2, 4)), 288);
}

TEST_F(RomanChessAITest, GetFigureStrenght_Consul_Red) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[7][4], BoardCoordinates(4, 7)), -560);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[5][4], BoardCoordinates(4, 5)), -700);
}

TEST_F(RomanChessAITest, GetFigureStrenght_Consul_Purple) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[0][3], BoardCoordinates(3, 0)), 560);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[2][3], BoardCoordinates(3, 2)), 700);
}

TEST_F(RomanChessAITest, GetFigureStrenght_PontifexMaximus_Red) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[7][2], BoardCoordinates(2, 7)), -100);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[5][2], BoardCoordinates(2, 5)), -50);
}

TEST_F(RomanChessAITest, GetFigureStrenght_PontifexMaximus_Purple) {
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[0][5], BoardCoordinates(5, 0)), 100);
	EXPECT_EQ(test_AI_.GetFigureStrengh((*board_image_ptr)[2][5], BoardCoordinates(5, 2)), 50);
}

TEST_F(RomanChessAITest, GetBoardStrenght) {
	EXPECT_EQ(BoardStrenghtValues[0],    -45);
	EXPECT_EQ(BoardStrenghtValues[1],      0);
	EXPECT_EQ(BoardStrenghtValues[2],    -75);
	EXPECT_EQ(BoardStrenghtValues[3],      0);
	EXPECT_EQ(BoardStrenghtValues[4],   -240);
	EXPECT_EQ(BoardStrenghtValues[5],      0);
	EXPECT_EQ(BoardStrenghtValues[6],   -150);
	EXPECT_EQ(BoardStrenghtValues[7],      0);
	EXPECT_EQ(BoardStrenghtValues[8],   -432);
	EXPECT_EQ(BoardStrenghtValues[9],      0);
	EXPECT_EQ(BoardStrenghtValues[10], -1260);
	EXPECT_EQ(BoardStrenghtValues[11],     0);
	EXPECT_EQ(BoardStrenghtValues[12],  -150);
	EXPECT_EQ(BoardStrenghtValues[13],     0);
}