#include "Tower.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "Game.h"
#include <algorithm>
#include "Enemy.h"
#include "Bullet.h"

Tower::Tower(Game* game) :
	Actor(game),
	mAttackCooldown(ATTACK_COOLDOWN)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("assets/tower_single.png"));
}

void Tower::UpdateActor(float deltaTime)
{
	mAttackCooldown -= deltaTime;

	// turn to face nearest enemy
	Enemy* nearestEnemy = GetGame()->GetNearestEnemy(GetPosition());
	if (nearestEnemy)
	{
		Vector2 diff = nearestEnemy->GetPosition() - GetPosition();
		float rotation = Math::Atan2(-diff.y, diff.x);
		SetRotation(rotation);

		if (mAttackCooldown <= 0.0f && diff.Magnitude() <= ATTACK_RANGE)
		{
			Bullet* bullet = new Bullet(GetGame());
			bullet->SetPosition(GetPosition() + GetForward() * 20.0f);
			bullet->SetRotation(GetRotation());
			mAttackCooldown = ATTACK_COOLDOWN;
		}
	}
	SDL_Log("%f\n", mAttackCooldown);

}
