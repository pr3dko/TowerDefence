#pragma once
#include "MoveComponent.h"
#include "Math.h"

class NavComponent : public MoveComponent
{
public:
	NavComponent(Actor* owner, bool screenWrap = true, int updateOrder = 10);

	void Update(float deltaTime) override;
	void TurnTo(const Vector2& pos);
	virtual Vector2 GetNextPoint() = 0;

protected:
	Vector2 mNextPoint;
};