#pragma once

#include <GameObject.h>
#include <Music.h>
#include <State.h>

class MenuState : public State {
public:
	MenuState();

	~MenuState();

	void LoadAssets() override;

	void Update(float) override;

	void Render() override;

	void Start() override;

	void Pause() override;

	void Resume() override;

private:
	int option;

	std::weak_ptr<GameObject> cursor;

	Music music;

	GameObject* CreateOption(std::string, Vec2 shift = { 0, 0 });
};