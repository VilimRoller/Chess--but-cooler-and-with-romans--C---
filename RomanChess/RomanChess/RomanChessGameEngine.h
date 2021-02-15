#pragma once
#include <array>
#include <vector>
#include <utility>
#include <memory>
#include <deque>
#include <algorithm>

#include "Constants.h"
#include "ID.h"
#include "FigureIncludes.h"
#include "BoardCoordinates.h"


using FigureImage = std::pair<figureType, figureColour>;
using BoardRow = std::array<FigureImage, Constants::boardSize>;
using BoardImage = std::array<BoardRow, Constants::boardSize>;
using RomanChessFigures = std::array<std::array<std::shared_ptr<Figure>, Constants::boardSize>, Constants::boardSize>;

class RomanChessGameEngine {

public:

	RomanChessGameEngine() {}
	RomanChessGameEngine(const BoardImage& board_image) : board_image_{board_image} {}
	~RomanChessGameEngine() {}


	/*------------------------------------------------------------------------------------------------------------*/
	/*                        FUNCTIONS FOR CALCULATING LEGAL MOVES FOR FIGURES                                   */
	/*------------------------------------------------------------------------------------------------------------*/

	bool IsMoveLegal(BoardCoordinates&& new_position) const {
		return std::any_of(legal_moves_.begin(), legal_moves_.end(),
			[&new_position](const auto& legal_move) {return new_position == legal_move; });
	}

	void CalculateLegalMoves(const std::shared_ptr<Figure>& figure) {
		ClearLegalMoves();
		if (figure != nullptr) {
			CalculateLegalMoves(figure->GetFigureImage(), figure->GetPosition());
		}
	}

	void CalculateLegalMoves(const FigureImage& figure_image, const BoardCoordinates& figure_coordinates) {
		ClearLegalMoves();
		switch (figure_image.first) {
		case figureType::Veles:
			CalculateLegalMovesVeles(figure_coordinates, figure_image.second);
			break;
		case figureType::Hastatus:
			CalculateLegalMovesHastatus(figure_coordinates, figure_image.second);
			break;
		case figureType::Princeps:
			CalculateLegalMovesPrinceps(figure_coordinates, figure_image.second);
			break;
		case figureType::Triarius:
			CalculateLegalMovesTriarius(figure_coordinates, figure_image.second);
			break;
		case figureType::Eques:
			CalculateLegalMovesEques(figure_coordinates, figure_image.second);
			break;
		case figureType::Consul:
			CalculateLegalMovesConsul(figure_coordinates, figure_image.second);
			break;
		case figureType::PontifexMaximus:
			CalculateLegalMovesPontifexMaximus(figure_coordinates, figure_image.second);
			break;
		}
	}

	void CalculateLegalMovesVeles(const BoardCoordinates& figure_coordinates, const figureColour& figure_colour) {
		ValidateIfEmpty(MoveFront(figure_coordinates, figure_colour));
		ValidateIfEnemy(MoveDiagonalLeftFront(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEnemy(MoveDiagonalRightFront(figure_coordinates, figure_colour), figure_colour);
	}

	void CalculateLegalMovesHastatus(const BoardCoordinates& figure_coordinates, const figureColour& figure_colour) {
		ValidateIfEmptyFront(figure_coordinates, figure_colour, Constants::hastatusMaxMovesFront);
		ValidateIfEnemy(MoveDiagonalLeftFront(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEnemy(MoveDiagonalRightFront(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmpty(MoveBack(figure_coordinates, figure_colour));
	}

	void CalculateLegalMovesPrinceps(const BoardCoordinates& figure_coordinates, const figureColour& figure_colour) {
		ValidateIfEmpty(MoveFront(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveBack(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveLeft(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveRight(figure_coordinates, figure_colour));

		ValidateDiagonalMoves(figure_coordinates, figure_colour);
	}

	void CalculateLegalMovesTriarius(const BoardCoordinates& figure_coordinates, const figureColour& figure_colour) {
		ValidateIfEmpty(MoveDiagonalLeftFront(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalRightFront(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalLeftBack(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalRightBack(figure_coordinates, figure_colour));

		ValidateStraightMoves(figure_coordinates, figure_colour);
	}

	void CalculateLegalMovesEques(const BoardCoordinates& figure_coordinates, const figureColour& figure_colour) {
		ValidateEquesMoveFront(figure_coordinates, figure_colour);
		ValidateEquesMoveBack(figure_coordinates, figure_colour);
		ValidateEquesMoveLeft(figure_coordinates, figure_colour);
		ValidateEquesMoveRight(figure_coordinates, figure_colour);
	}

	void CalculateLegalMovesConsul(const BoardCoordinates& figure_coordinates, const figureColour& figure_colour) {
		ValidateIfEmpty(MoveFront(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalRightFront(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveRight(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalRightBack(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveBack(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalLeftBack(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveLeft(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalLeftFront(figure_coordinates, figure_colour));
	}

	void CalculateLegalMovesPontifexMaximus(const BoardCoordinates& figure_coordinates, const figureColour& figure_colour) {
		ValidateIfEmptyOrEnemy(MoveFront(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveDiagonalRightFront(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveRight(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveDiagonalRightBack(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveBack(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveDiagonalLeftBack(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveLeft(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveDiagonalLeftFront(figure_coordinates, figure_colour), figure_colour);
	}

	const std::vector<BoardCoordinates>& GetLegalMoves(const std::shared_ptr<Figure>& figure) {
		CalculateLegalMoves(figure);
		return legal_moves_;
	}

	const std::vector<BoardCoordinates>& GetLegalMoves() {
		return legal_moves_;
	}
	/*------------------------------------------------------------------------------------------------------------*/
	/*                         FUNCTIONS FOR VALIDATING MOVES TO TILES ON BOARD                                   */
	/*------------------------------------------------------------------------------------------------------------*/

	bool ValidateIfEmpty(BoardCoordinates&& position) {
		if (IsOnBoard(position)) {
			if (IsPlaceEmpty(position)) {
				AddLegalMove(std::move(position));
				return true;
			}
		}
		return false;
	}

	bool ValidateIfEnemy(BoardCoordinates&& position, const figureColour& figure_colour) {
		if (IsOnBoard(position)) {
			switch (figure_colour) {
			case figureColour::Red:
				return AddLegalMoveIfPurple(std::move(position));
				break;
			case figureColour::Purple:
				return AddLegalMoveIfRed(std::move(position));
				break;
			}
		}
		return false;
	}

	void ValidateIfEmptyOrEnemy(BoardCoordinates&& position, const figureColour& figure_colour) {
		if (IsOnBoard(position)) {
			IsPlaceEmpty(position) ? ValidateIfEmpty(std::move(position)) : ValidateIfEnemy(std::move(position), figure_colour);
		}
		}

	void ValidateIfEmptyFront(const BoardCoordinates& figure_coordinates, 
							  const figureColour& figure_colour,
							  const int num_of_places) {
		for (int num_of_moves = 1; num_of_moves <= num_of_places; ++num_of_moves) {
			if (!ValidateIfEmpty(MoveFront(figure_coordinates, figure_colour, num_of_moves))) {
				break;
			}
		}
	}

	void ValidateDiagonalMoves(const BoardCoordinates& figure_coordinates, const figureColour& figure_colour) {

		ValidateMovesInDirection(figure_coordinates, figure_colour,
								[this](const BoardCoordinates& figure_coordinates, const figureColour& figure_colour, const int number_of_spaces)
								{return MoveDiagonalLeftFront(figure_coordinates, figure_colour, number_of_spaces); });
			
		ValidateMovesInDirection(figure_coordinates, figure_colour,
								[this](const BoardCoordinates& figure_coordinates, const figureColour& figure_colour, const int number_of_spaces)
								{return MoveDiagonalRightFront(figure_coordinates, figure_colour, number_of_spaces); });

		ValidateMovesInDirection(figure_coordinates, figure_colour,
								[this](const BoardCoordinates& figure_coordinates, const figureColour& figure_colour, const int number_of_spaces)
								{return MoveDiagonalLeftBack(figure_coordinates, figure_colour, number_of_spaces); });

		ValidateMovesInDirection(figure_coordinates, figure_colour,
								[this](const BoardCoordinates& figure_coordinates, const figureColour& figure_colour, const int number_of_spaces)
								{return MoveDiagonalRightBack(figure_coordinates, figure_colour, number_of_spaces); });

	}

	void ValidateStraightMoves(const BoardCoordinates& figure_coordinates, const figureColour& figure_colour) {

		ValidateMovesInDirection(figure_coordinates, figure_colour,
			[this](const BoardCoordinates& figure_coordinates, const figureColour& figure_colour, const int number_of_spaces)
			{return MoveFront(figure_coordinates, figure_colour, number_of_spaces); });

		ValidateMovesInDirection(figure_coordinates, figure_colour,
			[this](const BoardCoordinates& figure_coordinates, const figureColour& figure_colour, const int number_of_spaces)
			{return MoveBack(figure_coordinates, figure_colour, number_of_spaces); });

		ValidateMovesInDirection(figure_coordinates, figure_colour,
			[this](const BoardCoordinates& figure_coordinates, const figureColour& figure_colour, const int number_of_spaces)
			{return MoveLeft(figure_coordinates, figure_colour, number_of_spaces); });

		ValidateMovesInDirection(figure_coordinates, figure_colour,
			[this](const BoardCoordinates& figure_coordinates, const figureColour& figure_colour, const int number_of_spaces)
			{return MoveRight(figure_coordinates, figure_colour, number_of_spaces); });
	}

	template <class MOVE_LAMBDA>
	void ValidateMovesInDirection(const BoardCoordinates& figure_coordinates, 
								  const figureColour& figure_colour,
								  MOVE_LAMBDA&& MOVE_FUNCTION) {
		for (int num_of_moves = 1; IsOnBoard(MOVE_FUNCTION(figure_coordinates, figure_colour, num_of_moves)); ++num_of_moves) {
			if (!ValidateIfEmpty(MOVE_FUNCTION(figure_coordinates, figure_colour, num_of_moves))) {
				ValidateIfEnemy(MOVE_FUNCTION(figure_coordinates, figure_colour, num_of_moves), figure_colour);
				break;
			}
		}
	}

	void ValidateEquesMoveFront(const BoardCoordinates& figure_coordinates, const figureColour& figure_colour) {
		ValidateIfEmptyOrEnemy(MoveLeft(MoveFront(figure_coordinates, figure_colour, Constants::equesJump), figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveRight(MoveFront(figure_coordinates, figure_colour, Constants::equesJump), figure_colour), figure_colour);
	}

	void ValidateEquesMoveBack(const BoardCoordinates& figure_coordinates, const figureColour& figure_colour) {
		ValidateIfEmptyOrEnemy(MoveLeft(MoveBack(figure_coordinates, figure_colour, Constants::equesJump), figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveRight(MoveBack(figure_coordinates, figure_colour, Constants::equesJump), figure_colour), figure_colour);
	}

	void ValidateEquesMoveLeft(const BoardCoordinates& figure_coordinates, const figureColour& figure_colour) {
		ValidateIfEmptyOrEnemy(MoveFront(MoveLeft(figure_coordinates, figure_colour, Constants::equesJump), figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveBack(MoveLeft(figure_coordinates, figure_colour, Constants::equesJump), figure_colour), figure_colour);
	}

	void ValidateEquesMoveRight(const BoardCoordinates& figure_coordinates, const figureColour& figure_colour) {
		ValidateIfEmptyOrEnemy(MoveFront(MoveRight(figure_coordinates, figure_colour, Constants::equesJump), figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveBack(MoveRight(figure_coordinates, figure_colour, Constants::equesJump), figure_colour), figure_colour);
	}

	/*------------------------------------------------------------------------------------------------------------*/
	/*                            FUNCTIONS FOR MANIPULATING LEGAL MOVES VECTOR                                   */
	/*------------------------------------------------------------------------------------------------------------*/

	void ClearLegalMoves() {
		legal_moves_.clear();
	}

	void AddLegalMove(BoardCoordinates&& move_coordinate) {
		legal_moves_.emplace_back(move_coordinate);
	}

	bool AddLegalMoveIfRed(BoardCoordinates&& move_coordinate) {
		if (IsPlaceRed(move_coordinate)) {
			AddLegalMove(std::move(move_coordinate));
			return true;
		}
		return false;
	}

	bool AddLegalMoveIfPurple(BoardCoordinates&& move_coordinate) {
		if (IsPlacePurple(move_coordinate)) {
			AddLegalMove(std::move(move_coordinate));
			return true;
		}
		return false;
	}

	/*------------------------------------------------------------------------------------------------------------*/
	/*                                      HELPER BOOLEAN FUNCTIONS                                              */
	/*------------------------------------------------------------------------------------------------------------*/

	bool IsOnBoard(const BoardCoordinates& coordinates) const {
		return (coordinates.x >= 0) && (coordinates.x <= Constants::boardSize - 1) &&
			(coordinates.y >= 0) && (coordinates.y <= Constants::boardSize - 1);
	}

	bool IsPlaceEmpty(const BoardCoordinates& position) const {
		return board_image_[position.y][position.x] == empty_figure_image_;
	}

	bool IsPlaceRed(const BoardCoordinates& position) const {
		return board_image_[position.y][position.x].second == figureColour::Red;
	}

	bool IsPlacePurple(const BoardCoordinates& position) const {
		return board_image_[position.y][position.x].second == figureColour::Purple;
	}

	bool IsRed(const figureColour& colour) const {
		return colour == figureColour::Red;
	}

	bool IsFigureOnTile(const std::shared_ptr<Figure>& figure_ptr) const {
		return figure_ptr != nullptr;
	}


	/*------------------------------------------------------------------------------------------------------------*/
	/*                    FUNCTIONS FOR CALCULATING COORDINATES FOR FIGURE MOVES                                  */
	/*------------------------------------------------------------------------------------------------------------*/

	BoardCoordinates MoveFront(const BoardCoordinates& figure_coordinates, 
								 const figureColour& figure_colour, 
								 const int number_of_spaces = 1) const {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(0, -number_of_spaces) :
															BoardCoordinates(0, number_of_spaces));
	}

	BoardCoordinates MoveBack(const BoardCoordinates& figure_coordinates,
								const figureColour& figure_colour,
								const int number_of_spaces = 1) const {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(0, number_of_spaces) :
															BoardCoordinates(0, -number_of_spaces));
	}

	BoardCoordinates MoveLeft(const BoardCoordinates& figure_coordinates,
								const figureColour& figure_colour,
								const int number_of_spaces = 1) const {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(-number_of_spaces, 0) :
															BoardCoordinates(number_of_spaces, 0));
	}

	 BoardCoordinates MoveRight(const BoardCoordinates& figure_coordinates,
								const figureColour& figure_colour,
								const int number_of_spaces = 1) const {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(number_of_spaces, 0) :
															BoardCoordinates(-number_of_spaces, 0));
	}

	BoardCoordinates MoveDiagonalLeftFront(const BoardCoordinates& figure_coordinates,
											const figureColour& figure_colour,
											const int number_of_spaces = 1) const {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(-number_of_spaces, -number_of_spaces) :
															BoardCoordinates(number_of_spaces, number_of_spaces));
	}

	BoardCoordinates MoveDiagonalLeftBack(const BoardCoordinates& figure_coordinates,
											const figureColour& figure_colour,
											const int number_of_spaces = 1) const {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(-number_of_spaces, number_of_spaces) :
															BoardCoordinates(number_of_spaces, -number_of_spaces));
	}

	BoardCoordinates MoveDiagonalRightFront(const BoardCoordinates& figure_coordinates,
											  const figureColour& figure_colour,
											  const int number_of_spaces = 1) const {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(number_of_spaces, -number_of_spaces) :
															BoardCoordinates(-number_of_spaces, number_of_spaces));
	}

	BoardCoordinates MoveDiagonalRightBack(const BoardCoordinates& figure_coordinates,
											 const figureColour& figure_colour,
											 const int number_of_spaces = 1) const {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(number_of_spaces, number_of_spaces) :
															BoardCoordinates(-number_of_spaces, -number_of_spaces));
	}

	/*------------------------------------------------------------------------------------------------------------*/
	/*                             FUNCTIONS FOR MANAGING BOARD LAYOUT                                            */
	/*------------------------------------------------------------------------------------------------------------*/


	void UpdateBoardLayout(const BoardImage& board_layout) {
		board_image_ = board_layout;
	}

	void UpdateBoardLayout(const RomanChessFigures& figures) {
		board_image_ = MakeBoardImage(figures);
	}

	const BoardImage& GetBoardImage() {
		return board_image_;
	}

	BoardImage&& MakeBoardImage(const RomanChessFigures& figures) const {
		BoardImage result;

		for (int row = 0; row < Constants::boardSize; ++row) {
			for (int collumn = 0; collumn < Constants::boardSize; ++collumn) {
				if (IsFigureOnTile(figures[row][collumn])) {
					result[row][collumn] = figures[row][collumn]->GetFigureImage();
				}
				else {
					result[row][collumn] = empty_figure_image_;
				}
			}
		}
		return std::move(result);
	}

	void SaveBoardImageToDeque() {
		board_image_deque_.emplace_back(board_image_);
		if (IsDequeOverflowed()) {
			board_image_deque_.pop_front();
		}
	}

	bool IsDequeOverflowed() const {
		return board_image_deque_.size() > Constants::dequeMovesNumber;
	}

	/*------------------------------------------------------------------------------------------------------------*/
	/*                             FUNCTIONS FOR IMPLEMENTING GAME MECHANICS                                      */
	/*------------------------------------------------------------------------------------------------------------*/

	const figureColour& GetPlayerTurn() const {
		return player_turn_;
	}

	void NextPlayerTurn() {
		player_turn_ = (player_turn_ == figureColour::Red ? figureColour::Purple : figureColour::Red);
		++number_of_moves_;
	}

	void MoveFigure(const BoardCoordinates& old_position, const BoardCoordinates& new_position) {
		if (IsOnBoard(old_position) && IsOnBoard(new_position)) {
			board_image_[new_position.y][new_position.x] = board_image_[old_position.y][old_position.x];
			board_image_[old_position.y][old_position.x] = empty_figure_image_;
		}
	}

	void CheckIfConsul(BoardCoordinates&& position) {
		if (board_image_[position.y][position.x].first == figureType::Consul) {
			RemoveNumberOfConsuls(board_image_[position.y][position.x].second);
		}
	}

	void RemoveNumberOfConsuls(const figureColour& colour) {
		switch (colour) {
		case figureColour::Red:
			--number_of_consuls_.first;
			break;
		case figureColour::Purple:
			--number_of_consuls_.second;
			break;
		}
	}

	bool CheckIfPontifexMaximus(BoardCoordinates&& position) {
		if (board_image_[position.y][position.x].first == figureType::PontifexMaximus) {
			RewindBoard(board_image_[position.y][position.x].second);
			return true;
		}
		return false;
	}

	void RewindBoard(const figureColour& colour) {
		board_image_ = board_image_deque_[0];
		board_image_deque_.clear();
		RemovePontifexMaximus(colour);
	}

	void RemovePontifexMaximus(const figureColour& colour) {
		BoardRow::iterator figure_iterator;
		for (auto& row : board_image_) {
			figure_iterator = std::find(row.begin(), row.end(), FigureImage(figureType::PontifexMaximus, colour));
			if (figure_iterator != std::end(row)) {
				*figure_iterator = empty_figure_image_;
				break;
			}
		}
	}

	/*------------------------------------------------------------------------------------------------------------*/
	/*                                      FUNCTIONS FOR ENDING GAME                                             */
	/*------------------------------------------------------------------------------------------------------------*/


	void CheckGameOver() {
		if (!BothSidesHaveConsul()) {
			SetGameOver();
		}
	}
	
	void SetGameOver() {
		is_game_over_ = true;
	}

	bool IsGameOver() const {
		return is_game_over_;
	}

	const std::pair<int, int>& GetNumberOfConsuls() const {
		return number_of_consuls_;
	}

	bool BothSidesHaveConsul() const {
		return number_of_consuls_.first && number_of_consuls_.second;
	}


private:
	int number_of_moves_ = 0;
	figureColour player_turn_ = figureColour::Red;

	std::vector<BoardCoordinates> legal_moves_;

	BoardImage board_image_ = Constants::initialBoardImage;

	std::deque<BoardImage> board_image_deque_;

	std::pair<int, int> number_of_consuls_ = std::make_pair(2, 2);
	bool is_game_over_ = false;

	const FigureImage empty_figure_image_ = FigureImage(figureType::no_type, figureColour::no_colour);
};

