#pragma once

class Number {
public:
	static const float Pi;
	static const float Tao;
	static const float Eps;

	static const bool Zero(float x);

	static const bool Equal(float x, float y);

	static const void InitRand();

	static const int Rand();

	static const float FRand();
};