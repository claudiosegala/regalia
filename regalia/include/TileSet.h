#pragma once

#include <Sprite.h>

class TileSet {
public:
	TileSet(GameObject& go, int width, int height, const std::string& file);

	void RenderTile(unsigned int tileSetIndex, float x, float y);

	unsigned int GetQuantityTiles() const;

	int GetTileWidth() const;

	int GetTileHeight() const;

private:
	Sprite tileSet;

	int rows;

	int columns;

	int tileWidth;

	int tileHeight;
};
