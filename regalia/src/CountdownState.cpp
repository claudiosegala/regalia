#include "pch.h"
#include "CountdownState.h"
#include "Text.h"
#include "Game.h"
#include "InputManager.h"


CountdownState::CountdownState(State* playState)
    : playState(playState)
    , count(Constants::Countdown::StartValue) {

	LoadAssets();
}

CountdownState::~CountdownState() {}

void CountdownState::LoadAssets() {
	auto textGO = new GameObject();

	text = textGO->AddComponent<Text>(Constants::Countdown::Font, Constants::Countdown::TextSize, Text::TextStyle::BLENDED, std::to_string(count), Constants::Colors::Red);

	textGO->box.SetCenter({ Constants::Window::Width / 2, Constants::Window::Height / 2 });

	AddObject(textGO);
}

void CountdownState::Update(float dt) {
	auto& in = InputManager::GetInstance();

	quitRequested = in.QuitRequested();
	if (quitRequested) {
		return;
	}

	UpdateArray(dt);

	timer.Update(dt);

	if (timer.Get() > 1) {
		timer.Restart();

		count--;

		if (count > 0) {
			text->SetText(std::to_string(count));
		} else if (count == 0) {
			text->SetText("Fight!");
		} else {
			popRequested = true;
		}
	}
}

void CountdownState::Render() {
	// Render the play state as a background to the countdown
	playState->Render();

	RenderArray();
}

void CountdownState::Start() {
	StartArray();
	started = true;
}

void CountdownState::Pause() {}

void CountdownState::Resume() {}
