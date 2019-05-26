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
	auto player = this->player.lock();
	if (!player) {
		associated.RequestDelete();
		return;
	}

	auto& in = InputManager::GetInstance();
	auto rightStickVec = in.GamepadRightStick(playerId);
}

void PlayerAim::Render() {}

void PlayerAim::LoadAssets() {
	associated.AddComponent<Sprite>("assets/img/aim.png");
}
