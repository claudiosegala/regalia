#pragma once

#include <Util.h>

class SpriteSheetData {
public:
	SpriteSheetData(const std::string& file, int imageWidth, int imageHeight, float frameTime, int totalAnimations, const std::map<int, int>& animationsFrames, bool selfDestruct = false);
	SpriteSheetData(const SpriteSheetData& other) = delete;

	std::string file;
	float frameTime;
	bool selfDestruct;

	inline SDL_Rect GetAnimationRect(int animationId, int frame) const {
		assert(animationId >= 0 && animationId < int(animationsRect.size()));
		assert(frame >= 0 && frame < int(animationsRect[animationId].size()));
		return animationsRect[animationId][frame];
	}

	inline int GetNumberOfFrames(int animationId) const {
		assert(animationId >= 0 && animationId < int(animationsRect.size()));
		return int(animationsRect[animationId].size());
	}

	inline int GetImageWidth() const {
		return this->imageWidth;
	}

	inline int GetFrameWidth() const {
		return this->frameWidth;
	}

	inline int GetFrameHeight() const {
		return this->imageHeight;
	}

	inline void AssertSize(int width, int height) const {
		assert(width == this->imageWidth);
		assert(height == this->imageHeight);
		UNUSED(width);
		UNUSED(height);
	};

private:
	std::vector<std::vector<SDL_Rect>> animationsRect;

	int imageWidth, imageHeight, frameWidth;
};