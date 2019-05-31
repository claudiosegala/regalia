#include <pch.h>
#include <PlayerAim.h>
#include <InputManager.h>
#include <GameObject.h>
#include <Sprite.h>
#include <Util.h>
#include <Player.h>


PlayerAim::PlayerAim(GameObject& go, std::weak_ptr<GameObject> player)
    : Component(go)
    , player(player) {

	LoadAssets();
}

PlayerAim::~PlayerAim() {}

void PlayerAim::Update(float dt) {
	UNUSED(dt);

	auto currentPlayer = this->player.lock();
	if (!currentPlayer) {
		associated.RequestDelete();
		return;
	}

	auto playerId = currentPlayer->GetComponent<Player>()->id;

	auto& in = InputManager::GetInstance();
	auto rightStickVec = in.GamepadRightStick(playerId);

	if (rightStickVec.x == 0 && rightStickVec.y == 0) {
		associated.hide = true;
		return;
	}

	auto angle = rightStickVec.GetAngle();
	auto position = Vec2(50, 0).GetRotate(angle) + currentPlayer->box.Center();

	associated.hide = false;
	associated.box.SetCenter(position);
	associated.angle = angle;
}

void PlayerAim::Render() {}

void PlayerAim::LoadAssets() {
	auto sprite = associated.AddComponent<Sprite>("assets/img/aim.png");
	sprite->SetScale(0.8f, 0.8f);
}
