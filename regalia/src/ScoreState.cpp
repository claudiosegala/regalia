#include <pch.h>
#include <Camera.h>
#include <Game.h>
#include <GameData.h>
#include <GameObject.h>
#include <InputManager.h>
#include <Logger.h>
#include <Player.h>
#include <PlayState.h>
#include <Rect.h>
#include <ScoreState.h>
#include <Sprite.h>
#include <Text.h>
#include <Vec2.h>

ScoreState::ScoreState() {
	Logger::Info("Initializing Story State");

	//music.Open(Constants::Story::Music);

	LoadAssets();
}

ScoreState::~ScoreState() {
	Logger::Info("Destroying Story State");
}

void ScoreState::LoadAssets() {
	LoadBackground();
	LoadScore();
	LoadOptions();
}

void ScoreState::Update(unsigned dt) {
	auto& in = InputManager::GetInstance();

	popRequested = in.PopRequested();
	if (popRequested) {
		return;
	}

	quitRequested = in.QuitRequested();
	if (quitRequested) {
		return;
	}

	auto game = Game::GetInstance();

	if (in.GamepadPress(SDL_CONTROLLER_BUTTON_A)) {
		if (GameData::Paused) {
			GameData::Paused = false;
			popRequested = 1;
			return;
		}

		if (!GameData::Finished) { // has next set
			game->Push(new PlayState());
			popRequested = 2;
			return;
		}
	}

	if (in.GamepadPress(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) { // restart
		game->Push(new PlayState());
		popRequested = 2;
		return;
	}

	if (in.GamepadPress(SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) { // quit
		quitRequested = true;
		return;
	}

	UpdateArray(dt);
}

void ScoreState::Render() {
	RenderArray();
}

void ScoreState::Start() {
	Logger::Info("Starting Story State");
	Camera::Reset();

	StartArray();

	started = true;
}

void ScoreState::Pause() {
	Logger::Info("Pausing Title State");
}

void ScoreState::Resume() {
	Logger::Info("Resuming Title State");
	Camera::Reset();
}

void ScoreState::LoadBackground() {
	auto go = new GameObject();

	go->AddComponent<Sprite>(Constants::Score::Background);

	go->box.SetCenter(Constants::Window::Center);

	(void)AddObject(go);
}

// TODO: improve to be more generic
void ScoreState::LoadScore() {
	auto pos = Vec2(20, 150); // sprite frame width, arbitrario

	{
		auto go = new GameObject();
		auto text = GameData::Paused 
			? std::string("Set ") + std::to_string(GameData::Set) 
			: std::string("Scoreboard");

		go->AddComponent<Text>(Constants::Game::Font, Constants::Score::VictoriesSize, Text::TextStyle::BLENDED, text, Constants::Colors::White);
		go->box.SetCenter({ Constants::Window::Width / 2, 50 });

		(void)AddObject(go);
	}

	for (int i = 0; i < GameData::NumPlayers; i++) {
		auto victories = 0;

		for (int j = 0; j < Constants::Game::Sets; j++) {
			victories += (GameData::Result[j] == i);
		}

		{
			auto go = new GameObject();

			go->AddComponent<Sprite>(&Constants::Player::MisterN)->SetScale(3.0f, 3.0f);
			go->box.vector = pos;

			(void)AddObject(go);
		}

		{
			auto go = new GameObject();
			auto text = std::to_string(victories);

			go->AddComponent<Text>(Constants::Game::Font, Constants::Score::VictoriesSize, Text::TextStyle::BLENDED, text, Constants::Colors::White);
			go->box.SetCenter(pos + Vec2(187, 72));

			(void)AddObject(go);
		}

		pos += Vec2(230, 0);
	}
}

void ScoreState::LoadOptions() {
	std::vector<std::string> options;

	if (GameData::Paused) {
		options.emplace_back("A - Continue Match");
	} else if (!GameData::Finished) {
		options.emplace_back("A - Continue to Next Set");
	}

	options.emplace_back("R1 - Restart");
	options.emplace_back("L1 - Quit");

	for (size_t i = 0; i < options.size(); i++) {
		auto go = new GameObject();

		go->AddComponent<Text>(Constants::Game::Font, Constants::Score::OptionSize, Text::TextStyle::BLENDED, options[i], Constants::Colors::White);
		go->box.SetCenter({ Constants::Window::Width / 2, 350 + 50 * int(i) });

		(void)AddObject(go);
	}
}