#include <pch.h>
#include <Collision.h>
#include <Camera.h>
#include <Constants.h>
#include <Game.h>
#include <GameData.h>
#include <InputManager.h>
#include <Logger.h>
#include <Number.h>
#include <Player.h>
#include <PlayState.h>
#include <Rect.h>
#include <ScoreState.h>
#include <Sprite.h>
#include <TileMap.h>
#include <TileSet.h>
#include <Vec2.h>
#include <PlayerAim.h>
#include <CountdownState.h>
#include "GameTimer.h"

PlayState::PlayState() {
	Logger::Info("Initializing Play State");

	music.Open(Constants::Play::Music);

	if (!GameData::Started || GameData::Finished) {
		GameData::Init();
	}
}

PlayState::~PlayState() {
	Logger::Info("Destroying Play State");
}

void PlayState::LoadAssets() {
	CreateField();
	CreatePlayers();
	CreateGameTimer();
}

void PlayState::Update(unsigned dt) {
	GameData::CurrentRoundTimer.Update(dt);

	auto& in = InputManager::GetInstance();

	popRequested = in.PopRequested();
	if (popRequested) {
		return;
	}

	quitRequested = in.QuitRequested();
	if (quitRequested) {
		return;
	}

	if (in.GamepadPress(SDL_CONTROLLER_BUTTON_START)) {
		PauseSet();
		return;
	}

	// TODO: change to Player::counter == 1
	if (player_count == 0) {
		EndSet();
		return;
	}

	CheckCollision();
	UpdateArray(dt);
	PruneArray();
}

void PlayState::Render() {
	RenderArray();
}

void PlayState::Start() {
	Logger::Info("Starting Play State");
	Camera::Reset();
	GameData::CurrentRoundTimer.Restart();

	LoadAssets();
	StartArray();

	started = true;

	if (Constants::Countdown::Enabled) {
		Game::GetInstance()->Push(new CountdownState(this));
	} else {
		music.Play();
	}
}

void PlayState::Pause() {
	Logger::Info("Pausing Play State");
	music.Stop(0);
}

void PlayState::Resume() {
	Logger::Info("Resuming Play State");
	Camera::Reset();
	music.Play();
}

void PlayState::CreateField() {
	field_index = Number::Rand();

	GameObject* go;
	const auto& tileMapData = GetTileMapData(field_index);

	// Background
	go = new GameObject();
	go->AddComponent<Sprite>(&Constants::Play::CityBackground::Background);
	go->box.vector = Vec2(0, 0);
	(void)AddObject(go);

	// Cars 1
	go = new GameObject();
	go->AddComponent<Sprite>(&Constants::Play::CityBackground::Cars1);
	go->box.vector = { 162, 270 };
	(void)AddObject(go);

	// Cars 2
	go = new GameObject();
	go->AddComponent<Sprite>(&Constants::Play::CityBackground::Cars2);
	go->box.vector = { 162, 270 };
	(void)AddObject(go);

	// Crane
	go = new GameObject();
	go->AddComponent<Sprite>(&Constants::Play::CityBackground::Crane);
	go->box.vector = { 305, 161 };
	(void)AddObject(go);

	// Subway
	go = new GameObject();
	go->AddComponent<Sprite>(&Constants::Play::CityBackground::Subway);
	go->box.vector = { 252, 371 };
	(void)AddObject(go);

	go = new GameObject();
	tileMap = go->AddComponent<TileMap>(tileMapData.file);

	go->box.vector = Vec2(0, 0);
	(void)AddObject(go);
}

void PlayState::CreateGameTimer() {
	auto go = new GameObject();

	go->AddComponent<GameTimer>();

	(void)AddObject(go);
}

void PlayState::CreatePlayers() {
	for (int i = 0; i < GameData::NumPlayers; i++) {
		CreatePlayer(GameData::Personas[i]);
	}
}

void PlayState::CreatePlayer(Constants::PersonaType persona) {
	int playerId = player_count++;
	alive_player_count++;

	auto go = new GameObject();
	go->AddComponent<Player>(playerId, persona, tileMap->GetPlayerInitialPosition(playerId), this);
	auto player = AddObject(go);

	go = new GameObject();
	go->AddComponent<PlayerAim>(player);
	(void)AddObject(go);
}

const void PlayState::CheckCollision() {
	std::vector<int> goIdxs;

	for (size_t i = 0; i < objectArray.size(); i++) {
		if (objectArray[i]->hitbox != nullptr) {
			goIdxs.push_back(int(i));
		}
	}

	for (size_t i = 0; i < goIdxs.size(); i++) {
		auto go1 = objectArray[goIdxs[i]];

		for (size_t j = i + 1; j < goIdxs.size(); j++) {
			auto go2 = objectArray[goIdxs[j]];

			if (Collision::IsColliding(*(go1->hitbox), *(go2->hitbox), go1->angle, go2->angle)) {
				go1->NotifyCollision(*go2);
				go2->NotifyCollision(*go1);
			}
		}
	}
}

const BackgroundData& PlayState::GetBackgroundData(int idx) {
	auto& assets = Constants::Play::Backgrounds;

	return assets[idx % assets.size()];
}

const TileMapData& PlayState::GetTileMapData(int idx) {
	auto& assets = Constants::Play::TileMaps;

	return assets[idx % assets.size()];
}

const int PlayState::GetWinnerId() {
	auto getPlayer = [&](std::shared_ptr<GameObject>& ptr) {
		return ptr != nullptr && ptr->GetComponent<Player>() != nullptr;
	};

	auto go = std::find_if(objectArray.begin(), objectArray.end(), getPlayer);

	auto player = (*go)->GetComponent<Player>();

	return player->id;
}

const bool PlayState::IsGameFinished() {
	for (int i = 0; i < GameData::NumPlayers; i++) {
		int cnt = 0;

		for (int j = 0; j < Constants::Game::Sets; j++) {
			if (GameData::Result[j] == i) {
				cnt++;
			}
		}

		if (cnt >= 3) {
			return true;
		}
	}

	return false;
}

const void PlayState::PauseSet() {
	GameData::Paused = true;

	LoadScoreState();
}

const void PlayState::EndSet() {
	GameData::Result[GameData::Set] = GetWinnerId();
	GameData::Set++;
	GameData::Finished = IsGameFinished();

	LoadScoreState();
}

const void PlayState::LoadScoreState() {
	auto game = Game::GetInstance();

	game->Push(new ScoreState());
}