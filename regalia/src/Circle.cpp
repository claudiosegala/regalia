#include <pch.h>
#include <Number.h>
#include <Circle.h>

Circle::Circle()
    : radius(0)
    , center() {
}

Circle::Circle(float r, Vec2 p)
    : radius(r)
    , center(p) {}

bool Circle::Is(const std::string& type) {
	return (type == "Circle");
}

float Circle::Perimeter() const {
	return 2.0f * Number::Pi * radius;
}

float Circle::Area() const {
	return Number::Pi * radius * radius;
}