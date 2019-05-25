#pragma once

#include <Music.h>
#include <State.h>
#include <Timer.h>
#include <TileSet.h>
#include <TileMap.h>
#include <Sprite.h>

// TODO: add animation of Ready? Go!

class PlayState : public State {
public:
	PlayState();

	~PlayState();

	void LoadAssets();

	void Update(float);

	void Render();

	void Start();

	void Pause();

	void Resume();

private:

	int backgroundIdx;

	int tileSetIdx;

	int tileMapIdx;

	Timer roundTimer;

	Music music;
	
	void CreateField();

	void CreatePlayers();

	Sprite* BuildBackground(GameObject* gameObject, int rnd);

	TileSet* BuildTileSet(GameObject* gameObject, int rnd);

	TileMap* BuildTileMap(GameObject* gameObject, TileSet* tileSet);

};