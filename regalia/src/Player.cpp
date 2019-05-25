#include <pch.h>
#include <Bullet.h>
#include <Collider.h>
#include <Constants.h>
#include <GameObject.h>
#include <InputManager.h>
#include <Player.h>
#include <Sprite.h>
#include <Vec2.h>

int Player::counter = 0;

Player::Player(GameObject& go)
    : Component(go)
    , speed()
    , collisionBox() {
	this->id = ++Player::counter;
	this->hp = 50;
	this->stateAnimation = PlayerState::IDLE;

	// TODO: discover why there is one tile of shift
	this->associated.box.SetCenter({ 20.0f, 26.0f });

	LoadAssets();
}

Player::~Player() {
	Player::counter--;
}

void Player::NotifyCollision(GameObject& go) {
	auto component = go.GetComponent("Bullet");

	if (component == nullptr) {
		return;
	}

	auto bullet = std::static_pointer_cast<Bullet>(component);

	if (bullet->shooterId != this->id) {
		return; //> you cannot fire yourself
	}

	this->hp -= bullet->GetDamage();

	if (this->hp > 0) {
		return;
	}

	Die();
}

void Player::Update(float dt) {
	//Gravity(dt);
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
	auto collider = new Collider(this->associated, &this->collisionBox, { 0.5f, 0.8f }, { 0.0f, 4.0f });

	this->associated.AddComponent(image);
	this->associated.AddComponent(collider);
}

void Player::Move(float dt) {
	auto& in = InputManager::GetInstance();
	auto direction = in.GamepadLeftStick(0);
	auto isJumping = false;

	if (direction == Vec2(0.0f, 0.0f)) { // No input from gamepad stick, look for other inputs
		const auto keyUp = in.IsKeyDown(Constants::Key::W) || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_UP, 0);
		const auto keyDown = in.IsKeyDown(Constants::Key::S) || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN, 0);
		const auto keyLeft = in.IsKeyDown(Constants::Key::A) || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT, 0);
		const auto keyRight = in.IsKeyDown(Constants::Key::D) || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, 0);

		if (keyUp) {
			isJumping = true;
		}

		if (keyDown) {
			// nothing
		}

		if (keyLeft) {
			direction.x -= 1;
		}

		if (keyRight) {
			direction.x += 1;
		}
		W(direction);
	}
	W(Vec2(Constants::Player::SpeedMultiplier, 0.0f));
	auto horizontal_velocity = direction * Constants::Player::SpeedMultiplier;
	auto vertical_velocity = isJumping ? Constants::Game::Jump : (this->speed);
	auto velocity = Vec2(horizontal_velocity.x, vertical_velocity.y);

	CheckBestDelta(velocity, dt);
	W(direction);
	

	this->associated.box.vector += this->speed;
}

void Player::CheckBestDelta(Vec2 velocity, float delta) {
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

	auto cnt = 20;
	auto l = 0.0f;
	auto r = delta;
	auto d = delta;
	auto ans = Vec2(0.0f, 0.0f);

	while (cnt--) {
		const auto m = (r + l) / 2.0f;
		auto v = (velocity + Constants::Game::Gravity * m) * m;

		v.Limit(Constants::Game::MaxVelocity);

		const auto nxtPos = this->collisionBox + v;

		auto points = nxtPos.GetPoints();
		const auto upperLeft = std::get<1>(points);
		const auto downRight = std::get<0>(points);

		bool can = true;

		const auto x1 = int(upperLeft.x) / 24;
		const auto y1 = int(upperLeft.y) / 24;
		const auto x2 = int(downRight.x) / 24;
		const auto y2 = int(downRight.y) / 24;

		if (x1 < 0 || x1 >= 14 || y1 < 0 || y1 >= 20 || x2 < 0 || x2 >= 14 || y2 < 0 || y2 >= 20) {
			can = false;
		} else {
			for (int i = x1; i <= x2; i++) {
				for (int j = y1; j <= y2; j++) {
					if (collisionSet[j][i]) {
						can = false;
						break;
					}
				}
			}
		}

		if (can) {
			if (ans.GetLength() < v.GetLength()) {
				ans = v;
				this->speed = v;
			}

			l = m;
		} else {
			r = m;
		}
	}
}

void Player::Die() {
	this->associated.RequestDelete();

	// TODO: add animation of death
}