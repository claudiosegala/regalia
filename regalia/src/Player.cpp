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

	auto keyA = in.IsKeyDown(Constants::Key::A);
	auto keyD = in.IsKeyDown(Constants::Key::D);
	auto keyW = in.IsKeyDown(Constants::Key::W);
	auto keyS = in.IsKeyDown(Constants::Key::S);

	auto x = 0.0f;
	auto y = 0.0f;

	if (keyW || keyS) {
		y = (keyW ? -1.0f : 1.0f) * 100.0f * dt;
	}

	if (keyA || keyD) {
		x = (keyA ? -1.0f : 1.0f) * 100.0f * dt;
	}

	auto nxtPos = this->associated.box + Vec2(x, y);

	auto points = nxtPos.GetPoints();
	auto upperLeft = std::get<1>(points);
	auto downRight = std::get<0>(points);

	bool can = true;

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

	int x1 = (int)upperLeft.x / 24;
	int y1 = (int)upperLeft.y / 24;
	int x2 = (int)downRight.x / 24;
	int y2 = (int)downRight.y / 24;

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
		this->associated.box.vector += { x, y };
	}
}
