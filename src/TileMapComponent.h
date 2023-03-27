#pragma once
#include "SpriteComponent.h"
#include <string>
#include <vector>

class TileMapComponent : public SpriteComponent
{
public:
	TileMapComponent(Actor* owner, int tileWidth, int tileHeight, int drawOrder = 10);
	
	void LoadFromFile(const std::string& filePath);
	void Draw(SDL_Renderer* renderer) override;
	const std::vector<std::vector<int>>& GetTileMap() const { return mTileMap; }

private:
	std::vector<std::vector<int>> mTileMap;
	int mTileWidth;
	int mTileHeight;
};