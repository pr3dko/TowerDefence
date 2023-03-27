#pragma once
#include "Component.h"
#include <unordered_map>
#include <string>

class AIState;

class AIComponent : public Component
{
public:
	AIComponent(Actor* owner);

	void Update(float deltaTime) override;
	void ChangeState(const std::string& name);
	void RegisterState(AIState* state);

private:
	std::unordered_map<std::string, AIState*> mStates;
	AIState* mCurrentState;
};