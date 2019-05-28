#pragma once

#include <pch.h>
#include <Shape.h>
#include <Vec2.h>

class Circle : public Shape {
public:
	float radius;

	Vec2 center;

	Circle();

	Circle(float, Vec2);

	bool Is(const std::string&) override;

	float Perimeter();

	float Area();

};