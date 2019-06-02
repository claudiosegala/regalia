#pragma once
#include "State.h"
#include "Timer.h"
#include "Text.h"

class CountdownState : public State {
public:
	CountdownState(State* playState);

	~CountdownState();

	void LoadAssets() override;

	void Update(float dt) override;

	void Render() override;

	void Start() override;

	void Pause() override;

	void Resume() override;

private:
	State* playState;

	Timer timer;

	int count;

	GameObject* text;
};
