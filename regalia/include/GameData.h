#pragma once

#include <Constants.h>
#include <Player.h>

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

	static std::unique_ptr<Player> player1;

	static std::unique_ptr<Player> player2;
};