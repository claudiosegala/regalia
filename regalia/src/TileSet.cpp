#include <pch.h>
#include <TileSet.h>

TileSet::TileSet(GameObject& go, int width, int height, std::string file) : tileSet(go, file) {
    this->rows = this->tileSet.GetHeight() / height; 
    this->columns = this->tileSet.GetWidth() / width;
    this->tileWidth = width;
    this->tileHeight = height;
}
    
void TileSet::RenderTile(unsigned int index, float x, float y) {
    auto n = GetQuantityTiles();

    if (index < n) {
        auto cols = static_cast<unsigned int>(this->columns);
        auto i = static_cast<int>(index % cols);
        auto j = static_cast<int>(index / cols);

        this->tileSet.SetClip(i * this->tileWidth, j * this->tileHeight, this->tileWidth, this->tileHeight);
        this->tileSet.Render(x, y);
    } 
}

unsigned int TileSet::GetQuantityTiles() const {
    return static_cast<unsigned int>(this->tileWidth * this->tileHeight);
}

int TileSet::GetTileWidth() const {
    return this->tileWidth;
}

int TileSet::GetTileHeight() const {
    return this->tileHeight;
}