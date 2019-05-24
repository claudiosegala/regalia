#include <pch.h>
#include <GameData.h>

bool GameData::Finished = false;

int GameData::Set = 0;

GameData::ResultType GameData::Result[Constants::Play::NumSets];

std::unique_ptr<Player> GameData::player1 = nullptr;

std::unique_ptr<Player> GameData::player2 = nullptr;