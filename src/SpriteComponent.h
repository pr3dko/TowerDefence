#pragma once
#include "Component.h"
#include <SDL.h>

class SpriteComponent : public Component
{
public:
	// The lower the draw order, the further back in the scene the sprite is drawn
	SpriteComponent(Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetWidth() const { return mWidth; }
	int GetHeight() const { return mHeight;}
	int GetDrawOrder() const { return mDrawOrder; }

protected:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
	int mDrawOrder;
};