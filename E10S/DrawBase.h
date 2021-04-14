#pragma once
#define PI 3.1415926535898

#include <GL/glut.h>
#include "Vector2Df.h"
#include <math.h>

#define glVertexV(v) glVertex2f(v.x, v.y)

void DrawRect(Vector2Df p1, Vector2Df p2);
void DrawFan(Vector2Df centre, float r, float startDeg, float endDeg, int sep = 20);