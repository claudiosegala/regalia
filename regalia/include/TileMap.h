#pragma once

#include <Component.h>
#include <TileSet.h>

class TileMap : public Component {
public:
	TileMap(GameObject&, const std::string&, TileSet*);

	~TileMap();

	void Load(const std::string&);

	void SetTileSet(TileSet*);

	unsigned int Pos(int, int, int);

	int& At(int, int, int z = 0);

	void Update(float dt) override;

	void Render() override;

	void RenderLayer(int, int cameraX = 0, int cameraY = 0);

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
