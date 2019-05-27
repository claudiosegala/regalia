#pragma once
#include "Component.h"

class PlayerAim : public Component {
public:
	PlayerAim(GameObject& go, std::weak_ptr<GameObject> player, int playerId);
	~PlayerAim();

	void Update(float dt) override;
	void Render() override;

private:
	std::weak_ptr<GameObject> player;

	int playerId;

	void LoadAssets();
};