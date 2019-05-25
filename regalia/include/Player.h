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

	void NotifyCollision(GameObject& go);

	void Update(float);

	void Render();

	bool Is(std::string);

private:
	enum class PlayerState {
		IDLE,
		RUNNING,
		JUMPING,
		FALLING,
		ATTACKING,
		HANGING // wall slide
	};

	PlayerState stateAnimation;

	int hp;

	Vec2 speed;

	Rect collisionBox;

	void LoadAssets();
	
	void Move(float dt);
	
	void Die();
};