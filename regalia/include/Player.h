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

	void Update(float) override;

	void Render() override;

private:
	Constants::Player::State state;

	int hp;

	Vec2 speed;

	Rect collisionBox;

	bool isOnFloor;

	bool isOnWall;

	void LoadAssets();

	void UpdateState();

	void SetState(Constants::Player::State nextState, Sprite::Direction dirX);

	void Shoot();

	void Move(float dt);

	void MoveAndSlide(Vec2 velocity, float dt);

	std::vector<std::vector<int>> GetCollisionSet();

	Rect CalculatePosition(const Rect pos, const Vec2 velocity, const Vec2 acceleration, const float dt);

	float FindMaxDelta(const Rect pos, const Vec2 velocity, const Vec2 acceleration, const float dt);

	void Die();
};
