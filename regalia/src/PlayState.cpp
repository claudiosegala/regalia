#include <pch.h>
#include <Collider.h>
#include <Collision.h>
#include <Camera.h>
#include <Constants.h>
#include <Game.h>
#include <GameData.h>
#include <InputManager.h>
#include <Logger.h>
#include <Number.h>
#include <Player.h>
#include <PlayState.h>
#include <Rect.h>
#include <ScoreState.h>
#include <Sprite.h>
#include <StoryState.h>
#include <TileMap.h>
#include <TileSet.h>
#include <Vec2.h>
#include <PlayerAim.h>
#include <CountdownState.h>

PlayState::PlayState() {
	Logger::Info("Initializing Play State");

	backgroundIdx = 0;
	tileSetIdx = 0;
	tileMapIdx = 0;
	music.Open(Constants::Play::Music);

	if (!GameData::Started || GameData::Finished) {
		GameData::Init();
	}

	PlayState::LoadAssets();
}

PlayState::~PlayState() {
	Logger::Info("Destroying Play State");
}

void PlayState::LoadAssets() {
	CreateField();
	CreatePlayers();
}

void PlayState::Update(float dt) {
	auto& in = InputManager::GetInstance();

	popRequested = in.PopRequested() || in.GamepadPress(SDL_CONTROLLER_BUTTON_B);
	if (popRequested) {
		return;
	}

	quitRequested = in.QuitRequested();
	if (quitRequested) {
		return;
	}

	// TODO: uncomment this when constant is ok
	/*if (in.GamepadPress(Constants::Gamepad::Menu)) {
		GameData::Paused = true;
		LoadScoreState();
		return;
	}*/

	timer.Update(dt);

	// TODO: uncomment this when there are two players
	/*if (Player::counter == 1 || timer.Get() > Constants::Game::SetLenght) {
		GameData::Set++;
		GameData::Finished = (GameData::Set == Constants::Game::Sets);
		LoadScoreState();
		return;
	}*/

	CheckCollision();
	UpdateArray(dt);
	PruneArray();
}

void PlayState::Render() {
	RenderArray();
}

void PlayState::Start() {
	Logger::Info("Starting Play State");
	Camera::Reset();

	StartArray();

	started = true;

	if (Constants::Countdown::Enabled) {
		Game::GetInstance()->Push(new CountdownState(this));
	} else {
		music.Play();
	}
}

void PlayState::Pause() {
	Logger::Info("Pausing Play State");
	music.Stop(0);
}

void PlayState::Resume() {
	Logger::Info("Resuming Play State");
	Camera::Reset();
	music.Play();
}

void PlayState::CheckCollision() {
	// TODO: implement
}

void PlayState::CreateField() {
	const auto rnd = Number::Rand();

	auto& back = GetBackgroundData(rnd);
	auto& tileSet = GetTileSetData(rnd);
	auto& tileMap = GetTileMapData(rnd);

	auto backgroundGO = new GameObject();

	backgroundGO->AddComponent<Sprite>(back.file);

	// TODO: Remove when we have a better background image
	backgroundGO->box.width = Constants::Window::Width;
	backgroundGO->box.height = Constants::Window::Height;

	(void)AddObject(backgroundGO);

	auto tileMapGO = new GameObject();

	tileMapGO->AddComponent<TileMap>(tileMap.file, new TileSet(*tileMapGO, tileSet.width, tileSet.height, tileSet.file));

	tileMapGO->box.vector = Vec2(0, 0);

	(void)AddObject(tileMapGO);
}

void PlayState::CreatePlayers() {
	CreatePlayer();
	CreatePlayer();
}

void PlayState::CreatePlayer() {
	auto playerGO = new GameObject();
	playerGO->AddComponent<Player>();
	auto player = AddObject(playerGO);

	auto playerAimGO = new GameObject();
	playerAimGO->AddComponent<PlayerAim>(player);
	(void)AddObject(playerAimGO);
}

const BackgroundData& PlayState::GetBackgroundData(int rnd) {
	auto& assets = Constants::Play::Backgrounds;
	const auto idx = rnd % assets.size();
	backgroundIdx = int(idx);

	return assets[idx];
}

const TileSetData& PlayState::GetTileSetData(int rnd) {
	auto& assets = Constants::Play::TileSets;
	const auto idx = rnd % assets.size();
	tileSetIdx = int(idx);

	return assets[idx];
}

const TileMapData& PlayState::GetTileMapData(int rnd) {
	auto& assets = Constants::Play::TileMaps;
	const auto idx = rnd % assets.size();
	tileMapIdx = int(idx);

	return assets[idx];
}

void PlayState::LoadScoreState() {
	auto game = Game::GetInstance();

	game->Push(new ScoreState());
}