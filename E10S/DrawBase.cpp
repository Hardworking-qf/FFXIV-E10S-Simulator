#include "DrawBase.h"
void DrawRect(Vector2Df p1, Vector2Df p2) {
	glBegin(GL_QUADS); {
		glVertex2f(p1.x, p1.y);
		glVertex2f(p1.x, p2.y);
		glVertex2f(p2.x, p2.y);
		glVertex2f(p2.x, p1.y);
	}; glEnd();
}

void DrawFan(Vector2Df centre, float r, float startDeg, float endDeg, int sep) {
	float deltaDeg = (endDeg - startDeg) / sep;
	glBegin(GL_TRIANGLE_FAN); {
		glVertexV(centre);
		float d = startDeg;
		for (int i = 0; i <= sep; ++i) {
			glVertex2f(centre.x + sin(d) * r, centre.y + cos(d) * r);
			d += deltaDeg;
		}
	}; glEnd();
}
