#pragma once

#include <Music.h>
#include <State.h>

class CreditState : public State {
public:
	CreditState();

	~CreditState();

	void LoadAssets() override;

	void Update(unsigned dt) override;

	void Render() override;

	void Start() override;

	void Pause() override;

	void Resume() override;

private:
	Music music;
};