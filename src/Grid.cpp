#include "Grid.h"
#include <SDL.h>
#include "Tile.h"
#include "TileMapComponent.h"
#include "Game.h"
#include <stddef.h>
#include <algorithm>
#include "Tower.h"
#include "Enemy.h"

Grid::Grid(Game* game) :
	Actor(game),
	mSelectedTile(nullptr),
	mEnemyTimer(ENEMY_TIMER)
{
	SetPosition(Vector2(512.0f, 384.0f));

	// Load tilemap CSV files representing starting state of grid
	TileMapComponent* temp = new TileMapComponent(this, 64, 64, 1);
	temp->SetTexture(game->GetTexture("assets/towerDefense_tilesheet.png"));
	temp->LoadFromFile("assets/tilemap_layer1.csv");
	temp = new TileMapComponent(this, 64, 64, 2);
	temp->SetTexture(game->GetTexture("assets/towerDefense_tilesheet.png"));
	temp->LoadFromFile("assets/tilemap_layer2.csv");

	// Reserve space for tiles
	mTiles.resize(NUM_ROWS);
	for (size_t i = 0; i < mTiles.size(); i++)
	{
		mTiles[i].resize(NUM_COLS);
	}

	// Create tiles
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			mTiles[i][j] = new Tile(game);
			mTiles[i][j]->SetPosition(Vector2(j * TILE_SIZE + TILE_SIZE / 2.0f, i * TILE_SIZE + TILE_SIZE / 2.0f));
			if ((temp->GetTileMap())[i][j] != -1)
			{
				mTiles[i][j]->mBlocked = true;
			}
		}
	}

	GetStartTile()->SetTileState(Tile::Start);
	GetEndTile()->SetTileState(Tile::End);

	// Set up adjacency lists
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			if (i > 0)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i - 1][j]);
			}
			if (i < NUM_ROWS - 1)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i + 1][j]);
			}
			if (j > 0)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i][j - 1]);
			}
			if (j < NUM_COLS - 1)
			{
				mTiles[i][j]->mAdjacent.push_back(mTiles[i][j + 1]);
			}
		}
	}

	FindPath(GetEndTile(), GetStartTile());
	UpdatePathTiles(GetStartTile());
}

void Grid::UpdateActor(float deltaTime)
{
	mEnemyTimer -= deltaTime;
	if (mEnemyTimer < 0.0f)
	{
		Enemy* enemy = new Enemy(GetGame());
		mEnemyTimer = ENEMY_TIMER;
	}
}

Tile* Grid::GetStartTile() const
{
	return mTiles[8][0];
}

Tile* Grid::GetEndTile() const
{
	return mTiles[4][15];
}

bool Grid::FindPath(Tile* goal, Tile* start)
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			mTiles[i][j]->mG = 0.0f;
			mTiles[i][j]->mInOpenSet = false;
			mTiles[i][j]->mInClosedSet = false;
		}
	}

	std::vector<Tile*> openSet;

	Tile* current = goal;
	current->mInClosedSet = true;

	do
	{
		for (Tile* neighbour : current->mAdjacent)
		{
			if (neighbour->mBlocked)
			{
				continue;
			}

			if (!neighbour->mInClosedSet)
			{
				if (!neighbour->mInOpenSet)
				{
					neighbour->mParent = current;
					neighbour->mG = current->mG + TILE_SIZE;
					neighbour->mH = (neighbour->GetPosition() - start->GetPosition()).Magnitude();
					neighbour->mF = neighbour->mG + neighbour->mH;
					neighbour->mInOpenSet = true;
					openSet.emplace_back(neighbour);
				}
				else
				{
					float newG = current->mG + TILE_SIZE;
					if (newG < neighbour->mG)
					{
						neighbour->mG = newG;
						neighbour->mF = neighbour->mG + neighbour->mH;
						neighbour->mParent = current;
					}
				}
			}
		}

		if (openSet.empty())
		{
			break;
		}

		auto iter = std::min_element(openSet.begin(), openSet.end(),
			[](const Tile* t1, const Tile* t2) {return t1->mF < t2->mF; });

		current = *iter;
		current->mInClosedSet = true;
		current->mInOpenSet = false;
		openSet.erase(iter);
	} while (current != start);

	return current == start;
}

void Grid::ProcessClick(int x, int y)
{
	int row = static_cast<int>(y / TILE_SIZE);
	int col = static_cast<int>(x / TILE_SIZE);
	if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS)
	{
		SelectTile(row, col);
	}
}

void Grid::SelectTile(int row, int col)
{
	Tile::TileState tileState = mTiles[row][col]->GetTileState();
	if (!mTiles[row][col]->mBlocked && tileState != Tile::Start && tileState != Tile::End)
	{
		if (mSelectedTile)
		{
			mSelectedTile->ToggleSelect();
		}
		mSelectedTile = mTiles[row][col];
		mSelectedTile->ToggleSelect();
	}
}

void Grid::UpdatePathTiles(Tile* start)
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			mTiles[i][j]->SetTileState(Tile::Default);
		}
	}

	Tile* tile = start;
	while (tile != GetEndTile())
	{
		tile = tile->mParent;
		tile->SetTileState(Tile::Path);
	}

	GetStartTile()->SetTileState(Tile::Start);
	GetEndTile()->SetTileState(Tile::End);
}

void Grid::BuildTower()
{
	if (mSelectedTile && !mSelectedTile->mBlocked)
	{
		mSelectedTile->mBlocked = true;
		if (FindPath(GetEndTile(), GetStartTile()))
		{
			Tower* tower = new Tower(GetGame());
			tower->SetPosition(mSelectedTile->GetPosition());
		}
		else
		{
			mSelectedTile->mBlocked = false;
			FindPath(GetEndTile(), GetStartTile());
		}
		UpdatePathTiles(GetStartTile());
	}
}

void Grid::ActorInput(const uint8_t* keyboardState)
{
	if (keyboardState[SDL_SCANCODE_B])
	{
		BuildTower();
	}

	int x, y;
	SDL_PumpEvents();
	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		ProcessClick(x, y);
	}

}
