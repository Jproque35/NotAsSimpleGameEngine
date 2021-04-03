#ifndef MATHLIB_H
#define MATHLIB_H
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class MathLib
{
public:
	static float dot(const Vector2f& first, const Vector2f& second);
	static Vector2f normalize(const Vector2f& v);
	static float magnitude(const Vector2f& v);
};

#endif

