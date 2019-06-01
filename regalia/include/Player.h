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

	void Update(float dt) override;

	void Render() override;

private:
	Constants::Player::State state;

	int hp = Constants::Player::Hp;

	Vec2 speed = { 0, 0 };

	Rect collisionBox;

	bool isOnFloor = false;

	bool isOnWall = false;

	void LoadAssets();

	void UpdateState();

	void SetState(Constants::Player::State nextState, Sprite::Direction dirX);

	void Shoot();

	void UpdateSpeed(unsigned long dt);

	void MoveAndSlide(unsigned long dt);

	std::vector<std::vector<int>> GetCollisionSet();

	unsigned long FindMaxDelta(const Rect& box, const Vec2& velocity, const unsigned long dt);

	void Die();
};
