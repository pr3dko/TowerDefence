#pragma once
#include "NavComponent.h"

class Tile;

class EnemyNavComponent : public NavComponent
{
public:
	EnemyNavComponent(Actor* owner, bool screenWrap = true, int updateOrder = 10);

	void SetNextTile(const Tile* tile);
	Vector2 GetNextPoint() override;

private:
	const Tile* mNextTile;
};