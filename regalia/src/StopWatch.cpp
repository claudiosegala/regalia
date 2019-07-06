#include <pch.h>
#include <StopWatch.h>

#include <stdlib.h>

StopWatch::StopWatch()
    : time(0u) {}

void StopWatch::Start(unsigned st) {
	time = st;
}

void StopWatch::Update(unsigned dt) {
	time -= std::min(dt, time);
}

unsigned StopWatch::Get() {
	return time;
}

bool StopWatch::IsTimeUp() {
	return time == 0;
}
