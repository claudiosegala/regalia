#pragma once

class Timer {
public:
	Timer();

	void SetStart(unsigned st);

	void Update(unsigned dt);

	void Restart();

	unsigned Get();

private:
	unsigned time;
};