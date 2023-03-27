#include "AnimSpriteComponent.h"
#include <algorithm>

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder) :
	SpriteComponent(owner, drawOrder),
	mCurrFrame(0.0f),
	mAnimFPS(24.0f)
{
}

void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		mCurrFrame += mAnimFPS * deltaTime;

		if (mCurrAnim.mLooping)
		{
			while (mCurrFrame >= mCurrAnim.mStartFrame + mCurrAnim.mFrameCount)
			{
				mCurrFrame -= mCurrAnim.mFrameCount;
			}
		}
		else if (mCurrFrame >= mCurrAnim.mStartFrame + mCurrAnim.mFrameCount)
		{
			mCurrFrame = static_cast<float>(mCurrAnim.mStartFrame + mCurrAnim.mFrameCount - 1);
		}

		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*>& textures)
{
	mAnimTextures = textures;
	if (mAnimTextures.size() > 0)
	{
		mCurrFrame = 0.0f;
		SetTexture(mAnimTextures[0]);
	}
}

void AnimSpriteComponent::AddAnim(const std::string& name, int startFrame, int frameCount, bool looping)
{
	mAnims.emplace_back(AnimData{ name, startFrame, frameCount, looping });

	mCurrAnim = mAnims.back();
	mCurrFrame = static_cast<float>(startFrame);
}

void AnimSpriteComponent::SetAnim(const std::string& name)
{
	if (mCurrAnim.mName != name)
	{
		auto iter = std::find_if(mAnims.begin(), mAnims.end(),
			[name](const AnimData& anim) {return anim.mName == name; });
		if (iter != mAnims.end())
		{
			mCurrAnim = *iter;
			mCurrFrame = static_cast<float>(mCurrAnim.mStartFrame);
		}
		else
		{
			SDL_Log("Error: no animation with name %s exists.\n", name.c_str());
		}
	}
}
	
