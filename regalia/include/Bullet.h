#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Interfaces.h>
#include <Vec2.h>

class Bullet : public Component {
public:
	int shooterId;

	Bullet(GameObject& associated, BulletData& data, const std::string& file, int frameCount = 1, float frameTime = 1.0f);

	void Update(float dt) override;

	void Render() override;

	void NotifyCollision(GameObject& go) override;

	int GetDamage();

private:
	int damage;

	float distanceLeft;

	Vec2 speed;

	void LoadAssets(const std::string& file, int frameCount, float frameTime);
};