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

	void LoadPlayer(int n, Vec2 pos);

	void LoadPersona(Constants::PersonaType type, Vec2 pos);

	void LoadVictories(int id, int victories, Vec2 pos);	
};