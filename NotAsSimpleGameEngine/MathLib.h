#ifndef MATHLIB_H
#define MATHLIB_H
#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

namespace MathLib {
	const float dot(const Vector2f& first, const Vector2f& second);
	const Vector2f normalize(const Vector2f& v);
	const float magnitude(const Vector2f& v);
};

#endif

