#include "Enemy.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Grid.h"
#include "Tile.h"
#include "CircleComponent.h"
#include "EnemyNavComponent.h"

Enemy::Enemy(Game* game) :
	Actor(game),
	mHealth(5.0f)
{
	game->AddEnemy(this);

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("assets/enemy.png"));

	// Every enemy spawns on the start tile
	SetPosition(game->GetGrid()->GetStartTile()->GetPosition());

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(15.0f);

	EnemyNavComponent* enc = new EnemyNavComponent(this);
	enc->SetNextTile(game->GetGrid()->GetStartTile()->GetParent());
	enc->SetForwardSpeed(100.0f);
}

Enemy::~Enemy()
{
	GetGame()->RemoveEnemy(this);
}

void Enemy::UpdateActor(float deltaTime)
{
	// Destroy actor if it reaches the end tile
	Vector2 diff = GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition();
	if (Math::NearZero(diff.Magnitude(), 10.0f))
	{
		SetState(Dead);
	}
}

void Enemy::TakeHit(float damage)
{
	mHealth -= damage;
	if (mHealth <= 0.0f)
	{
		SetState(Actor::Dead);
	}
}
