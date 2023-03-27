#include "Bullet.h"
#include "CircleComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "MoveComponent.h"
#include "Enemy.h"

Bullet::Bullet(Game* game) :
	Actor(game),
	mCircle(nullptr),
	mDamage(2.0f)
{
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.0f);

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("assets/bullet.png"));

	MoveComponent* mc = new MoveComponent(this, false);
	mc->SetForwardSpeed(200.0f);

	SetScale(0.8f);
}

void Bullet::UpdateActor(float deltaTime)
{
	// Check for collisions with enemies
	for (auto enemy : GetGame()->GetEnemies())
	{
		if (Intersect(*mCircle, *(enemy->GetCircle())))
		{
			enemy->TakeHit(mDamage);
			SetState(Actor::Dead);
		}
	}
}