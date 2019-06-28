#pragma once

#include <GameObject.h>
#include <Music.h>
#include <State.h>

class MenuState : public State {
public:
	MenuState();

	~MenuState();

	void LoadAssets() override;

	void Update(unsigned dt) override;

	void Render() override;

	void Start() override;

	void Pause() override;

	void Resume() override;

private:
	int option = 0;

	std::weak_ptr<GameObject> cursor;

	Music music;

	GameObject* CreateBackground();

	GameObject* CreateOption(const std::string&, Vec2 shift = { 0, 0 });

	void PositionCursor(int position);
};