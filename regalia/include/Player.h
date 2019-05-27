#pragma once

#include <Component.h>
#include <Rect.h>
#include <Vec2.h>

class Player : public Component {
public:
	static int counter;

	int id;

	Player(GameObject& go, int playerId);

	~Player();

	void NotifyCollision(GameObject& go) override;

	void Update(float) override;

	void Render() override;

	int GetPlayerId() const;

private:

	Constants::Player::State state;

	int hp;

	int playerId;

	bool isOnFloor;

	bool isOnWall;

	Vec2 speed;

	Rect collisionBox;

	void LoadAssets();

	void UpdateState();

	void SetState(Constants::Player::State nextState, bool flipAnimation = false);
	
	void Shoot();

	void Move(float dt);

	void MoveAndSlide(Vec2 velocity, float dt);

	std::vector<std::vector<int>> GetCollisionSet();

	Rect CalculatePosition(const Rect pos, const Vec2 velocity, const Vec2 acceleration, const float dt);

	float FindMaxDelta(const Rect pos, const Vec2 velocity, const Vec2 acceleration, const float dt);

	void CheckBestDelta(Vec2 velocity, float delta);

	void Die();
};
