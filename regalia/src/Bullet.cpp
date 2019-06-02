#include <pch.h>
#include <Bullet.h>
#include <Circle.h>
#include <Collider.h>
#include <GameObject.h>
#include <Player.h>
#include <Sprite.h>
#include <Vec2.h>

Bullet::Bullet(GameObject& go, BulletData& data)
    : Component(go) {
	shooterId = data.shooterId;
	distanceLeft = data.maxDistance;
	damage = data.damage;
	speed = Vec2(data.speed * cos(data.angle), data.speed * sin(data.angle));

	LoadAssets(data);
}

void Bullet::Update(unsigned dt) {
	// Reduce the distance left
	auto dist = speed * float(dt);

	distanceLeft -= dist.GetLength();

	// Destroy if hit the maximum distance
	if (distanceLeft <= 0) {
		associated.RequestDelete();
		return;
	}

	// Change position
	associated.box.vector += dist;
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
