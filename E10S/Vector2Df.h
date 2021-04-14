#pragma once
struct Vector2Df {
	float x;
	float y;
	Vector2Df operator+(const Vector2Df& p) {
		return Vector2Df{ this->x + p.x, this->y + p.y };
	}
	Vector2Df operator-(const Vector2Df& p) {
		return Vector2Df{ this->x - p.x, this->y - p.y };
	}
	Vector2Df operator*(float a) {
		return Vector2Df{ this->x *a, this->y*a };
	}
	void operator+=(const Vector2Df& p) {
		*this = *this + p;
	}
};