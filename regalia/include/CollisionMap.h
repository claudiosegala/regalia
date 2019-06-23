#pragma once

#include <pch.h>
#include <Vec2.h>
#include <Rect.h>

class CollisionMap {
public:

	static void SetMap(std::vector<int> map, int _rows, int _cols);
	
	static unsigned long FindMaxDelta(const Rect& box, const Vec2& velocity, const unsigned long dt);

private:

	static int cols;

	static int rows;

	static std::vector<std::vector<int>> map;
};