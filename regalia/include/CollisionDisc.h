#pragma once

#include <CollisionShape.h>
#include <Circle.h>
#include <Rect.h>

class CollisionDisc : public CollisionShape {
public:
	Circle disc;

	bool IsColliding(Circle);

	bool IsColliding(Rect);

	bool IsType(std::string);
};