#include <PenguinCannon.h>
#include <Game.h>
#include <StageState.h>
#include <Camera.h>
#include <Sprite.h>
#include <Bullet.h>
#include <Collider.h>
#include <Timer.h>

float const PenguinCannon::restCoolDown = 1.0f;

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody) : Component(associated), coolDownTime() {
    // Adding image
    auto image = new Sprite(this->associated, "assets/img/cubngun.png");
    this->associated.AddComponent(image);

    // Adding Collider
    auto collider = new Collider(this->associated);
    this->associated.AddComponent(collider);

    // Initing variables
    this->pbody = penguinBody;
    this->angle = 0.0f;
}

void PenguinCannon::Update(float dt) {
    this->coolDownTime.Update(dt);

    auto penguinBody = this->pbody.lock();

    if (penguinBody == nullptr) {
        this->associated.RequestDelete();
        return;
    }

    // Set position
    this->associated.box.SetCenter(penguinBody->box.Center());

    // Adjust Cannon
    auto &in = InputManager::GetInstance();
    auto dir = in.GetMouse(Camera::pos) - this->associated.box.Center();

    this->associated.angle = this->angle = dir.GetAngle();

    auto left_click = in.MousePress(LEFT_MOUSE_BUTTON);
    auto ready = this->coolDownTime.Get() > PenguinCannon::restCoolDown;

    // Shoot if it is not cooling down and pressed the left button
    if (left_click && ready) {
        Shoot();
        this->coolDownTime.Restart();
    }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(std::string type) {
    return (type == "PenguinCannon");
}

void PenguinCannon::Shoot() {
    auto gameObject = new GameObject();

    auto bullet = new Bullet(*gameObject, PI + this->angle, Bullet::defaultSpeed, Bullet::defaultDamage, Bullet::defaultMaxDistance, "assets/img/penguinbullet.png", 4, 1, true);
    gameObject->box.SetCenter(Vec2(54, 0).GetRotate(this->angle) + this->associated.box.Center());
    gameObject->angle = this->angle;
    gameObject->AddComponent(bullet);

    auto game = Game::GetInstance();
    auto state = game->GetCurrentState();
    (void) state->AddObject(gameObject);
}