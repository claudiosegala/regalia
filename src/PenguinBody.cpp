#include <PenguinBody.h>
#include <Sprite.h>
#include <Sound.h>
#include <PenguinCannon.h>
#include <Game.h>
#include <StageState.h>
#include <Collider.h>
#include <Bullet.h>
#include <Camera.h>

int const PenguinBody::life = 50;

float const PenguinBody::spinPace = 1.5f;

float const PenguinBody::pace = 0.5f;

float const PenguinBody::maxSpeed = 1.0f;

PenguinBody* PenguinBody::player;

PenguinBody::PenguinBody (GameObject& associated) : Component(associated), pcannon() {
    Logger::Info("Creating Penguin Body");
    PenguinBody::player = this;
    
    this->hp = PenguinBody::life;
    this->angle = 0.0f;
    this->linearSpeed = 0.0f;
    this->speed = Vec2(0, 0);
    
    LoadAssets();
}

PenguinBody::~PenguinBody() {
    Logger::Info("Destroying Penguin Body");

    PenguinBody::player = nullptr;
}

void PenguinBody::LoadAssets() {
    auto image = new Sprite(this->associated, "assets/img/penguin.png");
    auto collider = new Collider(this->associated);

    this->associated.AddComponent(image);
    this->associated.AddComponent(collider);
}

void PenguinBody::Start() {
    Logger::Info("Starting Penguin Body");

    auto game = Game::GetInstance();
    auto state = game->GetCurrentState();
    auto ownGo = state->GetObjectPtr(&this->associated);

    auto go = new GameObject();
    auto pc = new PenguinCannon(*go, ownGo);

    go->AddComponent(pc);

    this->pcannon = state->AddObject(go);
}

void PenguinBody::Update(float dt) {
    auto& in  = InputManager::GetInstance();

    auto keyA = in.IsKeyDown(A_KEY);
    auto keyD = in.IsKeyDown(D_KEY);
    auto keyW = in.IsKeyDown(W_KEY);
    auto keyS = in.IsKeyDown(S_KEY);

    if (keyW || keyS) {
        this->linearSpeed += (keyW ? 1 : -1) * PenguinBody::pace * dt;
        this->linearSpeed = this->linearSpeed > 0 ? fmin(this->linearSpeed, PenguinBody::maxSpeed) : fmax(this->linearSpeed, -PenguinBody::maxSpeed);
    }

    if (keyA || keyD) {
        this->angle += (keyA ? -1 : 1) * PenguinBody::spinPace * dt;
    }

    this->speed = Vec2(1, 0).GetRotate(this->angle) * linearSpeed;
    this->associated.angle = this->angle;
    this->associated.box.vector += this->speed;
    this->associated.box.vector.Limit(1408, 0, 1280, 0);
}

void PenguinBody::Render() {}

void PenguinBody::NotifyCollision(GameObject &other) {
    auto component = other.GetComponent("Bullet");

    if (component == nullptr) return;    
    
    auto bullet = std::static_pointer_cast<Bullet>(component);

    // Check if bullet was launch by me
    if (bullet->targetPlayer) return;

    this->hp -= bullet->GetDamage();

    if (this->hp > 0) return;

    Die();
}

bool PenguinBody::Is(std::string type) {
    return (type == "PenguinBody");
}

Vec2 PenguinBody::GetPosition() {
    return this->associated.box.Center();
}

void PenguinBody::Die () {
    this->associated.RequestDelete();

    Camera::Unfollow();
    
    auto explosionObject = new GameObject();
    auto image = new Sprite(*explosionObject, "assets/img/penguindeath.png", 5, 0.05f, 0.25f);
    auto sound = new Sound(*explosionObject, "assets/audio/boom.wav");

    explosionObject->AddComponent(image);
    explosionObject->AddComponent(sound);
    explosionObject->box.SetCenter(this->associated.box.Center());

    auto game = Game::GetInstance();
    auto state = game->GetCurrentState();
    (void) state->AddObject(explosionObject);

    sound->Play();
}