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
	this->x = destination.x - start.x;
	this->y = destination.y - start.y;
}

bool Vec2::IsOrigin() const {
	return Number::Zero(this->x) && Number::Zero(this->y);
}

void Vec2::Reset() {
	this->x = this->y = 0;
}

void Vec2::Limit(float limit) {
	Limit(limit, -limit, limit, -limit);
}

void Vec2::Limit(float upperX, float lowerX, float upperY, float lowerY) {
	if (this->x < lowerX) {
		this->x = lowerX;
	} else {
		this->x = fmin(this->x, upperX);
	}

	if (this->y < lowerY) {
		this->y = lowerY;
	} else {
		this->y = fmin(this->y, upperY);
	}
}

float Vec2::GetLength() const {
	return (float)hypot(this->x, this->y);
}

float Vec2::GetAngle() const {
	return (float)atan2(this->y, this->x);
}

float Vec2::GetAngle(const Vec2& V) const {
	auto ds = this->GetLength() * V.GetLength();
	auto prod = (*this) ^ V;

	return (float)acos(prod / ds);
}

void Vec2::Unit() {
	(*this) /= this->GetLength();
}

Vec2 Vec2::GetUnit() const {
	return this->GetLength() ? (*this) / this->GetLength() : Vec2(0, 0);
}

void Vec2::Rotate(float angle) {
	auto xv = cos(angle) * this->x - sin(angle) * this->y;
	auto yv = sin(angle) * this->x + cos(angle) * this->y;

	this->x = static_cast<float>(xv);
	this->y = static_cast<float>(yv);
}

Vec2 Vec2::GetRotate(float angle) const {
	return Vec2(
	    static_cast<float>(cos(angle) * this->x - sin(angle) * this->y),
	    static_cast<float>(sin(angle) * this->x + cos(angle) * this->y));
}

float Vec2::Distance(const Vec2& V, const Vec2& U) {
	return (float)hypot(V.x - U.x, V.y - U.y);
}

Vec2 Vec2::operator=(const Vec2& V) {
	this->x = V.x;
	this->y = V.y;

	return *this;
}

bool Vec2::operator==(const Vec2& rhs) const {
	return x == rhs.x && y == rhs.y;
}

bool Vec2::operator!=(const Vec2& rhs) const {
	return !(rhs == *this);
}

Vec2 Vec2::operator*(const Vec2& V) {
	return Vec2(this->x * V.y, this->y * V.x);
}

float Vec2::operator^(const Vec2& V) const {
	return this->x * V.x + this->y * V.y;
}

Vec2 Vec2::operator*(const float v) const {
	return Vec2(this->x * v, this->y * v);
}

void Vec2::operator*=(const float v) {
	this->x *= v;
	this->y *= v;
}

Vec2 Vec2::operator/(const float v) const {
	return Vec2(this->x / v, this->y / v);
}

void Vec2::operator/=(const float v) {
	this->x /= v;
	this->y /= v;
}

Vec2 Vec2::operator+(const Vec2& V) const {
	return Vec2(this->x + V.x, this->y + V.y);
}

Vec2 Vec2::operator+=(const Vec2& V) {
	this->x += V.x;
	this->y += V.y;

	return (*this);
}

Vec2 Vec2::operator-(const float x) const {
	return Vec2(this->x - x, this->y - x);
}

Vec2 Vec2::operator-(const Vec2& V) const {
	return Vec2(this->x - V.x, this->y - V.y);
}

Vec2 Vec2::operator-=(const Vec2& V) {
	this->x -= V.x;
	this->y -= V.y;

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