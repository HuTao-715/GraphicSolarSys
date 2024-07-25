#ifndef _myQuaternion_H_
#define _myQuaternion_H_

class CVector415;
class CMatrix415;
class CEuler415;
class CQuaternion415 {
public:
	float x, y, z, w;
	//设置参数
	void Set(float fx, float fy, float fz, float fw);
	//向量形式设置参数，xyz看成向量
	void Set(CVector415 v, float fw);
	//通过旋转四元数设置,angle是角度，axis是轴
	void SetAngle(float angle, CVector415 axis); 
	//读入
	void read();
	//输出
	void print();
	//转化为浮点数组
	operator float* ();
	operator const float* () const;
	//赋值
	CQuaternion415& operator=(const CQuaternion415& p);
	//加四元数
	CQuaternion415 operator+(const CQuaternion415& p);
	//数乘
	CQuaternion415 operator*(float data);
	//四元数乘法
	CQuaternion415 operator*(const CQuaternion415& p);
	//点乘
	float dotMul(const CQuaternion415& p);
	//求模
	float len();
	//求标准化
	bool Normalize();	
	//变为逆四元数，然后返回
	CQuaternion415& Inverse();
	//求逆四元数,不改变自身，生成新的四元数
	CQuaternion415 GetInverse();
	//求差 当前为a,求c=a-b
	CQuaternion415 Div(const CQuaternion415& b); 
	//求旋转轴和角度
	void GetAngle(float& angle, CVector415& axis); 
	//求幂
	CQuaternion415 mi(float t);
	//插值。从当前四元数插值到Vend四元数,t是参数[0,1]
	CQuaternion415 Slerp(const CQuaternion415& Vend, float t); 
	//插值。一次插值出n个数据。插值参数保存在数组t中，结果返回到数组Result中。
	void Slerp(const CQuaternion415& Vend, int n, float* t, CQuaternion415* Result);
	//四元数转欧拉角
	CEuler415 toEuler();
	//四元数转化矩阵
	CMatrix415 toMatrix();
};
#endif // !_myQuaternion_H_
