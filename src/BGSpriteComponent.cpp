#include "BGSpriteComponent.h"
#include "Actor.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder) :
	SpriteComponent(owner, drawOrder),
	mScreenSize(),
	mScrollSpeed(0.0f)
{
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	for (auto& tex : mBGTextures)
	{
		tex.mOffset.x += mScrollSpeed * deltaTime;
		if (tex.mOffset.x < -mScreenSize.x)
		{
			tex.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& tex : mBGTextures)
	{
		SDL_Rect rect;
		rect.w = static_cast<int>(mScreenSize.x);
		rect.h = static_cast<int>(mScreenSize.y);
		rect.x = static_cast<int>(mOwner->GetPosition().x - rect.w / 2 + tex.mOffset.x);
		rect.y = static_cast<int>(mOwner->GetPosition().y - rect.h / 2 + tex.mOffset.y);

		SDL_RenderCopy(renderer, tex.mTexture, nullptr, &rect);
	}
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture bgTex;
		bgTex.mTexture = tex;
		bgTex.mOffset.x = count * mScreenSize.x;
		bgTex.mOffset.y = 0;
		mBGTextures.emplace_back(bgTex);
		count++;
	}
}

void BGSpriteComponent::SetScreenSize(float width, float height)
{
	mScreenSize.x = width;
	mScreenSize.y = height;
}
