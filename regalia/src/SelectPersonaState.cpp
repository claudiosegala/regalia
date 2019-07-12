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

	GameData::NumPlayers = std::min(in.NumberOfControllers(), Constants::Game::MaxNumPlayers);

	if (GameData::NumPlayers < Constants::Game::MinNumPlayers) {
		throw new std::runtime_error("You need more players to play this game!");
	}

	if (GameData::NumPlayers > Constants::Game::MaxNumPlayers) {
		throw new std::runtime_error("You need less players to play this game!");
	}

	LoadAssets();
}

SelectPersonaState::~SelectPersonaState() {
	Logger::Info("Destroying SelectPersonaState");
}

void SelectPersonaState::LoadAssets() {
	auto background = new GameObject();
	background->AddComponent<Sprite>(Constants::Score::Background)->SetScale(2.0f, 2.0f);
	background->box.SetCenter(Constants::Window::Center);
	(void)AddObject(background);

	auto chapter = new GameObject();
	chapter->AddComponent<Sprite>(Constants::SelectPersona::Title)->SetScale(2, 2);
	chapter->box.vector = Vec2(202, 70);
	(void)AddObject(chapter);

	for (int i = 0; i < Constants::Game::MaxNumPlayers; i++) {
		if (i < GameData::NumPlayers) {
			personaConfirmed.push_back(false);
			currentPersona.push_back(Constants::PersonaType::MISTER_N_RED);
			timers.push_back(Timer());

			LoadCard(0, Constants::Book::CardPositions[i]);
			LoadPlayerLabel(i);
			LoadPersona(i);
		} else {
			LoadCard(1, Constants::Book::CardPositions[i]);
		}
	}
}

void SelectPersonaState::LoadCard(int animation, Vec2 pos) {
	auto go = new GameObject();
	auto sprite = go->AddComponent<Sprite>(&Constants::Score::Cards, animation);
	sprite->SetScale(2.0f, 2.0f);
	go->box.vector = pos;
	(void)AddObject(go);
}

void SelectPersonaState::LoadPlayerLabel(int n) {
	auto go = new GameObject();
	auto sprite = go->AddComponent<Sprite>(&Constants::Score::PlayerLabel, n + 1);
	sprite->SetScale(2.0f, 2.0f);
	go->box.vector = Constants::Book::PlayerLabelPositions[n];
	(void)AddObject(go);
}

void SelectPersonaState::LoadPersona(int n) {
	auto playerGo = new GameObject();
	auto sprite = playerGo->AddComponent<Sprite>(personas[Constants::PersonaType::MISTER_N_RED].spriteSheetData);
	sprite->SetScale(2.0f, 2.0f);
	playerGo->box.vector = Constants::Book::PersonasPositions[n];
	(void)AddObject(playerGo);
	players.push_back(playerGo);

	auto rightArrowGO = new GameObject();
	rightArrowGO->AddComponent<Sprite>("assets/img/aim.png")->SetScale(0.75f, 0.75f);
	rightArrowGO->box.vector = Constants::Book::PersonasPositions[n] + Vec2(60, 110);
	(void)AddObject(rightArrowGO);

	auto leftArrowGO = new GameObject();
	leftArrowGO->AddComponent<Sprite>("assets/img/aim.png")->SetScale(0.75f, 0.75f);
	leftArrowGO->box.vector = Constants::Book::PersonasPositions[n] + Vec2(10, 110);
	leftArrowGO->angle = float(M_PI);
	(void)AddObject(leftArrowGO);

	arrows.emplace_back(rightArrowGO, leftArrowGO);
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
			personas[currentPersona[i]].isAvailable = true;

		} else if (!personaConfirmed[i]) {

			if (!personas[currentPersona[i]].isAvailable) {

				currentPersona[i] = nextPersona(currentPersona[i]);
				players[i]->GetComponent<Sprite>()->Open(personas[currentPersona[i]].spriteSheetData);

			} else if (in.GamepadPress(SDL_CONTROLLER_BUTTON_A, i)) {

				personaConfirmed[i] = true;
				personas[currentPersona[i]].isAvailable = false;

			} else if (timers[i].Get() > 300) {
				auto leftStickX = in.GamepadLeftStick(i).x;

				if (leftStickX != 0) {
					do {
						currentPersona[i] = leftStickX > 0 ? nextPersona(currentPersona[i]) : previousPersona(currentPersona[i]);
					} while (!personas[currentPersona[i]].isAvailable);

					players[i]->GetComponent<Sprite>()->Open(personas[currentPersona[i]].spriteSheetData);
					timers[i].Restart();
				}
			}
		}

		arrows[i].first->hide = arrows[i].second->hide = personaConfirmed[i];
	}

	if (std::all_of(personaConfirmed.begin(), personaConfirmed.end(), [](bool b) { return b; })) {
		for (int i = 0; i < GameData::NumPlayers; ++i) {
			GameData::Personas[i] = currentPersona[i];
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
