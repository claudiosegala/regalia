#pragma once

class Timer {
public:
	Timer();

	void SetStart(unsigned st);

	void Update(unsigned dt);

	void Reset();

	void Restart();

	void Pause();

	void Continue();

	bool IsPaused() const;

	unsigned Get();

private:
	unsigned time;

	bool paused;
};