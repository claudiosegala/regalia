#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Vec2.h>

class Bullet : public Component {
public:
	static int const defaultDamage;

	static float const defaultSpeed;

	static float const defaultMaxDistance;

	bool targetPlayer;

	Bullet(GameObject&, float, float, int, float, std::string, int frameCount = 1, float frameTime = 1.0f, bool targetPlayer = false);

	void Update(float);

	void Render();

	void NotifyCollision(GameObject&);

	bool Is(std::string);

	int GetDamage();

private:
	int damage;

	float distanceLeft;

	Vec2 speed;
};