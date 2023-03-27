#pragma once
#include <vector>
#include <SDL.h>
#include <memory>
#include <SDL_image.h>
#include <unordered_map>
#include <string>
#include "Math.h"

class Actor;
class SpriteComponent;
class Grid;
class Enemy;

class Game
{
public:
	Game();

	bool Initialise();
	void RunLoop();
	void Shutdown();
	
	void AddActor(Actor* actor);
	void RemoveActor(Actor* actor);

	void AddSprite(SpriteComponent* sprite);
	void RemoveSprite(SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& filePath);

	// Game-specific
	void AddEnemy(Enemy* e);
	void RemoveEnemy(Enemy* e);
	Grid* GetGrid() const { return mGrid; }
	std::vector<Enemy*> GetEnemies() const { return mEnemies; }
	Enemy* GetNearestEnemy(const Vector2& pos) const;

private:
	void ProcessInput();
	void Update();
	void GenerateOutput();
	void LoadData();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	bool mIsRunning;
	Uint32 mTicksCount;

	std::vector<Actor*> mActors;
	std::vector<Actor*> mPendingActors;
	bool mUpdatingActors;

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<SpriteComponent*> mSprites;

	// Game-specific
	// -------------
	Grid* mGrid;
	std::vector<Enemy*> mEnemies;
};