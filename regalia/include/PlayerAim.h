#pragma once
#include <Component.h>

class PlayerAim : public Component {
public:
	PlayerAim(GameObject& go, std::weak_ptr<GameObject> player);
	
	~PlayerAim();

	float GetAngle();

	void Update(unsigned dt) override;
	
	void Render() override;

private:
	std::weak_ptr<GameObject> player;

	float lastAngle = 0.0f;

	void LoadAssets();
};
