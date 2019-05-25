#pragma once

#include <Constants.h>

class GameData {
public:
	static bool Finished;

	static int Set;

	enum class ResultType {
		NONE,
		PLAYER1_VICTORY,
		PLAYER2_VICTORY
	};

	static ResultType Result[Constants::Play::NumSets];

	enum class PersonaType {
		MISTER_N,
		GOTICA,
		OUTRO,
		MAIS_OUTRO
	};

	static PersonaType Persona1;

	static PersonaType Persona2;
};