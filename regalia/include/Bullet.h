#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Interfaces.h>
#include <Vec2.h>
#include <Rect.h>

class Bullet : public Component {
public:
	int shooterId;

	Bullet(GameObject& go, BulletData& data);

	void Update(unsigned dt) override;

	void Render() override;

	void NotifyCollision(GameObject& go) override;

	int GetDamage();

private:

	int damage;

	float distanceLeft;

	Rect collisionBox;

	Vec2 speed;

	void LoadAssets(BulletData& data);
	
	void MoveAndBounce(unsigned long dt);
};