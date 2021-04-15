#pragma once
#include "DrawBase.h"
#define FRONT 0
#define RIGHT 1
#define BACK 2
#define LEFT 3

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

#define MOV_SPD 0.005

struct Boss {
	int FACE_DIRE;
	int ATK_DIRE;
	int SHADOW_DIRE;
};
struct Player {
	Vector2Df pos;
	int SHADOW_DIRE;
};

void DrawPlatform();
void DrawBoss();
void DrawPlayer();
void DrawShadow(Vector2Df pos, int DIRE, bool large = false);