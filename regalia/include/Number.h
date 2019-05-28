#pragma once

class Number {
public:
	static const float Pi;
	static const float Tao;
	static const float Eps;

	static bool Zero(float x);

	static bool Equal(float x, float y);

	static void InitRand();

	static int Rand();

	static float FRand();
};