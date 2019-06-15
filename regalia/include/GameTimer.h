#pragma once
#include "Component.h"
#include "Timer.h"

class GameTimer : public Component {
public:

	GameTimer(GameObject& go);

	void Update(unsigned dt) override;
	
	void Render() override;

private:
	
	Timer gameTimer;

	Timer animationTimer;
};
