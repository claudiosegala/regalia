#include <pch.h>
#include <Number.h>
#include <Circle.h>

Circle::Circle() : radius(0), center() {
}

Circle::Circle(float r, Vec2 p)
    : radius(r)
    , center(p) {}

bool Circle::Is(const std::string& type) {
	return (type == "Cicle");
}

float Circle::Perimeter() {
	return 2.0f * Number::Pi * this->radius;
}

float Circle::Area() {
	return Number::Pi * this->radius * this->radius;
}