#pragma once
#include "State.h"
#include "Timer.h"
#include "Text.h"

class CountdownState : public State {
public:
	CountdownState(State* playState);

	~CountdownState();

	void LoadAssets() override;

	void Update(unsigned dt) override;

	void Render() override;

	void Start() override;

	void Pause() override;

	void Resume() override;

private:

	Timer timer;

	int count = Constants::Countdown::StartValue;

	State* playState = nullptr;

	GameObject* text = nullptr;
};
