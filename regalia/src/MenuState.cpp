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

MenuState::MenuState() {
	Logger::Info("Initializing Menu State");

	music.Open(Constants::Menu::Music);
	LoadAssets();
}

MenuState::~MenuState() {
	Logger::Info("Destroying Menu State");
}

void MenuState::LoadAssets() {
	const auto horizontalOffset = Constants::Window::Width * 0.2f;

	(void)AddObject(CreateBackground());
	(void)AddObject(CreateOption("Regalia", { -horizontalOffset, 75.f }));
	(void)AddObject(CreateOption("Play", { horizontalOffset, 0.f }));
	(void)AddObject(CreateOption("Story", { horizontalOffset, 75.f }));
	(void)AddObject(CreateOption("Credits", { horizontalOffset, 150.f }));

	cursor = AddObject(CreateOption("-              -", { horizontalOffset, 0.f })); //> points towards first position
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

	if (in.KeyPress(Constants::Key::ArrowDown) || in.GamepadPress(SDL_CONTROLLER_BUTTON_DPAD_DOWN)) {
		option = (option + 1) % 3; // 0 to 2
		PositionCursor(option);
	}

	else if (in.KeyPress(Constants::Key::ArrowUp) || in.GamepadPress(SDL_CONTROLLER_BUTTON_DPAD_UP)) {
		option = (option - 1 + 3) % 3; // 0 to 2
		PositionCursor(option);
	}

	else if (in.KeyPress(Constants::Key::Space) || in.GamepadPress(SDL_CONTROLLER_BUTTON_A, 0)) {
		auto game = Game::GetInstance();

		game->Push(new PlayState());

		// if (option == 0) {
		//     game->Push(new PlayState());
		// } else if (option == 1) {
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
	music.Play();
	StartArray();

	started = true;
}

void MenuState::Pause() {
	Logger::Info("Pausing Title State");
	music.Stop(0);
}

void MenuState::Resume() {
	Logger::Info("Resuming Title State");
	Camera::Reset();
	music.Play();
}

GameObject* MenuState::CreateBackground() {
	auto go = new GameObject();

	go->AddComponent<Sprite>(Constants::Menu::Background);

	// TODO: Remove when we have a better background image
	go->box.width = Constants::Window::Width;
	go->box.height = Constants::Window::Height;

	go->box.vector.Reset();

	return go;
}

GameObject* MenuState::CreateOption(const std::string& message, Vec2 shift) {
	const auto pos = Vec2 {
		Constants::Window::Width / 2,
		Constants::Window::Height / 4
	};

	const auto textAsset = "assets/font/Dark Crystal.ttf";

	auto go = new GameObject();

	go->AddComponent<Text>(textAsset, Constants::Menu::TextSize, Text::TextStyle::BLENDED, message, Constants::Colors::Red);

	go->box.SetCenter(pos + shift);

	return go;
}

void MenuState::PositionCursor(int position) {
	if (auto ptr = cursor.lock()) {
		const auto pos = Vec2 {
			ptr->box.Center().x,
			float(Constants::Window::Height / 4 + position * 75)
		};

		ptr->box.SetCenter(pos);
	}
}
