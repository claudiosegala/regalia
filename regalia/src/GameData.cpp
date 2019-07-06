#include <pch.h>
#include <Number.h>
#include <GameData.h>

bool GameData::Started = false;

bool GameData::Paused = false;

bool GameData::Finished = false;

int GameData::Set = 0;

int GameData::NumPlayers = 0;

int GameData::Result[Constants::Game::Sets] = { 0 };

Timer GameData::CurrentRoundTimer;

GameData::PersonaType GameData::Personas[4] = { 
	GameData::PersonaType::MISTER_N,
	GameData::PersonaType::GOTICA,
	GameData::PersonaType::MAIS_OUTRO,
	GameData::PersonaType::OUTRO
};

bool GameData::WindowFullscreen = false;

void GameData::Init(int numPlayers) {
	Started = true;
	Paused = false;
	Finished = false;
	Set = 0;
	NumPlayers = numPlayers;

	for (int i = 0; i < Constants::Game::Sets; i++) {
		Result[i] = -1;
	}

	int rnd = Number::Rand();

	while (rnd--) {
		std::next_permutation(Personas, Personas + 4);
	}
}

bool GameData::IsTimeUp() {
	return GameData::CurrentRoundTimer.Get() < Constants::Game::MillisecondsPerRound;
}
