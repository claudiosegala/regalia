#pragma once

class Vec2 {
public:
	float x;

	float y;

	Vec2();

	Vec2(int, int);

	Vec2(float xv, float yv);

	Vec2(Vec2&, Vec2&);

	//> Find if the vector is (0, 0)
	bool IsOrigin() const;

	//> Set to (0, 0)
	void Reset();

	//> Limit the values of x and y to a range
	void Limit(float limit);

	//> Limit the values of x and y to a range
	void Limit(float, float, float, float);

	///> Find magnitude of vector
	float GetLength() const;

	///> Find angle with point (0, 0)
	float GetAngle() const;

	///> Find angle between this vector and another
	float GetAngle(const Vec2&) const;

	///> Transform vector, on unit
	void Unit();

	///> Get unit vector
	Vec2 GetUnit() const;

	///> Transform vector, rotating
	void Rotate(float);

	///> Get rotated vector
	Vec2 GetRotate(float) const;

	//> Distance between Vec2
	static float Distance(const Vec2&, const Vec2&);

	///> Cross product
	Vec2 operator*(const Vec2&);

	///> Dot product
	float operator^(const Vec2&) const;

	Vec2 operator*(const float)const;

	void operator*=(const float);

	Vec2 operator/(const float) const;

	void operator/=(const float);

	Vec2 operator+(const Vec2&) const;

	Vec2 operator+=(const Vec2&);

	Vec2 operator-(const Vec2&) const;

	Vec2 operator-=(const Vec2&);

	Vec2 operator=(const Vec2&);

	bool operator==(const Vec2& rhs) const;

	bool operator!=(const Vec2& rhs) const;

	friend std::ostream& operator<<(std::ostream& out, const Vec2& V);

	friend std::istream& operator>>(std::istream& in, Vec2& V);
};