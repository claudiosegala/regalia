#pragma once
#include "Component.h"
#include "Sprite.h"

class BackgroundAnimator : public Component {
public:
	explicit BackgroundAnimator(GameObject& go, const BackgroundAnimationData& animationData);
	void Update(unsigned dt) override;
	void Render() override;
	void Start() override;
private:
	const BackgroundAnimationData& animationData;
	Sprite* sprite = nullptr;
	int animationRunsLeft = 0;
	int currentAnimation = 0;
	int numAnimations = 0;
	bool animationDone = false;
	void UpdateAnimation();
};
