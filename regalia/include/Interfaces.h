#pragma once

#include <pch.h>
#include <SpriteSheetData.h>
#include <Constants.h>

namespace Constants {
enum class PersonaType;
}

class BulletData {
public:
	BulletData(int shooterId, int damage, float angle, int level, const SpriteSheetData* spriteSheetData, Constants::PersonaType personaType)
	    : shooterId(shooterId)
	    , damage(damage)
	    , angle(angle)
	    , level(level)
	    , spriteSheetData(spriteSheetData)
	    , personaType(personaType) {}

	int shooterId;
	int damage;
	float angle;
	int level;
	const SpriteSheetData* spriteSheetData;
	Constants::PersonaType personaType;
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
