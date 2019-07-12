#pragma once

#include <Component.h>
#include <Rect.h>
#include <Vec2.h>
#include <Sprite.h>
#include <Timer.h>
#include <StopWatch.h>
#include <Charge.h>
#include <PlayState.h>

class Player : public Component {
public:
	const int id;

	Player(GameObject& go, int id, Constants::PersonaType persona, Vec2 initialPosition, PlayState* play_state = nullptr);

	~Player();

	void Start() override;

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

	PlayState* play_state;

	int collisions = None;

	int playerState = Idle;

	bool canShoot = false;

	Constants::Player::AnimationState animationState = Constants::Player::IdleAnimation;

	Timer currentAnimationTimer;

	StopWatch shootingCoolDown;

	unsigned currentAnimationHoldTime = 0;

	float bulletAngle = 0;

	Charge* charge = nullptr;

	Sprite* sprite = nullptr;

	int hp = Constants::Player::Hp;

	Vec2 speed = { 0, 0 };

	Rect collisionBox;

	Constants::PersonaType personaType;

	void LoadAssets();

	void UpdateAnimationState();

	void LoadAndShoot();

	void UpdateSpeed(unsigned long dt);

	void MoveAndSlide(unsigned long dt);

	void Die();

	void CreateBullet(BulletData data);

	void CreateChargingAnimation(GameObject* playerGO);
};
