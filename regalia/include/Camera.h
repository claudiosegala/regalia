#pragma once

#include <GameObject.h>
#include <Vec2.h>

class Camera {
public:
	static Vec2 pos;

	static Vec2 speed;

	static void Reset();

	static void Follow(GameObject* go);

	static void Unfollow();

	static void Update(unsigned dt);

private:
	static GameObject* focus;

	static Vec2 GetMovement();
};