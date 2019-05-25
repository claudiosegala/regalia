#pragma once

#include <pch.h>
#include <Constants.h>
#include <Vec2.h>

class Circle {
public:
	float radius;

	Vec2 center;

	Circle(Vec2, float);

	float Perimeter();

	float Area();

};