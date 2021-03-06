#pragma once

#include <Component.h>
#include <TileSet.h>

class TileMap : public Component {
public:
	TileMap(GameObject& go, const std::string& file);

	~TileMap();

	void Load(const std::string& file);

	void SetTileSet(TileSet* ts);

	unsigned int Pos(int col, int row, int layer);

	int& At(int col, int row, int layer = 0);

	void Update(unsigned dt) override;

	void Render() override;

	void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

	int GetWidth();

	int GetHeight();

	int GetDepth();

	Vec2 GetPlayerInitialPosition(int id);

private:
	int mapWidth = 0;

	int mapHeight = 0;

	int mapDepth = 0;

	std::vector<int> tileMatrix;

	TileSet* tileSet;

	void SetCollisionMap();

	Vec2 initialPositions[4];

	std::string tileSetFile;
};
