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

enum class spriteID {
	VelesRed1, VelesRed2, VelesRed3, VelesRed4, VelesRed5,
	VelesPurple1, VelesPurple2, VelesPurple3, VelesPurple4, VelesPurple5,
	HastatusRed1, HastatusRed2, HastatusRed3,
	HastatusPurple1, HastatusPurple2, HastatusPurple3,
	PrincepsRed1, PrincepsRed2,
	PrincepsPurple1, PrincepsPurple2,
	TriariusRed1, TriariusRed2,
	TriariusPurple1, TriariusPurple2,
	EquesRed,
	EquesPurple,
	ConsulRed1, ConsulRed2,
	ConsulPurple1, ConsulPurple2,
	PontifexMaximusRed,
	PontifexMaximusPurple
};