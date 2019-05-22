#include <TitleState.h>
#include <GameObject.h>
#include <Rect.h>
#include <Sprite.h>
#include <Camera.h>
#include <Text.h>
#include <Game.h>
#include <StageState.h>
#include <InputManager.h>

TitleState::TitleState() : State(), timer() {
    Logger::Info("Initing Title State");
    Camera::Reset();

    LoadAssets();
}
        
TitleState::~TitleState() {
    Logger::Info("Destroying Title State");
}

void TitleState::LoadAssets() {
    auto imageObject = new GameObject();
    auto image = new Sprite(*imageObject, "assets/img/title.jpg");

    imageObject->AddComponent(image);

    (void) AddObject(imageObject);
}

void TitleState::Update(float dt) {
    this->timer.Update(dt);

    auto& in = InputManager::GetInstance();

    this->popRequested = in.KeyPress(ESCAPE_KEY);

    if (this->popRequested) return;

    this->quitRequested = in.QuitRequested();

    if (this->quitRequested) return;

    if (this->timer.Get() > 0.0f && !HasComponent("Text")) {
        auto textObject = new GameObject();
        auto textAsset = "assets/font/Call me maybe.ttf";
        auto msg = "Press Space Bar to Start";
        auto text = new Text(*textObject, textAsset, 20, Text::TextStyle::SOLID, msg,  { 255, 0, 0, 1 });

        text->SetFadeOut(1.0f);
        textObject->AddComponent(text);
        textObject->box.SetCenter({ 512, 500 });

        (void)AddObject(textObject);

        this->timer.SetStart(-1.5f);
    }

    if (in.KeyPress(SPACE_BAR)) {
        auto game = Game::GetInstance();
        auto stageState = new StageState();

        game->Push(stageState);
    }

    UpdateArray(dt);
    PruneArray();
}

void TitleState::Render() {
    RenderArray();
}

void TitleState::Start() {
    Logger::Info("Starting Title State");
    Camera::Reset();

    StartArray();

    this->started = true;
}

void TitleState::Pause() {
    Logger::Info("Pausing Title State");
}

void TitleState::Resume() {
    Logger::Info("Resuming Title State");
    Camera::Reset();
}