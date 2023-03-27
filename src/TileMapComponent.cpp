#include "TileMapComponent.h"
#include <fstream>
#include <sstream>
#include "Actor.h"

TileMapComponent::TileMapComponent(Actor* owner, int tileWidth, int tileHeight, int drawOrder) :
	SpriteComponent(owner, drawOrder),
	mTileWidth(tileWidth),
	mTileHeight(tileHeight)
{

}

void TileMapComponent::LoadFromFile(const std::string& filePath)
{
	mTileMap.clear();

	std::ifstream file(filePath);
	if (!file.is_open())
	{
		SDL_Log("Failed to open tile map file at %s\n", filePath.c_str());
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::vector<int> temp;
		std::istringstream ss(line);
		for (int i; ss >> i; )
		{
			temp.push_back(i);
			if (ss.peek() == ',')
			{
				ss.ignore();
			}
		}

		mTileMap.emplace_back(temp);
	}
}

void TileMapComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		// Assume the owner of a tilemap component has a scale of 1.0
		SDL_Rect destRect, srcRect;
		destRect.w = srcRect.w = mTileWidth;
		destRect.h = srcRect.h = mTileHeight;

		int tileMapWidth = mTileMap[0].size() * mTileWidth;
		int tileMapHeight = mTileMap.size() * mTileHeight;

		int srcImageCols = mWidth / mTileWidth;

		for (std::vector<std::vector<int>>::size_type row = 0; row < mTileMap.size(); row++)
		{
			destRect.y = static_cast<int>(mOwner->GetPosition().y - tileMapHeight / 2 + row * mTileHeight);

			for (std::vector<int>::size_type col = 0; col < mTileMap[0].size(); col++)
			{
				destRect.x = static_cast<int>(mOwner->GetPosition().x - tileMapWidth / 2 + col * mTileWidth);
				srcRect.x = (mTileMap[row][col] % srcImageCols) * mTileWidth;
				srcRect.y = static_cast<int>(mTileMap[row][col] / srcImageCols) * mTileHeight;
				SDL_RenderCopy(renderer, mTexture, &srcRect, &destRect);
			}
		}
	}
}
