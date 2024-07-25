#ifndef _myVector_H_
#define _myVector_H_

#include<cmath>
#include<iostream>
#include "myEuler.h"

#define Pi 3.1415926

//产生[a,b]之间的随机浮点数
float randFloat(float a, float b);
//三维向量类
class CVector415 {
public:
	//三个坐标
	float x, y, z;
	//构造方法
	CVector415() {}
	CVector415(float fx, float fy, float fz);
	//设置坐标
	void Set(float x, float y, float z);
	//随机设置-50,50以内的坐标
	void getRandom();
	//加上一个向量
	CVector415 operator+(const CVector415& a);
	//减去一个向量
	CVector415 operator-(const CVector415& a);
	//用另一个向量赋值
	void operator=(CVector415 a);
	//判断向量相等
	bool operator==(CVector415 a);
	//判断向量不相等
	bool operator!=(CVector415 a);
	//在右侧数乘
	CVector415 operator*(float k);
	//计算点积/数量积
	float dotMul(CVector415 a);
	//计算向量积/叉积
	CVector415 crossMul(CVector415 a);
	//计算长度
	float len();
	//向量标准化
	void Normalize();
	//计算到另一个向量的投影
	CVector415 project(CVector415 a);
	
	//打印向量，保留两位浮点数
	void print1();
	//输入
	void read();

	//计算夹角cos
	float getCos(CVector415 a) {
		float temp = dotMul(a) / a.len() / len();
		return temp;
	}
	float getAngle(CVector415 a){
		return acos(getCos(a)) * 180 / Pi;
	}

	//向量转化为欧拉角
	CEuler415 toEuler(){
		CEuler415 temp;
		temp.b = 0;//向量看不出侧倾
		CVector415 project,base;
		base.Set(0, 0, -1);//基准是x负半轴
		project.Set(x, 0, z);//在平面的投影
		//计算偏航
		temp.h = project.getAngle(base);
		if (x > 0)temp.h = -temp.h;//如果x大于0为负，小于零为正，绝对值小于等于180
		//计算俯仰
		temp.p = getAngle(project);
		if (y < 0)temp.p = -temp.p;//y大于0为正，反之为负
		return temp;
	}

	//插值
	CVector415 cut(const CVector415& Vend, float t);
	void cut(const CVector415& Vend, int n, float* t, CVector415* Result);
};

#endif