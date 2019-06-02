#pragma once

#include <Music.h>
#include <State.h>

class StoryState : public State {
public:
	StoryState();

	~StoryState();

	void LoadAssets() override;

	void Update(unsigned dt) override;

	void Render() override;

	void Start() override;

	void Pause() override;

	void Resume() override;

private:
	Music music;
};