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

	static Constants::PersonaType personas[4];

	static int Result[Constants::Game::Sets]; //> holds the id of the winner

	static bool WindowFullscreen;

	static Timer CurrentRoundTimer;

	static void Init();

	static bool IsTimeUp();
};
