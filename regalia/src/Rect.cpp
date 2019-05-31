#include <pch.h>
#include <Rect.h>
#include "Camera.h"
#include "Game.h"

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

Rect::Rect(const Vec2& upperLeft, const Vec2& bottomRight)
    : vector(upperLeft)
    , width(bottomRight.x - upperLeft.x)
    , height(bottomRight.y - upperLeft.y) {}

void Rect::Render(int r, int g, int b) const {
	SDL_Point points[5];

	Vec2 point = Vec2(vector.x, vector.y) - Camera::pos;

	points[0] = { int(point.x), int(point.y) };
	points[4] = { int(point.x), int(point.y) };

	point = Vec2(vector.x + width, vector.y) - Camera::pos;

	points[1] = { int(point.x), int(point.y) };

	point = Vec2(vector.x + width, vector.y + height) - Camera::pos;

	points[2] = { int(point.x), int(point.y) };

	point = Vec2(vector.x, vector.y + height) - Camera::pos;

	points[3] = { int(point.x), int(point.y) };

	SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), Uint8(r), Uint8(g), Uint8(b), SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance()->GetRenderer(), points, 5);
}

bool Rect::Is(const std::string& type) {
	return (type == "Rect");
}

float Rect::MaxRadius() const {
	return fmax(width, height) / 2.0f;
}

Vec2 Rect::Center() const {
	Vec2 dl, ur;

	std::tie(dl, ur) = GetPoints();

	return (dl + ur) / 2;
}

float Rect::CenterDistance(const Rect& R) const {
	auto c1 = Center();
	auto c2 = R.Center();

	return Vec2::Distance(c1, c2);
}

void Rect::SetCenter(const Vec2& V) {
	vector = V - Vec2(width / 2, height / 2);
}

bool Rect::IsInside(const Vec2& V) const {
	return (V.x >= vector.x && V.x <= vector.x + width)
	    && (V.y >= vector.y && V.y <= vector.y + height);
}

std::tuple<Vec2, Vec2> Rect::GetPoints() const {
	auto u = vector; // upper left
	auto v = u + Vec2(width, height); // down right

	return std::make_tuple(v, u);
}

Vec2 Rect::GetUpperLeft() const {
	return vector;
}

Vec2 Rect::GetLowerRight() const {
	return vector + Vec2(width, height);
}

Rect Rect::operator+(const Vec2& V) const {
	return Rect { vector + V, width, height };
}

void Rect::operator+=(const Vec2& V) {
	vector += V;
}

Rect Rect::operator-(const Vec2& V) const {
	return Rect { vector - V, width, height };
}

void Rect::operator-=(const Vec2& V) {
	vector -= V;
}

std::ostream& operator<<(std::ostream& os, const Rect& R) {
	os << "Rect: {\n\twidth:" << R.width << ",\n\theight:" << R.height << ",\n\t" << R.vector << " }";
	return os;
}

std::istream& operator>>(std::istream& is, Rect& R) {
	is >> R.width >> R.height >> R.vector;
	return is;
}