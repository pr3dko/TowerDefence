#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	MoveComponent(Actor* owner, bool screenWrap = true, int updateOrder = 10);

	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }

private:
	float mAngularSpeed; // radians/second
	float mForwardSpeed; // pixels/second
	bool mScreenWrap;
};