#include <pch.h>
#include <TileSet.h>
#include <Constants.h>

TileSet::TileSet(GameObject& go, int width, int height, const std::string& file)
    : tileSet(go, file) {
	this->tileWidth = width;
	this->tileHeight = height;
	this->rows = this->tileSet.GetHeight() / height;
	this->columns = this->tileSet.GetWidth() / width;
}

void TileSet::RenderTile(unsigned int tileSetIndex, float x, float y) {
	auto n = GetQuantityTiles();

	if (tileSetIndex < n) {
		auto cols = static_cast<unsigned int>(this->columns);
		auto i = static_cast<int>(tileSetIndex % cols);
		auto j = static_cast<int>(tileSetIndex / cols);

		this->tileSet.SetClip(i * this->tileWidth, j * this->tileHeight, this->tileWidth, this->tileHeight);
		this->tileSet.Render(x, y);
	}
}

unsigned int TileSet::GetQuantityTiles() const {
	// TODO: verify this
	return static_cast<unsigned int>(this->rows * this->columns);
}

int TileSet::GetTileWidth() const {
	return this->tileWidth;
}

int TileSet::GetTileHeight() const {
	return this->tileHeight;
}