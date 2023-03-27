#include "InputComponent.h"

InputComponent::InputComponent(Actor* owner) :
	MoveComponent(owner),
	mMaxForwardSpeed(0.0f),
	mMaxAngularSpeed(0.0f),
	mForwardKey(0),
	mBackwardKey(0),
	mClockwiseKey(0),
	mAntiClockwiseKey(0)
{

}

void InputComponent::ProcessInput(const uint8_t* keyboardState)
{
	float forwardSpeed = 0.0f;
	if (keyboardState[mForwardKey])
	{
		forwardSpeed += mMaxForwardSpeed;
	}
	if (keyboardState[mBackwardKey])
	{
		forwardSpeed -= mMaxForwardSpeed;
	}
	SetForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (keyboardState[mAntiClockwiseKey])
	{
		angularSpeed += mMaxAngularSpeed;
	}
	if (keyboardState[mClockwiseKey])
	{
		angularSpeed -= mMaxAngularSpeed;
	}
	SetAngularSpeed(angularSpeed);
}
