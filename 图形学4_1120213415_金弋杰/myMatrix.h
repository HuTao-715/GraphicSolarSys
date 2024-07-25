#ifndef _myMatrix_H_
#define _myMatrix_H_


#include<iostream>
#include "myVector.h"

class CEuler415;
//�����࣬Ĭ��������
class CMatrix415{
public:
	float m00, m10, m20, m30;
	float m01, m11, m21, m31;
	float m02, m12, m22, m32;
	float m03, m13, m23, m33;
	//����Ϊһ������
	void set(float* val);
	void setI();
	//����һ������������
	operator float* ();
	operator const float* () const;
	//��ֵΪ��һ������
	CMatrix415& operator=(const CMatrix415& p);
	//���ұ�����
	CMatrix415 operator*(float d);
	//�������
	CMatrix415 operator*(const CMatrix415& p);
	//�������������
	CVector415 vecMul(CVector415& p);
	//������λ�����
	CVector415 posMul(CVector415& p);
	//����Ϊ��ת����
	void setRotate(float seta, CVector415 axis);
	//����Ϊƽ�ƾ���
	void setTrans(CVector415 trans);
	//����Ϊ���ž���
	void setScale(CVector415 p);
	//������ʽ
	float Det();
	//�������棬�ɹ���������ʽ��ֵ�����򷵻�0
	float Inverse();
	//���������
	CMatrix415 getInverse();
	//���
	void print1() {
		printf("%.2f", (*this)[0]);
		for (int i = 1;i < 16;i++) {
			printf(",%.2f",(*this)[i]);
		}
	}
	void read();
	//����λ�õõ��±�
	int pos(int x, int y);
	//ת��Ϊŷ����
	CEuler415 toEuler();
	//ת��Ϊ��Ԫ��
	CQuaternion415 toQuaternion();
	//ת��Ϊλ��+ŷ����
	CVector415 toPos();
};

#endif // !_myMatrix_H_
