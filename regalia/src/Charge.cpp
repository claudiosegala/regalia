#include <pch.h>
#include <Charge.h>
#include <Rect.h>
#include <Vec2.h>

Charge::Charge(GameObject& go, GameObject* playerGO)
    : Component(go)
    , player(playerGO) {

	timer.Pause();

	LoadAssets();
}

void Charge::Update(unsigned dt) {
	timer.Update(dt);
	W(timer.Get());

	associated.box.SetCenter(player->box.Center());

	// TODO: update the animation
}

void Charge::Render() {}

void Charge::Load() {
	timer.Continue();
}

void Charge::Unload() {
	timer.Reset();
}

bool Charge::Overload() {
	return timer.Get() > Constants::Player::ChargeTimeMax;
}

int Charge::GetLevel() {
	using namespace Constants::Player;

	auto dt = timer.Get();

	W(dt);

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
	// TODO: load charge 
}