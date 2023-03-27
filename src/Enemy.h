#pragma once
#include "Actor.h"

class CircleComponent;

class Enemy : public Actor
{
public:
	Enemy(Game* game);
	~Enemy();

	void UpdateActor(float deltaTime) override;
	CircleComponent* GetCircle() const { return mCircle; }
	void TakeHit(float damage);

private:
	CircleComponent* mCircle;
	float mHealth;
};