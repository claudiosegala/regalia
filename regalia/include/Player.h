#pragma once

#include <Component.h>
#include <Rect.h>
#include <Vec2.h>
#include "Sprite.h"

class Player : public Component {
public:
	static int counter;

	const int id;

	Player(GameObject& go);

	~Player();

	void NotifyCollision(GameObject& go) override;

	void Update(unsigned dt) override;

	void Render() override;

private:
	enum Sides: int {
		None = 0,
		Top = 1 << 0,
		Bottom = 1 << 1,
		Left = 1 << 2,
		Right = 1 << 3
	};

	int collisions = None;

	Constants::Player::State state = Constants::Player::Idle;

	int hp = Constants::Player::Hp;

	Vec2 speed = { 0, 0 };

	Rect collisionBox;

	void LoadAssets();

	void UpdateState();

	void SetState(Constants::Player::State nextState, Sprite::Direction dirX);

	void Shoot();

	void UpdateSpeed(unsigned long dt);

	void MoveAndSlide(unsigned long dt);

	void Die();
};