#ifndef _myController_H_
#define _myController_H_

#include "myMatrix.h"
#include "myVector.h"
#include "myEuler.h"
#include "myQuaternion.h"
#include <GL/glut.h>
#include "myGraphic.h"

class myMan;
class myModel {
public:
	myModel* base = NULL;//父物体
	virtual void changeOnPos() {};
	//系列GL矩阵操作，参考系从父物体系变为该物体系（或只转到位置）
	virtual void BasetoThispos() {};
	virtual void BasetoThis() {
		BasetoThispos();
		changeOnPos();
	}
	//系列GL矩阵操作，参考系从世界系转到该物体系（或只转到位置）。并且考虑到可能是基于父物体系，也可能只基于父物体位置，所以不给默认
	//上下这四个函数都不重置矩阵,因为最开始还要调用摄像机与世界的转化
	virtual void WorldtoThispos() {};
	virtual void WorldtoThis() {
		WorldtoThispos();
		changeOnPos();
	}
	//绘制
	virtual void Draw() {};
};
class myView {//视角抽象类
public:
	CVector415 V;//位置
	CEuler415 E;//欧拉角
	CMatrix415 M;//矩阵
	int flag;//控制方式
	myModel* base;//绑定物体
	//这里参数定义的参考系是当前物体参考系
	myView() {
		V.Set(0, 0, 0);
		E.Set(0, 0, 0);
		M.setI();
		flag = 1;
	}
	myView(myModel* m) {
		myView();
		base = m;
	}
	//把位置从视点转化到绑定物体系的矩阵，通过位置欧拉角得到
	CMatrix415 pos_ViewtoThis() {
		if (flag == 2) return M;
		CMatrix415 T;
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glLoadIdentity();
		glTranslatef(V.x, V.y, V.z);
		glRotatef(E.h, 0, 1, 0);
		glRotatef(E.p, 1, 0, 0);
		glRotatef(E.b, 0, 0, 1);
		glGetFloatv(GL_MODELVIEW_MATRIX, T);

		glPopMatrix();
		return T;
	}
	//把位置从视点转化到世界系的矩阵
	CMatrix415 pos_ViewtoWorld() {
		CMatrix415 T;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		base->WorldtoThis();
		glGetFloatv(GL_MODELVIEW_MATRIX, T);
		return T*pos_ViewtoThis();
	}
	
	//把参考系从摄像机系变化为世界系，在每次绘制最初调用
	void ThistoWorld() {
		glLoadMatrixf(pos_ViewtoWorld().getInverse());
	}
};
class myController {
public:
	int able = 1;
	myView* view;//抽象类指针，可以载入
	int key[12];//记录键盘状态
	float Vm=8, Vr=1.5;
	//移动
	void move(CVector415 dir);
	
	//旋转
	void turnUp();
	void turnDown();
	void turnLeft();
	void turnRight();
	void rollLeft();
	void rollRight();
	//改变控制方式，1欧拉2自由
	void toEuler();
	void toFreedom();
	//改变速度
	void upVm();
	void downVm();
	void upVr();
	void downVr();
	//按键记录
	void startUp() { key[0] = 1; };
	void stopUp() { key[0] = 0; };
	void startDown() { key[1] = 1; };
	void stopDown() { key[1] = 0; };
	void startLeft() { key[2] = 1; };
	void stopLeft() { key[2] = 0; };
	void startRight() { key[3] = 1; };
	void stopRight() { key[3] = 0; };
	void startAhead() { key[4] = 1; };
	void stopAhead() { key[4] = 0; };
	void startBack() { key[5] = 1; };
	void stopBack() { key[5] = 0; };

	void startTurnUp() { key[6] = 1; };
	void stopTurnUp() { key[6] = 0; };
	void startTurnDown() { key[7] = 1; };
	void stopTurnDown() { key[7] = 0; };
	void startTurnLeft() { key[8] = 1; };
	void stopTurnLeft() { key[8] = 0; };
	void startTurnRight() { key[9] = 1; };
	void stopTurnRight() { key[9] = 0; };
	void startRollLeft() { key[10] = 1; };
	void stopRollLeft() { key[10] = 0; };
	void startRollRight() { key[11] = 1; };
	void stopRollRight() { key[11] = 0; };
	//更新一次，每帧中调用
	void scan(int x);
	//切换视角
	void shiftView(myView* view2, CVector415* V, CQuaternion415* Q, float* t, int frame);
};
//以下是具体实现的物体
class myWolrd:public myModel{
public:
};
class mySun :public myModel {
public:
	float time;
	int able = 1;
	float Vr=0.01,R=300;
	//位置不用改变
	void changeOnPos() override{
		glRotatef(time * Vr, 0, 1, 0);
	}
	void Draw() override {
		// 使用球函数绘制球体
		GLUquadric* sphere = gluNewQuadric();
		gluQuadricTexture(sphere, GL_TRUE); // 启用纹理
		gluSphere(sphere, R, 50, 50); // 绘制球体
		gluDeleteQuadric(sphere);
		//光源
		float pos[4] = { 0,0,0,1 };
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
	}
};
class myEarth :public myModel {
public:
	float time;
	int able = 1;
	float Vr1 = 1, Vr2 = 45, r=800, R=100;
	myEarth() {}
	myEarth(myModel* m) {
		base = m;
	}
	void changeOnPos() override {
		glRotatef(time * Vr2, 0, 1, 0);
	}
	void BasetoThispos() override {
		glRotatef(time * Vr1, 0, 1, 0);
		glTranslatef(r, 0, 0);
	}
	void WorldtoThispos() override {
		base->WorldtoThispos();
		BasetoThispos();
	}
	void Draw() override {
		// 使用球函数绘制球体
		GLUquadric* sphere = gluNewQuadric();
		gluQuadricTexture(sphere, GL_TRUE); // 启用纹理
		gluSphere(sphere, R, 50, 50); // 绘制球体
		gluDeleteQuadric(sphere);
	}
};
class myMoon :public myModel{
public:
	float time;
	int able=1;
	float Vr = 10, Vr2 = Vr, r = 350, R = 60;
	myMoon() {}
	myMoon(myModel* m) {
		base = m;
	}
	void changeOnPos() override {
		glRotatef(time*Vr2, 0, 1, 0);
	}
	void BasetoThispos() override {
		glRotatef(5, 0, 0, 1);//倾斜
		glRotatef(time * Vr, 0, 1, 0);//公转
		glTranslatef(r, 0, 0);
	}
	void WorldtoThispos() override {
		base->WorldtoThispos();
		BasetoThispos();
	}
	void Draw() override {
		// 使用球函数绘制球体
		GLUquadric* sphere = gluNewQuadric();
		gluQuadricTexture(sphere, GL_TRUE); // 启用纹理
		gluSphere(sphere, R, 50, 50); // 绘制球体
		gluDeleteQuadric(sphere);
	}
};
class myStation : public myModel {
public:
	int able = 1;
	float r=200,d=50;
	float R=5, L=80, w=40, l=20;//柱体半径、长度，板长宽
	int texture1, texture2;
	myStation(){}
	myStation(myModel* m) {
		base = m;
	}
	void BasetoThispos() override {
		glTranslatef(0, r, d);
	}
	void WorldtoThispos() override {
		base->WorldtoThis();//跟随地球旋转
		BasetoThispos();
	}
	void Draw() override {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		//柱体
		GLUquadric* qobj = gluNewQuadric();
		gluCylinder(qobj, R, R, L, 50, 50);
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		myDrawSolidCircle(R, 50);//封底
		glTranslatef(0, L, 0);
		myDrawSolidCircle(R, 50);
		glPopMatrix();
		gluDeleteQuadric(qobj);
		//电池板
		glTranslatef(0, 0, L / 2 - l / 2);
		glPushMatrix();
		glTranslatef(R, 0, 0);
		myDrawTexRectangle(texture1, w, l);
		glPopMatrix();
		glTranslatef(-R - w, 0, 0);
		myDrawTexRectangle(texture1, w, l);

		glPopMatrix();
	}
};
class myRocket :public myModel {
public:
	int able = 1, step = 0, running = 0;
	float r=3, h0=5, h1=10, h2=15;
	float dh1=h2, dh2=0;//记录起飞、脱落阶段的位置
	float dr = 0, dd = 0;//记录对接阶段旋转角，移动距离
	CVector415 Vend, Vnow;//记录与月亮开始对接的地点,和当前位置
	CQuaternion415 Q[100];//记录插值旋转
	CMatrix415 M;//记录在月亮上的位置
	float dis;
	int now=0;//配合插值

	int texture;
	myEarth* earth;
	myMoon* moon;
	myMan* man;
	myRocket(){}
	myRocket(myModel* m) {
		base = m;
	}
	//完成对接阶段第一次旋转插值，并得到方向
	void getVend() {
		//以地球的惯性系为参考
		CMatrix415 T;
		//当前位置参数（起点）
		CVector415 Vs;
		CMatrix415 Ms;
		CQuaternion415 Qs,Qend;
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		//地球到月球位置
		glLoadIdentity();
		glRotatef(5, 0, 0, 1);//倾斜
		glRotatef((moon->time+0.03*500)* moon->Vr, 0, 1, 0);//500帧后的公转
		glTranslatef(moon->r, 0, 0);
		glGetFloatv(GL_MODELVIEW_MATRIX, T);
		Vend.Set(0, 0, 0);Vend = T.posMul(Vend);
		Vend = Vend + CVector415(0, moon->R + 30, 0);//向惯性上方移动30
		

		//地球到火箭位置
		myEarth* earth = (myEarth*)base;//转型
		Vs.Set(0, 200, 0);//位置是确定的
		Vnow = Vs;
		glLoadIdentity();
		glRotatef(earth->time * earth->Vr2, 0, 1, 0);//目前跟随地球的自转
		glTranslatef(0, 200, 0);
		//这里先不把Y轴转到-Z上，因为矢量转化的四元数，效果是-Z轴转到矢量上
		//而我们的火箭要画在Y轴，所以绘图时需要多转一次。
		//从回归地球上空切换到向月球前进，不能跃变，多转的这一次，正好可以抵消原本的从树脂转到横向飞行
		glGetFloatv(GL_MODELVIEW_MATRIX, Ms);
		Qs = Ms.toQuaternion();

		glPopMatrix();
		Vend =Vend - Vs;//惯性系下相对方向
		//Vend.print1();
		Qend = Vend.toEuler().toQuaternion();//转化成四元数
		float t[100];
		for (int i = 0;i < 100;i++) {
			t[i] = 0.01;
		}
		Qs.Slerp(Qend, 100, t, Q);//插值100帧
		now = 0;//起始帧
	}
	//第二次旋转
	void getVend2(){
		float t[100];
		CMatrix415 T;
		T.setRotate(90,CVector415(1,0,0));//-Z轴转到Y
		for (int i = 0;i < 100;i++) {
			t[i] = 0.01;
		}
		Vend.toEuler().toQuaternion().Slerp(T.toQuaternion(), 100, t, Q);
		now = 0;
	}
	//跟随月亮
	void bindToMoon() {
		CMatrix415 T;
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glLoadIdentity();
		base->WorldtoThispos();//基准为地球惯性系
		glTranslatef(Vnow.x, Vnow.y, Vnow.z);
		glMultMatrixf(Q[99].toMatrix());
		glRotatef(-90, 1, 0, 0);
		glGetFloatv(GL_MODELVIEW_MATRIX, M);//取出将位置从火箭底部系变换到世界的矩阵

		glLoadIdentity();
		moon->WorldtoThis();
		glGetFloatv(GL_MODELVIEW_MATRIX, T);//取出将位置从月亮系变换到世界的矩阵

		M = T.getInverse() * M;//变换到月亮系下，之后火箭不再改变位置;
		glPopMatrix();
		base = moon;
	}
	void move() {
		if (!able) return;
		if (!running) return;
		//起飞阶段
		if (step == 1) {
			dh1 += 0.3;
			dh2 += 0.3;
			if (dh2 > 30) {
				step = 2;
			}
		}
		//脱落阶段
		else if (step == 2) {
			dh1 += 0.3;
			if(dh2 >= 0) dh2 -= 0.3;
			if (dh1 >= 100) step = 3;
		}
		//对接阶段-旋转
		else if (step == 3) {
			dr += 0.9;
			if (dr >= 90) step = 4;
		}
		//对接阶段-移动
		else if (step == 4) {
			dd += 0.3;
			dis = 50 - dd;
			if (dd >= 50) {
				running = 0;
				step = 5;
			}
		}
		//奔月阶段-返回中心
		else if (step == 6) {
			dd -= 0.3;
			if (dd <= 0) {
				dd = 0;
				getVend();//获取月球相对位置，准备插值、方向等
				step = 7;
			}
		}
		//奔月阶段 - 调整方向
		else if(step == 7)
		{
			now++;
			if (now == 100) {
				Vend =Vend * 0.005;//除以两百得到每帧
				step = 8;now = 0;
			}
		}
		//奔月阶段 - 前进
		else if (step == 8) {
			Vnow = Vnow + Vend;//Vend已经变到每一帧的长度了
			now++;
			if (now == 200) {
				getVend2();
				step = 9;
				now = 0;
			}
		}
		//奔月阶段 - 调整方向2
		else if(step == 9)
		{ 
			now++;
			if (now == 100) {
				Vend = Vend * 0.005;//除以两百得到每帧
				step = 10;now = 0;
			}
		}
		//奔月阶段 - 降落
		else if (step == 10) {
			Vnow.y -= 0.3;
			dis = 0.3*(100 - now) ;
			now++;
			if (now == 100) {
				bindToMoon();
				step = 11;
				running = 0;
				now = 0;
			}
		}
	}
	void go() {
		if (running) return;
		if (step == 0) {
			step = 1;
			running = 1;
			//printf("to1");
		}
		else if (step == 5) {
			step = 6;
			running = 1;
		}
		else if(step == 11)
		{
			step = 12;
		}
		else if (step == 13) {
			step = 0;
			running = 0;
			//重置
			dh1 = h2;dh2 = dr = dd = 0;
			now = 0;
			base = earth;
		}
	}
	//画第一节和火箭头
	void Draw1() {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		GLUquadric* qobj = gluNewQuadric();

		gluQuadricTexture(qobj, GL_TRUE);//启用纹理
		glBindTexture(GL_TEXTURE_2D, texture);
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);//z轴旋到y轴
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		myDrawSolidCircle(r, 50);
		glPopMatrix();
		gluCylinder(qobj, r, r, h1, 50, 50);//画第一节
		glPopMatrix();
		glTranslatef(0, h1, 0);//继续上移

		gluQuadricTexture(qobj, GL_FALSE);//禁用纹理
		glColor3f(1, 0, 0);
		glRotatef(-90, 1, 0, 0);//z轴旋到y轴
		gluCylinder(qobj, r, 0, h0, 50, 50);//画头
		glColor3f(1, 1, 1);

		glPopMatrix();
	}
	void Draw() override {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		GLUquadric* qobj = gluNewQuadric();
		if (step < 3) {
			glTranslatef(0, 100 + dh1, 0);//移动到第一级底部
			Draw1();
			if (dh2 > -0.01) {
				glTranslatef(0,-dh1 + dh2, 0);//移动到第二级底部
				glRotatef(-90, 1, 0, 0);//z轴旋到y轴
				gluCylinder(qobj, r, r, h2, 50, 50);//画第二节
			}
		}
		else if (step == 3) {
			glTranslatef(0, 200, 0);
			glRotatef(-dr, 1, 0, 0);
			Draw1();
		}
		else if (step == 4) {
			glTranslatef(0, 200, dd);
			glRotatef(-90, 1, 0, 0);
			Draw1();
		}
		else if (step == 5) {
			glTranslatef(0, 200, 50);
			glRotatef(-90, 1, 0, 0);
			Draw1();
		}
		else if (step == 6) {
			glTranslatef(0, 200, dd);
			glRotatef(-90, 1, 0, 0);
			Draw1();
		}
		//以下是奔月阶段
		else if (step == 7) {
			glTranslatef(0, 200, 0);
			glMultMatrixf(Q[now].toMatrix());
			glRotatef(-90, 1, 0, 0);
			//printf("%d:", now);Q[now].print();printf("\n");
			//Q[now].toMatrix().print1();printf("\n");
			Draw1();
		}
		else if (step == 8) {
			glTranslatef(Vnow.x, Vnow.y, Vnow.z);
			glMultMatrixf(Q[99].toMatrix());
			glRotatef(-90, 1, 0, 0);
			Draw1();
		}
		else if (step == 9) {
			glTranslatef(Vnow.x, Vnow.y, Vnow.z);
			glMultMatrixf(Q[now].toMatrix());
			glRotatef(-90, 1, 0, 0);
			Draw1();
		}
		else if (step == 10) {
			glTranslatef(Vnow.x, Vnow.y, Vnow.z);
			glMultMatrixf(Q[99].toMatrix());
			glRotatef(-90, 1, 0, 0);
			Draw1();
		}
		else if (step >= 11) {
			glMultMatrixf(M);
			Draw1();
		}
		//printf("step:%d\n", step);
		glPopMatrix();
	}

	void changeOnPos() override {
		//这里特殊处理，最终变化到火箭头位置
		//step<=6，基准位置都是地球球星+地球方向
		//7<=step，基准位置为地球球心+惯性系
		if (step < 3) {
			glTranslatef(0, 100 + dh1, 0);
		}
		else if (step == 3) {
			glTranslatef(0, 200, 0);
			glRotatef(-dr, 1, 0, 0);
		}
		else if (step == 4) {
			glTranslatef(0, 200, dd);
			glRotatef(-90, 1, 0, 0);
		}
		else if (step == 5) {
			glTranslatef(0, 200, 50);
			glRotatef(-90, 1, 0, 0);
		}
		else if (step == 6) {
			glTranslatef(0, 200, dd);
			glRotatef(-90, 1, 0, 0);
		}
		//以下是奔月阶段
		else if (step == 7) {
			glTranslatef(0, 200, 0);
			glMultMatrixf(Q[now].toMatrix());
			glRotatef(-90, 1, 0, 0);
		}
		else if (step == 8) {
			glTranslatef(Vnow.x, Vnow.y, Vnow.z);
			glMultMatrixf(Q[99].toMatrix());
			glRotatef(-90, 1, 0, 0);
		}
		else if (step == 9) {
			glTranslatef(Vnow.x, Vnow.y, Vnow.z);
			glMultMatrixf(Q[now].toMatrix());
			glRotatef(-90, 1, 0, 0);
		}
		else if (step == 10){
			glTranslatef(Vnow.x, Vnow.y, Vnow.z);
			glMultMatrixf(Q[99].toMatrix());
			glRotatef(-90, 1, 0, 0);
		}
		else if (step >= 11) {
			glMultMatrixf(M);
		}
		glTranslatef(0, h1 + h0, 0);
		glRotatef(90, 1, 0, 0);//视线z轴转到面向y
	}
	void WorldtoThispos() override {
		if (step <= 6) {
			base->WorldtoThis();//基准跟随地球
		}
		else if (7 <= step && step <= 10) {
			base->WorldtoThispos();//基准为地球惯性系
		}
		else if (step >= 11) {
			base->WorldtoThis();//基准为月亮系
		}
	}
};
class myMan :public myModel{
public:
	int able=1;
	float dr=0;
	myMoon* moon;
	myRocket* rocket;
	int texture;
	void move() {
		if (!able)return;
		if (rocket->step != 12)return;
		dr += 1.8;
		if (dr >= 360) {
			rocket->step = 13;
			dr = 0;
		}
	}
	void BasetoThispos() override {
		glRotatef(-90, 1, 0, 0);//撤回火箭视线z轴转到面向y
		glTranslatef(0, -rocket->h1 - rocket->h0, 0);
		if (rocket->step <= 11) return;
		glTranslatef(0, -moon->R, 0);
		glRotatef(dr, 1, 0, 0);
		glTranslatef(0, moon->R, 0);
	}
	void WorldtoThispos() override {
		rocket->WorldtoThis();
		BasetoThispos();
	}
	void Draw() override {
		glBindTexture(GL_TEXTURE_2D, texture);
		glMatrixMode(GL_MODELVIEW);
		glColor3f(1, 1, 1);
		//头
		glBegin(GL_POLYGON);
		glTexCoord2f(80.0 / 512, 400.0 / 512); glVertex3f(-0.5, 4, 0);
		glTexCoord2f(180.0 / 512, 400.0 / 512); glVertex3f(0.5, 4, 0);
		glTexCoord2f(180.0 / 512, 300.0 / 512); glVertex3f(0.5, 3, 0);
		glTexCoord2f(80.0 / 512, 300.0 / 512); glVertex3f(-0.5, 3, 0);
		glTexCoord2f(80.0 / 512, 400.0 / 512); glVertex3f(-0.5, 4, 0);
		glEnd();
		//身体
		glBegin(GL_POLYGON);
		glTexCoord2f(230.0 / 512, 300.0 / 512); glVertex3f(1, 3, 0);
		glTexCoord2f(230.0 / 512, 100.0 / 512); glVertex3f(1, 1, 0);
		glTexCoord2f(30.0 / 512, 100.0 / 512); glVertex3f(-1, 1, 0);
		glTexCoord2f(30.0 / 512, 300.0 / 512); glVertex3f(-1, 3, 0);
		glTexCoord2f(230.0 / 512, 300.0 / 512); glVertex3f(1, 3, 0);
		glEnd();
		//两只手(覆盖身体一起画)
		glBegin(GL_POLYGON);
		glTexCoord2f(260.0 / 512, 250.0 / 512); glVertex3f(1.3, 2.5, 0);
		glTexCoord2f(260.0 / 512, 150.0 / 512); glVertex3f(1.3, 1.5, 0);
		glTexCoord2f(0.0 / 512, 150.0 / 512); glVertex3f(-1.3, 1.5, 0);
		glTexCoord2f(0.0 / 512, 250.0 / 512); glVertex3f(-1.3, 2.5, 0);
		glTexCoord2f(260.0 / 512, 250.0 / 512); glVertex3f(1.3, 2.5, 0);
		glEnd();
		//左脚
		glBegin(GL_POLYGON);
		glTexCoord2f(80.0 / 512, 0.0 / 512); glVertex3f(-0.5, 0, 0);
		glTexCoord2f(80.0 / 512, 100.0 / 512); glVertex3f(-0.5, 1, 0);
		glTexCoord2f(110.0 / 512, 100.0 / 512); glVertex3f(-0.2, 1, 0);
		glTexCoord2f(110.0 / 512, 0.0 / 512); glVertex3f(-0.2, 0, 0);
		glTexCoord2f(80.0 / 512, 0.0 / 512); glVertex3f(-0.5, 0, 0);
		glEnd();
		//右脚
		glBegin(GL_POLYGON);
		glTexCoord2f(180.0 / 512, 0.0 / 512); glVertex3f(0.5, 0, 0);
		glTexCoord2f(180.0 / 512, 100.0 / 512); glVertex3f(0.5, 1, 0);
		glTexCoord2f(150.0 / 512, 100.0 / 512); glVertex3f(0.2, 1, 0);
		glTexCoord2f(150.0 / 512, 0.0 / 512); glVertex3f(0.2, 0, 0);
		glTexCoord2f(180.0 / 512, 0.0 / 512); glVertex3f(0.5, 0, 0);
		glEnd();
	}
};
#endif // !_myController_H_
