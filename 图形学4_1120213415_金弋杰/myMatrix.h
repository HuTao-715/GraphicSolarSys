#ifndef _myMatrix_H_
#define _myMatrix_H_


#include<iostream>
#include "myVector.h"

class CEuler415;
//矩阵类，默认列优先
class CMatrix415{
public:
	float m00, m10, m20, m30;
	float m01, m11, m21, m31;
	float m02, m12, m22, m32;
	float m03, m13, m23, m33;
	//设置为一个数组
	void set(float* val);
	void setI();
	//当做一个数组来访问
	operator float* ();
	operator const float* () const;
	//赋值为另一个矩阵
	CMatrix415& operator=(const CMatrix415& p);
	//在右边数乘
	CMatrix415 operator*(float d);
	//矩阵相乘
	CMatrix415 operator*(const CMatrix415& p);
	//矩阵与向量相乘
	CVector415 vecMul(CVector415& p);
	//矩阵与位置相乘
	CVector415 posMul(CVector415& p);
	//设置为旋转矩阵
	void setRotate(float seta, CVector415 axis);
	//设置为平移矩阵
	void setTrans(CVector415 trans);
	//设置为缩放矩阵
	void setScale(CVector415 p);
	//求行列式
	float Det();
	//矩阵求逆，成功返回行列式的值，否则返回0
	float Inverse();
	//返回逆矩阵
	CMatrix415 getInverse();
	//输出
	void print1() {
		printf("%.2f", (*this)[0]);
		for (int i = 1;i < 16;i++) {
			printf(",%.2f",(*this)[i]);
		}
	}
	void read();
	//根据位置得到下标
	int pos(int x, int y);
	//转化为欧拉角
	CEuler415 toEuler();
	//转化为四元数
	CQuaternion415 toQuaternion();
	//转化为位置+欧拉角
	CVector415 toPos();
};

#endif // !_myMatrix_H_
