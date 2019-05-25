#pragma once

#include <Shape.h>
#include <Component.h>
#include <GameObject.h>
#include <Rect.h>
#include <Vec2.h>

class Collider : public Component {
public:
	Shape* shape;

	Collider(GameObject&, Shape*, Vec2 scale = { 1, 1 }, Vec2 offset = { 0, 0 });

	void Update(float);

	void Render();

	bool Is(std::string);

	void SetScale(Vec2);

	void SetOffset(Vec2);

private:
	Vec2 offset;

	Vec2 scale;
};