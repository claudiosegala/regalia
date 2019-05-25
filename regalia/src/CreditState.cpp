#include <pch.h>
#include <Camera.h>
#include <Constants.h>
#include <CreditState.h>
#include <InputManager.h>
#include <Logger.h>
#include <Rect.h>
#include <Sprite.h>
#include <Vec2.h>

CreditState::CreditState() {
	Logger::Info("Initializing Credit State");

	//this->music.Open(Constants::Credit::Music);
	LoadAssets();
}

CreditState::~CreditState() {
	Logger::Info("Destroying Credit State");
}

void CreditState::LoadAssets() {
	auto go = new GameObject();

	go->AddComponent<Sprite>(Constants::Credit::Background);

	go->box.vector.Reset();

	(void)AddObject(go);

	// TODO: add message to say "Press ESC to return to Menu"
}

void CreditState::Update(float dt) {
	this->popRequested = InputManager::IsPopRequested();
	if (this->popRequested) {
		return;
	}
	
	this->quitRequested = InputManager::IsQuitRequested();
	if (this->quitRequested) {
		return;
	}

	UpdateArray(dt);
}

void CreditState::Render() {
	RenderArray();
}

void CreditState::Start() {
	Logger::Info("Starting Credit State");
	Camera::Reset();

	StartArray();

	this->started = true;
}

void CreditState::Pause() {
	Logger::Info("Pausing Title State");
}

void CreditState::Resume() {
	Logger::Info("Resuming Title State");
	Camera::Reset();
}