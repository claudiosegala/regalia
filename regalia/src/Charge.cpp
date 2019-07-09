#include <pch.h>
#include <Charge.h>
#include <Rect.h>
#include <Vec2.h>
#include <Sprite.h>

Charge::Charge(GameObject& go, GameObject* playerGO)
    : Component(go)
    , player(playerGO) {

	timer.Pause();

	LoadAssets();
}

void Charge::Update(unsigned dt) {
	associated.box.SetCenter(player->box.Center());
	timer.Update(dt);

	if (timer.Get() > Constants::Player::ChargeTimeMax) {
		overload = true;
	}

	auto sprite = associated.GetComponent<Sprite>();

	if (overload) {
		sprite->SetAnimation(0);
	} else {
		auto level = GetLevel();
		sprite->SetAnimation(level);
	}
}

void Charge::Render() {}

void Charge::Load() {
	timer.Continue();
}

void Charge::Unload() {
	timer.Reset();
	overload = false;
}

bool Charge::Overload() {
	return overload;
}

int Charge::GetLevel() {
	using namespace Constants::Player;

	auto dt = timer.Get();

	if (dt < ChargeTimeLevelOne) {
		return 1;
	}

	if (dt < ChargeTimeLevelTwo + ChargeTimeLevelOne) {
		return 2;
	}

	if (dt < ChargeTimeLevelThree + ChargeTimeLevelTwo + ChargeTimeLevelOne) {
		return 3;
	}

	throw std::runtime_error("Something went wrong");
}

void Charge::LoadAssets() {
	associated.AddComponent<Sprite>(&Constants::Player::Charge);
}