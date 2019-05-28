#include <pch.h>
#include <Camera.h>
#include <Util.h>
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

	this->tileMatrix.resize(n);
	this->mapHeight = x;
	this->mapWidth = y;
	this->mapDepth = z;

	for (auto layer = 0; layer < this->mapDepth; layer++) {
		for (auto row = 0; row < this->mapHeight; row++) {
			for (auto col = 0; col < this->mapWidth; col++) {
				getline(fs, line, ',');
				auto idx = Pos(col, row, layer);
				this->tileMatrix[idx] = std::stoi(line);
				this->tileMatrix[idx]--;
			}
		}
	}

	fs.close();
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