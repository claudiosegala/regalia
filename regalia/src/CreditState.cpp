#include <pch.h>
#include <InputManager.h>
#include <Camera.h>
#include <Constants.h>
#include <CreditState.h>
#include <Logger.h>
#include <Rect.h>
#include <Sprite.h>
#include <Vec2.h>

CreditState::CreditState() {
	Logger::Info("Initializing Credit State");

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
}

void CreditState::Update(unsigned dt) {
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

void CreditState::Render() {
	RenderArray();
}

void CreditState::Start() {
	Logger::Info("Starting Credit State");
	Camera::Reset();

	StartArray();

	started = true;
}

void CreditState::Pause() {
	Logger::Info("Pausing Title State");
}

void CreditState::Resume() {
	Logger::Info("Resuming Title State");
	Camera::Reset();
}