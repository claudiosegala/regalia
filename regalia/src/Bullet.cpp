#include <pch.h>
#include <Bullet.h>
#include <Circle.h>
#include <Number.h>
#include <Collider.h>
#include <CollisionMap.h>
#include <GameObject.h>
#include <Player.h>
#include <Sprite.h>

Bullet::Bullet(GameObject& go, BulletData& data)
    : Component(go) {
	shooterId = data.shooterId;
	distanceLeft = data.maxDistance;
	damage = data.damage;
	speed = Vec2(-data.speed * cos(data.angle), -data.speed * sin(data.angle));
	collisionBox = associated.box;

	LoadAssets(data);
}

void Bullet::Update(unsigned dt) {
	MoveAndBounce(dt);

	// Destroy if hit the maximum distance
	if (distanceLeft <= 0) {
		associated.RequestDelete();
		return;
	}
}

void Bullet::Render() {}

void Bullet::NotifyCollision(GameObject& go) {
	auto player = go.GetComponent<Player>();

	if (player == nullptr) {
		return;
	}

	if (player->id != shooterId) {
		associated.RequestDelete();
		return;
	}
}

int Bullet::GetDamage() {
	return damage;
}

void Bullet::LoadAssets(BulletData& data) {
	associated.AddComponent<Sprite>(data.spriteSheetData);
	auto circle = new Circle();
	associated.AddComponent<Collider>(circle);
}

void Bullet::MoveAndBounce(unsigned long dt) {
	// TODO: get a collision box
	while (dt && !Number::Zero(distanceLeft)) {
		auto delta = CollisionMap::FindMaxDelta(associated.box, speed, dt);
		auto dist = speed * float(delta) / 1000.0f;

		associated.box += dist;
		distanceLeft -= dist.GetLength();
		dt -= delta;

		if (dt) {
			if (Number::Zero(speed.x)) {
				speed.y *= -1;
			} else {
				speed.x *= -1;
			}
		}
	}
}
