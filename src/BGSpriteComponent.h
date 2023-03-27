#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <vector>

class BGSpriteComponent : public SpriteComponent
{
public:
	BGSpriteComponent(Actor* owner, int drawOrder = 10);

	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;

	void SetBGTextures(const std::vector<SDL_Texture*>& textures);
	void SetScreenSize(float width, float height);
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }

private:
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};