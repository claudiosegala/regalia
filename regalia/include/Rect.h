#pragma once

#include <pch.h>
#include <Shape.h>
#include <Vec2.h>

class Rect : public Shape {
public:
	Vec2 vector;

	float width;

	float height;

	Rect();

	Rect(Vec2, float, float);

	Rect(float, float, float, float);

	bool Is(const std::string&) override;

	float MaxRadius() const;

	Vec2 Center() const;

	float CenterDistance(const Rect&) const;

	void SetCenter(const Vec2&);

	bool IsInside(const Vec2&) const;

	std::tuple<Vec2, Vec2> GetPoints() const;

	Vec2 GetUpperLeft() const;

	Vec2 GetLowerRight() const;

	Rect operator+(const Vec2&) const;

	void operator+=(const Vec2&);

	Rect operator-(const Vec2&) const;

	void operator-=(const Vec2&);

	friend std::ostream& operator<<(std::ostream& os, const Rect& n);

	friend std::istream& operator>>(std::istream& is, Rect& n);
};