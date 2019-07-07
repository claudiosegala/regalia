#include "pch.h"
#include "CountdownState.h"
#include "Text.h"
#include "Game.h"
#include "InputManager.h"
#include "Sound.h"

CountdownState::CountdownState(State* playState)
    : playState(playState) {

	LoadAssets();
}

CountdownState::~CountdownState() {}

void CountdownState::LoadAssets() {
	text = new GameObject();

	text->AddComponent<Text>(Constants::Game::Font, Constants::Countdown::TextSize, Text::TextStyle::BLENDED, std::to_string(count), Constants::Colors::Red);

	text->box.SetCenter({ Constants::Window::Width / 2, Constants::Window::Height / 2 });

	(void)AddObject(text);

	text->AddComponent<Sound>(Constants::Countdown::Sound);
}

void CountdownState::Update(unsigned dt) {
	auto& in = InputManager::GetInstance();

	quitRequested = in.QuitRequested();
	if (quitRequested) {
		return;
	}

	UpdateArray(dt);

	timer.Update(dt);

	if (timer.Get() > 1000) {
		timer.Restart();

		text->GetComponent<Sound>()->Play();

		count--;

		if (count > 0) {
			text->GetComponent<Text>()->SetText(std::to_string(count));
		} else if (count == 0) {
			text->GetComponent<Text>()->SetText("Fight!");
		} else {
			popRequested = true;
		}

		text->box.SetCenter({ Constants::Window::Width / 2, Constants::Window::Height / 2 });
	}
}

void CountdownState::Render() {
	// Render the play state as a background to the countdown
	playState->Render();

	RenderArray();
}

void CountdownState::Start() {
	StartArray();
	text->GetComponent<Sound>()->Play();
	started = true;
}

void CountdownState::Pause() {}

void CountdownState::Resume() {}
