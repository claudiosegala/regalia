#include <Camera.h>
#include <CameraFollower.h>
#include <InputManager.h>
#include <Rect.h>
#include <Sound.h>
#include <Sprite.h>
#include <StageState.h>
#include <TileMap.h>
#include <TileSet.h>
#include <Vec2.h>
#include <Alien.h>
#include <PenguinBody.h>
#include <PenguinCannon.h>
#include <Collider.h>
#include <Collision.h>
#include <EndState.h>
#include <Game.h>
#include <GameData.h>

const int StageState::aliens_count = 3;

StageState::StageState () : State(), music() {
    Logger::Info("Initing Stage State");   
    this->started = false;
    this->quitRequested = false;
    this->music.Open("assets/audio/stageState.ogg");
    this->tileSet = nullptr;
    LoadAssets();
}

StageState::~StageState () {
    Logger::Info("Destroying Stage State");
    this->music.Stop();
}

void StageState::Start () {
    Logger::Info("Starting Stage State");
    StartArray();

    this->started = true;
    this->music.Play();
}

void StageState::Pause () {
    Logger::Info("Pausing Stage State");
    this->music.Stop(0);
}

void StageState::Resume () {
    Logger::Info("Resuming Stage State");
}

void StageState::LoadAssets () {
    Logger::Info("Loading Assets of Stage State");
    
    CreateField();
    CreateMainCharacter();
    CreateEnemies();
}

void StageState::Update (float dt) {
    auto& in = InputManager::GetInstance();

    this->popRequested = in.KeyPress(ESCAPE_KEY);

    if (this->popRequested) return;

    this->quitRequested = in.QuitRequested();

    if (this->quitRequested) return;

    if (Alien::alienCount == 0 || PenguinBody::player == nullptr) {
        EndMatch(PenguinBody::player != nullptr);
        return;
    }

    Camera::Update(dt);

    UpdateArray(dt);
    CheckCollision();
    PruneArray();
}

void StageState::Render () {
    RenderArray();

    for (auto &field : this->objectArray) {
        auto component = field->GetComponent("TileMap");

        if (component == nullptr) continue;

        auto tileMap = std::static_pointer_cast<TileMap>(component);

        tileMap->RenderLayer(1, (int) Camera::pos.x, (int) Camera::pos.y);
    }
}

void StageState::CheckCollision () {
    std::vector<int> objs;

    for (int i = 0; i < (int) this->objectArray.size(); i++) {
        if (this->objectArray[i]->GetComponent("Collider") != nullptr) {
            objs.push_back(i);
        }
    }

    for (int i = 0; i < (int) objs.size(); i++) {
        for (int j = i+1; j < (int) objs.size(); j++) {
            auto obj1 = this->objectArray[objs[i]];
            auto obj2 = this->objectArray[objs[j]];

            if (Collision::IsColliding(obj1->box, obj2->box, obj1->angle, obj2->angle)) {
                auto obj1_ptr = obj1.get();
                auto obj2_ptr = obj2.get();

                if (obj1_ptr) {
                    obj2->NotifyCollision(*obj1_ptr);
                }

                if (obj2_ptr) {
                    obj1->NotifyCollision(*obj2_ptr);
                }
            }
        }
    }
}

void StageState::CreateField () {
    auto backgroundObject = new GameObject();
    auto tileSet = new TileSet(*backgroundObject, 64, 64, "assets/img/tileset.png");
    auto image = new Sprite(*backgroundObject, "assets/img/ocean.jpg");
    auto tileMap = new TileMap(*backgroundObject, "assets/map/tileMap.txt", tileSet);
    auto cameraFollower = new CameraFollower(*backgroundObject);

    backgroundObject->AddComponent(image);
    backgroundObject->AddComponent(tileMap);
    backgroundObject->AddComponent(cameraFollower);
    backgroundObject->box.vector = Vec2(0, 0);

    (void)AddObject(backgroundObject);
}

void StageState::CreateMainCharacter () {
    auto gameObject = new GameObject();
    auto mainChar = new PenguinBody(*gameObject);

    gameObject->AddComponent(mainChar);
    gameObject->box.vector = Vec2(704, 640);

    Camera::Follow(gameObject);

    (void)AddObject(gameObject);
}

void StageState::CreateEnemies () {
    auto range = [=] (int n) {
        n++;
        return (rand() - n) % n; // -n to n
    };

    for (int i = 0; i < StageState::aliens_count; i++) {
        auto alienObject = new GameObject();
        auto alien = new Alien(*alienObject, 5);

        alienObject->AddComponent(alien);
        alienObject->box.vector = {
            512 + range(1000), 
            300 + range(1000)
        };

        (void)AddObject(alienObject);
    }
}

void StageState::EndMatch (bool victory) {
    GameData::playerVictory = victory;

    this->popRequested = true;

    auto game = Game::GetInstance();

    game->Push(new EndState());
}
