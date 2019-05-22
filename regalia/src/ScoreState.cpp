#include <Camera.h>
#include <InputManager.h>
#include <Rect.h>
#include <Sprite.h>
#include <ScoreState.h>
#include <Text.h>
#include <Vec2.h>

ScoreState::ScoreState() {
	Logger::Info("Initing Story State");

	//this->music.Open(Constants::Story::Music);
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