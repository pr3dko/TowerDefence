#pragma once
#include "Actor.h"

class CircleComponent;

class Bullet : public Actor
{
public:
	Bullet(Game* game);

	void UpdateActor(float deltaTime);


private:
	CircleComponent* mCircle;
	float mDamage;
};