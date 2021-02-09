#pragma once
#include <string>
#include <utility>
#include <array>
#include <map>
#include <set>
#include "ID.h"
#include <SFML/Graphics.hpp>

using FigureImage = std::pair<figureType, figureColour>;


namespace Constants {
	constexpr int boardSize = 8;
	constexpr int lastBoardElement = boardSize - 1;
	constexpr int dequeMovesNumber = 20;
	constexpr int PixelMultiplier = 100;

#pragma region FIGURE_IMAGES
	constexpr FigureImage VelesImage_red			  { figureType::Veles,			 figureColour::Red		 };
	constexpr FigureImage VelesImage_purple			  { figureType::Veles,			 figureColour::Purple	 };
	constexpr FigureImage HastatusImage_red			  { figureType::Hastatus,		 figureColour::Red		 };
	constexpr FigureImage HastatusImage_purple		  { figureType::Hastatus,		 figureColour::Purple	 };
	constexpr FigureImage PrincepsImage_red			  { figureType::Princeps,		 figureColour::Red		 };
	constexpr FigureImage PrincepsImage_purple		  { figureType::Princeps,		 figureColour::Purple	 };
	constexpr FigureImage TriariusImage_red			  { figureType::Triarius,		 figureColour::Red		 };
	constexpr FigureImage TriariusImage_purple		  { figureType::Triarius,		 figureColour::Purple	 };
	constexpr FigureImage EquesImage_red			  { figureType::Eques,			 figureColour::Red		 };
	constexpr FigureImage EquesImage_purple			  { figureType::Eques,			 figureColour::Purple	 };
	constexpr FigureImage ConsulImage_red			  { figureType::Consul,			 figureColour::Red		 };
	constexpr FigureImage ConsulImage_purple		  { figureType::Consul,			 figureColour::Purple	 };
	constexpr FigureImage PontifexMaximusImage_red	  { figureType::PontifexMaximus, figureColour::Red		 };
	constexpr FigureImage PontifexMaximusImage_purple { figureType::PontifexMaximus, figureColour::Purple	 };
	constexpr FigureImage EmptyFigureImage			  { figureType::no_type,		 figureColour::no_colour };

	
	static std::set<FigureImage> AllFigureImages = {
		VelesImage_red, VelesImage_purple, HastatusImage_red, HastatusImage_purple,
		PrincepsImage_red, PrincepsImage_purple, TriariusImage_red, TriariusImage_purple,
		EquesImage_red, EquesImage_purple, ConsulImage_red, ConsulImage_purple,
		PontifexMaximusImage_red, PontifexMaximusImage_purple
	};

#pragma endregion

#pragma region BOARD
	using BoardImage = std::array<std::array<FigureImage, boardSize>, boardSize>;
	constexpr std::array<FigureImage, boardSize> EmptyFigureLine{ {
		EmptyFigureImage, EmptyFigureImage, EmptyFigureImage, EmptyFigureImage,
		EmptyFigureImage, EmptyFigureImage, EmptyFigureImage, EmptyFigureImage } };

	constexpr BoardImage initialBoardImage {{
		{{ TriariusImage_purple, PrincepsImage_purple, EquesImage_purple, ConsulImage_purple,
		ConsulImage_purple, PontifexMaximusImage_purple, PrincepsImage_purple, TriariusImage_purple }},

		{{VelesImage_purple, VelesImage_purple, HastatusImage_purple, HastatusImage_purple,
		HastatusImage_purple, HastatusImage_purple, VelesImage_purple, VelesImage_purple }},

		EmptyFigureLine, EmptyFigureLine, EmptyFigureLine, EmptyFigureLine,

		{{ VelesImage_red, VelesImage_red, HastatusImage_red, HastatusImage_red,
		HastatusImage_red, HastatusImage_red, VelesImage_red, VelesImage_red }},

		{{ TriariusImage_red, PrincepsImage_red, EquesImage_red, ConsulImage_red,
		ConsulImage_red, PontifexMaximusImage_red, PrincepsImage_red, TriariusImage_red }}
	}};
	
#pragma endregion


	namespace AI {

		constexpr int AIMovesLimit = 200;
		constexpr int max_value = 1000000;
		constexpr int min_value = -1000000;

		namespace FigureEvaluation {

			//Plays balanced
			static std::map<FigureImage, int> CaesarAIFiguresMap = {
				std::make_pair(VelesImage_red,			    -3),
				std::make_pair(VelesImage_purple,			 3),
				std::make_pair(HastatusImage_red,			-5),
				std::make_pair(HastatusImage_purple,		 5),
				std::make_pair(PrincepsImage_red,			-8),
				std::make_pair(PrincepsImage_purple,		 8),
				std::make_pair(TriariusImage_red,			-10),
				std::make_pair(TriariusImage_purple,		 10),
				std::make_pair(EquesImage_red,				-16),
				std::make_pair(EquesImage_purple,			 16),
				std::make_pair(ConsulImage_red,				-70),
				std::make_pair(ConsulImage_purple,			 70),
				std::make_pair(PontifexMaximusImage_red,	-5),
				std::make_pair(PontifexMaximusImage_purple,  5)
			};

			//Plays defensive
			static std::map<FigureImage, int> AgrippaAIFiguresMap = {
				std::make_pair(VelesImage_red,				-3),
				std::make_pair(VelesImage_purple,			 6),
				std::make_pair(HastatusImage_red,			-5),
				std::make_pair(HastatusImage_purple,		 9),
				std::make_pair(PrincepsImage_red,			-8),
				std::make_pair(PrincepsImage_purple,		 15),
				std::make_pair(TriariusImage_red,			-10),
				std::make_pair(TriariusImage_purple,		 18),
				std::make_pair(EquesImage_red,				-16),
				std::make_pair(EquesImage_purple,			 25),
				std::make_pair(ConsulImage_red,				-50),
				std::make_pair(ConsulImage_purple,			 100),
				std::make_pair(PontifexMaximusImage_red,	-5),
				std::make_pair(PontifexMaximusImage_purple,  7)
			};

			//Plays offensive
			static std::map<FigureImage, int> ScipioAIFiguresMap = {
				std::make_pair(VelesImage_red,				-3),
				std::make_pair(VelesImage_purple,			 1),
				std::make_pair(HastatusImage_red,			-6),
				std::make_pair(HastatusImage_purple,		 3),
				std::make_pair(PrincepsImage_red,			-12),
				std::make_pair(PrincepsImage_purple,		 8),
				std::make_pair(TriariusImage_red,			-16),
				std::make_pair(TriariusImage_purple,		 10),
				std::make_pair(EquesImage_red,				-25),
				std::make_pair(EquesImage_purple,			 16),
				std::make_pair(ConsulImage_red,				-150),
				std::make_pair(ConsulImage_purple,			 70),
				std::make_pair(PontifexMaximusImage_red,	-10),
				std::make_pair(PontifexMaximusImage_purple,  5)
			};

			//Plays super defensive
			static std::map<FigureImage, int> CrassusAIFiguresMap = {
				std::make_pair(VelesImage_red,				  0),
				std::make_pair(VelesImage_purple,			  4),
				std::make_pair(HastatusImage_red,			  0),
				std::make_pair(HastatusImage_purple,		  5),
				std::make_pair(PrincepsImage_red,			  0),
				std::make_pair(PrincepsImage_purple,		  7),
				std::make_pair(TriariusImage_red,			  0),
				std::make_pair(TriariusImage_purple,		  7),
				std::make_pair(EquesImage_red,				  0),
				std::make_pair(EquesImage_purple,			 10),
				std::make_pair(ConsulImage_red,				-15),
				std::make_pair(ConsulImage_purple,			 40),
				std::make_pair(PontifexMaximusImage_red,	  0),
				std::make_pair(PontifexMaximusImage_purple,   3)
			};

			//Plays super offensive
			static std::map<FigureImage, int> VarroAIFiguresMap = {
				std::make_pair(VelesImage_red,				-5),
				std::make_pair(VelesImage_purple,			 0),
				std::make_pair(HastatusImage_red,			-8),
				std::make_pair(HastatusImage_purple,		 0),
				std::make_pair(PrincepsImage_red,			-6),
				std::make_pair(PrincepsImage_purple,		 0),
				std::make_pair(TriariusImage_red,			-8),
				std::make_pair(TriariusImage_purple,		 0),
				std::make_pair(EquesImage_red,				-8),
				std::make_pair(EquesImage_purple,			 0),
				std::make_pair(ConsulImage_red,				-15),
				std::make_pair(ConsulImage_purple,			 10),
				std::make_pair(PontifexMaximusImage_red,	-5),
				std::make_pair(PontifexMaximusImage_purple,  0)
			};

		}

		namespace EvaluationMultiplier {
			using IntegerMap2D = std::array<std::array<int, Constants::boardSize>, Constants::boardSize>;

			//Using Red perspective, Purple starts reading from IntegerMap2D[7][0]

#pragma region STANDARD_PLAYER_MODE
			constexpr IntegerMap2D VelesHastatusMultiplier_Standard = { {
			{{ 0,  0,  0,  0,  0,  0,  0,  0}},
			{{15, 15, 15, 15, 15, 15, 15, 15}},
			{{20, 20, 20, 20, 20, 20, 20, 20}},
			{{20, 15, 20, 15, 20, 15, 20, 15}},
			{{15, 10, 15, 10, 15, 10, 15, 10}},
			{{10, 10, 10, 10, 10, 10, 10, 10}},
			{{ 5,  5,  5,  5,  5,  5,  5,  5}},
			{{ 0,  0,  0,  0,  0,  0,  0,  0}}
			} };

			constexpr IntegerMap2D PrincepsMultiplier_Standard = { {
			{{10, 15, 15, 15, 15, 15, 15, 10}},
			{{ 8, 15, 15, 15, 15, 15, 15,  8}},
			{{ 8, 10, 14, 14, 14, 14, 10,  8}},
			{{ 8, 10, 15, 20, 20, 15, 10,  8}},
			{{ 8, 10, 15, 20, 20, 15, 10,  8}},
			{{ 8, 10, 10, 10, 10, 10, 10,  8}},
			{{ 8, 10, 10, 10, 10, 10, 10,  8}},
			{{ 5, 10, 10, 10, 10, 10, 10,  5}}
			} };

			constexpr IntegerMap2D TriariusMultiplier_Standard = { {
			{{15, 18, 20, 20, 20, 20, 18, 15}},
			{{15, 20, 20, 20, 20, 20, 20, 15}},
			{{ 8, 10, 10, 10, 10, 10, 10,  8}},
			{{ 8, 10, 10, 10, 10, 10, 10,  8}},
			{{ 8, 10, 10, 10, 10, 10, 10,  8}},
			{{ 8, 10, 10, 10, 10, 10, 10,  8}},
			{{10, 10, 10, 10, 10, 10, 10, 10}},
			{{ 5,  5,  5, 15, 15,  5,  5,  5}}
			} };

			constexpr IntegerMap2D EquesMultiplier_Standard = { {
			{{ 5,  7,  9, 14, 14,  9,  7,  5}},
			{{ 7,  9, 14, 16, 16, 14,  9,  7}},
			{{ 9, 14, 16, 18, 18, 16, 14,  9}},
			{{12, 16, 18, 20, 20, 18, 16, 12}},
			{{10, 14, 16, 18, 18, 16, 14, 10}},
			{{ 9, 12, 14, 16, 16, 14, 12,  9}},
			{{ 7,  9, 10, 10, 10, 10,  9,  7}},
			{{ 5,  7,  9,  9,  9,  9,  7,  5}}
			} };

			constexpr IntegerMap2D ConsulMultiplier_Standard = { {
			{{ 5,  8,  8,  8,  8,  8,  8,  5}},
			{{ 8, 10, 10, 10, 10, 10, 10,  8}},
			{{ 8, 10, 10, 10, 10, 10, 10,  8}},
			{{ 8, 10, 10, 10, 10, 10, 10,  8}},
			{{ 8, 10, 10, 10, 10, 10, 10,  8}},
			{{ 8, 10, 10, 10, 10, 10, 10,  8}},
			{{ 8, 10, 10, 10, 10, 10, 10,  8}},
			{{ 5,  8,  8,  8,  8,  8,  8,  5}}
			} };

			constexpr IntegerMap2D PontifexMaximusMultiplier_Standard = { {
			{{10, 10, 10, 10, 10, 10, 10, 10}},
			{{10, 10, 10, 10, 10, 10, 10, 10}},
			{{10, 10, 10, 10, 10, 10, 10, 10}},
			{{10, 10, 10, 10, 10, 10, 10, 10}},
			{{10, 10, 10, 10, 10, 10, 10, 10}},
			{{10, 10, 10, 10, 10, 10, 10, 10}},
			{{12, 16, 16, 16, 16, 16, 16, 12}},
			{{15, 20, 20, 20, 20, 20, 20, 15}}
			} };
#pragma endregion

			static std::map<figureType, IntegerMap2D> EvaluationMultiplierMap_Standard = { {
					std::make_pair(figureType::Veles,			VelesHastatusMultiplier_Standard),
					std::make_pair(figureType::Hastatus,		VelesHastatusMultiplier_Standard),
					std::make_pair(figureType::Princeps,		PrincepsMultiplier_Standard),
					std::make_pair(figureType::Triarius,		TriariusMultiplier_Standard),
					std::make_pair(figureType::Eques,			EquesMultiplier_Standard),
					std::make_pair(figureType::Consul,			ConsulMultiplier_Standard),
					std::make_pair(figureType::PontifexMaximus, PontifexMaximusMultiplier_Standard),
			} };

#pragma region FABIAN_STRATEGY_PLAYER_MODE

			constexpr IntegerMap2D VelesHastatusMultiplier_FabianStrategy = { {
			{{-50, -50, -50, -50, -50, -50, -50, -50}},
			{{-40, -40, -40, -40, -40, -40, -40, -40}},
			{{-30, -30, -30, -30, -30, -30, -30, -30}},
			{{-20, -20, -20, -20, -20, -20, -20, -20}},
			{{-10, -10, -10, -10, -10, -10, -10, -10}},
			{{  0,   0,   0,   0,   0,   0,   0,   0}},
			{{ 20,  20,  20,  20,  20,  20,  20,  20}},
			{{ 10,  10,  10,  10,  10,  10,  10,  10}},
			} };

			constexpr IntegerMap2D PrincepsMultiplier_FabianStrategy = { {
			{{-50, -50, -50, -50, -50, -50, -50, -50}},
			{{-50, -50, -50, -50, -50, -50, -50, -50}},
			{{-10, -10, -10, -10, -10, -10, -10, -10}},
			{{  0,   0,   0,   0,   0,   0,   0,   0}},
			{{ 10,  10,  10,  10,  10,  10,  10,  10}},
			{{ 15,  15,  15,  15,  15,  15,  15,  15}},
			{{ 15,  15,  15,  15,  15,  15,  15,  15}},
			{{ 15,  15,  15,  15,  15,  15,  15,  15}},
			} };

			constexpr IntegerMap2D TriariusMultiplier_FabianStrategy = { {
			{{-50, -50, -50, -50, -50, -50, -50, -50}},
			{{-50, -50, -50, -50, -50, -50, -50, -50}},
			{{-10, -10, -10, -10, -10, -10, -10, -10}},
			{{  0,   0,   0,   0,   0,   0,   0,   0}},
			{{ 15,  15,  15,  15,  15,  15,  15,  15}},
			{{ 15,  15,  15,  15,  15,  15,  15,  15}},
			{{ 15,  15,  15,  15,  15,  15,  15,  15}},
			{{ 15,  15,  15,  15,  15,  15,  15,  15}},
			} };

			constexpr IntegerMap2D EquesMultiplier_FabianStrategy = { {
			{{ 10,  15,  15,  15,  15,  15,  15,  10}},
			{{ 10,  15,  15,  15,  15,  15,  15,  10}},
			{{ 10,  15,  15,  15,  15,  15,  15,  10}},
			{{ 10,  20,  20,  20,  20,  20,  15,  10}},
			{{ 10,  15,  20,  20,  20,  15,  15,  10}},
			{{ 10,  15,  15,  15,  15,  15,  15,  10}},
			{{ 10,  15,  15,  15,  15,  15,  15,  10}},
			{{ 10,  10,  10,  10,  10,  10,  10,  10}},
			} };

			constexpr IntegerMap2D ConsulMultiplier_FabianStrategy = { {
			{{-50, -50, -50, -50, -50, -50, -50, -50}},
			{{-50, -50, -50, -50, -50, -50, -50, -50}},
			{{-50, -50, -50, -50, -50, -50, -50, -50}},
			{{-50, -50, -50, -50, -50, -50, -50, -50}},
			{{ 10,  10,  10,  10,  10,  10,  10,  10}},
			{{ 10,  10,  10,  10,  10,  10,  10,  10}},
			{{ 10,  10,  10,  10,  10,  10,  10,  10}},
			{{ 10,  10,  10,  10,  10,  10,  10,  10}},
			} };

			constexpr IntegerMap2D PontifexMaximusMultiplier_FabianStrategy = { {
			{{-50, -50, -50, -50, -50, -50, -50, -50}},
			{{-40, -40, -40, -40, -40, -40, -40, -40}},
			{{-30, -30, -30, -30, -30, -30, -30, -30}},
			{{-20, -20, -20, -20, -20, -20, -20, -20}},
			{{-10, -10, -10, -10, -10, -10, -10, -10}},
			{{  0,   0,   0,   0,   0,   0,   0,   0}},
			{{ 10,  10,  10,  10,  10,  10,  10,  10}},
			{{ 10,  10,  10,  10,  10,  10,  10,  10}},
			} };
#pragma endregion

			static std::map<figureType, IntegerMap2D> EvaluationMultiplierMap_FabianStrategy = { {
					std::make_pair(figureType::Veles,			VelesHastatusMultiplier_FabianStrategy),
					std::make_pair(figureType::Hastatus,		VelesHastatusMultiplier_FabianStrategy),
					std::make_pair(figureType::Princeps,		PrincepsMultiplier_FabianStrategy),
					std::make_pair(figureType::Triarius,		TriariusMultiplier_FabianStrategy),
					std::make_pair(figureType::Eques,			EquesMultiplier_FabianStrategy),
					std::make_pair(figureType::Consul,			ConsulMultiplier_FabianStrategy),
					std::make_pair(figureType::PontifexMaximus, PontifexMaximusMultiplier_FabianStrategy),
			} };

		}
	}
}

namespace ImagePaths {
	inline const std::string Board =			"images/Board.PNG";
	inline const std::string Figures =			"images/Figures.PNG";
	inline const std::string Yellow_Rectangle = "images/Yellow_Rectangle.PNG";
	inline const std::string Red_Rectangle =	"images/Red_Rectangle.PNG";

}


namespace SFMLConstants {
	const sf::Vector2i FigureSpriteRectSize(100, 100);

	const std::pair<sf::Vector2i, sf::Vector2i> FigureSpriteRectPos_Veles			(sf::Vector2(0,	  0), sf::Vector2(0,   100));
	const std::pair<sf::Vector2i, sf::Vector2i> FigureSpriteRectPos_Hastatus		(sf::Vector2(100, 0), sf::Vector2(100, 100));
	const std::pair<sf::Vector2i, sf::Vector2i> FigureSpriteRectPos_Princeps		(sf::Vector2(200, 0), sf::Vector2(200, 100));
	const std::pair<sf::Vector2i, sf::Vector2i> FigureSpriteRectPos_Triarius		(sf::Vector2(300, 0), sf::Vector2(300, 100));
	const std::pair<sf::Vector2i, sf::Vector2i> FigureSpriteRectPos_Eques			(sf::Vector2(400, 0), sf::Vector2(400, 100));
	const std::pair<sf::Vector2i, sf::Vector2i> FigureSpriteRectPos_Consul			(sf::Vector2(500, 0), sf::Vector2(500, 100));
	const std::pair<sf::Vector2i, sf::Vector2i> FigureSpriteRectPos_PontifexMaximus (sf::Vector2(600, 0), sf::Vector2(600, 100));
}


namespace ExceptionMessages {
	inline const std::string IsPlaceInFrontEmptyPurple =		"IsPlaceInFrontEmptyPurple()";
	inline const std::string IsEnemyOnDiagonalLeftPurple =		"IsEnemyOnDiagonalLeftPurple()";
	inline const std::string IsEnemyOnDiagonalRightPurple =		"IsEnemyOnDiagonalRightPurple()";
	inline const std::string IsPlaceInFrontEmptyRed =			"IsPlaceInFrontEmptyRed()";
	inline const std::string IsEnemyOnDiagonalLeftRed =			"IsEnemyOnDiagonalLeftRed()";
	inline const std::string IsEnemyOnDiagonalRightRed =		"IsEnemyOnDiagonalRightRed()";

	inline const std::string VelesGetLegalMovesRed =			"VelesGetLegalMovesRed()";
	inline const std::string VelesGetLegalMovesPurple =			"VelesGetLegalMovesPurple()";
	inline const std::string HastatusGetLegalMovesRed =			"HastatusGetLegalMovesRed()";
	inline const std::string HastatusGetLegalMovesPurple =		"HastatusGetLegalMovesPurple()";
	inline const std::string PrincepsGetLegalMovesRed =			"PrincepsGetLegalMovesRed()";
	inline const std::string PrincepsGetLegalMovesPurple =		"PrincepsGetLegalMovesPurple()";
	inline const std::string TriariusGetLegalMovesRed =			"TriariusGetLegalMovesRed()";
	inline const std::string TriariusGetLegalMovesPurple =		"TriariusGetLegalMovesPurple()";
	inline const std::string EquesGetLegalMovesRed =			"EquesGetLegalMovesRed()";
	inline const std::string EquesGetLegalMovesPurple =			"EquesGetLegalMovesPurple()";
}

