#pragma once

#include <Shape.h>
#include <Component.h>
#include <GameObject.h>
#include <Rect.h>
#include <Vec2.h>

class Collider : public Component {
public:
	
	Shape* shape;

	Collider(GameObject& go, Shape* shape, Vec2 scale = { 1, 1 }, Vec2 offset = { 0, 0 });

	void UpdateFather(unsigned dt);

	void Update(unsigned dt) override;

	void Render() override;

	void RenderBox(const Rect& box, int r, int g, int b);

	void SetScale(Vec2 scale);

	void SetOffset(Vec2 offset);

private:

	Vec2 scale;

	Vec2 offset;
};