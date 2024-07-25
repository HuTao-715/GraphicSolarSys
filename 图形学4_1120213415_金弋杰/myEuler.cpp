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

//设定值
void CEuler415::Set(float fh, float fp, float fb) {
	h = fh;p = fp;b = fb;
	return;
}
//输出
void CEuler415::print() {
	printf("%.2f,%.2f,%.2f", h, p, b);
}
//读入
void CEuler415::read() {
	scanf(" %f,%f,%f", &h, &p, &b);
}

//作为浮点数组
CEuler415::operator float* () {
	return &h;
}

//针对常量作为浮点数组
CEuler415::operator const float* () const {
	return &h;
}

//规划化
void CEuler415::Normalize() {
	float fh = hudu(h), fp = hudu(p), fb = hudu(b);
	float temp = cos(fp);//记录原本的cos
	fp = asin(sin(fp));
	if (temp<0) {
		//说明翻转了
		fh += 180;
		fb += 180;
	}
	if (cos(fp) == 0) {
		fh += fb;
		fb = 0;
	}
	fh = atan2(sin(fh), cos(fh));//利用atan2调整到+-180
	fb = atan2(sin(fb), cos(fb));
	h = jiaodu(fh);p = jiaodu(fp);b = jiaodu(fb);
}

//转化为向量
CVector415 CEuler415::toVector() {
	CVector415 temp,y;
	CMatrix415 m = toMatrix();
	temp.Set(0, 0, -1);y.Set(0, 1, 0);
	temp = m.vecMul(temp);y = m.vecMul(y);
	temp.print1();printf("\t");y.print1();
	return temp;
}

//转化为矩阵
CMatrix415 CEuler415::toMatrix() {
	CMatrix415 temp,mul;
	CVector415 dir;
	//偏航h，绕y旋转
	dir.Set(0, 1, 0);
	temp.setRotate(h, dir);
	//俯仰p，绕x轴旋转
	dir.Set(1, 0, 0);
	mul.setRotate(p, dir);
	temp = temp * mul;
	//偏航b,绕z轴旋转
	dir.Set(0, 0, 1);
	mul.setRotate(b, dir);
	temp = temp * mul;
	return temp;
}

//转化为四元数
CQuaternion415 CEuler415::toQuaternion() {
	CQuaternion415 qh, qp, qb;
	qh.SetAngle(h, CVector415(0, 1, 0));
	qp.SetAngle(p, CVector415(1, 0, 0));
	qb.SetAngle(b, CVector415(0, 0, 1));
	return qh * qp * qb;
}

