#include <pch.h>
#include <Camera.h>
#include <Constants.h>
#include <InputManager.h>
#include <Logger.h>
#include <Rect.h>
#include <Sprite.h>
#include <StoryState.h>
#include <Vec2.h>

StoryState::StoryState() {
	Logger::Info("Initializing Story State");

	//this->music.Open(Constants::Story::Music);
	LoadAssets();
}

StoryState::~StoryState() {
	Logger::Info("Destroying Story State");
}

void StoryState::LoadAssets() {
	auto go = new GameObject();

	go->AddComponent<Sprite>(Constants::Story::Background);

	go->box.vector.Reset();

	(void)AddObject(go);

	// TODO: add message to say "Press ESC to return to Menu"
}

void StoryState::Update(float dt) {
	this->popRequested = InputManager::IsPopRequested();
	if (this->popRequested > 0) {
		return;
	}

	this->quitRequested = InputManager::IsQuitRequested();
	if (this->quitRequested) {
		return;
	}

	UpdateArray(dt);
}

void StoryState::Render() {
	RenderArray();
}

void StoryState::Start() {
	Logger::Info("Starting Story State");
	Camera::Reset();

	StartArray();

	this->started = true;
}

void StoryState::Pause() {
	Logger::Info("Pausing Title State");
}

void StoryState::Resume() {
	Logger::Info("Resuming Title State");
	Camera::Reset();
}