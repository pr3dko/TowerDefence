#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* owner, bool screenWrap, int updateOrder) :
	Component(owner, updateOrder),
	mForwardSpeed(0.0f),
	mAngularSpeed(0.0f),
	mScreenWrap(screenWrap)
{
}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		float rotation = mOwner->GetRotation();
		rotation += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rotation);
	}

	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 position = mOwner->GetPosition();
		position += mOwner->GetForward() * mForwardSpeed * deltaTime;

		if (mScreenWrap)
		{
			if (position.x < 0.0f)
			{
				position.x = 1024.0f;
			}
			else if (position.x > 1024.0f)
			{
				position.x = 0.0f;
			}
			if (position.y < 0.0f)
			{
				position.y = 768.0f;
			}
			else if (position.y > 768.0f)
			{
				position.y = 0.0f;
			}
		}
	    else
		{
			if (position.x < 0.0f || position.x > 1024.0f || position.y < 0.0f || position.y > 768.0f)
			{
				mOwner->SetState(Actor::Dead);
			}
		}
		
		mOwner->SetPosition(position);
	}
}
