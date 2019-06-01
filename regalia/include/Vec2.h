#pragma once

class Vec2 {
public:
	float x;

	float y;

	Vec2();

	Vec2(int xv, int yv);

	Vec2(float xv, float yv);

	Vec2(Vec2& u, Vec2& v);

	//> Find if the vector is (0, 0)
	bool IsOrigin() const;

	//> Set to (0, 0)
	void Reset();

	//> Limit the values of x and y to a range
	void Limit(float limit);

	//> Limit the values of x and y to a range
	void Limit(Vec2 upper, Vec2 lower);

	///> Find magnitude of vector
	float GetLength() const;

	///> Find angle with point (0, 0)
	float GetAngle() const;

	///> Find angle between this vector and another
	float GetAngle(const Vec2& v) const;

	///> Transform vector, on unit
	void Unit();

	///> Get unit vector
	Vec2 GetUnit() const;

	///> Transform vector, rotating
	void Rotate(float angle);

	///> Get rotated vector
	Vec2 GetRotate(float angle) const;

	//> Distance between Vec2
	static float Distance(const Vec2& u, const Vec2& v);

	///> Cross product
	Vec2 operator*(const Vec2& v);

	///> Dot product
	float operator^(const Vec2& v) const;

	Vec2 operator*(const float k) const;

	void operator*=(const float k);

	Vec2 operator/(const float k) const;

	void operator/=(const float k);

	Vec2 operator+(const Vec2&) const;

	Vec2 operator+=(const Vec2&);

	Vec2 operator-(const float k) const;

	Vec2 operator-(const Vec2& v) const;

	Vec2 operator-=(const Vec2& v);

	Vec2 operator=(const Vec2& v);

	bool operator==(const Vec2& v) const;

	bool operator!=(const Vec2& v) const;

	friend std::ostream& operator<<(std::ostream& out, const Vec2& v);

	friend std::istream& operator>>(std::istream& in, Vec2& v);
};