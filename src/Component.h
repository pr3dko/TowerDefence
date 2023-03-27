#pragma once
#include <stdint.h>

class Actor;

class Component
{
public:
	// The lower the update order, the sooner this component is updated
	Component(Actor* owner, int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime);
	virtual void ProcessInput(const uint8_t* keyboardState);

	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	Actor* mOwner;
	int mUpdateOrder;
};