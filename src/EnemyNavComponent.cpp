#include "EnemyNavComponent.h"
#include "Tile.h"

EnemyNavComponent::EnemyNavComponent(Actor* owner, bool screenWrap, int updateOrder) :
	NavComponent(owner, screenWrap, updateOrder),
	mNextTile(nullptr)
{
}

void EnemyNavComponent::SetNextTile(const Tile* tile)
{
	mNextTile = tile;
	mNextPoint = tile->GetPosition();
}

Vector2 EnemyNavComponent::GetNextPoint()
{

	mNextTile = mNextTile->GetParent();

	// If we're at the goal node, there is no next tile
	if (!mNextTile)
	{
		return Vector2();
	}

	return mNextTile->GetPosition();
}