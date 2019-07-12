#pragma once
#include <vector>
#include "SpriteSheetData.h"

class BackgroundAnimationData {
public:
	BackgroundAnimationData(SpriteSheetData* SpriteSheet, Vec2 InitialPosition, std::vector<std::pair<int, int>> IntervalRange);
	~BackgroundAnimationData();
	SpriteSheetData* SpriteSheet;
	Vec2 InitialPosition;
	std::vector<std::pair<int, int>> IntervalRange;
};
