#include <PlayState.h>
#include <InputManager.h>
#include <Camera.h>
#include <Sprite.h>
#include <Text.h>
#include <Rect.h>
#include <Vec2.h>
#include <PlayState.h>
#include <StoryState.h>
#include <CreditState.h>

PlayState::PlayState() : roundTimer() {
    Logger::Info("Initing Play State");

    //this->music.Open(Constants::Play::Music);
    LoadAssets();
}

PlayState::~PlayState() {
    Logger::Info("Destroying Play State");
}

void PlayState::LoadAssets() {
    auto imageObject = new GameObject();
    auto image = new Sprite(*imageObject, Constants::Menu::Background);

    imageObject->AddComponent(image);
    imageObject->box.vector.Reset();

    auto cursorObject = CreateOption(">", { -75, 0 }); //> points towards first position
    auto playObject = CreateOption("Play", { 0, 0 });
    auto storyObject = CreateOption("Story", { 0, 75 });
    auto creditsObject = CreateOption("Credits", { 0, 150 });

    (void)AddObject(imageObject);
}

void PlayState::Update(float dt) {
    roundTime.Update(dt);

    this->popRequested = InputManager::IsPopRequested();
    if (this->popRequested) return;
    this->quitRequested = InputManager::IsQuitRequested();
    if (this->quitRequested) return;

    auto & in = InputManager::GetInstance();

    _update(dt);

    UpdateArray(dt);
}

void PlayState::Render() {
    RenderArray();
}

void PlayState::Start() {
    Logger::Info("Starting Play State");
    Camera::Reset();

    StartArray();

    this->started = true;
}

void PlayState::Pause() {
    Logger::Info("Pausing Title State");
}

void PlayState::Resume() {
    Logger::Info("Resuming Title State");
    Camera::Reset();
}