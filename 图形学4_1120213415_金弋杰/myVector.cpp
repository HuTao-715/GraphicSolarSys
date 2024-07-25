#define _CRT_SECURE_NO_WARNINGS
#include "myVector.h"
#include "myMatrix.h"
#include "myEuler.h"
#include<iostream>
//产生[a,b]间的随机浮点数
float randFloat(float a, float b) {
	if (a == b)return a;
	return a + (double)rand() / RAND_MAX * (b - a);
}

//-------------------------------

//三维向量类
//构造方法
CVector415::CVector415(float fx, float fy, float fz) {
	x = fx;y = fy;z = fz;
}

//设置坐标
void CVector415::Set(float x, float y, float z) {
	this->x = x;this->y = y;this->z = z;
}

//随机设置-50,50以内的坐标
void CVector415::getRandom() {
	x = randFloat(-50, 50);y = randFloat(-50, 50);z = randFloat(-50, 50);
}

//加上一个向量
CVector415 CVector415::operator+(const CVector415& a) {
	CVector415 temp;
	temp.x = x + a.x;temp.y = y + a.y;temp.z = z + a.z;
	return temp;
}

//减去一个向量
CVector415 CVector415::operator-(const CVector415& a) {
	CVector415 temp;
	temp.x = x - a.x;temp.y = y - a.y;temp.z = z - a.z;
	return temp;
}

//用另一个向量赋值
void CVector415::operator=(CVector415 a) {
	x = a.x;y = a.y;z = a.z;
}

//判断向量相等
bool CVector415::operator==(CVector415 a) {
	return x == a.x && y == a.y && z == a.z;
}

//判断向量不相等
bool CVector415::operator!=(CVector415 a) {
	return !(*this == a);
}

//在右侧数乘
CVector415 CVector415::operator*(float k) {
	CVector415 temp;
	temp.x = x * k;temp.y = y * k;temp.z = z * k;
	return temp;
}

//计算点积/数量积
float CVector415::dotMul(CVector415 a) {
	return x * a.x + y * a.y + z * a.z;
}

//计算向量积/叉积
CVector415 CVector415::crossMul(CVector415 a) {
	CVector415 temp;
	temp.x = y * a.z - z * a.y;
	temp.y = z * a.x - x * a.z;
	temp.z = x * a.y - y * a.x;
	return temp;
}

//计算长度
float CVector415::len() {
	return sqrt(x * x + y * y + z * z);
}

//向量标准化
void CVector415::Normalize() {
	float l = this->len();
	if (l == 0.0)return;
	x /= l;y /= l;z /= l;
}

//计算到另一个向量的投影
CVector415 CVector415::project(CVector415 a) {
	CVector415 temp = a;temp.Normalize();
	return temp * (this->dotMul(a) / a.len());
}

//打印向量，保留两位浮点数
void CVector415::print1() {
	printf("%.2f,%.2f,%.2f", x, y, z);
}

//读入
void CVector415::read() {
	scanf(" %f,%f,%f", &x, &y, &z);
}

//插值
CVector415 CVector415::cut(const CVector415& Vend, float t) {
	CVector415 dV = Vend;
	dV = dV - *this;
	return *this + dV * t;
}
void CVector415::cut(const CVector415& Vend, int n, float* t, CVector415* Result) {
	float sum = 0;
	for (int i = 0;i < n;i++) {
		sum += t[i];
		Result[i] = cut(Vend, sum);
	}
}
//------------------------------------------------