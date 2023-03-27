#pragma once
#include "Actor.h"

class Enemy;

class Tower : public Actor
{
public:
	Tower(Game* game);
	void UpdateActor(float deltaTime) override;

private:
	float mAttackCooldown;

	const float ATTACK_COOLDOWN = 2.5f;
	const float ATTACK_RANGE = 150.0f;
};