#include <pch.h>
#include <Game.h>
#include <Camera.h>
#include <Constants.h>
#include <InputManager.h>
#include <Logger.h>
#include <MenuState.h>
#include <StoryState.h>
#include <CreditState.h>
#include <PlayState.h>
#include <Rect.h>
#include <Sprite.h>
#include <Text.h>
#include <Vec2.h>
#include <SelectPersonaState.h>
#include "Sound.h"

MenuState::MenuState() {
	Logger::Info("Initializing Menu State");

	LoadAssets();
}

MenuState::~MenuState() {
	Logger::Info("Destroying Menu State");
}

void MenuState::LoadAssets() {
	const auto horizontalOffset = Constants::Window::Width * 0.2f;

	CreateBackground();

	CreateOption(Play, &Constants::Menu::Play, { 650, 230 });
	CreateOption(History, &Constants::Menu::History, { 320, 130 });
	CreateOption(Credits, &Constants::Menu::Credits, { 320, 230 });
	CreateOption(Exit, &Constants::Menu::Exit, { 320, 330 });

	CreateSound();

	music.Open(Constants::Menu::Music);
}

void MenuState::Update(unsigned dt) {
	auto& in = InputManager::GetInstance();

	popRequested = in.PopRequested();
	if (popRequested) {
		return;
	}

	quitRequested = in.QuitRequested();
	if (quitRequested) {
		return;
	}

	if (in.GamepadPress(SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
		SelectedOption = (SelectedOption + 1) % MAX_OPTION;
		sound->Play();
	} else if (in.GamepadPress(SDL_CONTROLLER_BUTTON_DPAD_UP)) {
		SelectedOption--;
		if (SelectedOption < 0) {
			SelectedOption = MAX_OPTION - 1;
		}
		sound->Play();
	} else if (in.GamepadPress(SDL_CONTROLLER_BUTTON_DPAD_LEFT) || in.GamepadPress(SDL_CONTROLLER_BUTTON_DPAD_RIGHT)) {
		SelectedOption = SelectedOption == Play ? History : Play;
		sound->Play();
	}

	if (in.GamepadPress(SDL_CONTROLLER_BUTTON_A)) {
		auto game = Game::GetInstance();

		sound->Open(Constants::Menu::ConfirmSound);
		sound->Play();

		if (SelectedOption == 0) {
			game->Push(new SelectPersonaState());
		} else if (SelectedOption == 1) {
			game->Push(new StoryState());
		} else if (SelectedOption == 2) {
			game->Push(new CreditState());
		} else {
			quitRequested = true;
		}
	}

	for (auto& sprite : OptionSprite) {
		sprite.second->SetAnimation(sprite.first == SelectedOption ? 1 : 0);
	}

	UpdateArray(dt);
}

void MenuState::Render() {
	RenderArray();
}

void MenuState::Start() {
	Logger::Info("Starting Menu State");
	Camera::Reset();
	music.Play();
	StartArray();

	started = true;
}

void MenuState::Pause() {
	Logger::Info("Pausing Title State");
}

void MenuState::Resume() {
	Logger::Info("Resuming Title State");
	music.Play();
}

void MenuState::CreateBackground() {
	auto go = new GameObject();

	go->AddComponent<Sprite>(Constants::Menu::Background);

	go->box.width = Constants::Window::Width;
	go->box.height = Constants::Window::Height;
	go->GetComponent<Sprite>()->SetScale(2.0f, 2.0f);

	go->box.vector.Reset();

	(void)AddObject(go);
}

void MenuState::CreateOption(int option, const SpriteSheetData* spriteSheetData, Vec2 position) {
	auto go = new GameObject();

	OptionSprite[option] = go->AddComponent<Sprite>(spriteSheetData);

	go->box.width = Constants::Window::Width;
	go->box.height = Constants::Window::Height;
	go->GetComponent<Sprite>()->SetScale(2.0f, 2.0f);

	go->box.SetCenter(position);

	(void)AddObject(go);
}

void MenuState::CreateSound() {
	auto go = new GameObject();
	sound = go->AddComponent<Sound>(Constants::Menu::Sound);
	(void)AddObject(go);
}