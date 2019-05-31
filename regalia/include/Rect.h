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

	Rect(Vec2 v, float w, float h);

	Rect(float x, float y, float w, float h);

	bool Is(const std::string& type) override;

	float MaxRadius() const;

	Vec2 Center() const;

	float CenterDistance(const Rect& R) const;

	void SetCenter(const Vec2& V);

	bool IsInside(const Vec2& V) const;

	std::tuple<Vec2, Vec2> GetPoints() const;

	Vec2 GetUpperLeft() const;

	Vec2 GetLowerRight() const;

	Rect operator+(const Vec2& V) const;

	void operator+=(const Vec2& V);

	Rect operator-(const Vec2& V) const;

	void operator-=(const Vec2& V);

	friend std::ostream& operator<<(std::ostream& os, const Rect& R);

	friend std::istream& operator>>(std::istream& is, Rect& R);
};