#include <Minion.h>
#include <Sprite.h>
#include <Bullet.h>
#include <Collider.h>
#include <Game.h>
#include <StageState.h>

float const Minion::alienDistance = 200.0f;

Minion::Minion (GameObject& go, std::weak_ptr<GameObject> alienCenter, float arcOffset) : Component(go) {
    Logger::Info("Creating Minion");
    
    // Adding image
    auto k = 1 + RAND/2;
    auto image = new Sprite(this->associated, "assets/img/minion.png");
    image->SetScale(k, k);
    go.AddComponent(image);

    // Adding Collider
    auto collider = new Collider(go);
    go.AddComponent(collider);

    // Initializing variables
    this->alienCenter = alienCenter;
    this->arc = arcOffset;

    SetPosition(0);
}
    
void Minion::Update(float dt) {
    SetPosition(dt);
}

void Minion::Render() {}

bool Minion::Is(std::string type) {
    return (type == "Minion");
}

void Minion::SetPosition(float dt) {
    auto alien = alienCenter.lock();

    if (alien == nullptr) {
        this->associated.RequestDelete();
        return;
    }
    
    auto alienPos = alien->box.Center();
    auto pos = Vec2(Minion::alienDistance, 0.0f).GetRotate(this->arc) + alienPos;

    this->associated.box.SetCenter(pos);
    this->associated.angle = this->arc;
    this->arc += 0.3f * dt;
}

void Minion::Shoot(Vec2 pos) {
    auto center = this->associated.box.Center();
    auto dir = (pos - center) * -1;
    auto ang = dir.GetAngle();
    auto go = new GameObject();
    auto bullet = new Bullet(*go, ang, Bullet::defaultSpeed, Bullet::defaultDamage, Bullet::defaultMaxDistance, "assets/img/minionbullet2.png", 3, 0.2f, false);

    go->box.SetCenter(center);
    go->angle = PI + ang;
    go->AddComponent(bullet);

	auto game = Game::GetInstance();
	auto state = game->GetCurrentState();

    (void)state->AddObject(go);
}