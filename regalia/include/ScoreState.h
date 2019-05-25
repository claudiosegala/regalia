#pragma once

#include <Constants.h>
#include <GameObject.h>
#include <Music.h>
#include <State.h>

#include <string>

class ScoreState : public State {
public:
	ScoreState();

	~ScoreState();

	void LoadAssets() override;

	void Update(float) override;

	void Render() override;

	void Start() override;

	void Pause() override;

	void Resume() override;

private:
	Music music;

	void LoadBackground();

	void LoadScore();

	void LoadPausedOptions();

	void LoadContinueOptions();

	void LoadFinishedOptions();

};