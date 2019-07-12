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

	//music.Open(Constants::Story::Music);
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
}

void StoryState::Update(unsigned dt) {
	auto& in = InputManager::GetInstance();

	popRequested = in.PopRequested();
	if (popRequested) {
		return;
	}

	quitRequested = in.QuitRequested();
	if (quitRequested) {
		return;
	}

	if (in.GamepadPress(SDL_CONTROLLER_BUTTON_B)) {
		popRequested = true;
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

	started = true;
}

void StoryState::Pause() {
	Logger::Info("Pausing Title State");
}

void StoryState::Resume() {
	Logger::Info("Resuming Title State");
	Camera::Reset();
}