#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner) :
	Component(owner),
	mRadius(0.0f)
{
}

Vector2 CircleComponent::GetCentre() const
{
	return mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b)
{
	Vector2 diff = a.GetCentre() - b.GetCentre();
	float diffSquared = diff.MagnitudeSquared();

	float sumOfRadiiSquared = a.GetRadius() + b.GetRadius();
	sumOfRadiiSquared *= sumOfRadiiSquared;

	return diffSquared <= sumOfRadiiSquared;
}
