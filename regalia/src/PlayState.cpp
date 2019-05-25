#include <pch.h>
#include <Collider.h>
#include <Collision.h>
#include <Camera.h>
#include <Constants.h>
#include <Game.h>
#include <GameData.h>
#include <InputManager.h>
#include <Logger.h>
#include <Player.h>
#include <PlayState.h>
#include <Rect.h>
#include <ScoreState.h>
#include <Sprite.h>
#include <StoryState.h>
#include <TileMap.h>
#include <TileSet.h>
#include <Vec2.h>

PlayState::PlayState() {
	Logger::Info("Initializing Play State");

	this->backgroundIdx = 0;
	this->tileSetIdx = 0;
	this->tileMapIdx = 0;
	this->music.Open(Constants::Play::Music);

	if (!GameData::Started || GameData::Finished) {
		GameData::Init();
	}

	PlayState::LoadAssets();
}

PlayState::~PlayState() {
	Logger::Info("Destroying Play State");
}

void PlayState::LoadAssets() {
	CreateField();
	CreatePlayers();
}

void PlayState::Update(float dt) {
	auto& in = InputManager::GetInstance();

	this->popRequested = InputManager::IsPopRequested() || in.GamepadPress(SDL_CONTROLLER_BUTTON_B);
	if (this->popRequested) {
		return;
	}

	this->quitRequested = InputManager::IsQuitRequested();
	if (this->quitRequested) {
		return;
	}

	// TODO: uncomment this when constant is ok
	/*if (in.GamepadPress(Constants::Gamepad::Menu)) {
		GameData::Paused = true;
		LoadScoreState();
		return;
	}*/

	this->timer.Update(dt);

	// TODO: uncomment this when there are two players
	/*if (Player::counter == 1 || this->timer.Get() > Constants::Game::SetLenght) {
		GameData::Set++;
		GameData::Finished = (GameData::Set == Constants::Game::Sets);
		LoadScoreState();
		return;
	}*/

	CheckCollision();
	UpdateArray(dt);
}

void PlayState::Render() {
	RenderArray();
}

void PlayState::Start() {
	Logger::Info("Starting Play State");
	Camera::Reset();

	StartArray();

	this->started = true;
	this->music.Play();
}

void PlayState::Pause() {
	Logger::Info("Pausing Play State");
	this->music.Stop(0);
}

void PlayState::Resume() {
	Logger::Info("Resuming Play State");
	Camera::Reset();
	this->music.Play();
}


void PlayState::CheckCollision() {
	// TODO: implement
}

void PlayState::CreateField() {
	const auto rnd = rand();

	auto go = new GameObject();
	const auto image = BuildBackground(go, rnd);
	const auto tileSet = BuildTileSet(go, rnd);
	const auto tileMap = BuildTileMap(go, tileSet);

	go->AddComponent(image);
	go->AddComponent(tileMap);
	go->box.vector = Vec2(0, 0);

	(void)AddObject(go);
}

void PlayState::CreatePlayers() {
	auto go1 = new GameObject();
	//auto go2 = new GameObject();

	const auto player1 = new Player(*go1);
	//auto player1 = new Player(*go1, GameData::Persona1);
	//auto player2 = new Player(*go2, GameData::Persona2);

	go1->AddComponent(player1);
	//go2->AddComponent(this->player2);

	(void)AddObject(go1);
	//(void)AddObject(go2);
}

Sprite* PlayState::BuildBackground(GameObject* go, int rnd) {
	auto assets = Constants::Play::Backgrounds;
	const auto idx = rnd % assets.size();
	const auto& asset = assets[idx];

	this->backgroundIdx = int(idx);

	return new Sprite(*go, asset.file);
}

TileSet* PlayState::BuildTileSet(GameObject* go, int rnd) {
	auto assets = Constants::Play::TileSets;
	const auto idx = rnd % assets.size();
	const auto& asset = assets[idx];

	this->tileSetIdx = int(idx);

	return new TileSet(*go, asset.width, asset.height, asset.file);
}

TileMap* PlayState::BuildTileMap(GameObject* go, TileSet* tileSet) {
	auto assets = Constants::Play::TileMaps;
	const auto idx = rand() % assets.size();
	const auto& asset = assets[idx];

	this->tileMapIdx = int(idx);

	return new TileMap(*go, asset.file, tileSet);
}

void PlayState::LoadScoreState() {
	auto game = Game::GetInstance();

	game->Push(new ScoreState());
}