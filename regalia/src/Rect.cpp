#include <pch.h>
#include <Rect.h>

Rect::Rect()
    : vector()
    , width(0)
    , height(0) {}

Rect::Rect(Vec2 v, float w, float h)
    : vector(v)
    , width(w)
    , height(h) {}

Rect::Rect(float x, float y, float w, float h)
    : vector(x, y)
    , width(w)
    , height(h) {}

Vec2 Rect::Center() const {
	Vec2 dl, ur;

	std::tie(dl, ur) = GetPoints();

	return (dl + ur) / 2;
}

float Rect::CenterDistance(const Rect& R) const {
	auto c1 = this->Center();
	auto c2 = R.Center();

	return Vec2::Distance(c1, c2);
}

void Rect::SetCenter(const Vec2& V) {
	this->vector = V - Vec2(this->width / 2, this->height / 2);
}

bool Rect::IsInside(const Vec2& V) const {
	return (V.x >= this->vector.x && V.x <= this->vector.x + this->width)
	    && (V.y >= this->vector.y && V.y <= this->vector.y + this->height);
}

std::tuple<Vec2, Vec2> Rect::GetPoints() const {
	auto u = this->vector; // down left
	auto v = u + Vec2(this->width, this->height); // upper right

	return std::make_tuple(v, u);
}

Rect Rect::operator+(const Vec2& V) const {
	return Rect { this->vector + V, this->width, this->height };
}

void Rect::operator+=(const Vec2& V) {
	this->vector.x += V.x;
	this->vector.y += V.y;
}

Rect Rect::operator-(const Vec2& V) const {
	return Rect { this->vector - V, this->width, this->height };
}

void Rect::operator-=(const Vec2& V) {
	this->vector.x -= V.x;
	this->vector.y -= V.y;
}

Rect Rect::operator*(float value) const {
	auto w = this->width * value;
	auto h = this->height * value;

	return Rect { this->vector, w, h };
}

void Rect::operator*=(float v) {
	this->vector.x *= v;
	this->vector.y *= v;
}

std::ostream& operator<<(std::ostream& out, const Rect& R) {
	out << "Rect: {\n\twidth:" << R.width << ",\n\theight:" << R.height << ",\n\t" << R.vector << " }";
	return out;
}

std::istream& operator>>(std::istream& in, Rect& R) {
	in >> R.width >> R.height >> R.vector;
	return in;
}