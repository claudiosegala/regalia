#pragma once

#include <GameObject.h>
#include <Component.h>
#include <Timer.h>

class Charge : public Component {
public:
	Charge(GameObject& go, GameObject* playerGO);

	void Update(unsigned dt) override;

	void Render() override;

	void Load();

	void Unload();

	bool Overload();

	int GetLevel();

private:
	int overload = false;

	Timer timer;

	GameObject* player;

	void LoadAssets();
};