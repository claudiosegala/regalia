#pragma once

#include <Music.h>
#include <State.h>
#include <Timer.h>

// TODO: add animation of Ready? Go!

class PlayState : public State {
public:
	PlayState();

	~PlayState();

	void LoadAssets();

	void Update(float);

	void Render();

	void Start();

	void Pause();

	void Resume();

private:
	Timer roundTimer;

	Music music;
};