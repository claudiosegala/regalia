#pragma once

#include <GameObject.h>
#include <Vec2.h>

class Camera {
public:
	static Vec2 pos;

	static Vec2 speed;

	static void Reset();

	static void Follow(GameObject*);

	static void Unfollow();

	static void Update(float);

private:
	static float const pace;

	static GameObject* focus;

	static Vec2 GetMovement();
};