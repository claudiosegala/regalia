#include <pch.h>
#include <Bullet.h>
#include <Collider.h>
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
	collisionBox = Rect(associated.box.vector + Vec2(13, 11), 22, 36);

	LoadAssets();
}

Player::~Player() {
	counter--;
}

void Player::NotifyCollision(GameObject& go) {
	auto bullet = go.GetComponent<Bullet>();

	if (bullet == nullptr) {
		return;
	}

	if (bullet->shooterId != id) {
		return; // you cannot shoot yourself
	}

	hp -= bullet->GetDamage();

	if (hp <= 0) {
		Die();
	}
}

void Player::Update(unsigned dt) {
	UpdateSpeed(dt);
	MoveAndSlide(dt);
	Shoot();

	UpdateState();
}

void Player::Render() {
#ifdef DEBUG
	collisionBox.Render(0, 255, 0);
	associated.box.Render(255, 0, 0);
#endif // DEBUG
}

void Player::LoadAssets() {
	associated.AddComponent<Sprite>(&Constants::Player::MisterN);
	//associated.AddComponent<Collider>(&collisionBox, Vec2(0.48f, 0.8f), Vec2(0.0f, 4.0f));
}

void Player::UpdateState() {
	Sprite::Direction dirX;

	if (speed.x > 0) {
		dirX = Sprite::Direction::Original;
	} else if (speed.x < 0) {
		dirX = Sprite::Direction::Flip;
	} else {
		dirX = Sprite::Direction::Keep;
	}

	if (isOnFloor) {
		if (Number::Zero(speed.x)) {
			SetState(Constants::Player::Idle, dirX);
		} else {
			SetState(Constants::Player::Running, dirX);
		}
	} else {
		if (speed.y < 0) {
			SetState(Constants::Player::Jumping, dirX);
		} else {
			SetState(Constants::Player::Falling, dirX);
		}
	}
}

void Player::SetState(Constants::Player::State nextState, Sprite::Direction dirX) {
	state = nextState;

	auto sprite = associated.GetComponent<Sprite>();
	sprite->SetNextAnimation(nextState, dirX);
}

void Player::Shoot() {
	auto& inputManager = InputManager::GetInstance();

	if (!inputManager.GamepadPress(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER, id)
	    || inputManager.GamepadRightStick(id).GetLength() == 0) {
		return;
	}

	const auto angle = inputManager.GamepadRightStick(id).GetAngle();
	const auto pos = associated.box.Center();

	BulletData bulletData = {
		id,
		10,
		angle,
		100,
		3,
		&Constants::Bullet::DefaultSpriteSheet
	};

	auto bulletGO = new GameObject();
	bulletGO->AddComponent<Bullet>(bulletData);

	// TODO: change when we have a bullet
	bulletGO->box.width = 10;
	bulletGO->box.height = 10;

	bulletGO->box.SetCenter(pos);
	bulletGO->angle = angle;

	void(Game::GetInstance()->GetCurrentState()->AddObject(bulletGO));
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

	if (keyLeft) {
		direction.x -= 1;
	}

	if (keyRight) {
		direction.x += 1;
	}

	speed.x = direction.x * Constants::Player::SpeedMultiplier;
	speed.y += Constants::Game::Gravity * float(dt) / 1000.0f;

	// TODO: WallJump should be treated differently
	if ((isOnFloor || isOnWall) && jump) {
		speed.y = Constants::Player::JumpSpeed;
	}

	speed.Limit(Constants::Game::MaxVelocity);
}

void Player::MoveAndSlide(unsigned long dt) {
	auto& box = collisionBox;
	const auto startingPosition = box.vector;

	// Find maximum diagonal movement
	auto delta = CollisionMap::FindMaxDelta(box, speed, dt);
	box += speed * float(delta) / 1000.0f;

	dt -= delta;

	// Find maximum vertical movement
	delta = CollisionMap::FindMaxDelta(box, { 0.f, speed.y }, dt);

	isOnFloor = (delta != dt);
	box.vector.y += speed.y * float(delta) / 1000.0f;

	if (isOnFloor) {
		speed.y = 0.0f;
	}

	// Find maximum horizontal movement
	if (!Number::Zero(speed.x)) {
		delta = CollisionMap::FindMaxDelta(box, { speed.x, 0.f }, dt);

		isOnWall = (delta != dt);
		box.vector.x += speed.x * float(delta) / 1000.0f;
	}

	associated.box += box.vector - startingPosition;
}

void Player::Die() {
	associated.RequestDelete();
	// TODO: add animation of death
}