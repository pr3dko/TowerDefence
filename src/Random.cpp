#include "Random.h"

std::default_random_engine Random::mEngine;

void Random::Init()
{
	std::random_device rd;
	mEngine.seed(rd());
}

Vector2 Random::GetVector(const Vector2& min, const Vector2& max)
{
	std::uniform_real_distribution<float> ux(min.x, max.x);
	std::uniform_real_distribution<float> uy(min.y, max.y);
	return Vector2(ux(mEngine), uy(mEngine));
}

float Random::GetFloat(float min, float max)
{
	std::uniform_real_distribution<float> u(min, max);
	return u(mEngine);
}

int Random::GetInt(int min, int max)
{
	std::uniform_int_distribution<int> u(min, max);
	return u(mEngine);
}
