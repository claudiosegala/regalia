#include <pch.h>
#include <Camera.h>
#include <Util.h>
#include <TileMap.h>
#include <CollisionMap.h>

TileMap::TileMap(GameObject& go, const std::string& file, TileSet* ts)
    : Component(go)
    , tileSet(ts) {

	Load(file);
	SetCollisionMap();
}

TileMap::~TileMap() {
	delete tileSet;
}

void TileMap::Load(const std::string& file) {
	std::ifstream fileStream(file);

	if (!fileStream.is_open()) {
		throw std::runtime_error("Can't open file " + file);
	}

	char ignore;
	int tileValue;

	fileStream >> mapWidth >> ignore
	    >> mapHeight >> ignore
	    >> mapDepth >> ignore;

	// Read the initial positions on this tile map
	for (int i = 0; i < 4; ++i) {
		int x, y;

		fileStream >> x >> ignore
		    >> y >> ignore;

		initialPositions[i].x = float(x * 24) - 12; // Start centralized at the tile x
		initialPositions[i].y = float(y * 24);
	}

	// Randomize the initial positions
	ShuffleArray(initialPositions, 4);

	while (fileStream >> tileValue >> ignore) {
		tileMatrix.push_back(tileValue);
	}

	auto expectedSize = mapWidth * mapHeight * mapDepth;
	if (tileMatrix.size() != expectedSize) {
		throw std::runtime_error("Invalid tile matrix size");
	}

	fileStream.close();
}

void TileMap::SetCollisionMap() {
	CollisionMap::SetMap(tileMatrix, mapHeight, mapWidth);
}

void TileMap::SetTileSet(TileSet* ts) {
	delete tileSet;
	tileSet = ts;
}

// TODO: redo this, this is wrong in so many levels
unsigned int TileMap::Pos(int col, int row, int layer) {
	auto mapSize = (mapWidth * mapHeight);
	auto rowSize = (mapWidth);

	return static_cast<unsigned int>(layer * mapSize + row * rowSize + col);
}

int& TileMap::At(int col, int row, int layer) {
	auto idx = Pos(col, row, layer);
	return tileMatrix[idx];
}

void TileMap::Update(unsigned dt) {
	UNUSED(dt);
}

void TileMap::Render() {
	for (int k = 0; k < mapDepth; k++) {
		RenderLayer(k, (int)Camera::pos.x, (int)Camera::pos.y);
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
	auto tileHeight = tileSet->GetTileHeight();
	auto tileWidth = tileSet->GetTileWidth();
	for (int row = 0; row < mapHeight; row++) {
		for (int col = 0; col < mapWidth; col++) {
			auto tileSetIdx = (unsigned int)At(col, row, layer);
			tileSet->RenderTile(tileSetIdx, (float)(col * tileWidth - cameraY), (float)(row * tileHeight - cameraX));
		}
	}
}

int TileMap::GetWidth() {
	return mapWidth;
}

int TileMap::GetHeight() {
	return mapHeight;
}

int TileMap::GetDepth() {
	return mapDepth;
}

Vec2 TileMap::GetPlayerInitialPosition(int id) {
	return initialPositions[id];
}
