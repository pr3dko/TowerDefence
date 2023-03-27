#pragma once
#include "SpriteComponent.h"
#include <vector>
#include <string>

class AnimSpriteComponent : public SpriteComponent
{
public:
	AnimSpriteComponent(Actor* owner, int drawOrder = 100);

	void Update(float deltaTime) override;

	float GetAnimFPS() const { return mAnimFPS; }

	void SetAnimTextures(const std::vector<SDL_Texture*>& textures);
	void SetAnimFPS(float fps) { mAnimFPS = fps; }

	void AddAnim(const std::string& name, int startFrame, int frameCount, bool looping = true);
	void SetAnim(const std::string& name);

private:
	struct AnimData
	{
		std::string mName;
		int mStartFrame;
		int mFrameCount;
		bool mLooping = true;
	} mCurrAnim;
	std::vector<SDL_Texture*> mAnimTextures;
	std::vector<AnimData> mAnims;
	float mCurrFrame;
	float mAnimFPS;
};