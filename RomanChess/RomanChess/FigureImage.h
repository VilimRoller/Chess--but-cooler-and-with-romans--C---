#pragma once
#include "ID.h"

struct FigureImage {

	figureType type;
	figureColour colour;

	constexpr FigureImage(const figureType input_type = figureType::no_type,
		const figureColour input_colour = figureColour::no_colour) :
		type{ input_type }, colour{ input_colour } {}


	bool operator==(const FigureImage right) const {
		return (type == right.type) && (colour == right.colour);
	}

	bool operator<(const FigureImage right) const {
		return type < right.type;
	}

};
