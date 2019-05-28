#include <pch.h>
#include <Number.h>

// TODO: make it inline and const 

const float Number::Pi = 3.141592653589793f;
const float Number::Tao = 2.0f * Number::Pi;
const float Number::Eps = 0.00001f;

bool Number::Zero (float x) {
    return Equal(x, 0.0f);
}

bool Number::Equal (float x, float y) {
    return fabs(x - y) < Number::Eps;
}

void Number::InitRand () {
    srand((unsigned int)time(NULL));
}

int Number::Rand () {
    return rand();
}

float Number::FRand () {
    return float(rand()) / float(RAND_MAX); // 0.0 to 1.0
}