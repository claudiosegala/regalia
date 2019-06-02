#include <pch.h>
#include <Timer.h>

Timer::Timer()
    : time(0) {
}

void Timer::SetStart(unsigned st) {
	time = st;
}

void Timer::Update(unsigned dt) {
	time += dt;
}

void Timer::Restart() {
	time = 0;
}

unsigned Timer::Get() {
	return time;
}