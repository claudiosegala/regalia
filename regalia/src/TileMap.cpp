#include <pch.h>
#include <Camera.h>
#include <Util.h>
#include <TileMap.h>

TileMap::TileMap(GameObject& go, const std::string& file, TileSet* ts)
    : Component(go)
    , tileSet(ts) {
	mapDepth = 0;
	mapHeight = 0;
	mapWidth = 0;

	Load(file);
}

TileMap::~TileMap() {
	delete tileSet;
}

void TileMap::Load(const std::string& file) {
	std::string line;
	std::ifstream fs(file);

	if (!fs.is_open()) {
		auto msg = std::string("Could not open file created file\n");
		throw std::runtime_error(msg);
	}

	getline(fs, line, ',');
	auto x = std::stoi(line);
	getline(fs, line, ',');
	auto y = std::stoi(line);
	getline(fs, line, ',');
	auto z = std::stoi(line);

	auto n = static_cast<unsigned int>(x * y * z);

	tileMatrix.resize(n);
	mapHeight = x;
	mapWidth = y;
	mapDepth = z;

	for (auto layer = 0; layer < mapDepth; layer++) {
		for (auto row = 0; row < mapHeight; row++) {
			for (auto col = 0; col < mapWidth; col++) {
				getline(fs, line, ',');
				auto idx = Pos(col, row, layer);
				tileMatrix[idx] = std::stoi(line);
				tileMatrix[idx]--;
			}
		}
	}

	fs.close();
}

void TileMap::SetTileSet(TileSet* ts) {
	delete tileSet;
	tileSet = ts;
}

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