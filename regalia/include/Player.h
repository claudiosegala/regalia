#pragma once

#include <Component.h>
#include <Rect.h>
#include <Vec2.h>

class Player : public Component {
public:
	static int counter;

	int id;

	Player(GameObject&);

	~Player();

	void NotifyCollision(GameObject& go) override;

	void Update(float) override;

	void Render() override;

private:

	Constants::Player::State state;

	int hp;

	Vec2 speed;

	Rect collisionBox;

	void LoadAssets();

	void UpdateState();

	void SetState(Constants::Player::State nextState, bool flipAnimation = false);
	
	void Move(float dt);

	void CheckBestDelta(Vec2, float);

	void Die();
};