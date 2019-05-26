#include <pch.h>
#include <Bullet.h>
#include <Circle.h>
#include <Collider.h>
#include <GameObject.h>
#include <Player.h>
#include <Sprite.h>
#include <Vec2.h>

Bullet::Bullet(GameObject& associated, BulletData& data, const std::string& file, int frameCount, float frameTime)
    : Component(associated) {
	this->shooterId = data.shooterId;
	this->distanceLeft = data.maxDistance;
	this->damage = data.damage;
	this->speed = Vec2(1, 0).GetRotate(data.angle) * data.speed;

	LoadAssets(file, frameCount, frameTime);
}

void Bullet::Update(float dt) {
	// Reduce the distance left
	auto dist = this->speed * dt;

	this->distanceLeft -= dist.GetLength();

	// Destroy if hit the maximum distance
	if (this->distanceLeft <= 0) {
		this->associated.RequestDelete();
		return;
	}

	// Change position
	this->associated.box.vector -= dist;
}

void Bullet::Render() {}

void Bullet::NotifyCollision(GameObject& go) {
	auto player = go.GetComponent<Player>();

	if (player == nullptr) {
		return;
	}

	if (player->id != shooterId) {
		this->associated.RequestDelete();
		return;
	}
}

int Bullet::GetDamage() {
	return this->damage;
}

void Bullet::LoadAssets(const std::string& file, int frameCount, float frameTime) {
	associated.AddComponent<Sprite>(file);
	auto circle = new Circle();
	associated.AddComponent<Collider>(circle);
}
