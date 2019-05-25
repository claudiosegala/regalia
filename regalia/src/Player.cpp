#include "pch.h"
#include "Player.h"
#include "Sprite.h"
#include "Constants.h"
#include "GameObject.h"
#include "InputManager.h"

Player::Player(GameObject& go)
    : Component(go) {
	this->hp = 50;
	this->stateAnimation = PlayerState::IDLE;
	this->speed = Vec2(0, 0);

	// TODO: discover why there is one tile of shift
	this->associated.box.SetCenter({ 50.0f, 226.0f });

	LoadAssets();
}

void Player::Update(float dt) {
	Move(dt);

	// change Player State
	// update sprite
	// actions if necessary
}

void Player::Render() {
}

bool Player::Is(std::string type) {
	return (type == "Player");
}

void Player::LoadAssets() {
	auto image = new Sprite(this->associated, "assets/img/mister_n_idle.png");
	this->associated.AddComponent(image);
}

void Player::Move(float dt) {
	auto& in = InputManager::GetInstance();

	Vec2 velocity = in.GamepadLeftStick(0);
	if (velocity == Vec2(0, 0)) { // No input from gamepad stick, look for other inputs
		const auto keyUp    = in.IsKeyDown(Constants::Key::W) || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_UP, 0);
		const auto keyDown  = in.IsKeyDown(Constants::Key::S) || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN, 0);
		const auto keyLeft  = in.IsKeyDown(Constants::Key::A) || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT, 0);
		const auto keyRight = in.IsKeyDown(Constants::Key::D) || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, 0);

		if (keyUp) {
			velocity.y -= 1;
		}

		if (keyDown) {
			velocity.y += 1;
		}

		if (keyLeft) {
			velocity.x -= 1;
		}

		if (keyRight) {
			velocity.x += 1;
		}
	}

	velocity *= (Constants::Player::SpeedMultiplier * dt);

	const auto nxtPos = this->associated.box + velocity;

	auto points = nxtPos.GetPoints();
	const auto upperLeft = std::get<1>(points);
	const auto downRight = std::get<0>(points);

	bool can = true;

	// TODO: PlayState should let this available
	int collisionSet[14][20] = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	const auto x1 = int(upperLeft.x) / 24;
	const auto y1 = int(upperLeft.y) / 24;
	const auto x2 = int(downRight.x) / 24;
	const auto y2 = int(downRight.y) / 24;

	for (int i = x1; i <= x2; i++) {
		for (int j = y1; j <= y2; j++) {
			std::cout << collisionSet[j][i] << " ";
			if (collisionSet[j][i]) {
				can = false;
				//break;
			}
		}
		std::cout << std::endl;
	}

	if (can) {
		W(this->associated.box)
		this->associated.box.vector += velocity;
	}
}
