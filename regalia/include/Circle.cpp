#include "pch.h"
#include "Circle.h"

Circle::Circle(Vec2 p, float r) : radius(r), center(p) {}

float Circle::Perimeter() {
	return 2.0f * Constants::Math::PI * this->radius;
}

float Circle::Area() {
	return Constants::Math::PI * this->radius * this->radius;
}
