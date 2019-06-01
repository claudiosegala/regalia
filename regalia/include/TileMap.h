#pragma once

#include <Component.h>
#include <TileSet.h>

class TileMap : public Component {
public:
	TileMap(GameObject& go, const std::string& file, TileSet* ts);

	~TileMap();

	void Load(const std::string& file);

	void SetTileSet(TileSet* ts);

	unsigned int Pos(int col, int row, int layer);

	int& At(int col, int row, int layer = 0);

	void Update(float dt) override;

	void Render() override;

	void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

	int GetWidth();

	int GetHeight();

	int GetDepth();

private:
	int mapWidth;

	int mapHeight;

	int mapDepth;

	std::vector<int> tileMatrix;

	TileSet* tileSet;
};
