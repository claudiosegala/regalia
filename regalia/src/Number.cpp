#include <pch.h>
#include <Number.h>

const float Number::Pi = 3.141592653589793f;
const float Number::Tao = 2.0f * Number::Pi;
const float Number::Eps = FLT_EPSILON;

const bool Number::Zero(float x) {
	return fabs(x) < Eps;
}

const bool Number::Equal(float x, float y) {
	return fabs(x - y) < Eps;
}

const void Number::InitRand() {
	srand((unsigned int)time(NULL));
}

const int Number::Rand() {
	return rand();
}

const int Number::RandRange(int lower, int upper) {
	if (upper == lower) {
		return upper;
	}
	assert(upper > lower);
	return lower + Rand() % (upper - lower);
}

const int Number::RandRange(std::pair<int, int> range) {
	return RandRange(range.first, range.second);
}

const float Number::FRand() {
	return float(rand()) / float(RAND_MAX); // 0.0 to 1.0
}
