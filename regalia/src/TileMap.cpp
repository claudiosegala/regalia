#include <pch.h>
#include <TileMap.h>
#include <Camera.h>
#include <Constants.h>

TileMap::TileMap(GameObject& go, std::string file, TileSet* ts) : Component(go), tileSet(ts) {
	this->mapDepth = 0;
	this->mapHeight = 0;
	this->mapWidth = 0;
	
	Load(file);
}

TileMap::~TileMap () {
    delete this->tileSet;
}

void TileMap::Load(std::string file) {
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
    this->mapDepth = z;
    this->mapHeight = y;
    this->mapWidth = x;

    for (auto k = 0; k < z; k++){
        for (auto i = 0; i < x; i++){
            for (auto j = 0; j < y; j++){
                getline(fs, line, ',');
                auto idx = Pos(j, i, k);
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

unsigned int TileMap::Pos(int x, int y, int z) {
    auto mapSize = (this->mapWidth * this->mapHeight);
    auto columnSize = (this->mapWidth);

    return static_cast<unsigned int>(z * mapSize + y * columnSize + x);
}

int& TileMap::At(int x, int y, int z) {
    auto idx = Pos(x, y, z);
    return this->tileMatrix[idx];
}

void TileMap::Update (float dt) {
    UNUSED(dt);
}

void TileMap::Render() {
    for (int k = 0; k < this->mapDepth; k++) {
        RenderLayer(k, (int) Camera::pos.x, (int) Camera::pos.y);
    }
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for (int i = 0; i < this->mapHeight; i++) {
        for (int j = 0; j < this->mapWidth; j++) {
            auto idx = (unsigned int) At(i, j, layer);
            auto x = i * this->tileSet->GetTileWidth() - cameraX;
            auto y = j * this->tileSet->GetTileHeight() - cameraY;

            tileSet->RenderTile(idx, (float) x, (float) y);
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

bool TileMap::Is (std::string type) {
    return (type == "TileMap");
}