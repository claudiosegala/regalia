#include <pch.h>
#include <Bullet.h>
#include <Collider.h>
#include <Constants.h>
#include <Game.h>
#include <GameObject.h>
#include <InputManager.h>
#include <Number.h>
#include <Player.h>
#include <Sprite.h>
#include <Vec2.h>

int Player::counter = 0;

Player::Player(GameObject& go)
    : Component(go)
    , id(counter++) {

	state = Constants::Player::Idle;

	// TODO: discover why there is one tile of shift
	associated.box.SetCenter({ 27.0f, 26.0f });

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

void Player::Update(float dt) {
	UpdateSpeed(dt);
	MoveAndSlide(dt);
	Shoot();

	UpdateState();

	// change Player State
	// actions if necessary
}

void Player::Render() {
#ifdef DEBUG
	collisionBox.Render(0, 255, 0);
	associated.box.Render(255, 0, 0);
#endif // DEBUG
}

void Player::LoadAssets() {
	associated.AddComponent<Sprite>(&Constants::Player::MisterN);
	collisionBox = Rect(associated.box.vector + Vec2(13, 11), 22, 36);
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
	const auto pos = Vec2(10, 0).GetRotate(angle) + associated.box.Center();

	BulletData bulletData = {
		id,
		10,
		angle,
		100,
		500,
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

void Player::UpdateSpeed(float dt) {
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
	speed.y += Constants::Game::Gravity * dt;

	// TODO: WallJump should be treated differently
	if ((isOnFloor || isOnWall) && jump) {
		speed.y = Constants::Player::JumpSpeed;
	}

	speed.Limit(Constants::Game::MaxVelocity);
}

void Player::MoveAndSlide(float dt) {
	auto& box = collisionBox;
	const auto startingPosition = box.vector;

	// Find maximum diagonal movement
	auto delta = FindMaxDelta(box, speed, dt);
	box += speed * delta;

	dt -= delta;

	// Find maximum vertical movement
	delta = FindMaxDelta(box, { 0.f, speed.y }, dt);

	isOnFloor = !Number::Zero(delta - dt);
	box.vector.y += speed.y * delta;

	// Find maximum horizontal movement
	delta = FindMaxDelta(box, { speed.x, 0.f }, dt);

	isOnWall = !Number::Zero(delta - dt);
	box.vector.x += speed.x * delta;

	if (isOnFloor) {
		speed.y = 0.0f;
	}

	associated.box += box.vector - startingPosition;
}

std::vector<std::vector<int>> Player::GetCollisionSet() {
	// TODO: PlayState should let this available
	std::vector<std::vector<int>> collisionSet = {
		{ 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 01, 01, 01, 01, 01, 01, 01, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 01, 01, 01, 01, 01, 01, 01, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01, 00, 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 01, 01, 01, 01, 01, 01, 00, 00, 00, 01, 01, 01, 01, 01, 01, 00, 00, 00, 01, 01, 01, 01, 01, 01, 00, 00, 00, 00, 01, 01, 01, 01, 01, 01, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 00, 01 },
		{ 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01, 01 },
	};

	return collisionSet;
}

float Player::FindMaxDelta(const Rect& box, const Vec2& velocity, const float dt) {
	const auto iterations = 20;

	const auto collisionSet = GetCollisionSet();
	const auto rows = int(collisionSet.size());
	const auto columns = int(collisionSet[0].size());

	auto ans = 0.0f;
	auto previous = 0.0f;
	auto min_delta = 0.0f;
	auto max_delta = dt;

	bool collision = false;
	for (int i = 0; i < iterations; i++) {
		const auto delta = (max_delta + min_delta) / 2.f;
		const auto p = box + velocity * delta;
		const auto ul = p.GetUpperLeft();
		const auto dr = p.GetLowerRight();

		const auto x1 = int(ul.x / 24.0f);
		const auto y1 = int(ul.y / 24.0f);
		const auto x2 = int(dr.x / 24.0f);
		const auto y2 = int(dr.y / 24.0f);

		collision = false;

		if (x1 < 0 || x1 >= columns || y1 < 0 || y1 >= rows || x2 < 0 || x2 >= columns || y2 < 0 || y2 >= rows) {
			collision = true;
		} else {
			for (int j = y1; j <= y2; j++) {
				for (int k = x1; k <= x2; k++) {
					if (collisionSet[j][k]) {
						collision = true;
						// These assignments cause both loops to terminate
						j = y2;
						k = x2;
					}
				}
			}
		}

		if (!collision) {
			previous = ans;
			ans = min_delta = delta;
		} else {
			max_delta = delta;
		}
	}

	if (collision) {
		std::cout << Constants::StdColor::Red << "COLLIDING\n"
		          << Constants::StdColor::Reset;
	} else {
		std::cout << Constants::StdColor::Green << "NOT COLLIDING\n"
		          << Constants::StdColor::Reset;
	}

	const auto result = collision ? previous : ans;
	return (dt - result) < (dt / iterations) ? dt : result;
}

void Player::Die() {
	associated.RequestDelete();

	// TODO: add animation of death
}