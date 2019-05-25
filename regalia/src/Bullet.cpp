#include <pch.h>
#include <Bullet.h>
#include <Collider.h>
#include <GameObject.h>
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

void Bullet::NotifyCollision(GameObject& other) {
	// If hit an penguin body or alien, it should destroy itself
	if ((other.GetPenguinBody() != nullptr && !shooterId) || (other.GetAlien() != nullptr && shooterId)) {
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