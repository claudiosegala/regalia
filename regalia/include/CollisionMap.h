#pragma once

#include <pch.h>
#include <Vec2.h>
#include <Rect.h>

class CollisionMap {
public:
	
	static unsigned long FindMaxDelta(const Rect& box, const Vec2& velocity, const unsigned long dt);

private:

	static std::vector<std::vector<int>> GetCollisionSet();
};