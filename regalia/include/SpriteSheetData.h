#pragma once


class SpriteSheetData {
public:
	SpriteSheetData(const std::string& file, int imageWidth, int imageHeight, float frameTime, int totalAnimations, const std::map<int, int>& animationsFrames, bool selfDestruct = false);

	std::string file;
	float frameTime;
	bool selfDestruct;

	inline SDL_Rect GetAnimationRect(int animationId, int frame) const {
		assert(animationId >= 0 && animationId < animationsRect.size());
		assert(frame >= 0 && frame < animationsRect[animationId].size());
		return animationsRect[animationId][frame];
	}

	inline int GetNumberOfFrames(int animationId) const {
		assert(animationId >= 0 && animationId < animationsRect.size());
		return int(animationsRect[animationId].size());
	}

	inline int GetFrameWidth() const {
		return frameWidth;
	}

	inline int GetFrameHeight() const {
		return imageHeight;
	}

	inline void AssertSize(int width, int height) const {
		assert(width == imageWidth);
		assert(height == imageHeight);
	};

private:
	std::vector<std::vector<SDL_Rect>> animationsRect;

	int imageWidth, imageHeight, frameWidth;
};