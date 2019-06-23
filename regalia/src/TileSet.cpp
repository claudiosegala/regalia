#include <pch.h>
#include <TileSet.h>

TileSet::TileSet(GameObject& go, int width, int height, const std::string& file)
    : tileSet(go, file) {
	tileWidth = width;
	tileHeight = height;
	rows = tileSet.GetHeight() / height;
	columns = tileSet.GetWidth() / width;
}

void TileSet::RenderTile(unsigned int tileSetIndex, float x, float y) {
	auto n = GetQuantityTiles();

	if (tileSetIndex < n) {
		auto cols = static_cast<unsigned int>(columns);
		auto i = static_cast<int>(tileSetIndex % cols);
		auto j = static_cast<int>(tileSetIndex / cols);

		tileSet.SetClip(i * tileWidth, j * tileHeight, tileWidth, tileHeight);
		tileSet.Render(x, y);
	}
}

unsigned int TileSet::GetQuantityTiles() const {
	return static_cast<unsigned int>(rows * columns);
}

int TileSet::GetTileWidth() const {
	return tileWidth;
}

int TileSet::GetTileHeight() const {
	return tileHeight;
}