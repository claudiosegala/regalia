#include <pch.h>
#include <Bullet.h>
#include <Collider.h>
#include <GameObject.h>
#include <Sprite.h>
#include <Vec2.h>

Bullet::Bullet(GameObject& go, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetPlayer)
    : Component(go) {
	// Adding Image
	auto image = new Sprite(this->associated, sprite, frameCount, frameTime);
	this->associated.AddComponent(image);

	// Adding Collider
	auto collider = new Collider(this->associated);
	this->associated.AddComponent(collider);

	// Initialization of variables
	this->targetPlayer = targetPlayer;
	this->distanceLeft = maxDistance;
	this->damage = damage;
	this->speed = Vec2(1, 0).GetRotate(angle) * speed;
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
	if ((other.GetPenguinBody() != nullptr && !targetPlayer) || (other.GetAlien() != nullptr && targetPlayer)) {
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