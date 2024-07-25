#include "myOpenGL.h"
void myShowDirection() {//»æÖÆ×ø±êÏµ
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2i(-1000, 0);
	glVertex2i(1000, 0);

	glColor3f(0, 1, 0);
	glVertex2i(0, 1000);
	glVertex2i(0, -1000);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 1000);
	glVertex3f(0, 0, -1000);
	glEnd();
}