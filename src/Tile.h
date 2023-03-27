#pragma once
#include "Actor.h"
#include <vector>

class SpriteComponent;

class Tile : public Actor
{
	friend class Grid;
public:
	enum TileState {Default, Path, Start, End};

	Tile(Game* game);

	void SetTileState(TileState state);

	TileState GetTileState() const { return mTileState; }
	const Tile* GetParent() const { return mParent; }

	void ToggleSelect();

private:
	void UpdateTexture();

	// Data needed for A* pathfinding algorithm
	std::vector<Tile*> mAdjacent;
	Tile* mParent;
	float mF;
	float mG;
	float mH;
	bool mInOpenSet;
	bool mInClosedSet;
	bool mBlocked;

	SpriteComponent* mSprite;
	TileState mTileState;
	bool mSelected;
};