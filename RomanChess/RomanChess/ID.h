#pragma once

enum class figureType {
	Veles = 1,
	Hastatus = 2,
	Princeps = 4,
	Triarius = 6,
	Eques = 10,
	Consul = 20,
	PontifexMaximus = 5,
	no_type = 0
};

enum class figureColour {
	Red = 'R',
	Purple = 'P',
	no_colour = 0
};

enum class AIType { 
	CaesarAI, 
	AgrippaAI,
	ScipioAI,
	CrassusAI,
	VarroAI
};

enum class AIStrategy {
	Standard,
	Fabian,
	HanibalAdPortas
};