#include "pch.h"
#include "SpriteSheetData.h"
#include "Logger.h"

SpriteSheetData::SpriteSheetData(const std::string& file, int imageWidth, int imageHeight, float frameTime, int totalAnimations, const std::map<int, int>& animationsFrames, bool selfDestruct)
    : file(file)
    , frameTime(frameTime)
	, selfDestruct(selfDestruct)
    , imageWidth(imageWidth)
    , imageHeight(imageHeight) {

	// Check if there is a missing animation
	assert(animationsFrames.size() == totalAnimations);

	auto totalFrames = std::accumulate(animationsFrames.begin(), animationsFrames.end(), 0, [](int acc, const std::map<int, int>::value_type& i) { return acc + i.second; });

	animationsRect.resize(totalAnimations);
	frameWidth = imageWidth / totalFrames;
	auto nextFrameX = 0;

	// Fill the animationsRect vector
	animationsRect.resize(totalAnimations);

	for (auto& animation : animationsFrames) {
		const auto& animationId = animation.first;
		const auto& frames = animation.second;

		if (frames == 0) {
			Logger::Warning("The animation " + std::to_string(animationId) + " has no frames, using the first animation on the sprite sheet as a fallback");
			animationsRect[animationId].push_back({ 0, 0, frameWidth, imageHeight });
			continue;
		}

		animationsRect[animationId].resize(frames);

		for (auto i = 0; i < frames; i++) {
			animationsRect[animationId][i] = { nextFrameX, 0, frameWidth, imageHeight };
			nextFrameX += frameWidth;
		}
	}
}

#ifdef _DEBUG
#endif
