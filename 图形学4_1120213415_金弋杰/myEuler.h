#ifndef _myEuler_H_
#define _myEuler_H_

float jiaodu(float x);
float hudu(float x);
class CVector415;//这里为了避免循环引用报错，先声明
class CMatrix415;
class CQuaternion415;
class CEuler415 {
public:
	float h, p, b;
	//设定值
	void Set(float fh, float fp, float fb);
	//输出
	void print();
	//读入
	void read();
	//作为浮点数组
	operator float* ();
	//针对常量作为浮点数组
	operator const float* () const;
	//规范化
	void Normalize();
	//转化为向量
	CVector415 toVector();
	//转化为矩阵
	CMatrix415 toMatrix();
	//转化为四元数
	CQuaternion415 toQuaternion();
};



#endif // !_myEuler_H_
