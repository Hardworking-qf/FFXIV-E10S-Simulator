#pragma once
#include "Vector2Df.h"
struct Rect {
	Vector2Df a, b;
	bool isContains(Vector2Df p) {
		int minx, maxx, miny, maxy;
		if (a.x > b.x) {
			maxx = a.x;
			minx = b.x;
		}
		else {
			maxx = b.x;
			minx = a.x;
		}
		if (a.y > b.y) {
			maxy = a.y;
			miny = b.y;
		}
		else {
			maxy = b.y;
			miny = a.y;
		}
		return minx <= p.x && p.x <= maxx && miny <= p.y && p.y <= maxy;
	}
};