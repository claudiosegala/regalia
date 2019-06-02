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

	associated.hide = true;

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
	auto stick = in.GamepadRightStick(playerId);
	auto show = stick.x != 0 || stick.y != 0;

	associated.hide = !show;

	if (!show) {
		return;
	}

	auto angle = stick.GetAngle();
	auto dist = Constants::Player::ArrowDistance;
	auto position = dist.GetRotate(angle) + currentPlayer->box.Center();

	associated.box.SetCenter(position);
	associated.angle = angle;
}

void PlayerAim::Render() {}

void PlayerAim::LoadAssets() {
	auto sprite = associated.AddComponent<Sprite>("assets/img/aim.png");
	sprite->SetScale(0.8f, 0.8f);
}
