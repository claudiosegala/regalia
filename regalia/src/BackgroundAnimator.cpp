#include "pch.h"
#include "BackgroundAnimator.h"
#include "GameObject.h"
#include "Number.h"

BackgroundAnimator::BackgroundAnimator(GameObject& go, const BackgroundAnimationData& animationData)
    : Component(go)
    , animationData(animationData) {
	numAnimations = int(animationData.IntervalRange.size());
	sprite = associated.AddComponent<Sprite>(animationData.SpriteSheet);
	associated.box.vector = animationData.InitialPosition;
	animationRunsLeft = Number::RandRange(animationData.IntervalRange[currentAnimation]);
}

void BackgroundAnimator::Update(unsigned dt) {
	if (animationDone) {
		UpdateAnimation();
	}
	UNUSED(dt);
}

void BackgroundAnimator::Render() {
}

void BackgroundAnimator::Start() {
	sprite->RunAnimation(0, [&]() {
		animationDone = true;
	},
	    Number::RandRange(animationData.IntervalRange[currentAnimation]));
}

void BackgroundAnimator::UpdateAnimation() {
	animationDone = false;

	currentAnimation = (currentAnimation + 1) % numAnimations;

	sprite->RunAnimation(currentAnimation, [&]() {
		animationDone = true; }, Number::RandRange(animationData.IntervalRange[currentAnimation]));
}
