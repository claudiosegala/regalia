#include "pch.h"
#include "BackgroundAnimationData.h"
#include <utility>

BackgroundAnimationData::BackgroundAnimationData(SpriteSheetData* SpriteSheet, Vec2 InitialPosition,
    std::vector<std::pair<int, int>> IntervalRange)
    : SpriteSheet(SpriteSheet)
    , InitialPosition(InitialPosition)
    , IntervalRange(std::move(IntervalRange)) {
}

BackgroundAnimationData::~BackgroundAnimationData() {
	delete SpriteSheet;
}
