#include "MathLib.h"

float MathLib::dot(const Vector2f& first, const Vector2f& second) {
	return first.x * second.x + first.y * second.y;
}

Vector2f MathLib::normalize(const Vector2f& v) {

	float magnitude = MathLib::magnitude(v);
	
	return Vector2f(v.x / magnitude, v.y / magnitude);

}

float MathLib::magnitude(const Vector2f& v) {
	return sqrt(v.x * v.x + v.y * v.y);
}