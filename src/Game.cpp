#include "Game.h"
#include <algorithm>
#include "Actor.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include "Random.h"
#include "Grid.h"
#include "Enemy.h"

Game::Game() :
	mWindow(nullptr),
	mRenderer(nullptr),
	mIsRunning(true),
	mTicksCount(0),
	mUpdatingActors(false)
{
}

bool Game::Initialise()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_Log("Failed to initialise SDL. Error: %s\n", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("SDL Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window. Error: %s\n", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer. Error: %s\n", SDL_GetError());
		return false;
	}

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		SDL_Log("Failed to initialise SDL_image. Error: %s\n", IMG_GetError());
		return false;
	}

	Random::Init();

	LoadData();

	return true;
}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		Update();
		GenerateOutput();
	}
}

void Game::Shutdown()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	for (auto texture : mTextures)
	{
		SDL_DestroyTexture(texture.second);
	}
	mTextures.clear();

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);

	IMG_Quit();
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		mPendingActors.erase(iter);
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		mActors.erase(iter);
	}

}

void Game::AddSprite(SpriteComponent* sprite)
{
	auto insertionPoint = std::find_if(mSprites.begin(), mSprites.end(),
		[sprite](SpriteComponent* sc) {return sc->GetDrawOrder() > sprite->GetDrawOrder(); });

	mSprites.insert(insertionPoint, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	if (iter != mSprites.end())
	{
		mSprites.erase(iter);
	}
}

SDL_Texture* Game::GetTexture(const std::string& filePath)
{
	auto iter = mTextures.find(filePath);
	if (iter != mTextures.end())
	{
		return iter->second;
	}
	else
	{
		SDL_Surface* surface = IMG_Load(filePath.c_str());
		if (!surface)
		{
			SDL_Log("Failed to load image at %s. Error: %s\n", filePath.c_str(), IMG_GetError());
			return nullptr;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);
		if (!texture)
		{
			SDL_Log("Failed to create texture from surface. Error: %s\n", IMG_GetError());
			return nullptr;
		}

		mTextures.emplace(filePath, texture);
		return texture;
	}
}

void Game::AddEnemy(Enemy* e)
{
	mEnemies.emplace_back(e);
}

void Game::RemoveEnemy(Enemy* e)
{
	auto iter = std::find(mEnemies.begin(), mEnemies.end(), e);
	if (iter != mEnemies.end())
	{
		mEnemies.erase(iter);
	}
}

Enemy* Game::GetNearestEnemy(const Vector2& pos) const
{
	Enemy* bestEnemy = nullptr;

	if (mEnemies.size() > 0)
	{
		float bestDistance = std::numeric_limits<float>::infinity();
		for (auto enemy : mEnemies)
		{
			// Calculate squared distance to avoid calculating a square root
			float distance = (pos - enemy->GetPosition()).MagnitudeSquared();

			if (distance < bestDistance)
			{
				bestDistance = distance;
				bestEnemy = enemy;
			}
		}
	}

	return bestEnemy;
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(keyboardState);
	}
	mUpdatingActors = false;
}

void Game::Update()
{
	// Cap frame rate to 60
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	// Calculate the time in seconds since the last frame
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	for (auto actor : mPendingActors)
	{
		mActors.emplace_back(actor);
	}
	mPendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	// Draw game
	// ---------
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	mGrid = new Grid(this);
}
