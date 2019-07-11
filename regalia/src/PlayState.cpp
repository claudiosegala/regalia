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
		GameData::Paused = true;
		LoadScoreState();
		return;
	}

	GameData::CurrentRoundTimer.Update(dt);

	// TODO: change to Player::counter == 1
	if (player_count == 0) {
		auto go = std::find_if(objectArray.begin(), objectArray.end(), [&](std::shared_ptr<GameObject>& ptr) {
			return ptr != nullptr && ptr->GetComponent<Player>() != nullptr;
		});

		auto player = (*go)->GetComponent<Player>();
	
		GameData::Result[GameData::Set] = player->id;
		GameData::Set++;
		GameData::Finished = (GameData::Set == Constants::Game::Sets);
		LoadScoreState();
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

void PlayState::CheckCollision() {
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

void PlayState::CreateField() {
	field_index = Number::Rand();

	GameObject* go;
	const auto& back = GetBackgroundData(field_index);
	const auto& tileSet = GetTileSetData(field_index);
	const auto& tileMapData = GetTileMapData(field_index);

	go = new GameObject();
	go->AddComponent<Sprite>(back.file);
	go->box.vector = Vec2(0, 0);
	(void)AddObject(go);

	go = new GameObject();
	tileMap = go->AddComponent<TileMap>(tileMapData.file, new TileSet(*go, tileSet.width, tileSet.height, tileSet.file));


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

	auto go = new GameObject();
	go->AddComponent<Player>(playerId, persona, tileMap->GetPlayerInitialPosition(playerId));
	auto player = AddObject(go);

	go = new GameObject();
	go->AddComponent<PlayerAim>(player);
	(void)AddObject(go);
}

const BackgroundData& PlayState::GetBackgroundData(int idx) {
	auto& assets = Constants::Play::Backgrounds;

	return assets[idx % assets.size()];
}

const TileSetData& PlayState::GetTileSetData(int idx) {
	auto& assets = Constants::Play::TileSets;

	return assets[idx % assets.size()];
}

const TileMapData& PlayState::GetTileMapData(int idx) {
	auto& assets = Constants::Play::TileMaps;

	return assets[idx % assets.size()];
}

void PlayState::LoadScoreState() {
	auto game = Game::GetInstance();

	game->Push(new ScoreState());
}