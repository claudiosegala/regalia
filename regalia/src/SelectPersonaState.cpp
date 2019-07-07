#include <pch.h>
#include <SelectPersonaState.h>
#include <Logger.h>
#include <Sprite.h>
#include "InputManager.h"
#include "GameData.h"
#include "Game.h"
#include "PlayState.h"

SelectPersonaState::SelectPersonaState() {

	Logger::Info("Initializing Menu State");

	auto& in = InputManager::GetInstance();

	GameData::NumPlayers = in.NumberOfControllers() > 4 ? 4 : in.NumberOfControllers();

	LoadAssets();
}

SelectPersonaState::~SelectPersonaState() {
	Logger::Info("Destroying SelectPersonaState");
}

void SelectPersonaState::LoadAssets() {
	auto background = new GameObject();
	background->AddComponent<Sprite>(Constants::Menu::Background);
	(void)AddObject(background);

	for (int i = 0; i < GameData::NumPlayers; ++i) {
		personaConfirmed.push_back(false);
		currentPersona.push_back(Constants::PersonaType::MISTER_N);
		timers.push_back(Timer());

		auto playerGo = new GameObject();
		auto sprite = playerGo->AddComponent<Sprite>(personas[Constants::PersonaType::MISTER_N].spriteSheetData);
		sprite->SetScale(3.0f, 3.0f);
		playerGo->box.SetCenter(positions[i]);
		(void)AddObject(playerGo);
		players.push_back(playerGo);

		auto rightArrowGO = new GameObject();
		rightArrowGO->AddComponent<Sprite>("assets/img/aim.png");
		rightArrowGO->box.SetCenter(positions[i] + Vec2(75, 0));
		(void)AddObject(rightArrowGO);

		auto leftArrowGO = new GameObject();
		leftArrowGO->AddComponent<Sprite>("assets/img/aim.png");
		leftArrowGO->box.SetCenter(positions[i] + Vec2(-75, 0));
		leftArrowGO->angle = float(M_PI);
		(void)AddObject(leftArrowGO);

		arrows.emplace_back(rightArrowGO, leftArrowGO);
	}
}

void SelectPersonaState::Update(unsigned dt) {
	auto& in = InputManager::GetInstance();

	popRequested = in.PopRequested();
	if (popRequested) {
		return;
	}

	quitRequested = in.QuitRequested();
	if (quitRequested) {
		return;
	}

	for (auto& timer : timers) {
		timer.Update(dt);
	}

	for (int i = 0; i < GameData::NumPlayers; ++i) {
		if (personaConfirmed[i] && in.GamepadPress(SDL_CONTROLLER_BUTTON_B, i)) {

			personaConfirmed[i] = false;
			personas[currentPersona[i]].isAvaiable = true;

		} else if (!personaConfirmed[i]) {

			if (!personas[currentPersona[i]].isAvaiable) {

				currentPersona[i] = nextPersona(currentPersona[i]);
				players[i]->GetComponent<Sprite>()->Open(personas[currentPersona[i]].spriteSheetData);

			} else if (in.GamepadPress(SDL_CONTROLLER_BUTTON_A, i)) {

				personaConfirmed[i] = true;
				personas[currentPersona[i]].isAvaiable = false;

			} else if (timers[i].Get() > 300) {
				auto leftStickX = in.GamepadLeftStick(i).x;

				if (leftStickX != 0) {
					do {
						currentPersona[i] = leftStickX > 0 ? nextPersona(currentPersona[i]) : previousPersona(currentPersona[i]);
					} while (!personas[currentPersona[i]].isAvaiable);

					players[i]->GetComponent<Sprite>()->Open(personas[currentPersona[i]].spriteSheetData);
					timers[i].Restart();
				}
			}
		}

		arrows[i].first->hide = arrows[i].second->hide = personaConfirmed[i];
	}

	if (std::all_of(personaConfirmed.begin(), personaConfirmed.end(), [](bool b) { return b; })) {
		for (int i = 0; i < GameData::NumPlayers; ++i) {
			GameData::personas[i] = currentPersona[i];
		}

		auto game = Game::GetInstance();
		game->Push(new PlayState());

		popRequested = true;
	}

	UpdateArray(dt);
}

void SelectPersonaState::Render() {
	RenderArray();
}

void SelectPersonaState::Start() {
	Logger::Info("Starting SelectPersonaState");

	StartArray();

	started = true;
}

void SelectPersonaState::Pause() {
	Logger::Info("Pausing SelectPersonaState");
}

void SelectPersonaState::Resume() {
	Logger::Info("Resuming SelectPersonaState");
}

Constants::PersonaType SelectPersonaState::nextPersona(Constants::PersonaType persona) {
	return Constants::PersonaType(int(persona) + 1) == Constants::PersonaType::MAX_VALUE ? Constants::PersonaType(0) : Constants::PersonaType(int(persona) + 1);
}

Constants::PersonaType SelectPersonaState::previousPersona(Constants::PersonaType persona) {
	return int(persona) - 1 < 0 ? Constants::PersonaType(int(Constants::PersonaType::MAX_VALUE) - 1) : Constants::PersonaType(int(persona) - 1);
}
