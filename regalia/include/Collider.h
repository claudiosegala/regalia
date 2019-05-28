#pragma once

#include <Shape.h>
#include <Component.h>
#include <GameObject.h>
#include <Rect.h>
#include <Vec2.h>

class Collider : public Component {
public:

	Collider(GameObject&, Shape*, Vec2 scale = { 1, 1 }, Vec2 offset = { 0, 0 });

	void Update(float) override;

	void Render() override;
	
	void SetScale(Vec2);

	void SetOffset(Vec2);

private:
	Shape* shape;

	Vec2 scale;

	Vec2 offset;
};