#include <pch.h>
#include <Bullet.h>
#include <Collider.h>
#include <GameObject.h>
#include <Player.h>
#include <Sprite.h>
#include <Vec2.h>

Bullet::Bullet(GameObject& go, BulletData& data, std::string file, int frameCount, float frameTime)
    : Component(go) {
	// Adding Image
	auto image = new Sprite(this->associated, file, frameCount, frameTime);
	this->associated.AddComponent(image);

	// Adding Collider
	auto collider = new Collider(this->associated);
	this->associated.AddComponent(collider);

	// Initialization of variables
	this->shooterId = data.shooterId;
	this->distanceLeft = data.maxDistance;
	this->damage = data.damage;
	this->speed = Vec2(1, 0).GetRotate(data.angle) * data.speed;
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
	auto component = go.GetComponent("Player");

	if (component == nullptr) {
		return;
	}

	auto player = std::static_pointer_cast<Player>(component);

	if (player == nullptr) {
		return;
	}

	if (player->id != shooterId) {
		this->associated.RequestDelete();
		return;
	}
}

bool Bullet::Is(std::string type) {
	return (type == "Bullet");
}

int Bullet::GetDamage() {
	return this->damage;
}