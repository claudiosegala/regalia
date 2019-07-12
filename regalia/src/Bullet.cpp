#include <pch.h>
#include <Bullet.h>
#include <CollisionMap.h>
#include <Constants.h>
#include <GameObject.h>
#include <Player.h>
#include <Sprite.h>
#include "GameData.h"
#include "Sound.h"

Bullet::Bullet(GameObject& go, BulletData& data)
    : Component(go)
    , shooterId(data.shooterId)
    , damage(data.damage)
    , level(data.level) {

	if (level <= 0 || level > 3) {
		throw std::runtime_error("Invalid bullet level");
	}

	shooterId = data.shooterId;
	level = data.level;
	damage = data.damage;
	speed = Vec2(Constants::Bullet::LevelSpeed[level - 1] * cos(data.angle), Constants::Bullet::LevelSpeed[level - 1] * sin(data.angle));
	invincible = GameData::IsTimeUp();

	LoadAssets(data);
	associated.hitbox = new Rect(associated.box.vector, Constants::Bullet::Size, Constants::Bullet::Size);

	auto sound = associated.AddComponent<Sound>(Constants::SharedAssets::Sounds::Shot);
	sound->Play();
}

void Bullet::Update(unsigned dt) {
	if (level <= 0) {
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
	associated.hitbox->SetCenter(associated.box.Center());

	auto& box = *associated.hitbox;
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

		if (!invincible) {
			level--;

			if (level > 0) {
				speed = speed.GetUnit() * Constants::Bullet::LevelSpeed[level - 1];
			}
		}
	}

	associated.box.SetCenter(box.Center());
}
