#pragma once

#include <Constants.h>

class GameData {
public:
	static bool Started;

	static bool Paused;

	static bool Finished;

	static int Set;

	static int NumPlayers;

	static int Result[Constants::Game::Sets]; //> holds the id of the winner

	enum class PersonaType {
		MISTER_N,
		GOTICA,
		OUTRO,
		MAIS_OUTRO
	};

	static PersonaType Personas[4];

	static bool WindowFullscreen;

	static void Init(int numPlayer = 2);
};