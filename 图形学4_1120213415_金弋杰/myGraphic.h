#ifndef _myGraphic_H_
#define _myGraphic_H_
//绘制基础图形

#include<GL/glut.h>
#include "myVector.h"
#include "myEuler.h"
#include "myMatrix.h"
#include "myQuaternion.h"

class CMatrix415;
class CVector415;

//绘制一个坐标系,len是长度，arrayW是箭头轴向宽度，arrayH是箭头垂直轴向长度，kind是样式
//kind>0时有箭头
void myDrawDirection(float len, float arrayW, float arrayH, int kind);

//绘制一个圆，r是半径，div是精细程度
void myDrawCircle(float r, int div);
void myDrawSolidCircle(float r, int div);

//绘制一个实心圆锥，朝向y轴
void myDrawSolidCone(float r, float h, int div);
//线框圆锥
void myDrawWireCone(float r, float h, int div);

//绘制一个实心圆台,朝向y轴,r1是底面半径
void myDrawSolidTable(float r1, float r2, float h, int div);


//绘制一个有纹理的矩形
void myDrawTexRectangle(int texture, float w, float h);

#endif // !_myGraphic_H_