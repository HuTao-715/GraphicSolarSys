#include<cmath>
//����[a,b]֮������������
float randFloat(float a, float b);
//��ά������
class CVector415 {
public:
	//��������
	float x, y, z;
	//��������
	void Set(float x, float y, float z);
	//�������-50,50���ڵ�����
	void getRandom();
	//����һ������
	CVector415 operator+(CVector415& a);
	//��ȥһ������
	CVector415 operator-(CVector415& a);
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
	void print();
};

