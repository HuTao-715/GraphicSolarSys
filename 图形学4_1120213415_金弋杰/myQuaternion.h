#ifndef _myQuaternion_H_
#define _myQuaternion_H_

class CVector415;
class CMatrix415;
class CEuler415;
class CQuaternion415 {
public:
	float x, y, z, w;
	//���ò���
	void Set(float fx, float fy, float fz, float fw);
	//������ʽ���ò�����xyz��������
	void Set(CVector415 v, float fw);
	//ͨ����ת��Ԫ������,angle�ǽǶȣ�axis����
	void SetAngle(float angle, CVector415 axis); 
	//����
	void read();
	//���
	void print();
	//ת��Ϊ��������
	operator float* ();
	operator const float* () const;
	//��ֵ
	CQuaternion415& operator=(const CQuaternion415& p);
	//����Ԫ��
	CQuaternion415 operator+(const CQuaternion415& p);
	//����
	CQuaternion415 operator*(float data);
	//��Ԫ���˷�
	CQuaternion415 operator*(const CQuaternion415& p);
	//���
	float dotMul(const CQuaternion415& p);
	//��ģ
	float len();
	//���׼��
	bool Normalize();	
	//��Ϊ����Ԫ����Ȼ�󷵻�
	CQuaternion415& Inverse();
	//������Ԫ��,���ı����������µ���Ԫ��
	CQuaternion415 GetInverse();
	//��� ��ǰΪa,��c=a-b
	CQuaternion415 Div(const CQuaternion415& b); 
	//����ת��ͽǶ�
	void GetAngle(float& angle, CVector415& axis); 
	//����
	CQuaternion415 mi(float t);
	//��ֵ���ӵ�ǰ��Ԫ����ֵ��Vend��Ԫ��,t�ǲ���[0,1]
	CQuaternion415 Slerp(const CQuaternion415& Vend, float t); 
	//��ֵ��һ�β�ֵ��n�����ݡ���ֵ��������������t�У�������ص�����Result�С�
	void Slerp(const CQuaternion415& Vend, int n, float* t, CQuaternion415* Result);
	//��Ԫ��תŷ����
	CEuler415 toEuler();
	//��Ԫ��ת������
	CMatrix415 toMatrix();
};
#endif // !_myQuaternion_H_
