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

Vec2::Vec2(Vec2& u, Vec2& v) {
	this->x = v.x - u.x;
	this->y = v.y - u.y;
}

bool Vec2::IsOrigin() const {
	return Number::Zero(x) && Number::Zero(y);
}

void Vec2::Reset() {
	x = y = 0;
}

void Vec2::Limit(float limit) {
	Limit({ limit, limit }, { -limit, -limit });
}

void Vec2::Limit(const Vec2& limit) {
	Limit(limit, -limit);
}

void Vec2::Limit(const Vec2& upper, const Vec2& lower) {
	if (x < lower.x) {
		x = lower.x;
	} else {
		x = fmin(x, upper.x);
	}

	if (y < lower.y) {
		y = lower.y;
	} else {
		y = fmin(y, upper.y);
	}
}

float Vec2::GetLength() const {
	return (float)hypot(x, y);
}

float Vec2::GetAngle() const {
	return (float)atan2(y, x);
}

float Vec2::GetAngle(const Vec2& v) const {
	auto ds = GetLength() * v.GetLength();
	auto prod = (*this) ^ v;

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

float Vec2::Distance(const Vec2& u, const Vec2& v) {
	return (float)hypot(v.x - u.x, v.y - u.y);
}

Vec2 Vec2::operator=(const Vec2& v) {
	x = v.x;
	y = v.y;

	return *this;
}

bool Vec2::operator==(const Vec2& v) const {
	return x == v.x && y == v.y;
}

bool Vec2::operator!=(const Vec2& v) const {
	return !(v == *this);
}

Vec2 Vec2::operator*(const Vec2& v) {
	return Vec2(x * v.y, y * v.x);
}

float Vec2::operator^(const Vec2& v) const {
	return x * v.x + y * v.y;
}

Vec2 Vec2::operator*(const float k) const {
	return Vec2(x * k, y * k);
}

void Vec2::operator*=(const float k) {
	x *= k;
	y *= k;
}

Vec2 Vec2::operator/(const float k) const {
	return Vec2(x / k, y / k);
}

void Vec2::operator/=(const float k) {
	x /= k;
	y /= k;
}

Vec2 Vec2::operator+(const Vec2& v) const {
	return Vec2(x + v.x, y + v.y);
}

Vec2 Vec2::operator+=(const Vec2& v) {
	x += v.x;
	y += v.y;

	return (*this);
}

Vec2 Vec2::operator-(const float k) const {
	return Vec2(x - k, y - k);
}

Vec2 Vec2::operator-(const Vec2& v) const {
	return Vec2(x - v.x, y - v.y);
}

Vec2 Vec2::operator-() const {
	return Vec2(-x, -y);
}

Vec2 Vec2::operator-=(const Vec2& v) {
	x -= v.x;
	y -= v.y;

	return (*this);
}

std::ostream& operator<<(std::ostream& out, const Vec2& v) {
	out << "vector: { x:" << v.x << ", y:" << v.y << " }";
	return out;
}

std::istream& operator>>(std::istream& in, Vec2& v) {
	in >> v.x >> v.y;
	return in;
}