#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Interfaces.h>
#include <Vec2.h>

class Bullet : public Component {
public:
	int shooterId;

	Bullet(GameObject&, BulletData&, std::string, int frameCount = 1, float frameTime = 1.0f);

	void Update(float) override;

	void Render() override;

	void NotifyCollision(GameObject&) override;

	bool Is(std::string);

	int GetDamage();

private:
	int damage;

	float distanceLeft;

	Vec2 speed;

	void LoadAssets(std::string, int, float);
};