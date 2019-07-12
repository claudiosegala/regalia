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
#include <MenuState.h>
#include <Sprite.h>
#include <Text.h>
#include <Vec2.h>

ScoreState::ScoreState() {
	Logger::Info("Initializing Story State");

	music.Open(Constants::Score::Music);

	LoadAssets();
}

ScoreState::~ScoreState() {
	Logger::Info("Destroying Story State");
}

void ScoreState::LoadAssets() {
	LoadBackground();
	LoadChapter();
	//LoadOptions();
	LoadScore();
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

	if (in.GamepadPress(SDL_CONTROLLER_BUTTON_B)) { // restart
		GameData::Init();
		game->Push(new PlayState());
		popRequested = 2;
		return;
	}

	if (in.GamepadPress(SDL_CONTROLLER_BUTTON_Y)) { // go back to menu
		game->Push(new MenuState());
		popRequested = 3;
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

	music.Play();
}

void ScoreState::Pause() {
	Logger::Info("Pausing Title State");
	music.Stop(0);
}

void ScoreState::Resume() {
	Logger::Info("Resuming Title State");
	Camera::Reset();
	music.Play();
}

void ScoreState::LoadBackground() {
	auto go = new GameObject();

	go->AddComponent<Sprite>(Constants::Score::Background);

	go->box.SetCenter(Constants::Window::Center);

	(void)AddObject(go);
}

void ScoreState::LoadChapter() {
	GameObject* go;

	if (GameData::Finished) {
		go = new GameObject();
		go->AddComponent<Sprite>(Constants::Score::End)->SetScale(2, 2);
		go->box.vector = Vec2(175, 75);

		(void)AddObject(go);
	} else {
		go = new GameObject();
		go->AddComponent<Sprite>(Constants::Score::Chapter)->SetScale(2, 2);
		go->box.vector = Vec2(175, 75);

		(void)AddObject(go);

		/*go = new GameObject();
		go->AddComponent<Sprite>(Constants::Score::Nums)->SetAnimation(GameData::Set);
		go->box.vector = Vec2(300, 75);

		(void)AddObject(go);*/
	}
}

void ScoreState::LoadScore() {
	auto pos = Vec2(500, 100); // sprite frame width, arbitrario

	for (int i = 0; i < Constants::Game::MaxNumPlayers; i++) {
		auto victories = 0;

		for (int j = 0; j < Constants::Game::Sets; j++) {
			victories += (GameData::Result[j] == i);
		}

		if (i < GameData::NumPlayers) {
			LoadCard(1 + (victories == Constants::Game::VictoriesToWin), pos);
			LoadPlayer(i, pos);
			LoadPersona(GameData::Personas[i], pos);
			LoadVictories(i, victories, pos);
		} else {
			LoadCard(0, pos);
		}

		pos += Vec2(230, 0);
	}
}

void ScoreState::LoadCard(int animation, Vec2 pos) {
	(void)animation;
	(void)pos;
}

void ScoreState::LoadPlayer(int n, Vec2 pos) {
	(void)n;
	(void)pos;
}

void ScoreState::LoadPersona(Constants::PersonaType type, Vec2 pos) {
	auto go = new GameObject();

	switch (type) {
		case Constants::PersonaType::MISTER_N_RED:
			go->AddComponent<Sprite>(&Constants::Player::MisterNRed)->SetScale(3.0f, 3.0f);
			break;
		case Constants::PersonaType::MISTER_N_BLUE:
			go->AddComponent<Sprite>(&Constants::Player::MisterNBlue)->SetScale(3.0f, 3.0f);
			break;
		case Constants::PersonaType::GOTICA_RED:
			go->AddComponent<Sprite>(&Constants::Player::GoticaRed)->SetScale(3.0f, 3.0f);
			break;
		case Constants::PersonaType::GOTICA_PURPLE:
			go->AddComponent<Sprite>(&Constants::Player::GoticaPurple)->SetScale(3.0f, 3.0f);
			break;
		default:
			throw std::runtime_error("Invalid persona type");
	}

	go->box.vector = pos;

	(void)AddObject(go);
}

void ScoreState::LoadVictories(int id, int victories, Vec2 pos) {
	auto go = new GameObject();
	auto text = std::to_string(1);
	(void)id;
	(void)victories;
	go->AddComponent<Text>(Constants::Game::Font, Constants::Score::VictoriesSize, Text::TextStyle::BLENDED, text, Constants::Colors::White);
	go->box.SetCenter(pos + Vec2(187, 72));

	(void)AddObject(go);
}