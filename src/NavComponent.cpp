#include "NavComponent.h"
#include "Tile.h"

NavComponent::NavComponent(Actor* owner, bool screenWrap, int updateOrder) :
	MoveComponent(owner, screenWrap, updateOrder)
{

}

void NavComponent::Update(float deltaTime)
{
	Vector2 diff = mNextPoint - mOwner->GetPosition();
	if (diff.Magnitude() <= 2.0f)
	{
		mNextPoint = GetNextPoint();
		TurnTo(mNextPoint);
	}

	MoveComponent::Update(deltaTime);
}

void NavComponent::TurnTo(const Vector2& pos)
{
	Vector2 diff = pos - mOwner->GetPosition();
	float rotation = Math::Atan2(-diff.y, diff.x);
	mOwner->SetRotation(rotation);
}
