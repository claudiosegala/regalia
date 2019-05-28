#include <pch.h>
#include <Camera.h>
#include <Game.h>
#include <GameData.h>
#include <GameObject.h>
#include <InputManager.h>
#include <Logger.h>
#include <Player.h>
#include <PlayState.h>
#include <Rect.h>
#include <ScoreState.h>
#include <Sprite.h>
#include <Vec2.h>

ScoreState::ScoreState() {
	Logger::Info("Initializing Story State");

	//music.Open(Constants::Story::Music);

	LoadAssets();
}

ScoreState::~ScoreState() {
	Logger::Info("Destroying Story State");
}

void ScoreState::LoadAssets() {
	LoadBackground();
	LoadScore();

	if (GameData::Paused) {
		LoadPausedOptions();
	} else if (GameData::Finished) {
		LoadFinishedOptions();
	} else {
		LoadContinueOptions();
	}
}

void ScoreState::Update(float dt) {
	popRequested = InputManager::IsPopRequested();
	if (popRequested)
		return;
	quitRequested = InputManager::IsQuitRequested();
	if (quitRequested)
		return;

	//auto& in = InputManager::GetInstance();

	//if (in.GamepadPress(Constants::Gamepad::A)) {
	//	if (GameData::Paused) {
	//		GameData::Paused = false;
	//		popRequested = 1;
	//		return;
	//	}

	//	if (!GameData::Finished) { // has next set
	//		Game::Append(new PlayState());
	//		popRequested = 2;
	//		return;
	//	}
	//}

	//if (in.GamepadPress(Constants::Gamepad::R1)) { // restart
	//	Game::Append(new PlayState());
	//	popRequested = 2;
	//	return;
	//}

	//if (in.GamepadPress(Constants::Gamepad::R2)) { // quit
	//	quitRequested = true;
	//	return;
	//}

	UpdateArray(dt);
}

void ScoreState::Render() {
	RenderArray();
}

void ScoreState::Start() {
	Logger::Info("Starting Story State");
	Camera::Reset();

	StartArray();

	started = true;
}

void ScoreState::Pause() {
	Logger::Info("Pausing Title State");
}

void ScoreState::Resume() {
	Logger::Info("Resuming Title State");
	Camera::Reset();
}

void ScoreState::LoadBackground() {
	auto go = new GameObject();

	go->AddComponent<Sprite>(Constants::Story::Background);

	go->box.SetCenter(Constants::Window::Center);

	(void)AddObject(go);
}

void ScoreState::LoadScore() {
	// TODO: load score in a cool way
}

void ScoreState::LoadPausedOptions() {
	//    SCORE
	// X    v    Y
	//
	// A - Continue Set
	// R1 - Restart
	// R2 - Quit
}

void ScoreState::LoadContinueOptions() {
	//    SCORE
	// X    v    Y
	//
	// A - Continue Match
	// R1 - Restart
	// R2 - Quit
}

void ScoreState::LoadFinishedOptions() {
	//    SCORE
	// X    v    Y
	//
	// R1 - Restart
	// R2 - Quit
}