#pragma once

class AnimationData {
public:
	AnimationData(int id, int numberOfFrames);

	int id;
	int numberOfFrames;
};

class SpriteSheetData {
public:
	SpriteSheetData(const std::string& file, int width, int height, float frameTime, const std::vector<AnimationData>& animations);

	std::string file;
	float frameTime;

	inline SDL_Rect getAnimationRect(int animationId, int frame) {
		assert(animationId >= 0 && animationId < animationsRect.size());
		assert(frame >= 0 && frame < animationsRect[animationId].size());
		return animationsRect[animationId][frame];
	};

	inline int getNumberOfFrames(int animationId) {
		assert(animationId >= 0 && animationId < animationsRect.size());
		return int(animationsRect[animationId].size());
	}

// Only check in DEBUG mode
#ifdef _DEBUG
#else
#endif

private:
	std::vector<std::vector<SDL_Rect>> animationsRect;

	int width, height;
};