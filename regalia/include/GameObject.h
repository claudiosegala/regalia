#pragma once

#include <CollisionShape.h>
#include <Rect.h>

class Component;

class GameObject {
public:
	CollisionShape* shape;

	Rect box;

	float angle;

	GameObject();

	~GameObject();

	void Start();

	void Update(float);

	void Render();

	bool IsDead();

	void RequestDelete();

	void AddComponent(Component*);

	void RemoveComponent(std::shared_ptr<Component>&);

	std::shared_ptr<Component> GetComponent(std::string);

	void NotifyCollision(GameObject&);

private:
	bool started;

	bool isDead;

	std::vector<std::shared_ptr<Component>> components;
};