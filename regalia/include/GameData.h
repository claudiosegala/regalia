#pragma once

#include <Constants.h>
#include "Timer.h"

class GameData {
public:
	static bool Started;

	static bool Paused;

	static bool Finished;

	static int Set;

	static int NumPlayers;

	static int Result[Constants::Game::Sets]; //> holds the id of the winner

	//static PersonaType Personas[4];

	static bool WindowFullscreen;

	static Timer CurrentRoundTimer;

	static void Init(int numPlayer = 2);

	static bool IsTimeUp();
};
