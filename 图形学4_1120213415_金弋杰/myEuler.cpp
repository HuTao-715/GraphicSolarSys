#define _CRT_SECURE_NO_WARNINGS
#include "myMatrix.h"
#include "myVector.h"
#include "myEuler.h"
#include "myQuaternion.h"

float jiaodu(float x) {
	return x * 180 / Pi;
}
float hudu(float x) {
	return x / 180 * Pi;
}

//�趨ֵ
void CEuler415::Set(float fh, float fp, float fb) {
	h = fh;p = fp;b = fb;
	return;
}
//���
void CEuler415::print() {
	printf("%.2f,%.2f,%.2f", h, p, b);
}
//����
void CEuler415::read() {
	scanf(" %f,%f,%f", &h, &p, &b);
}

//��Ϊ��������
CEuler415::operator float* () {
	return &h;
}

//��Գ�����Ϊ��������
CEuler415::operator const float* () const {
	return &h;
}

//�滮��
void CEuler415::Normalize() {
	float fh = hudu(h), fp = hudu(p), fb = hudu(b);
	float temp = cos(fp);//��¼ԭ����cos
	fp = asin(sin(fp));
	if (temp<0) {
		//˵����ת��
		fh += 180;
		fb += 180;
	}
	if (cos(fp) == 0) {
		fh += fb;
		fb = 0;
	}
	fh = atan2(sin(fh), cos(fh));//����atan2������+-180
	fb = atan2(sin(fb), cos(fb));
	h = jiaodu(fh);p = jiaodu(fp);b = jiaodu(fb);
}

//ת��Ϊ����
CVector415 CEuler415::toVector() {
	CVector415 temp,y;
	CMatrix415 m = toMatrix();
	temp.Set(0, 0, -1);y.Set(0, 1, 0);
	temp = m.vecMul(temp);y = m.vecMul(y);
	temp.print1();printf("\t");y.print1();
	return temp;
}

//ת��Ϊ����
CMatrix415 CEuler415::toMatrix() {
	CMatrix415 temp,mul;
	CVector415 dir;
	//ƫ��h����y��ת
	dir.Set(0, 1, 0);
	temp.setRotate(h, dir);
	//����p����x����ת
	dir.Set(1, 0, 0);
	mul.setRotate(p, dir);
	temp = temp * mul;
	//ƫ��b,��z����ת
	dir.Set(0, 0, 1);
	mul.setRotate(b, dir);
	temp = temp * mul;
	return temp;
}

//ת��Ϊ��Ԫ��
CQuaternion415 CEuler415::toQuaternion() {
	CQuaternion415 qh, qp, qb;
	qh.SetAngle(h, CVector415(0, 1, 0));
	qp.SetAngle(p, CVector415(1, 0, 0));
	qb.SetAngle(b, CVector415(0, 0, 1));
	return qh * qp * qb;
}

