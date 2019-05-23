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

PlayState::PlayState() {
	Logger::Info("Initing Play State");

	this->music.Open(Constants::Play::Music);
	LoadAssets();
}

PlayState::~PlayState() {
	Logger::Info("Destroying Play State");
}

void PlayState::LoadAssets() {
	CreateField();
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
	auto backgroundObject = new GameObject();
	auto image = new Sprite(*backgroundObject, "assets/img/ocean.jpg");
	auto tileSet = new TileSet(*backgroundObject, 24, 24, "assets/img/tileSetSample.png");
	auto tileMap = new TileMap(*backgroundObject, "assets/map/tileMapSample.txt", tileSet);

	backgroundObject->AddComponent(image);
	backgroundObject->AddComponent(tileMap);
	backgroundObject->box.vector = Vec2(0, 0);

	(void)AddObject(backgroundObject);
}