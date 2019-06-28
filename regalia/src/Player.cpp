#include <pch.h>
#include <Bullet.h>
#include <Constants.h>
#include <Game.h>
#include <GameObject.h>
#include <InputManager.h>
#include <CollisionMap.h>
#include <Number.h>
#include <Player.h>
#include <Sprite.h>
#include <Vec2.h>

int Player::counter = 0;

Player::Player(GameObject& go)
    : Component(go)
    , id(counter++) {

	associated.box.SetCenter({ 27.0f, 26.0f });
	associated.hitbox = new Rect(associated.box.vector + Vec2(13, 11), 22, 36);

	LoadAssets();
}

Player::~Player() {
	counter--;
}

void Player::NotifyCollision(GameObject& go) {
	auto bullet = go.GetComponent<Bullet>();

	if (bullet == nullptr || (bullet->shooterId == id && !Constants::Game::FriendlyFire)) {
		return; // you cannot shoot yourself
	}

	hp -= bullet->GetDamage();

	if (hp <= 0) {
		Die();
	}
}

void Player::Update(unsigned dt) {
	if (playerState & IsDying) {
		return;
	}

	currentAnimationTimer.Update(dt);

	UpdateSpeed(dt);
	MoveAndSlide(dt);
	LoadAndShoot();
	UpdateAnimationState();
}

void Player::Render() {
#ifdef DEBUG
	associated.hitbox->Render(0, 255, 0);
	associated.box.Render(255, 0, 0);
#endif // DEBUG
}

void Player::LoadAssets() {
	associatedSprite = associated.AddComponent<Sprite>(&Constants::Player::MisterN);
	//associated.AddComponent<Collider>(&collisionBox, Vec2(0.48f, 0.8f), Vec2(0.0f, 4.0f));
}

void Player::UpdateAnimationState() {
	using namespace Constants::Player;

	Sprite::Direction nextDirX;
	AnimationState nextAnimation;
	unsigned nextAnimationHoldTime = 0;

	if (speed.x > 0) {
		nextDirX = Sprite::Direction::Original;
	} else if (speed.x < 0) {
		nextDirX = Sprite::Direction::Flip;
	} else {
		nextDirX = Sprite::Direction::Keep;
	}

	if (playerState & IsShooting) {

		const float bulletAngleAbs = abs(bulletAngle);
		const float pi_8 = Number::Pi / 8;
		nextAnimationHoldTime = 300;

		if (bulletAngleAbs < pi_8) {
			nextAnimation = ShootingHorizontalAnimation;
			nextDirX = Sprite::Direction::Original;
		} else if (bulletAngleAbs < 3 * pi_8) {
			nextAnimation = bulletAngle < 0 ? ShootingDiagUpAnimation : ShootingDiagDownAnimation;
			nextDirX = Sprite::Direction::Original;
		} else if (bulletAngleAbs < 5 * pi_8) {
			nextAnimation = bulletAngle < 0 ? ShootingUpAnimation : ShootingDownAnimation;
		} else if (bulletAngleAbs < 7 * pi_8) {
			nextAnimation = bulletAngle < 0 ? ShootingDiagUpAnimation : ShootingDiagDownAnimation;
			nextDirX = Sprite::Direction::Flip;
		} else {
			nextAnimation = ShootingHorizontalAnimation;
			nextDirX = Sprite::Direction::Flip;
		}

	} else if (playerState & IsMidAir) {

		if (speed.y <= 0) {
			nextAnimation = JumpingAnimation;
		} else {
			if (collisions & (Left | Right)) {
				nextAnimation = SlidingAnimation;
			} else {
				if (animationState != StartFallingAnimation && animationState != FallingAnimation) {
					nextAnimation = StartFallingAnimation;
					nextAnimationHoldTime = 100;
				} else {
					nextAnimation = FallingAnimation;
				}
			}
		}

	} else {
		nextAnimation = Number::Zero(speed.x) ? IdleAnimation : RunningAnimation;
	}

	if (currentAnimationTimer.Get() > currentAnimationHoldTime) {
		if (nextAnimation != animationState) {
			animationState = nextAnimation;
			currentAnimationHoldTime = nextAnimationHoldTime;
			currentAnimationTimer.Restart();
			associatedSprite->SetAnimation(animationState);
		}

		associatedSprite->SetAnimationDirX(nextDirX);
	}
}

void Player::LoadAndShoot() {
	auto& inputManager = InputManager::GetInstance();

	playerState &= ~IsLoading & ~IsShooting;

	if (inputManager.IsGamepadDown(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, id)) {

		playerState |= IsLoading;

	} else if (inputManager.GamepadRelease(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, id)) {

		playerState |= IsShooting;

		bulletAngle = inputManager.GamepadRightStick(id).GetAngle();
		const auto pos = associated.box.Center();

		BulletData bulletData = {
			id,
			Constants::Bullet::DefaultDamage,
			bulletAngle,
			Constants::Bullet::DefaultSpeed,
			3,
			&Constants::Bullet::DefaultSpriteSheet
		};

		auto bulletGO = new GameObject();
		bulletGO->AddComponent<Bullet>(bulletData);

		// TODO: change when we have a bullet
		bulletGO->box.width = 10;
		bulletGO->box.height = 10;

		bulletGO->box.SetCenter(pos);
		bulletGO->angle = bulletAngle;

		void(Game::GetInstance()->GetCurrentState()->AddObject(bulletGO));
	}
}

void Player::UpdateSpeed(unsigned long dt) {
	auto& in = InputManager::GetInstance();
	auto direction = in.GamepadLeftStick(id);

	const auto jump = in.KeyPress(Constants::Key::W)
	    || in.GamepadPress(SDL_CONTROLLER_BUTTON_DPAD_UP, id)
	    || in.GamepadPress(SDL_CONTROLLER_BUTTON_A, id);

	const auto keyLeft = in.IsKeyDown(Constants::Key::A)
	    || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT, id);

	const auto keyRight = in.IsKeyDown(Constants::Key::D)
	    || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, id);

#ifdef DEBUG
	// We only want to allow this while debugging. Otherwise it could be used
	// as an exploit to increase the player's movement speed

	if (keyLeft) {
		direction.x -= 1;
	}

	if (keyRight) {
		direction.x += 1;
	}
#endif // DEBUG

	// Sideways movement
	if (playerState & IsMidAir) {
		// When moving mid-air, the player behaves like he has some inertia.
		// Here, the gamepad input acts as a force applied to the player
		speed.x += direction.x * Constants::Player::LateralForce * float(dt) / 1000.0f;
	} else {
		// When on the ground, the player has direct control over movement speed,
		// being able to change the speed instantly (without inertia)
		speed.x = direction.x * Constants::Player::SpeedMultiplier;
	}

	// Gravity
	speed.y += Constants::Game::Gravity * float(dt) / 1000.0f;

	// Wall slide
	if ((collisions & (Left | Right)) && speed.y > 0) {
		speed.y /= 1.5;
	}

	// Jumping
	if (jump) {
		// Ground jump
		if (collisions & Bottom) {
			speed.y = Constants::Player::JumpSpeed;
		}

		// Wall jump
		else if (collisions & (Left | Right)) {
			const auto angle = speed.x < 0 ? 45.0f : -45.0f;
			speed = { 0.0f, Constants::Player::WallJumpSpeed };
			speed.Rotate(angle);
		}
	}

	speed.Limit(Constants::Game::MaxVelocity);
}

void Player::MoveAndSlide(unsigned long dt) {
	auto& box = *associated.hitbox;
	const auto startingPosition = box.vector;
	collisions = None;

	// Find maximum diagonal movement
	auto delta = CollisionMap::FindMaxDelta(box, speed, dt);
	box += speed * float(delta) / 1000.0f;

	dt -= delta;

	// Find maximum vertical movement
	delta = CollisionMap::FindMaxDelta(box, { 0.f, speed.y }, dt);
	box.vector.y += speed.y * float(delta) / 1000.0f;

	if (delta != dt) {
		collisions |= speed.y > 0 ? Bottom : Top;
		speed.y = 0.0f;
	}

	// Find maximum horizontal movement
	if (!Number::Zero(speed.x)) {
		delta = CollisionMap::FindMaxDelta(box, { speed.x, 0.f }, dt);
		if (delta != dt) {
			collisions |= speed.x > 0 ? Right : Left;
		}
		box.vector.x += speed.x * float(delta) / 1000.0f;
	}

	associated.box += box.vector - startingPosition;

	if (collisions & Bottom) {
		playerState &= ~IsMidAir;
	} else {
		playerState |= IsMidAir;
	}
}

void Player::Die() {
	playerState |= IsDying;
	associated.GetComponent<Sprite>()->RunAnimation(Constants::Player::DyingAnimation, [&]() { associated.RequestDelete(); });
}
