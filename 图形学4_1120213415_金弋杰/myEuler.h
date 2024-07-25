#ifndef _myEuler_H_
#define _myEuler_H_

float jiaodu(float x);
float hudu(float x);
class CVector415;//����Ϊ�˱���ѭ�����ñ���������
class CMatrix415;
class CQuaternion415;
class CEuler415 {
public:
	float h, p, b;
	//�趨ֵ
	void Set(float fh, float fp, float fb);
	//���
	void print();
	//����
	void read();
	//��Ϊ��������
	operator float* ();
	//��Գ�����Ϊ��������
	operator const float* () const;
	//�淶��
	void Normalize();
	//ת��Ϊ����
	CVector415 toVector();
	//ת��Ϊ����
	CMatrix415 toMatrix();
	//ת��Ϊ��Ԫ��
	CQuaternion415 toQuaternion();
};



#endif // !_myEuler_H_
