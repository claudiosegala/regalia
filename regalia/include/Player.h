#pragma once

#include <Component.h>
#include <Rect.h>
#include <Vec2.h>
#include "Sprite.h"
#include "Timer.h"

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
	enum Sides : int {
		None = 0,
		Top = 1 << 0,
		Bottom = 1 << 1,
		Left = 1 << 2,
		Right = 1 << 3
	};

	enum PlayerState : int {
		Idle = 0,
		IsDying = 1 << 0,
		IsMidAir = 1 << 1,
		IsLoading = 1 << 2,
		IsShooting = 1 << 3
	};

	int collisions = None;

	int playerState = Idle;

	Constants::Player::AnimationState animationState = Constants::Player::IdleAnimation;

	Timer currentAnimationTimer;

	unsigned currentAnimationHoldTime = 0;

	Sprite* associatedSprite = nullptr;

	int hp = Constants::Player::Hp;

	Vec2 speed = { 0, 0 };

	Rect collisionBox;

	void LoadAssets();

	void UpdateAnimationState();

	void SetState(Constants::Player::AnimationState nextState, Sprite::Direction dirX);

	void LoadAndShoot();

	void UpdateSpeed(unsigned long dt);

	void MoveAndSlide(unsigned long dt);

	void Die();
};
