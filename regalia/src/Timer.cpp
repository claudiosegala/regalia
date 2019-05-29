#include <pch.h>
#include <Timer.h>

Timer::Timer() {
	time = 0.0f;
}

void Timer::SetStart(float st) {
	time = st;
}

void Timer::Update(float dt) {
	time += dt;
}

void Timer::Restart() {
	time = 0.0f;
}

float Timer::Get() {
	return time;
}