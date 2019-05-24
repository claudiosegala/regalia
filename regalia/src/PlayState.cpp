#include <pch.h>
#include <Camera.h>
#include <TileMap.h>
#include <TileSet.h>
#include <Constants.h>
#include <InputManager.h>
#include <Logger.h>
#include <PlayState.h>
#include <Rect.h>
#include <Sprite.h>
#include <StoryState.h>
#include <Vec2.h>
#include <GameData.h>
#include <Player.h>

PlayState::PlayState() {
	Logger::Info("Initing Play State");

	this->backgroundIdx = 0;
	this->tileSetIdx = 0;
	this->tileMapIdx = 0;
	this->music.Open(Constants::Play::Music);

	LoadAssets();
}

PlayState::~PlayState() {
	Logger::Info("Destroying Play State");
}

void PlayState::LoadAssets() {
	CreateField();

	// TODO: remove player initiation from here
	auto go = new GameObject();
	auto player = new Player(*go);

	go->AddComponent(player);

	(void)AddObject(go);
}

void PlayState::Update(float dt) {
	roundTimer.Update(dt);

	this->popRequested = InputManager::IsPopRequested();
	if (this->popRequested) {
		return;
	}

	this->quitRequested = InputManager::IsQuitRequested();
	if (this->quitRequested) {
		return;
	}

	auto& in = InputManager::GetInstance();

	//  _update(dt);

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

void PlayState::CreateField() {
	auto rnd = rand();

	auto go = new GameObject();
	auto image = BuildBackground(go, rnd);
	auto tileSet = BuildTileSet(go, rnd);
	auto tileMap = BuildTileMap(go, tileSet);

	go->AddComponent(image);
	go->AddComponent(tileMap);
	go->box.vector = Vec2(0, 0);

	(void)AddObject(go);
}

Sprite* PlayState::BuildBackground(GameObject* gameObject, int rnd) {
	auto assets = Constants::Play::Backgrounds;
	auto idx = rnd % assets.size();
	auto asset = assets[idx];

	this->backgroundIdx = (int)idx;

	return new Sprite(*gameObject, asset.file);
}

TileSet* PlayState::BuildTileSet(GameObject* gameObject, int rnd) {
	auto assets = Constants::Play::TileSets;
	auto idx = rnd % assets.size();
	auto asset = assets[idx];

	this->tileSetIdx = (int)idx;

	return new TileSet(*gameObject, asset.width, asset.height, asset.file);
}

TileMap* PlayState::BuildTileMap(GameObject* gameObject, TileSet* tileSet) {
	auto assets = Constants::Play::TileMaps;
	auto idx = rand() % assets.size();
	auto asset = assets[idx];

	this->tileMapIdx = (int)idx;

	return new TileMap(*gameObject, asset.file, tileSet);
}