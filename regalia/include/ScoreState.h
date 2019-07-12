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

	const Vec2 cardPositions[4] = {
		{ 528, 70 },
		{ 652, 70 },
		{ 528, 246 },
		{ 652, 246 }
	};

	const Vec2 playerLabelPositions[4] = {
		{ 564, 82 },
		{ 688, 82 },
		{ 564, 258 },
		{ 688, 258 }
	};

	const Vec2 personasPositions[4] = {
		{ 536, 90 },
		{ 660, 90 },
		{ 536, 266 },
		{ 660, 266 }
	};

	const Vec2 victoriesPositions[4] = {
		{ 540, 198 },
		{ 664, 198 },
		{ 540, 374 },
		{ 664, 374 }
	};
};