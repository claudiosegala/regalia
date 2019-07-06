#include <pch.h>
#include <Bullet.h>
#include <Circle.h>
#include <CollisionMap.h>
#include <Constants.h>
#include <GameObject.h>
#include <Number.h>
#include <Player.h>
#include <Sprite.h>
#include "GameData.h"

Bullet::Bullet(GameObject& go, BulletData& data)
    : Component(go) {
	data.speed += data.level * Constants::Bullet::LevelSpeedIncrease;

	shooterId = data.shooterId;
	level = data.level;
	damage = data.damage;
	speed = Vec2(data.speed * cos(data.angle), data.speed * sin(data.angle));
	invencible = GameData::IsTimeUp();


	LoadAssets(data);
	associated.hitbox = new Rect(associated.box);
}

void Bullet::Update(unsigned dt) {
	if (level < 0) {
		associated.RequestDelete();
		return;
	}

	MoveAndBounce(dt);
}

void Bullet::Render() {}

void Bullet::NotifyCollision(GameObject& go) {
	auto player = go.GetComponent<Player>();

	if (player != nullptr && (player->id != shooterId || Constants::Game::FriendlyFire)) {
		associated.RequestDelete();
	}
}

int Bullet::GetDamage() {
	return damage;
}

void Bullet::LoadAssets(BulletData& data) {
	associated.AddComponent<Sprite>(data.spriteSheetData);
}

void Bullet::MoveAndBounce(unsigned dt) {
	auto& box = *associated.hitbox = associated.box;
	const auto startingPosition = box.vector;
	auto maxDelta = CollisionMap::FindMaxDelta(box, speed, dt);

	auto dist = speed * float(maxDelta) / 1000.0f;

	box += dist;

	if (maxDelta != dt) {
		auto remainingDelta = dt - maxDelta;

		auto maxDeltaX = CollisionMap::FindMaxDelta(box, { speed.x, 0.0f }, remainingDelta);
		auto maxDeltaY = CollisionMap::FindMaxDelta(box, { 0.0f, speed.y }, remainingDelta);

		if (maxDeltaX > maxDeltaY) {
			speed.y *= -1;
		} else {
			speed.x *= -1;
		}

		associated.angle = speed.GetAngle();

		maxDelta = CollisionMap::FindMaxDelta(box, speed, remainingDelta);

		dist = speed * float(maxDelta) / 1000.0f;

		box += dist;

		if (!invencible) {
			level--;
			speed -= Vec2(Constants::Bullet::LevelSpeedIncrease, Constants::Bullet::LevelSpeedIncrease);
		}
	}

	associated.box += box.vector - startingPosition;
}
