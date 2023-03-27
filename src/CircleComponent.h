#pragma once
#include "Component.h"
#include "Math.h"

class CircleComponent : public Component
{
public:
	CircleComponent(Actor* owner);

	Vector2 GetCentre() const;

	void SetRadius(float radius) { mRadius = radius; }
	float GetRadius() const { return mRadius; }

private:
	float mRadius;
};

bool Intersect(const CircleComponent& a, const CircleComponent& b);