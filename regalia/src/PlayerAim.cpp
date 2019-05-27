#include "pch.h"
#include "PlayerAim.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Sprite.h"

PlayerAim::PlayerAim(GameObject& go, std::weak_ptr<GameObject> player, int playerId)
    : Component(go)
    , player(player)
    , playerId(playerId) {

	LoadAssets();
}

PlayerAim::~PlayerAim() {}

void PlayerAim::Update(float dt) {
	UNUSED(dt);

	auto player = this->player.lock();
	if (!player) {
		associated.RequestDelete();
		return;
	}

	auto& in = InputManager::GetInstance();
	auto rightStickVec = in.GamepadRightStick(playerId);

	if (rightStickVec.x == 0 && rightStickVec.y == 0) {
		associated.hide = true;
		return;
	}

	auto angle = rightStickVec.GetAngle();
	auto position = Vec2(50, 0).GetRotate(angle) + player->box.Center();

	associated.hide = false;
	associated.box.SetCenter(position);
	associated.angle = angle;
}

void PlayerAim::Render() {}

void PlayerAim::LoadAssets() {
	associated.AddComponent<Sprite>("assets/img/aim.png");
}
