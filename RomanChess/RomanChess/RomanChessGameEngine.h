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
#include "FigureImage.h"
#include "BadInputException.h"
#include "TypeAliases.h"

using BoardRow = std::array<FigureImage, Constants::boardSize>;
using BoardImage = std::array<BoardRow, Constants::boardSize>;
using RomanChessFigures = std::array<std::array<std::shared_ptr<Figure>, Constants::boardSize>, Constants::boardSize>;

class RomanChessGameEngine {

public:

	RomanChessGameEngine() noexcept {}

	RomanChessGameEngine(const BoardImage& board_image) noexcept : board_image_{board_image} {}

	RomanChessGameEngine(const RomanChessFigures& chess_figures) noexcept {
		UpdateBoardLayout(chess_figures);
	}

	~RomanChessGameEngine() noexcept {}


	/*------------------------------------------------------------------------------------------------------------*/
	/*										CALCULATING LEGAL MOVES		 								          */
	/*------------------------------------------------------------------------------------------------------------*/

#pragma region CALCULATING LEGAL MOVES

	[[nodiscard]] bool IsMoveLegal(BoardCoordinates new_position) const noexcept {
		return std::any_of(legal_moves_.begin(), legal_moves_.end(),
			[&new_position](const auto& legal_move) {return new_position == legal_move; });
	}

	void CalculateLegalMoves(const std::shared_ptr<Figure>& figure) {
		if (figure != nullptr)
			CalculateLegalMoves(figure->GetFigureImage(), figure->GetPosition());
	}

	void CalculateLegalMoves(const BoardCoordinates figure_coordinates) {
		auto figure_image = board_image_[figure_coordinates.y][figure_coordinates.x];
		CalculateLegalMoves(figure_image, figure_coordinates);
	}


	void CalculateLegalMoves(const FigureImage figure_image, const BoardCoordinates figure_coordinates) {
		ClearLegalMoves();
		switch (figure_image.type) {
		case figureType::Veles:
			CalculateLegalMovesVeles(figure_coordinates, figure_image.colour);
			break;
		case figureType::Hastatus:
			CalculateLegalMovesHastatus(figure_coordinates, figure_image.colour);
			break;
		case figureType::Princeps:
			CalculateLegalMovesPrinceps(figure_coordinates, figure_image.colour);
			break;
		case figureType::Triarius:
			CalculateLegalMovesTriarius(figure_coordinates, figure_image.colour);
			break;
		case figureType::Eques:
			CalculateLegalMovesEques(figure_coordinates, figure_image.colour);
			break;
		case figureType::Consul:
			CalculateLegalMovesConsul(figure_coordinates, figure_image.colour);
			break;
		case figureType::PontifexMaximus:
			CalculateLegalMovesPontifexMaximus(figure_coordinates, figure_image.colour);
			break;
		default:
			break;
		}
	}

	void CalculateLegalMovesVeles(const BoardCoordinates figure_coordinates,
								  const figureColour figure_colour) noexcept {
		ValidateIfEmpty(MoveFront(figure_coordinates, figure_colour));
		ValidateIfEnemy(MoveDiagonalLeftFront(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEnemy(MoveDiagonalRightFront(figure_coordinates, figure_colour), figure_colour);
	}

	void CalculateLegalMovesHastatus(const BoardCoordinates figure_coordinates,
									 const figureColour figure_colour) noexcept {
		ValidateIfEmptyFront(figure_coordinates, figure_colour, Constants::hastatusMaxMovesFront);
		ValidateIfEnemy(MoveDiagonalLeftFront(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEnemy(MoveDiagonalRightFront(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmpty(MoveBack(figure_coordinates, figure_colour));
	}

	void CalculateLegalMovesPrinceps(const BoardCoordinates figure_coordinates,
									 const figureColour figure_colour) noexcept {
		ValidateIfEmpty(MoveFront(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveBack(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveLeft(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveRight(figure_coordinates, figure_colour));

		ValidateDiagonalMoves(figure_coordinates, figure_colour);
	}

	void CalculateLegalMovesTriarius(const BoardCoordinates figure_coordinates,
									 const figureColour figure_colour) noexcept {
		ValidateIfEmpty(MoveDiagonalLeftFront(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalRightFront(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalLeftBack(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalRightBack(figure_coordinates, figure_colour));

		ValidateStraightMoves(figure_coordinates, figure_colour);
	}

	void CalculateLegalMovesEques(const BoardCoordinates figure_coordinates,
								  const figureColour figure_colour) noexcept {
		ValidateEquesMoveFront(figure_coordinates, figure_colour);
		ValidateEquesMoveBack(figure_coordinates, figure_colour);
		ValidateEquesMoveLeft(figure_coordinates, figure_colour);
		ValidateEquesMoveRight(figure_coordinates, figure_colour);
	}

	void CalculateLegalMovesConsul(const BoardCoordinates figure_coordinates,
								   const figureColour figure_colour) noexcept {
		ValidateIfEmpty(MoveFront(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalRightFront(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveRight(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalRightBack(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveBack(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalLeftBack(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveLeft(figure_coordinates, figure_colour));
		ValidateIfEmpty(MoveDiagonalLeftFront(figure_coordinates, figure_colour));
	}

	void CalculateLegalMovesPontifexMaximus(const BoardCoordinates figure_coordinates,
											const figureColour figure_colour) {
		ValidateIfEmptyOrEnemy(MoveFront(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveDiagonalRightFront(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveRight(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveDiagonalRightBack(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveBack(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveDiagonalLeftBack(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveLeft(figure_coordinates, figure_colour), figure_colour);
		ValidateIfEmptyOrEnemy(MoveDiagonalLeftFront(figure_coordinates, figure_colour), figure_colour);
	}

	[[nodiscard]] const std::vector<BoardCoordinates>& GetLegalMoves(const std::shared_ptr<Figure>& figure) noexcept {
		CalculateLegalMoves(figure);
		return legal_moves_;
	}

	[[nodiscard]] const std::vector<BoardCoordinates>& GetLegalMoves() noexcept {
		return legal_moves_;
	}

#pragma endregion 

	/*------------------------------------------------------------------------------------------------------------*/
	/*										   VALIDATING MOVES													  */
	/*------------------------------------------------------------------------------------------------------------*/

#pragma region VALIDATING MOVES

	bool ValidateIfEmpty(BoardCoordinates position) noexcept {
		if (IsOnBoard(position))
			if (IsPlaceEmpty(position))
				return AddLegalMove(std::move(position));

		return false;
	}

	bool ValidateIfEnemy(BoardCoordinates position, const figureColour figure_colour) {
		if (IsOnBoard(position))
			switch (figure_colour) {
			case figureColour::Red:
				return AddLegalMoveIfPurple(std::move(position));
				break;
			case figureColour::Purple:
				return AddLegalMoveIfRed(std::move(position));
				break;
			default:
				throw BadInputException(ExceptionMessages::ValidateIfEnemy);
				break;
			}
		return false;
	}

	void ValidateIfEmptyOrEnemy(BoardCoordinates position, const figureColour figure_colour) noexcept {
		if (IsOnBoard(position)) 
			IsPlaceEmpty(position) ? ValidateIfEmpty(std::move(position)) :
						   			 ValidateIfEnemy(std::move(position), figure_colour);
	}

	void ValidateIfEmptyFront(const BoardCoordinates figure_coordinates, 
							  const figureColour figure_colour,
							  const int8 num_of_places) noexcept {
		for (int8 num_of_moves = int8(1); num_of_moves <= num_of_places; ++num_of_moves) 
			if (!ValidateIfEmpty(MoveFront(figure_coordinates, figure_colour, num_of_moves))) 
				break;
	}

	void ValidateDiagonalMoves(const BoardCoordinates figure_coordinates,
							   const figureColour figure_colour) noexcept {

		ValidateMovesInDirection(figure_coordinates, figure_colour,
								[this](const BoardCoordinates figure_coordinates,
									   const figureColour figure_colour,
									   const int8 number_of_spaces)
								{return MoveDiagonalLeftFront(figure_coordinates, figure_colour, number_of_spaces); });
			
		ValidateMovesInDirection(figure_coordinates, figure_colour,
								[this](const BoardCoordinates figure_coordinates, 
									   const figureColour figure_colour, 
									   const int8 number_of_spaces)
								{return MoveDiagonalRightFront(figure_coordinates, figure_colour, number_of_spaces); });

		ValidateMovesInDirection(figure_coordinates, figure_colour,
								[this](const BoardCoordinates figure_coordinates,
									   const figureColour figure_colour, 
									   const int8 number_of_spaces)
								{return MoveDiagonalLeftBack(figure_coordinates, figure_colour, number_of_spaces); });

		ValidateMovesInDirection(figure_coordinates, figure_colour,
								[this](const BoardCoordinates figure_coordinates, 
									   const figureColour figure_colour, 
									   const int8 number_of_spaces)
								{return MoveDiagonalRightBack(figure_coordinates, figure_colour, number_of_spaces); });

	}

	void ValidateStraightMoves(const BoardCoordinates figure_coordinates, 
							   const figureColour figure_colour) noexcept {

		ValidateMovesInDirection(figure_coordinates, figure_colour,
			[this](const BoardCoordinates figure_coordinates,
				   const figureColour figure_colour,
				   const int8 number_of_spaces)
			{return MoveFront(figure_coordinates, figure_colour, number_of_spaces); });

		ValidateMovesInDirection(figure_coordinates, figure_colour,
			[this](const BoardCoordinates figure_coordinates,
				   const figureColour figure_colour,
				   const int8 number_of_spaces)
			{return MoveBack(figure_coordinates, figure_colour, number_of_spaces); });

		ValidateMovesInDirection(figure_coordinates, figure_colour,
			[this](const BoardCoordinates figure_coordinates,
				   const figureColour figure_colour,
				   const int8 number_of_spaces)
			{return MoveLeft(figure_coordinates, figure_colour, number_of_spaces); });

		ValidateMovesInDirection(figure_coordinates, figure_colour,
			[this](const BoardCoordinates figure_coordinates,
				   const figureColour figure_colour,
				   const int8 number_of_spaces)
			{return MoveRight(figure_coordinates, figure_colour, number_of_spaces); });
	}

	template <class MOVE_LAMBDA>
	void ValidateMovesInDirection(const BoardCoordinates figure_coordinates, 
								  const figureColour figure_colour,
								  MOVE_LAMBDA&& MOVE_FUNCTION) noexcept {
		for (int8 num_of_moves = int8(1);
			IsOnBoard(MOVE_FUNCTION(figure_coordinates, figure_colour, num_of_moves));
			++num_of_moves) {
			if (!ValidateIfEmpty(MOVE_FUNCTION(figure_coordinates, figure_colour, num_of_moves))) {
				ValidateIfEnemy(MOVE_FUNCTION(figure_coordinates, figure_colour, num_of_moves), figure_colour);
				break;
			}
		}
	}

	void ValidateEquesMoveFront(const BoardCoordinates figure_coordinates,
								const figureColour figure_colour) noexcept {
		ValidateIfEmptyOrEnemy(MoveLeft(MoveFront(figure_coordinates, figure_colour, Constants::equesJump),
										figure_colour),
							   figure_colour);
		ValidateIfEmptyOrEnemy(MoveRight(MoveFront(figure_coordinates, figure_colour, Constants::equesJump),
										 figure_colour),
							   figure_colour);
	}

	void ValidateEquesMoveBack(const BoardCoordinates figure_coordinates,
							   const figureColour figure_colour) noexcept {
		ValidateIfEmptyOrEnemy(MoveLeft(MoveBack(figure_coordinates, figure_colour, Constants::equesJump),
										figure_colour),
							   figure_colour);
		ValidateIfEmptyOrEnemy(MoveRight(MoveBack(figure_coordinates, figure_colour, Constants::equesJump),
										 figure_colour),
							   figure_colour);
	}

	void ValidateEquesMoveLeft(const BoardCoordinates figure_coordinates,
							   const figureColour figure_colour) noexcept {
		ValidateIfEmptyOrEnemy(MoveFront(MoveLeft(figure_coordinates, figure_colour, Constants::equesJump),
										 figure_colour),
							   figure_colour);
		ValidateIfEmptyOrEnemy(MoveBack(MoveLeft(figure_coordinates, figure_colour, Constants::equesJump),
												 figure_colour),
							   figure_colour);
	}

	void ValidateEquesMoveRight(const BoardCoordinates figure_coordinates, 
								const figureColour figure_colour) noexcept {
		ValidateIfEmptyOrEnemy(MoveFront(MoveRight(figure_coordinates, figure_colour, Constants::equesJump),
										 figure_colour), 
							   figure_colour);
		ValidateIfEmptyOrEnemy(MoveBack(MoveRight(figure_coordinates, figure_colour, Constants::equesJump),
										figure_colour),
							   figure_colour);
	}

#pragma endregion

	/*------------------------------------------------------------------------------------------------------------*/
	/*									MANIPULATING LEGAL MOVES VECTOR							                  */
	/*------------------------------------------------------------------------------------------------------------*/

#pragma region MANIPULATING LEGAL MOVES VECTOR

	void ClearLegalMoves() noexcept {
		legal_moves_.clear();
	}

	bool AddLegalMove(BoardCoordinates move_coordinate) noexcept {
		legal_moves_.emplace_back(move_coordinate);
		return true;
	}

	bool AddLegalMoveIfRed(BoardCoordinates move_coordinate) noexcept {
		if (IsPlaceRed(move_coordinate)) 
			return AddLegalMove(std::move(move_coordinate));
		else
			return false;
	}

	bool AddLegalMoveIfPurple(BoardCoordinates move_coordinate) noexcept {
		if (IsPlacePurple(move_coordinate))
			return AddLegalMove(std::move(move_coordinate));
		else
			return false;
	}

#pragma endregion

	/*------------------------------------------------------------------------------------------------------------*/
	/*                                     AUXILIARY BOOLEAN FUNCTIONS                                            */
	/*------------------------------------------------------------------------------------------------------------*/

#pragma region AUXILIARY BOOLEAN FUNCTIONS 

	[[nodiscard]] bool IsOnBoard(const BoardCoordinates coordinates) const noexcept {
		return (coordinates.x >= 0) && (coordinates.x <= Constants::boardSize - 1) &&
			   (coordinates.y >= 0) && (coordinates.y <= Constants::boardSize - 1);
	}

	[[nodiscard]] bool IsPlaceEmpty(const BoardCoordinates position) const noexcept {
		return board_image_[position.y][position.x] == Constants::EmptyFigureImage;
	}

	[[nodiscard]] bool IsPlaceRed(const BoardCoordinates position) const noexcept {
		return board_image_[position.y][position.x].colour == figureColour::Red;
	}

	[[nodiscard]] bool IsPlacePurple(const BoardCoordinates position) const noexcept {
		return board_image_[position.y][position.x].colour == figureColour::Purple;
	}

	[[nodiscard]] bool IsRed(const figureColour colour) const noexcept {
		return colour == figureColour::Red;
	}

	[[nodiscard]] bool IsPontifexMaximus(const figureType type) const noexcept {
		return type == figureType::PontifexMaximus;
	}

	[[nodiscard]] bool IsFigureOnTile(const std::shared_ptr<Figure>& figure_ptr) const noexcept{
		return figure_ptr != nullptr;
	}

	[[nodiscard]] bool LegalMovesExist() const noexcept {
		return legal_moves_.size() > std::size_t(0);
	}

#pragma endregion

	/*------------------------------------------------------------------------------------------------------------*/
	/*									CALCULATING FIGURE MOVES COORDINATES									  */
	/*------------------------------------------------------------------------------------------------------------*/

#pragma region CALCULATING FIGURE MOVES COORDINATES

	[[nodiscard]] BoardCoordinates MoveFront(const BoardCoordinates figure_coordinates,
											const figureColour figure_colour, 
											const int8 number_of_spaces = int8(1)) const noexcept {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(int8(0), -number_of_spaces) :
															BoardCoordinates(int8(0), number_of_spaces));
	}

	[[nodiscard]] BoardCoordinates MoveBack(const BoardCoordinates figure_coordinates,
											const figureColour figure_colour,
											const int8 number_of_spaces = int8(1)) const noexcept {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(int8(0), number_of_spaces) :
															BoardCoordinates(int8(0), -number_of_spaces));
	}

	[[nodiscard]] BoardCoordinates MoveLeft(const BoardCoordinates figure_coordinates,
											const figureColour figure_colour,
											const int8 number_of_spaces = int8(1)) const noexcept {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(-number_of_spaces, int8(0)) :
															BoardCoordinates(number_of_spaces, int8(0)));
	}

	[[nodiscard]] BoardCoordinates MoveRight(const BoardCoordinates figure_coordinates,
											 const figureColour figure_colour,
											 const int8 number_of_spaces = int8(1)) const noexcept {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(number_of_spaces, int8(0)) :
															BoardCoordinates(-number_of_spaces, int8(0)));
	}

	[[nodiscard]] BoardCoordinates MoveDiagonalLeftFront(const BoardCoordinates figure_coordinates,
														 const figureColour figure_colour,
														 const int8 number_of_spaces = int8(1)) const noexcept {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(-number_of_spaces, -number_of_spaces) :
															BoardCoordinates(number_of_spaces, number_of_spaces));
	}

	[[nodiscard]] BoardCoordinates MoveDiagonalLeftBack(const BoardCoordinates figure_coordinates,
														const figureColour figure_colour,
														const int8 number_of_spaces = int8(1)) const noexcept {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(-number_of_spaces, number_of_spaces) :
															BoardCoordinates(number_of_spaces, -number_of_spaces));
	}

	[[nodiscard]] BoardCoordinates MoveDiagonalRightFront(const BoardCoordinates figure_coordinates,
														  const figureColour figure_colour,
														  const int8 number_of_spaces = int8(1)) const noexcept {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(number_of_spaces, -number_of_spaces) :
															BoardCoordinates(-number_of_spaces, number_of_spaces));
	}

	[[nodiscard]] BoardCoordinates MoveDiagonalRightBack(const BoardCoordinates figure_coordinates,
														 const figureColour figure_colour,
														 const int8 number_of_spaces = int8(1)) const noexcept {
		return figure_coordinates + (IsRed(figure_colour) ? BoardCoordinates(number_of_spaces, number_of_spaces) :
															BoardCoordinates(-number_of_spaces, -number_of_spaces));
	}

#pragma endregion

	/*------------------------------------------------------------------------------------------------------------*/
	/*										   MANAGING BOARD LAYOUT				                              */
	/*------------------------------------------------------------------------------------------------------------*/

#pragma region MANAGING BOARD LAYOUT

	void UpdateBoardLayout(const BoardImage board_layout) noexcept {
		board_image_ = board_layout;
	}

	void UpdateBoardLayout(const RomanChessFigures& figures) noexcept {
		board_image_ = MakeBoardImage(figures);
	}

	[[nodiscard]] const BoardImage& GetBoardImage() const noexcept{
		return board_image_;
	}

	[[nodiscard]] BoardImage&& MakeBoardImage(const RomanChessFigures& figures) const noexcept {
		BoardImage result;

		for (int8 row = int8(0); row < Constants::boardSize; ++row) 
			for (int8 collumn = int8(0); collumn < Constants::boardSize; ++collumn)
				PopulateTileOnBoardImage(figures, result, BoardCoordinates(collumn, row));
		
		return std::move(result);
	}

	void PopulateTileOnBoardImage(const RomanChessFigures& figures, BoardImage& board_image,
								  const BoardCoordinates coordinates) const noexcept {
		if (IsFigureOnTile(figures[coordinates.y][coordinates.x]))
			board_image[coordinates.y][coordinates.x] = figures[coordinates.y][coordinates.x]->GetFigureImage();
		else
			board_image[coordinates.y][coordinates.x] = Constants::EmptyFigureImage;
	}

	void SaveBoardImageToDeque() noexcept {
		board_image_deque_.emplace_back(board_image_);
		if (IsDequeOverflowed())
			board_image_deque_.pop_front();
	}

	[[nodiscard]] bool IsDequeOverflowed() const noexcept {
		return board_image_deque_.size() > Constants::dequeMovesNumber;
	}

#pragma endregion

	/*------------------------------------------------------------------------------------------------------------*/
	/*										IMPLEMENTING GAME MECHANICS			                                  */
	/*------------------------------------------------------------------------------------------------------------*/

#pragma region IMPLEMENTING GAME MECHANICS

	[[nodiscard]] const figureColour GetPlayerTurn() const noexcept {
		return player_turn_;
	}

	void NextPlayerTurn() noexcept {
		player_turn_ = (player_turn_ == figureColour::Red ? figureColour::Purple : figureColour::Red);
		++moves_counter_;
	}

	void MoveFigure(const BoardCoordinates old_position, const BoardCoordinates new_position) noexcept {
		if (IsOnBoard(old_position) && IsOnBoard(new_position)) {
			board_image_[new_position.y][new_position.x] = board_image_[old_position.y][old_position.x];
			board_image_[old_position.y][old_position.x] = Constants::EmptyFigureImage;
		}
	}

	void CheckIfConsul(BoardCoordinates position) noexcept {
		if (board_image_[position.y][position.x].type == figureType::Consul)
			DecreaseNumberOfConsuls(board_image_[position.y][position.x].colour);
	}

	void DecreaseNumberOfConsuls(const figureColour colour) noexcept {
		switch (colour) {
		case figureColour::Red:
			--number_of_consuls_.first;
			break;
		case figureColour::Purple:
			--number_of_consuls_.second;
			break;
		}
	}

	void InitializeNumberOfConsuls() {
		number_of_consuls_ = std::make_pair(int8(0), int8(0));
		for (auto& row : board_image_)
			CountNumberOfConsulsInRow(row);
	}

	void CountNumberOfConsulsInRow(const BoardRow& row) {
		if (number_of_consuls_.first < 2)
			number_of_consuls_.first += static_cast<int8>(std::count(row.begin(), row.end(), Constants::ConsulImage_red));

		if (number_of_consuls_.second < 2)
			number_of_consuls_.second += static_cast<int8>(std::count(row.begin(), row.end(), Constants::ConsulImage_purple));
	}

	[[nodiscard]] bool CheckIfPontifexMaximus(BoardCoordinates position) noexcept {
		if (!IsPontifexMaximus(board_image_[position.y][position.x].type))
			return false;
		else
			RewindBoard(board_image_[position.y][position.x].colour);
		return true;
	}

	void RewindBoard(const figureColour colour) noexcept {
		board_image_ = board_image_deque_[0];
		board_image_deque_.clear();
		RemovePontifexMaximus(colour);
		InitializeNumberOfConsuls();
	}

	void RemovePontifexMaximus(const figureColour colour) noexcept {
		for (auto& row : board_image_)
			if (CheckRowForPontifexMaximus(row, colour))
				return;
	}

	bool CheckRowForPontifexMaximus(BoardRow& row, figureColour colour) noexcept {
		BoardRow::iterator figure_iterator = std::find(row.begin(), row.end(),
													   FigureImage(figureType::PontifexMaximus, colour));
		bool is_found = figure_iterator != std::end(row);

		if (is_found)
			*figure_iterator = Constants::EmptyFigureImage;
		return is_found;
	}

#pragma endregion

	/*------------------------------------------------------------------------------------------------------------*/
	/*												ENDING GAME												      */
	/*------------------------------------------------------------------------------------------------------------*/

#pragma region ENDING GAME

	void CheckGameOver() noexcept {
		if (!BothSidesHaveConsul())
			SetGameOver();
	}
	
	void SetGameOver() noexcept {
		is_game_over_ = true;
	}

	[[nodiscard]] bool IsGameOver() const noexcept {
		return is_game_over_;
	}

	[[nodiscard]] const std::pair<int, int>& GetNumberOfConsuls() const noexcept {
		return number_of_consuls_;
	}

	[[nodiscard]] bool BothSidesHaveConsul() const noexcept {
		return number_of_consuls_.first && number_of_consuls_.second;
	}

#pragma endregion

private:
	/*------------------------------------------------------------------------------------------------------------*/
	/*											  CLASS MEMBERS											          */
	/*------------------------------------------------------------------------------------------------------------*/

#pragma region CLASS MEMBERS

	uint16 moves_counter_ = uint16(0);
	figureColour player_turn_ = figureColour::Red;

	std::vector<BoardCoordinates> legal_moves_;

	BoardImage board_image_ = Constants::initialBoardImage;

	std::deque<BoardImage> board_image_deque_;

	std::pair<int8, int8> number_of_consuls_ = std::make_pair(int8(2), int8(2));
	bool is_game_over_ = false;

#pragma endregion
};

