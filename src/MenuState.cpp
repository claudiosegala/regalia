#include <MenuState.h>

MenuState::MenuState() : option(0) {
    Logger::Info("Initing Menu State");

    this->cursor = nullptr;
    this->music.Open(Constants::Music::Opening);
}

MenuState::~MenuState() {
    Logger::Info("Destroying Menu State");
}

void MenuState::LoadAssets() {
    auto imageObject = new GameObject();
    auto image = new Sprite(*imageObject, Constants::Image::MenuBackground);

    imageObject->AddComponent(image);
    imageObject->box.vector.Reset();

    auto cursorObject = CreateOption("> ", { -50, -100 }); //> points towards first position
    auto playObject = CreateOption("Play   ", { 0, -100 });
    auto storyObject = CreateOption("Story  ", { 0, -200 });
    auto creditsObject = CreateOption("Credits", { 0, -300 });

    (void)AddObject(imageObject);
    (void)AddObject(playObject);
    (void)AddObject(storyObject);
    (void)AddObject(creditsObject);

    this->cursor = AddObject(cursorObject);
}

void MenuState::Update(float) {
    if (this->popRequested = InputManager::PopRequested()) return;
    if (this->quitRequested = InputManager::QuitRequested()) return;

    auto & in = InputManager::GetInstance();

    if (in.KeyPress(Constants::Key::ArrowUp)) {
        this->option = (this->option + 1) % 3 + 1; // 1 to 3
        this->cursor->box.vector.y = this->option * (-100);
    }

    if (in.KeyPress(Constants::Key::ArrowUp)) {
        this->option = (this->option - 1 + 3) % 3 + 1; // 1 to 3
        this->cursor->box.vector.y = this->option * (-100);
    }

    UpdateArray();
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

GameObject* MenuState::CreateOption (std::string message, Vec2 shift) {
    auto pos = Vec2 {
        Constants::Window::Width / 2;
        Constants::Window::Height / 2;
    };

    auto textAsset = "assets/font/Call me maybe.ttf";

    auto object = new GameObject();
    auto text = new Text(*object, textAsset, Constants::Menu::TextSize, Text::TextStyle::SOLID, message, { 255, 0, 0, 1 });

    textObject->AddComponent(text);
    textObject->box.SetCenter(pos + shift);
}