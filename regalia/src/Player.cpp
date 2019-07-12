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
#include <Charge.h>
#include <PlayState.h>

Player::Player(GameObject& go, int id, Constants::PersonaType persona, Vec2 initialPosition, PlayState* play_state)
    : Component(go)
    , id(id)
    , play_state(play_state)
    , personaType(persona) {

	associated.box.SetCenter(initialPosition);
	associated.hitbox = new Rect(associated.box.vector + Vec2(15, 11), 18, 34);

	LoadAssets();

	// Make all players start the game facing the center of the map
	if (initialPosition.x > Constants::Window::Center.x) {
		sprite->SetAnimationDirX(Sprite::Direction::Flip);
	}
}

Player::~Player() {
	if (play_state != nullptr) {
		play_state->player_count--;
	}
}

void Player::Start() {
	CreateChargingAnimation(&associated);
}

void Player::NotifyCollision(GameObject& go) {
	if (playerState & IsDying) {
		return;
	}

	if (play_state != nullptr && play_state->alive_player_count == 1) {
		return; // Don't die when you're the only one left alive
	}

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

	shootingCoolDown.Update(dt);
	currentAnimationTimer.Update(dt);

	if (charge->Overload()) {
		charge->Unload();
		shootingCoolDown.Start(Constants::Player::ShootingCoolDown);
		canShoot = false;
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
		case Constants::PersonaType::MISTER_N_RED:
			sprite = associated.AddComponent<Sprite>(&Constants::Player::MisterNRed, Constants::Player::StartFallingAnimation);
			break;

		case Constants::PersonaType::MISTER_N_BLUE:
			sprite = associated.AddComponent<Sprite>(&Constants::Player::MisterNBlue, Constants::Player::StartFallingAnimation);
			break;

		case Constants::PersonaType::GOTICA_GREEN:
			sprite = associated.AddComponent<Sprite>(&Constants::Player::GoticaGreen, Constants::Player::StartFallingAnimation);
			break;

		case Constants::PersonaType::GOTICA_PURPLE:
			sprite = associated.AddComponent<Sprite>(&Constants::Player::GoticaPurple, Constants::Player::StartFallingAnimation);
			break;

		default:
			throw std::runtime_error("Invalid persona type");
	}
}

void Player::UpdateAnimationState() {
	using namespace Constants::Player;

	if (InputManager::GetInstance().GamepadPress(SDL_CONTROLLER_BUTTON_BACK)) {
		associated.GetComponent<Sprite>()->RunAnimation(Constants::Player::AnimationState::DyingAnimation, []() { W("Morreu"); }, 5);
	}

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
			sprite->SetAnimation(animationState);
		}

		sprite->SetAnimationDirX(nextDirX);
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
		charge->Load();

	} else if (in.GamepadRelease(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, id)) {
		auto rightStick = in.GamepadRightStick(id);
		auto bulletLevel = charge->GetLevel();

		charge->Unload();

		if (rightStick.GetLength() == 0) { // Only shoot when aiming
			return;
		}

		canShoot = false;
		playerState |= IsShooting;
		bulletAngle = rightStick.GetAngle();
		shootingCoolDown.Start(Constants::Player::ShootingCoolDown);

		const SpriteSheetData* spriteSheetData;

		switch (personaType) {
			case Constants::PersonaType::MISTER_N_RED:
			case Constants::PersonaType::MISTER_N_BLUE:
				spriteSheetData = &Constants::Bullet::MisterN;
				break;

			case Constants::PersonaType::GOTICA_GREEN:
				spriteSheetData = &Constants::Bullet::GoticaGreen;
				break;

			case Constants::PersonaType::GOTICA_PURPLE:
				spriteSheetData = &Constants::Bullet::GoticaPurple;
				break;

			default:
				throw std::runtime_error("Invalid persona type");
		}

		BulletData bulletData = {
			id,
			Constants::Bullet::DefaultDamage,
			bulletAngle,
			bulletLevel,
			spriteSheetData
		};

		CreateBullet(bulletData);
	}
}

void Player::UpdateSpeed(unsigned long dt) {
	auto& in = InputManager::GetInstance();
	auto direction = in.GamepadLeftStick(id);

	const auto jump = in.GamepadPress(SDL_CONTROLLER_BUTTON_DPAD_UP, id)
	    || in.GamepadPress(SDL_CONTROLLER_BUTTON_A, id)
	    || in.GamepadPress(SDL_CONTROLLER_BUTTON_LEFTSHOULDER, id);

	const auto jumpHold = in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_UP, id)
	    || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_A, id)
	    || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_LEFTSHOULDER, id);

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

	speed.Limit(Constants::Player::MaxVelocity);
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

	if (play_state != nullptr) {
		play_state->alive_player_count--;
	}

	associated.GetComponent<Sprite>()->RunAnimation(Constants::Player::DyingAnimation, [&]() { associated.RequestDelete(); });
}

void Player::CreateBullet(BulletData data) {
	auto go = new GameObject();

	(void)go->AddComponent<Bullet>(data, play_state);

	go->box.SetCenter(associated.box.Center());
	go->angle = bulletAngle;

	auto game = Game::GetInstance();
	auto state = game->GetCurrentState();

	(void)state->AddObject(go);
}

void Player::CreateChargingAnimation(GameObject* playerGO) {
	auto go = new GameObject();

	charge = go->AddComponent<Charge>(playerGO);

	auto game = Game::GetInstance();
	auto state = game->GetCurrentState();

	(void)state->AddObject(go);
}