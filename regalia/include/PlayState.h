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

	void LoadAssets() override;

	void Update(unsigned dt) override;

	void Render() override;

	void Start() override;

	void Pause() override;

	void Resume() override;

private:
	int field_index = 0;

	Music music;

	void CheckCollision();

	void CreateField();

	void CreatePlayers();

	void CreatePlayer();

	void CreateGameTimer();

	const BackgroundData& GetBackgroundData(int rnd);

	const TileSetData& GetTileSetData(int rnd);

	const TileMapData& GetTileMapData(int rnd);

	void LoadScoreState();
};