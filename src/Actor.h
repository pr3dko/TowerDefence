#pragma once
#include "Math.h"
#include <vector>
#include <stdint.h>

class Game;
class Component;

class Actor
{
public:
	enum State {Active, Paused, Dead};

	Actor(Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	void ProcessInput(const uint8_t* keyboardState);
	virtual void ActorInput(const uint8_t* keyboardState);

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	Game* GetGame() const { return mGame; }
	State GetState() const { return mState; }
	Vector2 GetPosition() const { return mPosition; }
	float GetScale() const { return mScale; }
	float GetRotation() const { return mRotation; }
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	void SetState(State state) { mState = state; }
	void SetPosition(const Vector2& position) { mPosition = position; }
	void SetScale(float scale) { mScale = scale; }
	void SetRotation(float rotation) { mRotation = rotation; }

private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation; // radians
	std::vector<Component*> mComponents;
	Game* mGame;
};