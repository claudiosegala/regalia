#include <pch.h>
#include <ScoreState.h>
#include <InputManager.h>
#include <GameData.h>
#include <Camera.h>
#include <Logger.h>
#include <Rect.h>
#include <Sprite.h>
#include <Vec2.h>

ScoreState::ScoreState() {
	Logger::Info("Initing Story State");

	//this->music.Open(Constants::Story::Music);
	this->status = ScoreStatus::FINISHED_MATCH; // TODO: Infer from game data the current situation
	LoadAssets();
}

ScoreState::~ScoreState() {
	Logger::Info("Destroying Story State");
}

void ScoreState::LoadAssets() {
	auto imageObject = new GameObject();
	auto image = new Sprite(*imageObject, Constants::Story::Background);

	imageObject->AddComponent(image);
	imageObject->box.vector.Reset();

	(void)AddObject(imageObject);

	// TODO: add message to say "Press ESC to return to Menu"
}

void ScoreState::Update(float dt) {
	this->popRequested = InputManager::IsPopRequested();
	if (this->popRequested)
		return;
	this->quitRequested = InputManager::IsQuitRequested();
	if (this->quitRequested)
		return;

	auto& in = InputManager::GetInstance();

	if (in.GamepadPress(Constants::Gamepad::R1) && this->status == ScoreStatus::PAUSED) {
		// continue
		//this->popRequested = 1;
		return;
	}

	if (in.GamepadPress(Constants::Gamepad::R2)) {
		// restart
		//GameData::Reset();
		//Game::Append(new PlayState());

		//this->popRequested = 2;
		return;
	}

	if (in.GamepadPress(Constants::Gamepad::L1) && this->status == ScoreStatus::UNFINISHED_MATCH) {
		// has next set
		//Game::Append(new PlayState());

		//this->popRequested = 2;
		return;
	}

	if (in.GamepadPress(Constants::Gamepad::L2)) {
		this->quitRequested = true;
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

	this->started = true;
}

void ScoreState::Pause() {
	Logger::Info("Pausing Title State");
}

void ScoreState::Resume() {
	Logger::Info("Resuming Title State");
	Camera::Reset();
}