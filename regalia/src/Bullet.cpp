#include <pch.h>
#include <Bullet.h>
#include <Circle.h>
#include <Collider.h>
#include <CollisionMap.h>
#include <Constants.h>
#include <GameObject.h>
#include <Number.h>
#include <Player.h>
#include <Sprite.h>

Bullet::Bullet(GameObject& go, BulletData& data)
    : Component(go) {
	shooterId = data.shooterId;
	distanceLeft = data.maxDistance;
	damage = data.damage;
	speed = Vec2(data.speed * cos(data.angle), data.speed * sin(data.angle));

	LoadAssets(data);
}

void Bullet::Update(unsigned dt) {
	// Destroy if hit the maximum distance
	if (distanceLeft <= 0) {
		associated.RequestDelete();
		return;
	}

	MoveAndBounce(dt);
}

void Bullet::Render() {}

void Bullet::NotifyCollision(GameObject& go) {
	auto player = go.GetComponent<Player>();

	if (player == nullptr) {
		return;
	}

	if (player->id != shooterId || Constants::Game::FriendlyFire) {
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

void Bullet::MoveAndBounce(unsigned dt) {
	auto maxDelta = CollisionMap::FindMaxDelta(associated.box, speed, dt);

	auto dist = speed * float(maxDelta) / 1000.0f;

	associated.box += dist;
	distanceLeft -= dist.GetLength();

	if (maxDelta != dt) {
		auto remainingDelta = dt - maxDelta;

		auto maxDeltaX = CollisionMap::FindMaxDelta(associated.box, { speed.x, 0.0f }, remainingDelta);
		auto maxDeltaY = CollisionMap::FindMaxDelta(associated.box, { 0.0f, speed.y }, remainingDelta);

		if (maxDeltaX > maxDeltaY) {
			speed.y *= -1;
		} else  {
			speed.x *= -1;
		}

		associated.angle = speed.GetAngle();

		maxDelta = CollisionMap::FindMaxDelta(associated.box, speed, remainingDelta);

		dist = speed * float(maxDelta) / 1000.0f;

		associated.box += dist;
		distanceLeft -= dist.GetLength();
	}
}
