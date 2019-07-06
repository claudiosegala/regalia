#pragma once

class StopWatch {
public:
	StopWatch();

	void Start(unsigned st);

	void Update(unsigned dt);

	unsigned Get();

	bool IsTimeUp();

private:
	unsigned time;
};