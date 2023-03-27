#include "AIComponent.h"
#include "AIState.h"
#include <SDL.h>

AIComponent::AIComponent(Actor* owner) :
	Component(owner),
	mCurrentState(nullptr)
{
}

void AIComponent::Update(float deltaTime)
{
	if (mCurrentState)
	{
		mCurrentState->Update(deltaTime);
	}
}

void AIComponent::ChangeState(const std::string& name)
{
	if (mCurrentState)
	{
		mCurrentState->OnExit();
	}

	auto iter = mStates.find(name);
	if (iter != mStates.end())
	{
		mCurrentState = iter->second;
		mCurrentState->OnEnter();
	}
	else
	{
		SDL_Log("Error: could not find state %s\n", name.c_str());
		mCurrentState = nullptr;
	}
}

void AIComponent::RegisterState(AIState* state)
{
	mStates.emplace(state->GetName(), state);
}
