#include "myMath.h"
#include<iostream>
//����[a,b]������������
float randFloat(float a, float b) {
	if (a == b)return a;
	return a + (double)rand() / RAND_MAX * (b - a);
}
//��ά������
class CVector415 {
public:
	//��������
	float x, y, z;
	//��������
	void Set(float x, float y, float z) {
		this->x = x;this->y = y;this->z = z;
	}
	//�������-50,50���ڵ�����
	void getRandom() {
		x = randFloat(-50, 50);y = randFloat(-50, 50);z = randFloat(-50, 50);
	}
	//����һ������
	CVector415 operator+(CVector415& a) {
		CVector415 temp;
		temp.x = x + a.x;temp.y = y + a.y;temp.z = z + a.z;
		return temp;
	}
	//��ȥһ������
	CVector415 operator-(CVector415& a) {
		CVector415 temp;
		temp.x = x - a.x;temp.y = y - a.y;temp.z = z - a.z;
		return temp;
	}
	//����һ��������ֵ
	void operator=(CVector415 a) {
		x = a.x;y = a.y;z = a.z;
	}
	//�ж��������
	bool operator==(CVector415 a) {
		return x == a.x && y == a.y && z == a.z;
	}
	//�ж����������
	bool operator!=(CVector415 a) {
		return !(*this == a);
	}
	//���Ҳ�����
	CVector415 operator*(float k) {
		CVector415 temp;
		temp.x = x * k;temp.y = y * k;temp.z = z * k;
		return temp;
	}
	//������/������
	float dotMul(CVector415 a) {
		return x * a.x + y * a.y + z * a.z;
	}
	//����������/���
	CVector415 crossMul(CVector415 a) {
		CVector415 temp;
		temp.x = y * a.z - z * a.y;
		temp.y = z * a.x - x * a.z;
		temp.z = x * a.y - y * a.x;
		return temp;
	}
	//���㳤��
	float len() {
		return sqrt(x * x + y * y + z * z);
	}
	//������׼��
	void Normalize() {
		float l = this->len();
		x /= l;y /= l;z /= l;
	}
	//���㵽��һ��������ͶӰ
	CVector415 project(CVector415 a) {
		CVector415 temp = a;temp.Normalize();
		return temp * (this->dotMul(a) / a.len());
	}
	//��ӡ������������λ������
	void print() {
		printf("%.2f,%.2f,%.2f", x, y, z);
	}
};