#define _CRT_SECURE_NO_WARNINGS
#include "myMatrix.h"
#include "myVector.h"
#include "myEuler.h"
#include "myQuaternion.h"

//������
//����Ϊһ������
void CMatrix415::set(float* val) { 
	//���*this�ǽṹ�壬Ȼ��ͨ�����صĺ�������ǿ��ת��Ϊfloat*��
	//ǿ��ת���ɱ������Զ�ִ�У�ʡ�Ե���
	float* s = *this;
	for (int i = 0; i < 16; i++){
		s[i] = val[i];
	}
}
void CMatrix415::setI() {
	float s[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
	set(s);
}

//����һ��float����������
//���Ǳ�֤ͨ���±���ʵĺ���
CMatrix415::operator float* () {
	return &m00;
}
CMatrix415::operator const float* () const {
	//const����ָ����ߣ�����ָ��ָ����;�����ұߣ���ʾָ�뱾���ǳ���
	//�ڶ���const��ʾ�����صĲ����Ƕ��ڸ���ĳ���ִ�С�����˵�������˸ú�������ı����״̬��
	return &m00;
}

//��ֵΪ��һ������
CMatrix415& CMatrix415::operator=(const CMatrix415& p) {
	float* s = *this;
	const float* t = p;//��ת��Ϊ����float����
	for (int i = 0;i < 16; i++) {
		s[i] = t[i];
	}
	return *this;
}

//���ұ�����
CMatrix415 CMatrix415::operator*(float d) {
	CMatrix415 temp;
	float* ptemp = temp;
	float* s = *this;
	for (int i = 0;i < 16;i++) {
		ptemp[i] = s[i] * d;
	}
	return temp;
}

//�������
CMatrix415 CMatrix415::operator*(const CMatrix415& p) {
	CMatrix415 temp;
	float* s = *this;
	const float* t = p;
	float* tp = temp;
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			int tpi = pos(i, j);//i��j��
			tp[tpi] = 0.0f;
			for (int k = 0;k < 4;k++) {
				tp[tpi] += s[pos(i,k)] * t[pos(k,j)];
			}
		}
	}
	return temp;
}
//�������������
CVector415 CMatrix415::vecMul(CVector415& p) {
	CVector415 temp;
	float* s = *this;
	float x = p.x, y = p.y, z = p.z, w = 0;
	temp.x = x * s[pos(0, 0)] + y * s[pos(0, 1)] + z * s[pos(0, 2)] + w * s[pos(0, 3)];
	temp.y = x * s[pos(1, 0)] + y * s[pos(1, 1)] + z * s[pos(1, 2)] + w * s[pos(1, 3)];
	temp.z = x * s[pos(2, 0)] + y * s[pos(2, 1)] + z * s[pos(2, 2)] + w * s[pos(2, 3)];
	w = x * s[pos(3, 0)] + y * s[pos(3, 1)] + z * s[pos(3, 2)] + w * s[pos(3, 3)];
	//if (w != 0.0f) {
	//	temp.x /= w;temp.y /= w;temp.z /= w;
	//}
	return temp;
}
//������λ�����
CVector415 CMatrix415::posMul(CVector415& p) {
	CVector415 temp;
	float* s = *this;
	float x = p.x, y = p.y, z = p.z, w = 1;
	temp.x = x * s[pos(0, 0)] + y * s[pos(0, 1)] + z * s[pos(0, 2)] + w * s[pos(0, 3)];
	temp.y = x * s[pos(1, 0)] + y * s[pos(1, 1)] + z * s[pos(1, 2)] + w * s[pos(1, 3)];
	temp.z = x * s[pos(2, 0)] + y * s[pos(2, 1)] + z * s[pos(2, 2)] + w * s[pos(2, 3)];
	w = x * s[pos(3, 0)] + y * s[pos(3, 1)] + z * s[pos(3, 2)] + w * s[pos(3, 3)];
	/*if (w != 0.0f) {
		temp.x /= w;temp.y /= w;temp.z /= w;
	}*/
	return temp;
}
//����Ϊ��ת����
void CMatrix415::setRotate(float seta, CVector415 axis) {
	CVector415 n = axis;
	n.Normalize();
	float rad = seta * Pi / 180.0f;
	float a = cos(rad), b = 1 - a, c = sin(rad);
	m00 = n.x * n.x * b + a, m01 = n.x * n.y * b - n.z * c, m02 = n.x * n.z * b + n.y * c, m03 = 0.0f;
	m10 = n.x * n.y * b + n.z * c, m11 = n.y * n.y * b + a, m12 = n.y * n.z * b - n.x * c, m13 = 0.0f;
	m20 = n.x * n.z * b - n.y * c, m21 = n.y * n.z * b + n.x * c, m22 = n.z * n.z * b + a, m23 = 0.0f;
	m30 = 0.0f, m31 = 0.0f, m32 = 0.0f, m33 = 1.0f;
}
//����Ϊƽ�ƾ���
void CMatrix415::setTrans(CVector415 trans) {
	m00 = 1.0f, m01 = 0.0f, m02 = 0.0f, m03 = trans.x;
	m10 = 0.0f, m11 = 1.0f, m12 = 0.0f, m13 = trans.y;
	m20 = 0.0f, m21 = 0.0f, m22 = 1.0f, m23 = trans.z;
	m30 = 0.0f, m31 = 0.0f, m32 = 0.0f, m33 = 1.0f;
}
//����Ϊ���ž���
void CMatrix415::setScale(CVector415 p) {
	m00 = p.x, m01 = 0.0f, m02 = 0.0f, m03 = 0.0f;
	m10 = 0.0f, m11 = p.y, m12 = 0.0f, m13 = 0.0f;
	m20 = 0.0f, m21 = 0.0f, m22 = p.z, m23 = 0.0f;
	m30 = 0.0f, m31 = 0.0f, m32 = 0.0f, m33 = 1.0f;
}
//������ʽ
float CMatrix415::Det() {
	//ȡ��һ�еĴ�������ʽ��Ӳ�㣻
	return m00 * (m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 - m13 * m22 * m31)
		- m01 * (m10 * m22 * m33 + m12 * m23 * m30 + m13 * m20 * m32 - m10 * m23 * m32 - m12 * m20 * m33 - m13 * m22 * m30)
		+ m02 * (m10 * m21 * m33 + m11 * m23 * m30 + m13 * m20 * m31 - m10 * m23 * m31 - m11 * m20 * m33 - m13 * m21 * m30)
		- m03 * (m10 * m21 * m32 + m11 * m22 * m30 + m12 * m20 * m31 - m10 * m22 * m31 - m11 * m20 * m32 - m12 * m21 * m30);
}
//�������棬�ɹ���������ʽ��ֵ�����򷵻�0
float CMatrix415::Inverse() {
	float det = Det();
	if (det != 0.0f) {
		*this = getInverse();
	}
	return det;
}
//���������
CMatrix415 CMatrix415::getInverse() {
	//��������ת�ã�Ӳ��
	CMatrix415 ret;
	float det = Det();
	if (det != 0.0f) {
		ret.m00 = (m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 - m13 * m22 * m31) / det;
		ret.m10 = -(m10 * m22 * m33 + m12 * m23 * m30 + m13 * m20 * m32 - m10 * m23 * m32 - m12 * m20 * m33 - m13 * m22 * m30) / det;
		ret.m20 = (m10 * m21 * m33 + m11 * m23 * m30 + m13 * m20 * m31 - m10 * m23 * m31 - m11 * m20 * m33 - m13 * m21 * m30) / det;
		ret.m30 = -(m10 * m21 * m32 + m11 * m22 * m30 + m12 * m20 * m31 - m10 * m22 * m31 - m11 * m20 * m32 - m12 * m21 * m30) / det;

		ret.m01 = -(m01 * m22 * m33 + m02 * m23 * m31 + m03 * m21 * m32 - m01 * m23 * m32 - m02 * m21 * m33 - m03 * m22 * m31) / det;
		ret.m11 = (m00 * m22 * m33 + m02 * m23 * m30 + m03 * m20 * m32 - m00 * m23 * m32 - m02 * m20 * m33 - m03 * m22 * m30) / det;
		ret.m21 = -(m00 * m21 * m33 + m01 * m23 * m30 + m03 * m20 * m31 - m00 * m23 * m31 - m01 * m20 * m33 - m03 * m21 * m30) / det;
		ret.m31 = (m00 * m21 * m32 + m01 * m22 * m30 + m02 * m20 * m31 - m00 * m22 * m31 - m01 * m20 * m32 - m02 * m21 * m30) / det;

		ret.m02 = (m01 * m12 * m33 + m02 * m13 * m31 + m03 * m11 * m32 - m01 * m13 * m32 - m02 * m11 * m33 - m03 * m12 * m31) / det;
		ret.m12 = -(m00 * m12 * m33 + m02 * m13 * m30 + m03 * m10 * m32 - m00 * m13 * m32 - m02 * m10 * m33 - m03 * m12 * m30) / det;
		ret.m22 = (m00 * m11 * m33 + m01 * m13 * m30 + m03 * m10 * m31 - m00 * m13 * m31 - m01 * m10 * m33 - m03 * m11 * m30) / det;
		ret.m32 = -(m00 * m11 * m32 + m01 * m12 * m30 + m02 * m10 * m31 - m00 * m12 * m31 - m01 * m10 * m32 - m02 * m11 * m30) / det;

		ret.m03 = -(m01 * m12 * m23 + m02 * m13 * m21 + m03 * m11 * m22 - m01 * m13 * m22 - m02 * m11 * m23 - m03 * m12 * m21) / det;
		ret.m13 = (m00 * m12 * m23 + m02 * m13 * m20 + m03 * m10 * m22 - m00 * m13 * m22 - m02 * m10 * m23 - m03 * m12 * m20) / det;
		ret.m23 = -(m00 * m11 * m23 + m01 * m13 * m20 + m03 * m10 * m21 - m00 * m13 * m21 - m01 * m10 * m23 - m03 * m11 * m20) / det;
		ret.m33 = (m00 * m11 * m22 + m01 * m12 * m20 + m02 * m10 * m21 - m00 * m12 * m21 - m01 * m10 * m22 - m02 * m11 * m20) / det;
	}
	return ret;
}
//����λ�õõ��±�
int CMatrix415::pos(int x, int y) {
	return y * 4 + x;
}
//����
void CMatrix415::read() {
	float* t = (float*)(*this);
	scanf(" %f", &t[0]);
	for (int i = 1;i < 16;i++) {
		scanf(",%f", &t[i]);
	}
}

//ת��Ϊŷ����
CEuler415 CMatrix415::toEuler() {
	CEuler415 temp;
	float p, h, b;
	p = asin(-m12);
	temp.p = jiaodu(p);
	if (cos(p) == 0) {
		h = atan2(-m20, m00);
		temp.h = jiaodu(h);
		temp.b = 0;
	}
	else {
		h = atan2(m02, m22);
		b = atan2(m10, m11);
		temp.h = jiaodu(h);
		temp.b = jiaodu(b);
	}
	return temp;
}

//ת��Ϊ��Ԫ��
CQuaternion415 CMatrix415::toQuaternion() {
	CQuaternion415 temp;
	float fx, fy, fz, fw, maxx = 0;
	fw = sqrt(m00 + m11 + m22 + 1) / 2;if (fw > maxx)maxx = fw;
	fx = sqrt(m00 - m11 - m22 + 1) / 2;if (fx > maxx)maxx = fx;
	fy = sqrt(-m00 + m11 - m22 + 1) / 2;if (fy > maxx)maxx = fy;
	fz = sqrt(-m00 - m11 + m22 + 1) / 2;if (fz > maxx)maxx = fz;
	if (maxx == fw) {
		fx = (m21 - m12) / 4 / fw;
		fy = (m02 - m20) / 4 / fw;
		fz = (m10 - m01) / 4 / fw;
	}
	else if (maxx == fx) {
		fw = (m21 - m12) / 4 / fx;
		fy = (m10 + m01) / 4 / fx;
		fz = (m02 + m20) / 4 / fx;
	}
	else if (maxx == fy) {
		fw = (m02 - m20) / 4 / fy;
		fx = (m10 + m01) / 4 / fy;
		fz = (m21 + m12) / 4 / fy;
	}
	else if (maxx == fz) {
		fw = (m10 - m01) / 4 / fz;
		fx = (m02 + m20) / 4 / fz;
		fy = (m21 + m12) / 4 / fz;
	}
	temp.w = fw;temp.x = fx;temp.y = fy;temp.z = fz;
	return temp;
}
//ת����λ��
CVector415 CMatrix415::toPos() {
	CVector415 V;
	V.Set(0, 0, 0);
	return posMul(V);
}