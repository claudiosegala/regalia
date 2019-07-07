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

Player::Player(GameObject& go, Constants::PersonaType persona)
    : Component(go)
    , id(counter++)
    , personaType(persona) {

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

	auto& in = InputManager::GetInstance();

	if (in.GamepadPress(SDL_CONTROLLER_BUTTON_LEFTSHOULDER, id)) {
		in.GamepadRumble(id, 0.5, 1000);
	}

	chargeTimer.Update(dt);
	shootingCoolDown.Update(dt);
	currentAnimationTimer.Update(dt);

	if (chargeTimer.Get() > Constants::Player::ChargeTimeMax) {
		chargeTimer.Reset();
		shootingCoolDown.Start(Constants::Player::ShootingCoolDown);
	}

	UpdateSpeed(dt);
	MoveAndSlide(dt);
	LoadAndShoot();
	UpdateAnimationState();
}

void Player::Render() {
#ifdef DEBUG
	associated.hitbox->Render(0, 255, 0);
	associated.box.Render(255, 0, 0);
#endif
}

void Player::LoadAssets() {
	switch (personaType) {
		case Constants::PersonaType::MISTER_N:
			associatedSprite = associated.AddComponent<Sprite>(&Constants::Player::MisterN);
			break;

		case Constants::PersonaType::GOTICA:
			associatedSprite = associated.AddComponent<Sprite>(&Constants::Player::Gotica);
			break;

		case Constants::PersonaType::MONGE:
			associatedSprite = associated.AddComponent<Sprite>(&Constants::Player::Monge);
			break;

		case Constants::PersonaType::ALQUIMISTA:
			associatedSprite = associated.AddComponent<Sprite>(&Constants::Player::Alquimista);
			break;

		default:
			throw std::runtime_error("Invalid persona type");
			break;
	}
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
			if (animationState != StartFallingAnimation && animationState != FallingAnimation) {
				nextAnimation = StartFallingAnimation;
				nextAnimationHoldTime = 100;
			} else {
				nextAnimation = FallingAnimation;
			}
		}

	} else {
		if (collisions & (Left | Right)) {
			if (speed.y > 0) {
				nextAnimation = SlidingAnimation;
			} else if (speed.y < 0) {
				nextAnimation = JumpingAnimation;
			} else {
				nextAnimation = RunningAnimation;
			}
		} else {
			nextAnimation = Number::Zero(speed.x) ? IdleAnimation : RunningAnimation;
		}
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
	auto& in = InputManager::GetInstance();

	playerState &= ~IsLoading & ~IsShooting;
	canShoot |= shootingCoolDown.IsTimeUp() && in.GamepadPress(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, id);

	if (!canShoot) {
		return;
	}

	if (in.IsGamepadDown(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, id)) {

		playerState |= IsLoading;
		chargeTimer.Continue();

	} else if (in.GamepadRelease(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, id)) {
		auto rightStick = in.GamepadRightStick(id);

		// Only shoot when aiming
		if (rightStick.GetLength() != 0) {
			playerState |= IsShooting;

			bulletAngle = rightStick.GetAngle();

			CreateBullet();

			canShoot = false;
			shootingCoolDown.Start(Constants::Player::ShootingCoolDown);
			chargeTimer.Reset();
		}
	}
}

int Player::GetBulletLevel() {
	using namespace Constants::Player;

	auto dt = chargeTimer.Get();

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

void Player::UpdateSpeed(unsigned long dt) {
	auto& in = InputManager::GetInstance();
	auto direction = in.GamepadLeftStick(id);

	const auto jump = in.GamepadPress(SDL_CONTROLLER_BUTTON_DPAD_UP, id)
	    || in.GamepadPress(SDL_CONTROLLER_BUTTON_A, id);

	const auto jumpHold = in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_UP, id)
	    || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_A, id);

	const auto keyLeft = in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT, id);

	const auto keyRight = in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, id);

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
	float gravity = Constants::Game::Gravity;
	// Sideways movement and gravity
	if (playerState & IsMidAir) {
		// When moving mid-air, the player behaves like he has some inertia.
		// Here, the gamepad input acts as a force applied to the player
		speed.x += direction.x * Constants::Player::LateralForce * float(dt) / 1000.0f;

		if (speed.y < 0 && jumpHold) { // Moving up and falling slowly
			gravity = Constants::Game::LongJumpGravity;
		}

	} else {
		// When on the ground, the player has direct control over movement speed,
		// being able to change the speed instantly (without inertia)
		speed.x = direction.x * Constants::Player::SpeedMultiplier;
	}

	// Vertical movement
	speed.y += gravity * float(dt) / 1000.0f;

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

	if (collisions & (Bottom | Left | Right)) {
		playerState &= ~IsMidAir;
	} else {
		playerState |= IsMidAir;
	}
}

void Player::Die() {
	playerState |= IsDying;
	associated.GetComponent<Sprite>()->RunAnimation(Constants::Player::DyingAnimation, [&]() { associated.RequestDelete(); });
}

void Player::CreateBullet() {
	const SpriteSheetData* spriteSheetData;

	switch (personaType) {
		case Constants::PersonaType::MISTER_N:
			spriteSheetData = &Constants::Bullet::Rabbit;
			break;

		default:
			spriteSheetData = &Constants::Bullet::DefaultSpriteSheet; // TODO
			break;
	}

	BulletData bulletData = {
		id,
		Constants::Bullet::DefaultDamage,
		bulletAngle,
		GetBulletLevel(),
		spriteSheetData
	};

	auto bulletGO = new GameObject();
	bulletGO->AddComponent<Bullet>(bulletData);

	bulletGO->box.SetCenter(associated.box.Center());
	bulletGO->angle = bulletAngle;

	void(Game::GetInstance()->GetCurrentState()->AddObject(bulletGO));
}
