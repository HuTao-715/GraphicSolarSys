#include<cmath>
//产生[a,b]之间的随机浮点数
float randFloat(float a, float b);
//三维向量类
class CVector415 {
public:
	//三个坐标
	float x, y, z;
	//设置坐标
	void Set(float x, float y, float z);
	//随机设置-50,50以内的坐标
	void getRandom();
	//加上一个向量
	CVector415 operator+(CVector415& a);
	//减去一个向量
	CVector415 operator-(CVector415& a);
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
	void print();
};

