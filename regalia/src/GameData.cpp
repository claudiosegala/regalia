#include <pch.h>
#include <GameData.h>

bool GameData::Started = false;

bool GameData::Paused = false;

bool GameData::Finished = false;

int GameData::Set = 0;

int GameData::Result[Constants::Game::Sets] = { 0 };

GameData::PersonaType GameData::Persona1;

GameData::PersonaType GameData::Persona2;

bool GameData::WindowFullscreen = false;

void GameData::Init() {
	GameData::Started = true;
	GameData::Paused = false;
	GameData::Finished = false;
	GameData::Set = 0;

	for (int i = 0; i < Constants::Game::Sets; i++) {
		GameData::Result[i] = 0;
	}

	// TODO: Choose the personas randomly
	//GameData::Persona1 = ;
	//GameData::Persona2 = ;
}