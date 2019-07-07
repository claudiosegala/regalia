#pragma once

#include <pch.h>
#include <SpriteSheetData.h>

class BulletData {
public:
	BulletData(int shooterId, int damage, float angle, float speed, int level, const SpriteSheetData* spriteSheetData)
	    : shooterId(shooterId)
	    , damage(damage)
	    , angle(angle)
	    , speed(speed)
	    , level(level)
	    , spriteSheetData(spriteSheetData) {}

	int shooterId;
	int damage;
	float angle;
	float speed;
	int level;
	const SpriteSheetData* spriteSheetData;
};

struct TileSetData {
	int width;
	int height;
	std::string file;
};

struct TileMapData {
	std::string file;
};

struct BackgroundData {
	std::string file;
};
