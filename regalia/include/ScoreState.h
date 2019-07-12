#pragma once

#include <Music.h>
#include <State.h>

#include <string>

class ScoreState : public State {
public:
	ScoreState();

	~ScoreState();

	void LoadAssets() override;

	void Update(unsigned dt) override;

	void Render() override;

	void Start() override;

	void Pause() override;

	void Resume() override;

private:
	Music music;

	void LoadBackground();

	void LoadChapter();

	void LoadScore();

	void LoadCard(int animation, Vec2 pos);

	void LoadPlayerLabel(int n);

	void LoadPersona(int n);

	void LoadVictories(int n, int victories);
};