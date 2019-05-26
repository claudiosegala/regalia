#include "pch.h"
#include "SpriteSheetData.h"

AnimationData::AnimationData(int id, int numberOfFrames)
    : id(id)
    , numberOfFrames(numberOfFrames) {}

SpriteSheetData::SpriteSheetData(const std::string& file, int width, int height, float frameTime, const std::vector<AnimationData>& animations)
    : file(file)
    , frameTime(frameTime)
    , width(width)
    , height(height) {

#ifdef _DEBUG
	// Check if the animations ids are sorted and there is no empty animation
	assert(std::is_sorted(animations.begin(), animations.end(), [](const AnimationData& x, const AnimationData& y) { return x.id == (y.id - 1); }));

	assert(animations.front().id == 0);
	assert(animations.back().id == animations.size() - 1);
#endif

	auto totalFrames = std::accumulate(animations.begin(), animations.end(), 0, [](int acc, const AnimationData& y) { return acc + y.id; });

	// Fill the animationsRect vector
	animationsRect.resize(animations.size());
	auto frameWidth = width / totalFrames;
	auto nextFrameX = 0;

	for (auto& animation : animations) {
		animationsRect[animation.id].resize(animation.numberOfFrames);

		for (auto i = 0; i < animation.numberOfFrames; i++) {
			animationsRect[animation.id][i] = { nextFrameX, 0, frameWidth, height };
			nextFrameX += frameWidth;
		}
	}
}

#ifdef _DEBUG
#endif
