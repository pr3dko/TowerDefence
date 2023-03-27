#pragma once
#include <random>
#include "Math.h"

class Random
{
public:
	static void Init();
	static Vector2 GetVector(const Vector2& min, const Vector2& max);
	static float GetFloat(float min, float max);
	static int GetInt(int min, int max);

private:
	static std::default_random_engine mEngine;
};