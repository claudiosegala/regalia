#include <pch.h>
#include <Number.h>
#include <Vec2.h>

Vec2::Vec2()
    : x(0.0f)
    , y(0.0f) {}

Vec2::Vec2(int xv, int yv)
    : x(static_cast<float>(xv))
    , y(static_cast<float>(yv)) {}

Vec2::Vec2(float xv, float yv)
    : x(xv)
    , y(yv) {}

Vec2::Vec2(Vec2& start, Vec2& destination) {
	(*this) = destination - start;
}

bool Vec2::IsOrigin() const {
	return Number::Zero(x) && Number::Zero(y);
}

void Vec2::Reset() {
	x = y = 0;
}

void Vec2::Limit(float limit) {
	Limit(limit, -limit, limit, -limit);
}

void Vec2::Limit(float upperX, float lowerX, float upperY, float lowerY) {
	if (x < lowerX) {
		x = lowerX;
	} else {
		x = fmin(x, upperX);
	}

	if (y < lowerY) {
		y = lowerY;
	} else {
		y = fmin(y, upperY);
	}
}

float Vec2::GetLength() const {
	return (float)hypot(x, y);
}

float Vec2::GetAngle() const {
	return (float)atan2(y, x);
}

float Vec2::GetAngle(const Vec2& V) const {
	auto ds = GetLength() * V.GetLength();
	auto prod = (*this) ^ V;

	return (float)acos(prod / ds);
}

void Vec2::Unit() {
	(*this) /= GetLength();
}

Vec2 Vec2::GetUnit() const {
	return GetLength() ? (*this) / GetLength() : Vec2(0, 0);
}

void Vec2::Rotate(float angle) {
	auto xv = cos(angle) * x - sin(angle) * y;
	auto yv = sin(angle) * x + cos(angle) * y;

	x = static_cast<float>(xv);
	y = static_cast<float>(yv);
}

Vec2 Vec2::GetRotate(float angle) const {
	return Vec2(
	    static_cast<float>(cos(angle) * x - sin(angle) * y),
	    static_cast<float>(sin(angle) * x + cos(angle) * y));
}

float Vec2::Distance(const Vec2& V, const Vec2& U) {
	return (float)hypot(V.x - U.x, V.y - U.y);
}

Vec2 Vec2::operator=(const Vec2& V) {
	x = V.x;
	y = V.y;

	return *this;
}

bool Vec2::operator==(const Vec2& rhs) const {
	return x == rhs.x && y == rhs.y;
}

bool Vec2::operator!=(const Vec2& rhs) const {
	return !(rhs == *this);
}

Vec2 Vec2::operator*(const Vec2& V) {
	return Vec2(x * V.y, y * V.x);
}

float Vec2::operator^(const Vec2& V) const {
	return x * V.x + y * V.y;
}

Vec2 Vec2::operator*(const float v) const {
	return Vec2(x * v, y * v);
}

void Vec2::operator*=(const float v) {
	x *= v;
	y *= v;
}

Vec2 Vec2::operator/(const float v) const {
	return Vec2(x / v, y / v);
}

void Vec2::operator/=(const float v) {
	x /= v;
	y /= v;
}

Vec2 Vec2::operator+(const Vec2& V) const {
	return Vec2(x + V.x, y + V.y);
}

Vec2 Vec2::operator+=(const Vec2& V) {
	x += V.x;
	y += V.y;

	return (*this);
}

Vec2 Vec2::operator-(const Vec2& V) const {
	return Vec2(x - V.x, y - V.y);
}

Vec2 Vec2::operator-=(const Vec2& V) {
	x -= V.x;
	y -= V.y;

	return (*this);
}

std::ostream& operator<<(std::ostream& out, const Vec2& V) {
	out << "vector: { x:" << V.x << ", y:" << V.y << " }";
	return out;
}

std::istream& operator>>(std::istream& in, Vec2& V) {
	in >> V.x >> V.y;
	return in;
}