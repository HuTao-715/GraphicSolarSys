#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include "myEuler.h"
#include "myMatrix.h"
#include "myQuaternion.h"
#include "myVector.h"

//���ò���
void CQuaternion415::Set(float fx, float fy, float fz, float fw) {
	x = fx;y = fy;z = fz;w = fw;
}

//ͨ���������ã���x,y,z��������
void CQuaternion415::Set(CVector415 v, float fw) {
	x = v.x;y = v.y;z = v.z;w = fw;
}

//ͨ����ת��Ԫ������,angle�ǽǶȣ�axis����
void CQuaternion415::SetAngle(float angle, CVector415 axis) {
	axis.Normalize();
	float a = hudu(angle)/2;
	Set(axis * sin(a), cos(a));
}

//����
void CQuaternion415::read() {
	scanf(" %f,%f,%f,%f", &x, &y, &z, &w);
}

//���
void CQuaternion415::print() {
	printf("%.2f,%.2f,%.2f,%.2f\t", x, y, z, w);
}

//ת��Ϊ��������
CQuaternion415::operator float* () {
	return &x;
}
CQuaternion415::operator const float* () const {
	return &x;
}

//��ֵ
CQuaternion415& CQuaternion415::operator=(const CQuaternion415& p) {
	x = p.x;y = p.y;z = p.z;w = p.w;
	return *this;
}
//��Ԫ���ӷ�
CQuaternion415 CQuaternion415::operator+(const CQuaternion415& p) {
	CQuaternion415 temp;
	temp.x = x + p.x;temp.y = y + p.y;
	temp.z = z + p.z;temp.w = w + p.w;
	return temp;
}
//����
CQuaternion415 CQuaternion415::operator*(float data) {
	CQuaternion415 temp = *this;
	temp.x *= data;temp.y *= data;
	temp.z *= data;temp.w *= data;
	return temp;
}

//��Ԫ���˷�
CQuaternion415 CQuaternion415::operator*(const CQuaternion415& p) {
	CQuaternion415 temp;
	CVector415 v1, v2;
	v1.Set(x, y, z);v2.Set(p.x, p.y, p.z);
	temp.w = w * p.w - v1.dotMul(v2);
	v1 = v2 * w + v1 * p.w + v1.crossMul(v2);
	temp.Set(v1, temp.w);
	return temp;
}

//���
float CQuaternion415::dotMul(const CQuaternion415& p) {
	return x * p.x + y * p.y + z * p.z + w * p.w;
}

//��ģ
float CQuaternion415::len() {
	return sqrt(x * x + y * y + z * z + w * w);
}
//��׼��
bool CQuaternion415::Normalize() {
	float l = len();
	if (l == 0)return false;
	else{
		x /= l;y /= l;
		z /= l;w /= l;
	}
	return true;
}
//��Ϊ����Ԫ����Ȼ�󷵻�
CQuaternion415& CQuaternion415::Inverse() {
	*this = GetInverse();
	return *this;
}
//������Ԫ��,���ı����������µ���Ԫ��
CQuaternion415 CQuaternion415::GetInverse() {
	CQuaternion415 temp;
	float l = len();
	if (l == 0) {
		temp.Set(0, 0, 0, 0);
	}
	else {
		temp.Set(-x, -y, -z, w);
		temp = temp * (1 / l / l);
	}
	return temp;
}
//��� ��ǰΪa,��c=a-b
CQuaternion415 CQuaternion415::Div(const CQuaternion415& b) {
	CQuaternion415 temp = b;
	return (*this) * (temp.GetInverse());
}
//����ת��ͽǶ�
void CQuaternion415::GetAngle(float& angle, CVector415& axis) {
	CQuaternion415 temp = *this;
	temp.Normalize();//��λ��
	float a = acos(temp.w);//��Ƕ�
	temp.x /= sin(a);temp.y /= sin(a);temp.z /= sin(a);//��ȥsin�õ���
	angle = jiaodu(a)*2;
	axis.Set(temp.x, temp.y, temp.z);
}

//��Ԫ��תŷ����
CEuler415 CQuaternion415::toEuler() {
	//�����Ԫ��ת����;���תŷ���ǵõ���ʽ
	//p=asin(2wx-2yz)
	// 
	//cosp=0:
	// h=atan2(2wy-2zx,1-2y^2-2z^2)
	// b=0
	// 
	//cosp!=0:
	//h=atan2(2zx+2wy,1-2x^2-2y^2)
	//b=atan2(2xy+2wz,1-2z^z-2x^2)
	CEuler415 temp;
	float h,p,b;
	p = asin(2 * w * x - 2 * y * z);
	if (cos(p) == 0) {
		h = atan2(2 * w * y - 2 * z * x, 1 - 2 * y * y - 2 * z * z);
		b = 0;
	}
	else{
		h = atan2(2 * z * x + 2 * w * y, 1 - 2 * x * x - 2 * y * y);
		b = atan2(2 * x * y + 2 * w * z, 1 - 2 * z * z - 2 * x * x);
	}
	temp.h = jiaodu(h);temp.p = jiaodu(p); temp.b = jiaodu(b);
	return temp;
}

//��Ԫ��ת������
CMatrix415 CQuaternion415::toMatrix() {
	CMatrix415 temp;
	temp.m00 = 1 - 2 * y * y - 2 * z * z;
	temp.m01 = 2 * x * y - 2 * w * z;
	temp.m02 = 2 * x * z + 2 * w * y;
	temp.m03 = 0;

	temp.m10 = 2 * x * y + 2 * w * z;
	temp.m11 = 1 - 2 * x * x - 2 * z * z;
	temp.m12 = 2 * y * z - 2 * w * x;
	temp.m13 = 0;

	temp.m20 = 2 * x * z - 2 * w * y;
	temp.m21 = 2 * y * z + 2 * w * x;
	temp.m22 = 1 - 2 * x * x - 2 * y * y;
	temp.m23 = 0;

	temp.m30 = 0;
	temp.m31 = 0;
	temp.m32 = 0;
	temp.m33 = 1;
	return temp;
}
//����,�����Ѿ���λ��
CQuaternion415 CQuaternion415::mi(float t) {
	CQuaternion415 temp;
	CVector415 v;
	float a;
	GetAngle(a, v);
	a *= t;
	temp.SetAngle(a, v);
	return temp;
}
//��ֵ
CQuaternion415 CQuaternion415::Slerp(const CQuaternion415& Vend, float t) {
	CQuaternion415 me=*this,vend = Vend;
	me.Normalize();vend.Normalize();
	return (vend.Div(me).mi(t))*(me);
}
//��ֵ��һ�β�ֵ��n�����ݡ���ֵ��������������t�У�������ص�����Result�С�
void CQuaternion415::Slerp(const CQuaternion415& Vend, int n, float* t, CQuaternion415* Result) {
	float sum = 0;
	for (int i = 0;i < n;i++) {
		sum += t[i];
		Result[i] = Slerp(Vend, sum);
	}
}