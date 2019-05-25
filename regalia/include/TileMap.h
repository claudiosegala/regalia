#pragma once

#include <Component.h>
#include <TileSet.h>

class TileMap : public Component {
public:
	TileMap(GameObject&, std::string, TileSet*);

	~TileMap();

	void Load(std::string);

	void SetTileSet(TileSet*);

	unsigned int Pos(int, int, int);

	int& At(int, int, int z = 0);

	void Update(float) override;

	void Render() override;

	void RenderLayer(int, int cameraX = 0, int cameraY = 0);

	int GetWidth();

	int GetHeight();

	int GetDepth();

	bool Is(std::string);

private:
	int mapWidth;

	int mapHeight;

	int mapDepth;

	std::vector<int> tileMatrix;

	TileSet* tileSet;
};
