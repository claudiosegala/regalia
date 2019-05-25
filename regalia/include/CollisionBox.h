#pragma once

#include <CollisionShape.h>
#include <Circle.h>
#include <Rect.h>

class CollisionBox : public CollisionShape {
public:
	Rect box;

	bool IsColliding(Circle);

	bool IsColliding(Rect);

	bool IsType(std::string);
};