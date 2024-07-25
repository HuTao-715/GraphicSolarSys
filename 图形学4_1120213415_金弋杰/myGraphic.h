#ifndef _myGraphic_H_
#define _myGraphic_H_
//���ƻ���ͼ��

#include<GL/glut.h>
#include "myVector.h"
#include "myEuler.h"
#include "myMatrix.h"
#include "myQuaternion.h"

class CMatrix415;
class CVector415;

//����һ������ϵ,len�ǳ��ȣ�arrayW�Ǽ�ͷ�����ȣ�arrayH�Ǽ�ͷ��ֱ���򳤶ȣ�kind����ʽ
//kind>0ʱ�м�ͷ
void myDrawDirection(float len, float arrayW, float arrayH, int kind);

//����һ��Բ��r�ǰ뾶��div�Ǿ�ϸ�̶�
void myDrawCircle(float r, int div);
void myDrawSolidCircle(float r, int div);

//����һ��ʵ��Բ׶������y��
void myDrawSolidCone(float r, float h, int div);
//�߿�Բ׶
void myDrawWireCone(float r, float h, int div);

//����һ��ʵ��Բ̨,����y��,r1�ǵ���뾶
void myDrawSolidTable(float r1, float r2, float h, int div);


//����һ��������ľ���
void myDrawTexRectangle(int texture, float w, float h);

#endif // !_myGraphic_H_