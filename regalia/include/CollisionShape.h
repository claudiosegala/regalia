#pragma once

#include <pch.h>
#include <Circle.h>
#include <Rect.h>

class CollisionShape {
public:

	virtual bool IsColliding(Circle) = 0;

	virtual bool IsColliding(Rect) = 0;

	virtual bool IsType(std::string) = 0;

};