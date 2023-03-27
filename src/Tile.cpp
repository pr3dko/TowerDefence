#include "Tile.h"
#include "SpriteComponent.h"
#include "Game.h"

Tile::Tile(Game* game) :
	Actor(game),
	mParent(nullptr),
	mF(0.0f),
	mG(0.0f),
	mH(0.0f),
	mInOpenSet(false),
	mInClosedSet(false),
	mBlocked(false),
	mSprite(nullptr),
	mTileState(Default),
	mSelected(false)
{
	mSprite = new SpriteComponent(this);
	UpdateTexture();
}

void Tile::SetTileState(TileState state)
{
	mTileState = state;
	UpdateTexture();
}

void Tile::ToggleSelect()
{
	mSelected = !mSelected;
	UpdateTexture();
}

void Tile::UpdateTexture()
{
	switch (mTileState)
	{
		case Default:
			if (mSelected)
				mSprite->SetTexture(GetGame()->GetTexture("assets/towerDefense_tile015.png"));
			else
				mSprite->SetTexture(nullptr);
			break;
		case Path:
			if (mSelected)
				mSprite->SetTexture(GetGame()->GetTexture("assets/towerDefense_tile015.png"));
			else
				mSprite->SetTexture(GetGame()->GetTexture("assets/towerDefense_tile020.png"));
			break;
		case Start:
			mSprite->SetTexture(GetGame()->GetTexture("assets/towerDefense_tile201.png"));
			break;
		case End:
			mSprite->SetTexture(GetGame()->GetTexture("assets/towerDefense_tile086.png"));
			break;
			
	}
}
