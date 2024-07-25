#define _CRT_SECURE_NO_WARNINGS
#include "myGraphic.h"
#include <GL/glut.h>

//����һ������ϵ,len�ǳ��ȣ�arrayW�Ǽ�ͷ�����ȣ�arrayH�Ǽ�ͷ��ֱ���򳤶ȣ�kind����ʽ
//kind>0ʱ�м�ͷ
void myDrawDirection(float len, float arrayW, float arrayH, int kind) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-len, 0, 0);
	glVertex3f(len, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, len, 0);
	glVertex3f(0, -len, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, len);
	glVertex3f(0, 0, -len);
	glEnd();

	if (kind > 0) {
		glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex3f(len - arrayW, arrayH, 0);
		glVertex3f(len, 0, 0);
		glVertex3f(len - arrayW, -arrayH, 0);
		glVertex3f(len, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, len, 0);
		glVertex3f(arrayH, len - arrayW, 0);
		glVertex3f(0, len, 0);
		glVertex3f(-arrayH, len - arrayW, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, len);
		glVertex3f(0, arrayH, len - arrayW);
		glVertex3f(0, 0, len);
		glVertex3f(0, -arrayH, len - arrayW);
		glEnd();
	}

	glPopMatrix();
}

//����һ��Բ��r�ǰ뾶��div�Ǿ�ϸ�̶�
void myDrawCircle(float r, int div) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	float dx = 360.0 / div / 180 * 3.1415926;
	glBegin(GL_LINE_LOOP);
	for (int i = 0;i < div;i++) {
		glVertex3f(r * cos(dx * i), 0, r * sin(dx * i));
	}
	glEnd();

	glPopMatrix();
}
void myDrawSolidCircle(float r, int div) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	float dx = 360.0 / div / 180 * 3.1415926;
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0;i < div;i++) {
		glVertex3f(r * cos(dx * i), 0, r * sin(dx * i));
	}
	glEnd();

	glPopMatrix();
}

//����һ��ʵ��Բ׶������y��
void myDrawSolidCone(float r, float h, int div) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glRotatef(-90, 1, 0, 0);
	glutSolidCone(r, h, div, div);

	glPopMatrix();
}
//�߿�Բ׶
void myDrawWireCone(float r, float h, int div) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glRotatef(-90, 1, 0, 0);
	glutWireCone(r, h, div, div);

	glPopMatrix();
}

//����һ��ʵ��Բ̨,����y��,r1�ǵ���뾶
void myDrawSolidTable(float r1, float r2, float h, int div) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	GLUquadricObj* qobj = gluNewQuadric();
	glRotatef(-90, 1, 0, 0);
	gluCylinder(qobj, r1, r2, h, div, div);

	glPopMatrix();
}

//����һ��������ľ���
void myDrawTexRectangle(int texture, float w, float h) {
	glBindTexture(GL_TEXTURE_2D,texture);//�л�����
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glTexCoord2f(0, 1); glVertex3f(0, 0, h);
	glTexCoord2f(1, 1); glVertex3f(w, 0, h);
	glTexCoord2f(1, 0); glVertex3f(w, 0, 0);
	glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
	glEnd();

	glPopMatrix();
}