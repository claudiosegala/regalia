#include <Util.h>
#include <EndState.h>
#include <Game.h>
#include <GameData.h>
#include <Sprite.h>
#include <Music.h>
#include <Text.h>
#include <InputManager.h>
#include <Util.h>
#include <Camera.h>
#include <TitleState.h>

EndState::EndState () {
    Logger::Info("Initing End State");
    LoadAssets();
}

EndState::~EndState () {
    Logger::Info("Destroying End State");
}

void EndState::LoadAssets () {
    auto soundAsset = GameData::playerVictory ? "assets/audio/endStateWin.ogg" : "assets/audio/endStateLose.ogg";

    this->backgroundMusic.Open(soundAsset);

    auto imageAsset = GameData::playerVictory ? "assets/img/win.jpg" : "assets/img/lose.jpg";
    auto imageObject = new GameObject();
    auto image = new Sprite(*imageObject, imageAsset);

    imageObject->AddComponent(image);

    auto msg = "Pressione SPACE BAR para jogar novamente e ESC para sair";
    auto textAsset = "assets/font/Call me maybe.ttf";
    auto textObject = new GameObject();
    auto text = new Text(*textObject, textAsset, 20, Text::TextStyle::SOLID, msg, { 255, 0, 0, 1 });

    textObject->AddComponent(text);
    textObject->box.SetCenter({ 512, 580 });

    (void) AddObject(imageObject);
    (void) AddObject(textObject);
}

void EndState::Update (float dt) {
    UNUSED(dt);

    auto& in = InputManager::GetInstance();

    this->quitRequested = this->popRequested = in.KeyPress(ESCAPE_KEY);

    if (this->popRequested) return;

    this->quitRequested = in.QuitRequested();

    if (this->quitRequested) return;

    if (in.KeyPress(SPACE_BAR)) {
        this->popRequested = true;
    }

	UpdateArray(dt);
}

void EndState::Render () {
	RenderArray();
}

void EndState::Start () {
    Logger::Info("Starting End State");
    Camera::Reset();
    
	StartArray();

    this->started = true;
    this->backgroundMusic.Play();
}

void EndState::Pause () {
    Logger::Info("Pausing End State");
    this->backgroundMusic.Stop(0);
}

void EndState::Resume () {
    Logger::Info("Resuming End State");
    Camera::Reset();
}