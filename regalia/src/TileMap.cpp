#include <pch.h>
#include <Camera.h>
#include <Constants.h>
#include <TileMap.h>

TileMap::TileMap(GameObject& go, const std::string& file, TileSet* ts)
    : Component(go)
    , tileSet(ts) {
	this->mapDepth = 0;
	this->mapHeight = 0;
	this->mapWidth = 0;

	Load(file);
}

TileMap::~TileMap() {
	delete this->tileSet;
}

void TileMap::Load(const std::string& file) {
	std::ifstream fs(file);
	char c;
	fs >> mapWidth >> c;
	fs >> mapHeight >> c;
	fs >> mapDepth >> c;

	const size_t mapSize = mapWidth * mapHeight * mapDepth;

	tileMatrix.clear();
	tileMatrix.reserve(mapSize);

	while (tileMatrix.size() < tileMatrix.capacity()) {
		int tile;
		fs >> tile >> c;
		tileMatrix.push_back(tile - 1);
	}

	if (tileMatrix.size() != mapSize) {
		throw std::runtime_error("Bad tile map: " + file);
	}
}

void TileMap::SetTileSet(TileSet* ts) {
	delete this->tileSet;
	this->tileSet = ts;
}

unsigned int TileMap::Pos(int col, int row, int layer) {
	auto mapSize = (this->mapWidth * this->mapHeight);
	auto rowSize = (this->mapWidth);

	return static_cast<unsigned int>(layer * mapSize + row * rowSize + col);
}

int& TileMap::At(int col, int row, int layer) {
	auto idx = Pos(col, row, layer);
	return this->tileMatrix[idx];
}

void TileMap::Update(float dt) {
	UNUSED(dt);
}

void TileMap::Render() {
	for (int k = 0; k < this->mapDepth; k++) {
		RenderLayer(k, (int)Camera::pos.x, (int)Camera::pos.y);
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	auto tileHeight = this->tileSet->GetTileHeight();
	auto tileWidth = this->tileSet->GetTileWidth();
	for (int row = 0; row < this->mapHeight; row++) {
		for (int col = 0; col < this->mapWidth; col++) {
			auto tileSetIdx = (unsigned int)At(col, row, layer);
			tileSet->RenderTile(tileSetIdx, (float)(col * tileWidth - cameraY), (float)(row * tileHeight - cameraX));
		}
	}
}

int TileMap::GetWidth() {
	return this->mapWidth;
}

int TileMap::GetHeight() {
	return this->mapHeight;
}

int TileMap::GetDepth() {
	return this->mapDepth;
}