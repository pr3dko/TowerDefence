#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Math.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) :
	Component(owner),
	mTexture(nullptr),
	mWidth(0),
	mHeight(0),
	mDrawOrder(drawOrder)
{
	mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (mTexture)
	{
		SDL_Rect rect;
		rect.w = static_cast<int>(mWidth * mOwner->GetScale());
		rect.h = static_cast<int>(mHeight * mOwner->GetScale());
		rect.x = static_cast<int>(mOwner->GetPosition().x - rect.w / 2);
		rect.y = static_cast<int>(mOwner->GetPosition().y - rect.h / 2);

		SDL_RenderCopyEx(renderer, mTexture, nullptr, &rect, -Math::RadiansToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mWidth, &mHeight);
}
