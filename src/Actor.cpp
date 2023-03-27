#include "Actor.h"
#include "Component.h"
#include "Game.h"
#include <algorithm>

Actor::Actor(Game* game) :
	mState(Active),
	mPosition(),
	mScale(1.0f),
	mRotation(0.0f),
	mGame(game)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);

	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == Active)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto component : mComponents)
	{
		component->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const uint8_t* keyboardState)
{
	if (mState == Active)
	{
		for (auto component : mComponents)
		{
			component->ProcessInput(keyboardState);
		}

		ActorInput(keyboardState);
	}
}

void Actor::ActorInput(const uint8_t* keyboardState)
{
}

void Actor::AddComponent(Component* component)
{
	// Find the first component with an update order greater than this new component
	auto insertPoint = std::find_if(mComponents.begin(), mComponents.end(),
		[component](Component* existingComp) { return existingComp->GetUpdateOrder() > component->GetUpdateOrder(); }
	);

	mComponents.insert(insertPoint, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}
