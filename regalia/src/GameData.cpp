#include <pch.h>
#include <Number.h>
#include <GameData.h>

bool GameData::Started = false;

bool GameData::Paused = false;

bool GameData::Finished = false;

int GameData::Set = 0;

int GameData::NumPlayers = 0;

Constants::PersonaType GameData::personas[4];

int GameData::Result[Constants::Game::Sets] = { 0 };

Timer GameData::CurrentRoundTimer;

bool GameData::WindowFullscreen = false;

void GameData::Init() {
	Started = true;
	Paused = false;
	Finished = false;
	Set = 0;

	for (int i = 0; i < Constants::Game::Sets; i++) {
		Result[i] = -1;
	}
}

bool GameData::IsTimeUp() {
	return GameData::CurrentRoundTimer.Get() >= Constants::Game::MillisecondsPerRound;
}
