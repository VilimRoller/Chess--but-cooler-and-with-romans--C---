#pragma once
#include <string>
#include <map>
#include <utility>
#include <array>
#include "ID.h"

using FigureImage = std::pair<figureType, figureColour>;

namespace Constants {
	constexpr short int boardSize = 8;

	//Maximum number of figures
	constexpr unsigned short int velesMaxNum = 5;
	constexpr unsigned short int hastatusMaxNum = 3;
	constexpr unsigned short int princepsMaxNum = 2;
	constexpr unsigned short int triariusMaxNum = 2;
	constexpr unsigned short int equesMaxNum = 1;
	constexpr unsigned short int consulMaxNum = 2;
	constexpr unsigned short int pontifexMaximusMaxNum = 1;

	constexpr unsigned short int figureImageTypesNumber = 14;
	constexpr unsigned short int figureTypesNum = 8;
	constexpr unsigned short int numOfFiguresPerPlayer = 16;

	constexpr FigureImage VelesImage_red{ figureType::Veles, figureColour::Red };
	constexpr FigureImage VelesImage_purple{ figureType::Veles, figureColour::Purple };
	constexpr FigureImage HastatusImage_red{ figureType::Hastatus, figureColour::Red };
	constexpr FigureImage HastatusImage_purple{ figureType::Hastatus, figureColour::Purple };
	constexpr FigureImage PrincepsImage_red{ figureType::Princeps, figureColour::Red };
	constexpr FigureImage PrincepsImage_purple{ figureType::Princeps, figureColour::Purple };
	constexpr FigureImage TriariusImage_red{ figureType::Triarius, figureColour::Red };
	constexpr FigureImage TriariusImage_purple{ figureType::Triarius, figureColour::Purple };
	constexpr FigureImage EquesImage_red{ figureType::Eques, figureColour::Red };
	constexpr FigureImage EquesImage_purple{ figureType::Eques, figureColour::Purple };
	constexpr FigureImage ConsulImage_red{ figureType::Consul, figureColour::Red };
	constexpr FigureImage ConsulImage_purple{ figureType::Consul, figureColour::Purple };
	constexpr FigureImage PontifexMaximusImage_red{ figureType::PontifexMaximus, figureColour::Red };
	constexpr FigureImage PontifexMaximusImage_purple{ figureType::PontifexMaximus, figureColour::Purple };
	constexpr FigureImage EmptyFigureImage{ figureType::no_type, figureColour::no_colour };
	constexpr std::array<FigureImage, boardSize> EmptyFigureLine{ {
		EmptyFigureImage, EmptyFigureImage, EmptyFigureImage, EmptyFigureImage,
		EmptyFigureImage, EmptyFigureImage, EmptyFigureImage, EmptyFigureImage } };

	using BoardImage = std::array<std::array<FigureImage, boardSize>, boardSize>;
	
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
	
	


}

namespace ImagePaths {
	inline const std::string Board = "images/board.PNG";

	const std::map<FigureImage, std::string> FigureTextures = {
	std::make_pair(FigureImage(figureType::Veles,				figureColour::Red),			"images/Veles_Red"),
	std::make_pair(FigureImage(figureType::Veles,				figureColour::Purple),		"images/Veles_Purple"),
	std::make_pair(FigureImage(figureType::Hastatus,			figureColour::Red),			"images/Hastatus_Red"),
	std::make_pair(FigureImage(figureType::Hastatus,			figureColour::Purple),		"images/Hastatus_Purple"),
	std::make_pair(FigureImage(figureType::Princeps,			figureColour::Red),			"images/Princeps_Red"),
	std::make_pair(FigureImage(figureType::Princeps,			figureColour::Purple),		"images/Princeps_Purple"),
	std::make_pair(FigureImage(figureType::Triarius,			figureColour::Red),			"images/Triarius_Red"),
	std::make_pair(FigureImage(figureType::Triarius,			figureColour::Purple),		"images/Triarius_Purple"),
	std::make_pair(FigureImage(figureType::Eques,				figureColour::Red),			"images/Eques_Red"),
	std::make_pair(FigureImage(figureType::Eques,				figureColour::Purple),		"images/Eques_Purple"),
	std::make_pair(FigureImage(figureType::Consul,				figureColour::Red),			"images/Consul_Red"),
	std::make_pair(FigureImage(figureType::Consul,				figureColour::Purple),		"images/Consul_Purple"),
	std::make_pair(FigureImage(figureType::PontifexMaximus,		figureColour::Red),			"images/PontifexMaximus_Red"),
	std::make_pair(FigureImage(figureType::PontifexMaximus,		figureColour::Purple),		"images/PontifexMaximus_Purple")
	};

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

