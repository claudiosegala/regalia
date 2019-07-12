#pragma once

#include <Music.h>
#include <State.h>
#include <Timer.h>
#include <TileSet.h>
#include <TileMap.h>
#include <Sprite.h>

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

	int player_count = 0;

	int alive_player_count = 0;

private:
	int field_index = 0;

	Music music;

	TileMap* tileMap = nullptr;

	void CreateField();

	void CreatePlayers();

	void CreatePlayer(Constants::PersonaType persona);

	void CreateGameTimer();

	const void CheckCollision();

	const BackgroundData& GetBackgroundData(int idx);

	const TileSetData& GetTileSetData(int idx);

	const TileMapData& GetTileMapData(int idx);

	const int GetWinnerId();

	const bool IsGameFinished();

	const void PauseSet();

	const void EndSet();

	const void LoadScoreState();
};