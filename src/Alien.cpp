#include <Alien.h>
#include <Game.h>
#include <StageState.h>
#include <InputManager.h>
#include <PenguinBody.h>
#include <Camera.h>
#include <Bullet.h>
#include <Minion.h>
#include <Sound.h>
#include <Sprite.h>
#include <Collider.h>

int Alien::alienCount = 0;

int const Alien::life = 50;

int const Alien::restCoolDown = 5;

float const Alien::pace = 200.0f;

float const Alien::spinPace = 0.001f;

Alien::Alien(GameObject& associated, int qnt_minions) : Component(associated), restTimer(), minions(qnt_minions) {
    Logger::Info("Creating Alien");

    // Adding Image
    auto image = new Sprite(this->associated, "assets/img/alien.png");
    this->associated.AddComponent(image);

    // Adding Collider
    auto collider = new Collider(this->associated);
    this->associated.AddComponent(collider);

    // Initialize variables
    Alien::alienCount++;

    this->hp = Alien::life;
    this->speed = Vec2(0, 0);
    this->destination = Vec2(0, 0);
    this->state = AlienState::RESTING;
};

Alien::~Alien() {
    Logger::Info("Destroying Alien");

    // Clear minions
    // I can do this cause it is the job of the shared_ptr to free the memory
    this->minions.clear();

    // Reduce the quantity of aliens alive
    Alien::alienCount--;
}

void Alien::Start() {
    Logger::Info("Starting Alien");

    // Init minions
    auto game = Game::GetInstance();
    auto state = game->GetCurrentState();
    auto associated_ptr = state->GetObjectPtr(&this->associated);

    auto n = (int) this->minions.size();
    auto arc = 2 * PI / n;

    for (int i = 0; i < n; i++) {
        auto gameObject = new GameObject();
        auto minion = new Minion(*gameObject, associated_ptr, arc * i);

        gameObject->AddComponent(minion);

        minions[i] = state->AddObject(gameObject);
    }
}

void Alien::Update(float dt) {
    switch (this->state) {
        case AlienState::RESTING:
            Rest(dt);
            break;
        case AlienState::MOVING:
            Move();
            break;
        case AlienState::NOP:
            break;
    }

    this->associated.angle -= Alien::spinPace;
}

void Alien::Rest (float dt) {
    auto &in = InputManager::GetInstance();
    auto pos = in.GetMouse(Camera::pos);
    
    // Update Timer
    this->restTimer.Update(dt);

    auto _randomic_number = (rand() % 2) * -(rand() % 2);

    if (this->restTimer.Get() <= Alien::restCoolDown + _randomic_number) return;

    // Start Moving
    auto u = this->associated.box.Center();
    auto v = this->destination = pos;
    auto direction = Vec2(u, v).GetUnit();

    this->speed = direction * dt * Alien::pace;
    this->state = AlienState::MOVING;
}

void Alien::Move () {
    auto u = this->associated.box.Center();
    auto v1 = this->destination; // destination
    auto v2 = u + this->speed; // where I am going

    // Get distance that should make and distance that will make
    auto totalDist = Vec2::Distance(u, v1);
    auto dist = Vec2::Distance(u, v2);

    if (totalDist > dist) {
        // Walk the distance
        this->associated.box.SetCenter(v2);
    } else {
        // Stop on the point
        this->associated.box.SetCenter(v1);

        // Change state
        this->state = AlienState::RESTING;
        this->restTimer.Restart();
        this->speed.Reset();

        // Try to Shoot
        auto pg = PenguinBody::player;

        if (pg != nullptr) {
            Shoot(pg->GetPosition());
        } else {
            // 'Dies'
            this->state = AlienState::NOP;
        }
    }
}

void Alien::Shoot (Vec2 pos) {
    // Choose closest minion
    auto idx = GetClosestMinion(pos);
    auto gameObject = this->minions[idx].lock();

    if (gameObject == nullptr) return;

    auto component = gameObject->GetComponent("Minion");

    if (component == nullptr) return;

    auto minion = std::static_pointer_cast<Minion>(component);
            
    minion->Shoot(pos);
}

int Alien::GetClosestMinion (Vec2 pos) {
    auto idx = 0;
    auto min_dist = 1e9f;

    for (int i = 0; i < (int) this->minions.size(); i++) {
        auto gameObject = this->minions[i].lock();
        auto dist = Vec2::Distance(gameObject->box.Center(), pos);

        if (gameObject != nullptr && min_dist >= dist) {
            min_dist = dist;
            idx = i;    
        }
    }

    return idx;
}

void Alien::Render() {}

void Alien::NotifyCollision(GameObject &other) {
    auto component = other.GetComponent("Bullet");

    if (component == nullptr) return;
    
    auto bullet = std::static_pointer_cast<Bullet>(component);

    // Check if bullet was launch by me
    if (!bullet->targetPlayer) return;

    // Alien loses life
    this->hp -= bullet->GetDamage();

    // Check if has died
    if (this->hp > 0) return;

    // 'Dies'
    this->associated.RequestDelete();

    // Start adding Animation of death
    auto gameObject = new GameObject();
    
    // Adding explosion image
    auto image = new Sprite(*gameObject, "assets/img/aliendeath.png", 4, 0.05f, 0.2f);
    gameObject->box = this->associated.box;
    gameObject->AddComponent(image);

    // Adding sound of explosion
    auto sound = new Sound(*gameObject, "assets/audio/boom.wav");
    gameObject->AddComponent(sound);
    sound->Play();

    // Adding to state
    auto game = Game::GetInstance();
    auto state = game->GetCurrentState();

    (void) state->AddObject(gameObject);
}

bool Alien::Is(std::string type) {
    return (type == "Alien");
}