#ifndef _myVector_H_
#define _myVector_H_

#include<cmath>
#include<iostream>
#include "myEuler.h"

#define Pi 3.1415926

//����[a,b]֮������������
float randFloat(float a, float b);
//��ά������
class CVector415 {
public:
	//��������
	float x, y, z;
	//���췽��
	CVector415() {}
	CVector415(float fx, float fy, float fz);
	//��������
	void Set(float x, float y, float z);
	//�������-50,50���ڵ�����
	void getRandom();
	//����һ������
	CVector415 operator+(const CVector415& a);
	//��ȥһ������
	CVector415 operator-(const CVector415& a);
	//����һ��������ֵ
	void operator=(CVector415 a);
	//�ж��������
	bool operator==(CVector415 a);
	//�ж����������
	bool operator!=(CVector415 a);
	//���Ҳ�����
	CVector415 operator*(float k);
	//������/������
	float dotMul(CVector415 a);
	//����������/���
	CVector415 crossMul(CVector415 a);
	//���㳤��
	float len();
	//������׼��
	void Normalize();
	//���㵽��һ��������ͶӰ
	CVector415 project(CVector415 a);
	
	//��ӡ������������λ������
	void print1();
	//����
	void read();

	//����н�cos
	float getCos(CVector415 a) {
		float temp = dotMul(a) / a.len() / len();
		return temp;
	}
	float getAngle(CVector415 a){
		return acos(getCos(a)) * 180 / Pi;
	}

	//����ת��Ϊŷ����
	CEuler415 toEuler(){
		CEuler415 temp;
		temp.b = 0;//��������������
		CVector415 project,base;
		base.Set(0, 0, -1);//��׼��x������
		project.Set(x, 0, z);//��ƽ���ͶӰ
		//����ƫ��
		temp.h = project.getAngle(base);
		if (x > 0)temp.h = -temp.h;//���x����0Ϊ����С����Ϊ��������ֵС�ڵ���180
		//���㸩��
		temp.p = getAngle(project);
		if (y < 0)temp.p = -temp.p;//y����0Ϊ������֮Ϊ��
		return temp;
	}

	//��ֵ
	CVector415 cut(const CVector415& Vend, float t);
	void cut(const CVector415& Vend, int n, float* t, CVector415* Result);
};

#endif