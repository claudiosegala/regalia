#pragma once

#include <pch.h>

struct BulletData {
	int shooterId;
	int damage;
	float angle;
	float speed;
	float maxDistance;
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
