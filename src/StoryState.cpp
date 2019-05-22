#include <StoryState.h>
#include <InputManager.h>
#include <Camera.h>
#include <Sprite.h>
#include <Text.h>
#include <Rect.h>
#include <Vec2.h>

StoryState::StoryState() {
    Logger::Info("Initing Story State");

    //this->music.Open(Constants::Menu::Music);
    LoadAssets();
}

StoryState::~StoryState() {
    Logger::Info("Destroying Story State");
}

void StoryState::LoadAssets() {
    auto imageObject = new GameObject();
    auto image = new Sprite(*imageObject, Constants::Story::Background);

    imageObject->AddComponent(image);
    imageObject->box.vector.Reset();

    (void)AddObject(imageObject);

    this->cursor = AddObject(cursorObject);
}

void StoryState::Update(float dt) {
    this->popRequested = InputManager::IsPopRequested();
    if (this->popRequested) return;
    this->quitRequested = InputManager::IsQuitRequested();
    if (this->quitRequested) return;

    UpdateArray(dt);
}

void StoryState::Render() {
    RenderArray();
}

void StoryState::Start() {
    Logger::Info("Starting Story State");
    Camera::Reset();

    StartArray();

    this->started = true;
}

void StoryState::Pause() {
    Logger::Info("Pausing Title State");
}

void StoryState::Resume() {
    Logger::Info("Resuming Title State");
    Camera::Reset();
}