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

void ScoreState::Update(unsigned dt) {
	auto& in = InputManager::GetInstance();

	popRequested = in.PopRequested();
	if (popRequested) {
		return;
	}

	quitRequested = in.QuitRequested();
	if (quitRequested) {
		return;
	}

	auto game = Game::GetInstance();

	if (in.GamepadPress(SDL_CONTROLLER_BUTTON_A) || in.KeyPress(Constants::Key::A)) {
		if (GameData::Paused) { 
			GameData::Paused = false;
			popRequested = 1;
			return;
		}

		if (!GameData::Finished) { // has next set
			game->Push(new PlayState());
			popRequested = 2;
			return;
		}
	}

	if (in.GamepadPress(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER) || in.KeyPress(Constants::Key::S)) { // restart
		game->Push(new PlayState());
		popRequested = 2;
		return;
	}

	if (in.GamepadPress(SDL_CONTROLLER_BUTTON_LEFTSHOULDER) || in.KeyPress(Constants::Key::D)) { // quit
		quitRequested = true;
		return;
	}

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

	go->AddComponent<Sprite>(Constants::Score::Background);

	go->box.SetCenter(Constants::Window::Center);

	(void)AddObject(go);
}

void ScoreState::LoadScore() {
	for (int i = 0; i < GameData::NumPlayers; i++) {
		// TODO: load user
		// TODO: load victories of each user
	}
}

void ScoreState::LoadPausedOptions() {
	//    SCORE
	// X    v    Y
	//
	// A - Continue Set
	// R1 - Restart
	// L1 - Quit
}

void ScoreState::LoadContinueOptions() {
	//    SCORE
	// X    v    Y
	//
	// A - Continue Match
	// R1 - Restart
	// L1 - Quit
}

void ScoreState::LoadFinishedOptions() {
	//    SCORE
	// X    v    Y
	//
	// R1 - Restart
	// L1 - Quit
}