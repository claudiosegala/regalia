#pragma once

#include <pch.h>
#include <Shape.h>
#include <Vec2.h>

class Circle : public Shape {
public:
	float radius;

	Vec2 center;

	Circle();

	Circle(float r, Vec2 p);

	bool Is(const std::string& type) override;

	float Perimeter() const;

	float Area() const;
};