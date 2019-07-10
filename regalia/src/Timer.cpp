#include <pch.h>
#include <Timer.h>

Timer::Timer()
    : time(0)
	, paused(false) {
}

void Timer::SetStart(unsigned st) {
	time = st;
}

void Timer::Update(unsigned dt) {
	if (!paused) {
		time += dt;
	}
}

void Timer::Reset() {
	time = 0;
	paused = true;
}

void Timer::Restart() {
	time = 0;
	paused = false;
}

void Timer::Pause() {
	paused = true;
}

void Timer::Continue() {
	paused = false;
}

bool Timer::IsPaused() const {
	return paused;
}

unsigned Timer::Get() {
	return time;
}
