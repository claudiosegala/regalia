#pragma once

#include <Component.h>
#include <GameObject.h>
#include <Logger.h>
#include <TileSet.h>
#include <Constants.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

class TileMap : public Component {
    public:

        TileMap(GameObject&, std::string, TileSet*);

        ~TileMap();

        void Load(std::string);

        void SetTileSet(TileSet*);

        unsigned int Pos(int, int, int);

        int& At(int, int, int z = 0);

        void Update(float);

        void Render();

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