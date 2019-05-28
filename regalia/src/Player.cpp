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

Player::Player(GameObject& go, int playerId)
    : Component(go)
    , playerId(playerId)
    , hp(50)
    , speed({ 0, 0 })
    , collisionBox()
    , isOnFloor(false)
    , isOnWall(false) {
	this->id = ++Player::counter;
	this->state = Constants::Player::Idle;

	// TODO: discover why there is one tile of shift
	this->associated.box.SetCenter({ 20.0f, 26.0f });

	LoadAssets();
}

Player::~Player() {
	Player::counter--;
}

void Player::NotifyCollision(GameObject& go) {
	auto bullet = go.GetComponent<Bullet>();

	if (bullet == nullptr) {
		return;
	}

	if (bullet->shooterId != this->id) {
		return; //> you cannot fire yourself
	}

	this->hp -= bullet->GetDamage();

	if (this->hp > 0) {
		return;
	}

	Die();
}

void Player::Update(float dt) {
	//Gravity(dt);
	Move(dt);
	Shoot();

	UpdateState();

	// change Player State
	// actions if necessary
}

void Player::Render() {
}

int Player::GetPlayerId() const {
	return playerId;
}

void Player::LoadAssets() {
	associated.AddComponent<Sprite>(&Constants::Player::MisterN);
	associated.AddComponent<Collider>(&collisionBox, Vec2(0.5f, 0.8f), Vec2(0.0f, 4.0f));
}

void Player::UpdateState() {
	if (isOnFloor) {
		if (Number::Zero(speed.x)) {
			SetState(Constants::Player::Idle);
		} else {
			SetState(Constants::Player::Running, speed.x < 0);
		}
	} else {
		if (speed.y < 0) {
			SetState(Constants::Player::JumpingUp, speed.x < 0);
		} else {
			SetState(Constants::Player::JumpingDown, speed.x < 0);
		}
	}
}

void Player::SetState(Constants::Player::State nextState, bool flipAnimation) {
	state = nextState;

	auto sprite = associated.GetComponent<Sprite>();
	sprite->SetNextAnimation(nextState, flipAnimation);
}

void Player::Shoot() {
	auto& inputManager = InputManager::GetInstance();

	if (inputManager.GamepadPress(SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
		auto angle = inputManager.GamepadRightStick(playerId).GetAngle();
		auto pos = Vec2(25, 0).GetRotate(angle) + associated.box.Center();

		BulletData bulletData = {
			playerId,
			10,
			angle,
			20,
			500,
			&Constants::Bullet::DefaultSpriteSheet
		};

		auto bulletGO = new GameObject();
		bulletGO->AddComponent<Bullet>(bulletData);
		bulletGO->box.SetCenter(pos);
		bulletGO->angle = angle;

		auto state = Game::GetInstance()->GetCurrentState();
		(void)state->AddObject(bulletGO);
	}
}

void Player::Move(float dt) {
	auto& in = InputManager::GetInstance();
	auto direction = in.GamepadLeftStick(playerId);
	auto isJumping = false;

	if (direction.IsOrigin()) { // No input from gamepad stick, look for other inputs
		const auto keyUp = in.IsKeyDown(Constants::Key::W) || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_UP, playerId);
		const auto keyDown = in.IsKeyDown(Constants::Key::S) || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_DOWN, playerId);
		const auto keyLeft = in.IsKeyDown(Constants::Key::A) || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_LEFT, playerId);
		const auto keyRight = in.IsKeyDown(Constants::Key::D) || in.IsGamepadDown(SDL_CONTROLLER_BUTTON_DPAD_RIGHT, playerId);

		if (keyUp) {
			isJumping = true;
		}

		if (keyDown) {
			// nothing
		}

		if (keyLeft) {
			direction.x -= 1;
		}

		if (keyRight) {
			direction.x += 1;
		}
	}

	this->speed.x = direction.x * Constants::Player::SpeedMultiplier;

	if ((this->isOnFloor || this->isOnWall) && isJumping) {
		this->speed.y = Constants::Player::JumpForce;
	}

	W(this->isOnFloor);
	W(this->isOnWall);

	MoveAndSlide(this->speed, dt);
}

void Player::MoveAndSlide(Vec2 velocity, float dt) {
	auto box = this->collisionBox;
	auto& pos = this->associated.box;

	/* try to move diagonaly */
	auto delta = FindMaxDelta(box, velocity, Constants::Game::Gravity, dt);

	pos = CalculatePosition(pos, velocity, Constants::Game::Gravity, delta);
	box = CalculatePosition(box, velocity, Constants::Game::Gravity, delta);
		
	auto accumulatedGravity = Constants::Game::Gravity.y * delta * delta;
	this->speed.y += accumulatedGravity;
	velocity.y += accumulatedGravity;

	if (Number::Equal(dt, delta)) {
		this->isOnWall = false;
		this->isOnFloor = false;
		return;
	}

	/* try slide horizontaly */

	if (!Number::Zero(velocity.x)) {
		auto horizontal = Vec2 { velocity.x, 0.0f };
		auto delta_slide = FindMaxDelta(box, horizontal, Vec2(), dt - delta);

		pos = CalculatePosition(pos, horizontal, Vec2(), delta_slide);
		box = CalculatePosition(box, horizontal, Vec2(), delta_slide);

		this->isOnWall = !Number::Equal(dt - delta, delta_slide); // is on wall if could not finish the movement

		if (this->isOnWall) {
			this->speed.x = 0.0f;
		}
	}

	/* try slide verticaly */
	auto vertical = Vec2 { 0.0f, velocity.y };
	auto delta_slide = FindMaxDelta(box, vertical, Constants::Game::Gravity, dt - delta);

	pos = CalculatePosition(pos, vertical, Constants::Game::Gravity, delta_slide);
	box = CalculatePosition(box, vertical, Constants::Game::Gravity, delta_slide);
	
	this->isOnFloor = !Number::Equal(dt - delta, delta_slide); // is on floor if could not finish the movement

	if (this->isOnFloor) {
		this->speed.y = 0.0f;
	} else {
		this->speed.y += Constants::Game::Gravity.y * delta_slide * delta_slide; // accumulate gravity
	}
}

std::vector<std::vector<int>> Player::GetCollisionSet() {
	// TODO: PlayState should let this available
	std::vector<std::vector<int>> collisionSet = {
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
		{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};

	return collisionSet;
}

// TODO: change to calculate velocity and return a vec2, let the box + v to be in another place
Rect Player::CalculatePosition(const Rect box, const Vec2 velocity, const Vec2 acceleration, const float dt) {
	auto v = (velocity + acceleration * dt) * dt;

	v.Limit(Constants::Game::MaxVelocity);

	return box + v;
}

float Player::FindMaxDelta(const Rect box, const Vec2 velocity, const Vec2 acceleration, const float dt) {
	const auto collisionSet = GetCollisionSet();
	const auto rows = int(collisionSet.size());
	const auto columns = int(collisionSet[0].size());

	auto ans = 0.0f;
	auto min_delta = 0.0f;
	auto max_delta = dt;

	for (int i = 0; i < 20; i++) {
		const auto delta = (max_delta + min_delta) / 2.f;
		const auto p = CalculatePosition(box, velocity, acceleration, delta);
		const auto ul = p.GetUpperLeft();
		const auto dr = p.GetDownRight();
		const auto x1 = int(ul.x) / 24;
		const auto y1 = int(ul.y) / 24;
		const auto x2 = int(dr.x) / 24;
		const auto y2 = int(dr.y) / 24;

		auto conflict = false;

		if (x1 < 0 || x1 >= columns || y1 < 0 || y1 >= rows || x2 < 0 || x2 >= columns || y2 < 0 || y2 >= rows) {
			conflict = true;
			std::cout << "Out of bounds" << std::endl;
		} else {
			for (int j = y1; j <= y2; j++) {
				for (int i = x1; i <= x2; i++) {
					if (collisionSet[j][i]) {
						conflict = true;
						//break;
					}
				}
			}

			#ifdef DEBUG
			/*for (int j = y1; j <= y2; j++) {
				for (int i = x1; i <= x2; i++) {
					std::cout << collisionSet[j][i];
				}
				std::cout << '\n';
			}
			std::cout << '\n';*/
			#endif
		}

		if (!conflict) {
			ans = fmax(ans, delta);
			min_delta = delta;
		} else {
			max_delta = delta;
		}
	}

	return ans;
}

void Player::Die() {
	this->associated.RequestDelete();

	// TODO: add animation of death
}