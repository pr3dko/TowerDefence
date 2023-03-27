#pragma once
#include "Actor.h"
#include <vector>
#include <string>

class Tile;
class TileMapComponent;

class Grid : public Actor
{
public:
	Grid(Game* game);

	void UpdateActor(float deltaTime) override;
	Tile* GetStartTile() const;
	Tile* GetEndTile() const;
	bool FindPath(Tile* goal, Tile* start);
	void ProcessClick(int x, int y);
	void SelectTile(int row, int col);
	void UpdatePathTiles(Tile* start);
	void BuildTower();
	void ActorInput(const uint8_t* keyboardState) override;

private:
	std::vector<std::vector<Tile*>> mTiles;
	Tile* mSelectedTile;
	float mEnemyTimer;

	const float TILE_SIZE = 64.0f;
	const float ENEMY_TIMER = 2.5f;
	const int NUM_ROWS = 12;
	const int NUM_COLS = 16;
};