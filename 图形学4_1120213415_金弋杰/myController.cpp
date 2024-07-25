#define _CRT_SECURE_NO_WARNINGS

#include <GL/glut.h>
#include "myMatrix.h"
#include "myEuler.h"
#include "myVector.h"
#include "myController.h"

//�ƶ�
void myController::move(CVector415 dir) {
	if (view->flag == 1) {
		CMatrix415 T=view->pos_ViewtoThis();
		dir = T.vecMul(dir);//�任����ǰ������
		dir.Normalize();
		view->V = view->V + dir * Vm;
	}
	else if (view->flag == 2) {
		CMatrix415 T;
		dir.Normalize();
		T.setTrans(dir * Vm);
		view->M = view->M * T;
	}
}
//��ת
void myController::turnLeft() {
	if (view->flag == 1) {
		view->E.h += Vr;
	}
	else if (view->flag == 2) {
		CMatrix415 T;
		T.setRotate(Vr, CVector415(0, 1, 0));
		view->M = view->M * T;
	}
}
void myController::turnRight() {
	if (view->flag == 1) {
		view->E.h -= Vr;
	}
	else if (view->flag == 2) {
		CMatrix415 T;
		T.setRotate(-Vr, CVector415(0, 1, 0));
		view->M = view->M * T;
	}
}
void myController::turnUp() {
	if (view->flag == 1) {
		view->E.p += Vr;
		if (view->E.p > 89.9)view->E.p = 89.9;
	}
	else if (view->flag == 2) {
		CMatrix415 T;
		T.setRotate(Vr, CVector415(1, 0, 0));
		view->M = view->M * T;
	}
}
void myController::turnDown() {
	if (view->flag == 1) {
		view->E.p -= Vr;
		if (view->E.p < -89.9)view->E.p = -89.9;
	}
	else if (view->flag == 2) {
		CMatrix415 T;
		T.setRotate(-Vr, CVector415(1, 0, 0));
		view->M = view->M * T;
	}
}
void myController::rollLeft() {
	if (view->flag == 1) {
		view->E.b += Vr;
	}
	else if (view->flag == 2) {
		CMatrix415 T;
		T.setRotate(Vr, CVector415(0, 0, 1));
		view->M = view->M * T;
	}
}
void myController::rollRight() {
	if (view->flag == 1) {
		view->E.b -= Vr;
	}
	else if (view->flag == 2) {
		CMatrix415 T;
		T.setRotate(-Vr, CVector415(0, 0, 1));
		view->M = view->M * T;
	}
}
//�ı���Ʒ�ʽ��1ŷ��2����
void myController::toEuler() {
	if (view->flag == 2) {
		view->V = view->M.toPos();
		view->E = view->M.toEuler();
		view->flag = 1;
	}
}
void myController::toFreedom() {
	if (view->flag == 1) {
		view->M = view->pos_ViewtoThis();
		view->flag = 2;
	}
}
//�ı��ٶ�
void myController::upVm() {
	Vm += 0.5;
	if (Vm > 15)Vm = 15;
}
void myController::downVm() {
	Vm -= 0.5;
	if (Vm < 0)Vm = 0;
}
void myController::upVr() {
	Vr += 0.2;
	if (Vr > 3)Vr = 3;
}
void myController::downVr() {
	Vr -= 0.2;
	if (Vr < 0)Vr = 0;
}
//����һ�Σ�ÿ֡�е���
void myController::scan(int x) {
	if (!able)return;
	CVector415 dir=CVector415(0,0,0);
	if (key[0]) dir.y += 1;
	if (key[1]) dir.y -= 1;
	if (key[2]) dir.x -= 1;
	if (key[3]) dir.x += 1;
	if (key[4]) dir.z -= 1;
	if (key[5]) dir.z += 1;
	//dir.print1();printf("\n");
	move(dir);
	if (key[6]) turnUp();
	if (key[7]) turnDown();
	if (key[8]) turnLeft();
	if (key[9]) turnRight();
	if (key[10]) rollLeft();
	if (key[11]) rollRight();
	view->E.Normalize();
	//view->V.print1();printf("\t");view->E.print();printf("\t%d", view->flag);printf("\n");
}
//�л��ӽ�
void myController::shiftView(myView* view2,CVector415* V, CQuaternion415* Q, float* t, int frame) {
	CMatrix415 M1, M2;
	CVector415 pos1, pos2;
	CQuaternion415 Q1, Q2;
	M1 = view->pos_ViewtoWorld(); M2 = view2->pos_ViewtoWorld();
	pos1 = M1.toPos();pos2 = M2.toPos();
	Q1 = M1.toQuaternion();Q2 = M2.toQuaternion();
	for (int i = 0;i < frame;i++) {
		t[i] = 1.0 / frame;
	}
	//������Ԫ��
	Q1.Slerp(Q2, frame, t, Q);
	//����λ��
	pos1.cut(pos2, frame, t, V);
	view = view2;
}