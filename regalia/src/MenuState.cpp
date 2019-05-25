#include <pch.h>
#include <Game.h>
#include <Camera.h>
#include <Constants.h>
#include <InputManager.h>
#include <Logger.h>
#include <MenuState.h>
#include <PlayState.h>
#include <Rect.h>
#include <Sprite.h>
#include <Text.h>
#include <Vec2.h>

MenuState::MenuState()
    : option(0)
    , cursor() {
	Logger::Info("Initializing Menu State");

	//this->music.Open(Constants::Menu::Music);
	LoadAssets();
}

MenuState::~MenuState() {
	Logger::Info("Destroying Menu State");
}

void MenuState::LoadAssets() {
	(void)AddObject(CreateBackground());
	(void)AddObject(CreateOption("Play", { 0, 0 }));
	(void)AddObject(CreateOption("Story", { 0, 75 }));
	(void)AddObject(CreateOption("Credits", { 0, 150 }));

	this->cursor = AddObject(CreateOption(">", { -75, 0 })); //> points towards first position
}

void MenuState::Update(float dt) {
	this->popRequested = InputManager::IsPopRequested();
	if (this->popRequested) {
		return;
	}
	this->quitRequested = InputManager::IsQuitRequested();
	if (this->quitRequested) {
		return;
	}

	auto& in = InputManager::GetInstance();

	if (in.KeyPress(Constants::Key::ArrowDown) || in.GamepadPress(SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
		this->option = (this->option + 1) % 3; // 0 to 2

		if (auto ptr = this->cursor.lock()) {
			const auto pos = Vec2 {
				Constants::Window::Width / 2 - 75,
				Constants::Window::Height / 2 + this->option * 75
			};

			ptr->box.SetCenter(pos);
		}
	}

	else if (in.KeyPress(Constants::Key::ArrowUp) || in.GamepadPress(SDL_CONTROLLER_BUTTON_DPAD_UP)) {
		this->option = (this->option - 1 + 3) % 3; // 0 to 2

		if (auto ptr = this->cursor.lock()) {
			const auto pos = Vec2 {
				Constants::Window::Width / 2 - 75,
				Constants::Window::Height / 2 + this->option * 75
			};

			ptr->box.SetCenter(pos);
		}
	}

	else if (in.KeyPress(Constants::Key::Space) || in.GamepadPress(SDL_CONTROLLER_BUTTON_A, 0)) {
		auto game = Game::GetInstance();

		game->Push(new PlayState());

		// if (this->option == 0) {
		//     game->Push(new PlayState());
		// } else if (this->option == 1) {
		//     game->Push(new StoryState());
		// } else {
		//     game->Push(new CreditState());
		// }
	}

	UpdateArray(dt);
}

void MenuState::Render() {
	RenderArray();
}

void MenuState::Start() {
	Logger::Info("Starting Menu State");
	Camera::Reset();

	StartArray();

	this->started = true;
}

void MenuState::Pause() {
	Logger::Info("Pausing Title State");
}

void MenuState::Resume() {
	Logger::Info("Resuming Title State");
	Camera::Reset();
}

GameObject* MenuState::CreateBackground() {
	auto go = new GameObject();
	const auto image = new Sprite(*go, Constants::Menu::Background);

	go->AddComponent(image);
	go->box.vector.Reset();

	return go;
}

GameObject* MenuState::CreateOption(std::string message, Vec2 shift) {
	const auto pos = Vec2 {
		Constants::Window::Width / 2,
		Constants::Window::Height / 2
	};

	const auto textAsset = "assets/font/Call me maybe.ttf";

	auto go = new GameObject();
	const auto text = new Text(*go, textAsset, Constants::Menu::TextSize, Text::TextStyle::SOLID, message, { 255, 0, 0, 0 });

	go->AddComponent(text);
	go->box.SetCenter(pos + shift);

	return go;
}