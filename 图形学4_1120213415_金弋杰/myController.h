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
	myModel* base = NULL;//������
	virtual void changeOnPos() {};
	//ϵ��GL����������ο�ϵ�Ӹ�����ϵ��Ϊ������ϵ����ֻת��λ�ã�
	virtual void BasetoThispos() {};
	virtual void BasetoThis() {
		BasetoThispos();
		changeOnPos();
	}
	//ϵ��GL����������ο�ϵ������ϵת��������ϵ����ֻת��λ�ã������ҿ��ǵ������ǻ��ڸ�����ϵ��Ҳ����ֻ���ڸ�����λ�ã����Բ���Ĭ��
	//�������ĸ������������þ���,��Ϊ�ʼ��Ҫ����������������ת��
	virtual void WorldtoThispos() {};
	virtual void WorldtoThis() {
		WorldtoThispos();
		changeOnPos();
	}
	//����
	virtual void Draw() {};
};
class myView {//�ӽǳ�����
public:
	CVector415 V;//λ��
	CEuler415 E;//ŷ����
	CMatrix415 M;//����
	int flag;//���Ʒ�ʽ
	myModel* base;//������
	//�����������Ĳο�ϵ�ǵ�ǰ����ο�ϵ
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
	//��λ�ô��ӵ�ת����������ϵ�ľ���ͨ��λ��ŷ���ǵõ�
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
	//��λ�ô��ӵ�ת��������ϵ�ľ���
	CMatrix415 pos_ViewtoWorld() {
		CMatrix415 T;
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		base->WorldtoThis();
		glGetFloatv(GL_MODELVIEW_MATRIX, T);
		return T*pos_ViewtoThis();
	}
	
	//�Ѳο�ϵ�������ϵ�仯Ϊ����ϵ����ÿ�λ����������
	void ThistoWorld() {
		glLoadMatrixf(pos_ViewtoWorld().getInverse());
	}
};
class myController {
public:
	int able = 1;
	myView* view;//������ָ�룬��������
	int key[12];//��¼����״̬
	float Vm=8, Vr=1.5;
	//�ƶ�
	void move(CVector415 dir);
	
	//��ת
	void turnUp();
	void turnDown();
	void turnLeft();
	void turnRight();
	void rollLeft();
	void rollRight();
	//�ı���Ʒ�ʽ��1ŷ��2����
	void toEuler();
	void toFreedom();
	//�ı��ٶ�
	void upVm();
	void downVm();
	void upVr();
	void downVr();
	//������¼
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
	//����һ�Σ�ÿ֡�е���
	void scan(int x);
	//�л��ӽ�
	void shiftView(myView* view2, CVector415* V, CQuaternion415* Q, float* t, int frame);
};
//�����Ǿ���ʵ�ֵ�����
class myWolrd:public myModel{
public:
};
class mySun :public myModel {
public:
	float time;
	int able = 1;
	float Vr=0.01,R=300;
	//λ�ò��øı�
	void changeOnPos() override{
		glRotatef(time * Vr, 0, 1, 0);
	}
	void Draw() override {
		// ʹ��������������
		GLUquadric* sphere = gluNewQuadric();
		gluQuadricTexture(sphere, GL_TRUE); // ��������
		gluSphere(sphere, R, 50, 50); // ��������
		gluDeleteQuadric(sphere);
		//��Դ
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
		// ʹ��������������
		GLUquadric* sphere = gluNewQuadric();
		gluQuadricTexture(sphere, GL_TRUE); // ��������
		gluSphere(sphere, R, 50, 50); // ��������
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
		glRotatef(5, 0, 0, 1);//��б
		glRotatef(time * Vr, 0, 1, 0);//��ת
		glTranslatef(r, 0, 0);
	}
	void WorldtoThispos() override {
		base->WorldtoThispos();
		BasetoThispos();
	}
	void Draw() override {
		// ʹ��������������
		GLUquadric* sphere = gluNewQuadric();
		gluQuadricTexture(sphere, GL_TRUE); // ��������
		gluSphere(sphere, R, 50, 50); // ��������
		gluDeleteQuadric(sphere);
	}
};
class myStation : public myModel {
public:
	int able = 1;
	float r=200,d=50;
	float R=5, L=80, w=40, l=20;//����뾶�����ȣ��峤��
	int texture1, texture2;
	myStation(){}
	myStation(myModel* m) {
		base = m;
	}
	void BasetoThispos() override {
		glTranslatef(0, r, d);
	}
	void WorldtoThispos() override {
		base->WorldtoThis();//���������ת
		BasetoThispos();
	}
	void Draw() override {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		//����
		GLUquadric* qobj = gluNewQuadric();
		gluCylinder(qobj, R, R, L, 50, 50);
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		myDrawSolidCircle(R, 50);//���
		glTranslatef(0, L, 0);
		myDrawSolidCircle(R, 50);
		glPopMatrix();
		gluDeleteQuadric(qobj);
		//��ذ�
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
	float dh1=h2, dh2=0;//��¼��ɡ�����׶ε�λ��
	float dr = 0, dd = 0;//��¼�Խӽ׶���ת�ǣ��ƶ�����
	CVector415 Vend, Vnow;//��¼��������ʼ�Խӵĵص�,�͵�ǰλ��
	CQuaternion415 Q[100];//��¼��ֵ��ת
	CMatrix415 M;//��¼�������ϵ�λ��
	float dis;
	int now=0;//��ϲ�ֵ

	int texture;
	myEarth* earth;
	myMoon* moon;
	myMan* man;
	myRocket(){}
	myRocket(myModel* m) {
		base = m;
	}
	//��ɶԽӽ׶ε�һ����ת��ֵ�����õ�����
	void getVend() {
		//�Ե���Ĺ���ϵΪ�ο�
		CMatrix415 T;
		//��ǰλ�ò�������㣩
		CVector415 Vs;
		CMatrix415 Ms;
		CQuaternion415 Qs,Qend;
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		//��������λ��
		glLoadIdentity();
		glRotatef(5, 0, 0, 1);//��б
		glRotatef((moon->time+0.03*500)* moon->Vr, 0, 1, 0);//500֡��Ĺ�ת
		glTranslatef(moon->r, 0, 0);
		glGetFloatv(GL_MODELVIEW_MATRIX, T);
		Vend.Set(0, 0, 0);Vend = T.posMul(Vend);
		Vend = Vend + CVector415(0, moon->R + 30, 0);//������Ϸ��ƶ�30
		

		//���򵽻��λ��
		myEarth* earth = (myEarth*)base;//ת��
		Vs.Set(0, 200, 0);//λ����ȷ����
		Vnow = Vs;
		glLoadIdentity();
		glRotatef(earth->time * earth->Vr2, 0, 1, 0);//Ŀǰ����������ת
		glTranslatef(0, 200, 0);
		//�����Ȳ���Y��ת��-Z�ϣ���Ϊʸ��ת������Ԫ����Ч����-Z��ת��ʸ����
		//�����ǵĻ��Ҫ����Y�ᣬ���Ի�ͼʱ��Ҫ��תһ�Ρ�
		//�ӻع�����Ͽ��л���������ǰ��������Ծ�䣬��ת����һ�Σ����ÿ��Ե���ԭ���Ĵ���֬ת���������
		glGetFloatv(GL_MODELVIEW_MATRIX, Ms);
		Qs = Ms.toQuaternion();

		glPopMatrix();
		Vend =Vend - Vs;//����ϵ����Է���
		//Vend.print1();
		Qend = Vend.toEuler().toQuaternion();//ת������Ԫ��
		float t[100];
		for (int i = 0;i < 100;i++) {
			t[i] = 0.01;
		}
		Qs.Slerp(Qend, 100, t, Q);//��ֵ100֡
		now = 0;//��ʼ֡
	}
	//�ڶ�����ת
	void getVend2(){
		float t[100];
		CMatrix415 T;
		T.setRotate(90,CVector415(1,0,0));//-Z��ת��Y
		for (int i = 0;i < 100;i++) {
			t[i] = 0.01;
		}
		Vend.toEuler().toQuaternion().Slerp(T.toQuaternion(), 100, t, Q);
		now = 0;
	}
	//��������
	void bindToMoon() {
		CMatrix415 T;
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();

		glLoadIdentity();
		base->WorldtoThispos();//��׼Ϊ�������ϵ
		glTranslatef(Vnow.x, Vnow.y, Vnow.z);
		glMultMatrixf(Q[99].toMatrix());
		glRotatef(-90, 1, 0, 0);
		glGetFloatv(GL_MODELVIEW_MATRIX, M);//ȡ����λ�ôӻ���ײ�ϵ�任������ľ���

		glLoadIdentity();
		moon->WorldtoThis();
		glGetFloatv(GL_MODELVIEW_MATRIX, T);//ȡ����λ�ô�����ϵ�任������ľ���

		M = T.getInverse() * M;//�任������ϵ�£�֮�������ٸı�λ��;
		glPopMatrix();
		base = moon;
	}
	void move() {
		if (!able) return;
		if (!running) return;
		//��ɽ׶�
		if (step == 1) {
			dh1 += 0.3;
			dh2 += 0.3;
			if (dh2 > 30) {
				step = 2;
			}
		}
		//����׶�
		else if (step == 2) {
			dh1 += 0.3;
			if(dh2 >= 0) dh2 -= 0.3;
			if (dh1 >= 100) step = 3;
		}
		//�Խӽ׶�-��ת
		else if (step == 3) {
			dr += 0.9;
			if (dr >= 90) step = 4;
		}
		//�Խӽ׶�-�ƶ�
		else if (step == 4) {
			dd += 0.3;
			dis = 50 - dd;
			if (dd >= 50) {
				running = 0;
				step = 5;
			}
		}
		//���½׶�-��������
		else if (step == 6) {
			dd -= 0.3;
			if (dd <= 0) {
				dd = 0;
				getVend();//��ȡ�������λ�ã�׼����ֵ�������
				step = 7;
			}
		}
		//���½׶� - ��������
		else if(step == 7)
		{
			now++;
			if (now == 100) {
				Vend =Vend * 0.005;//�������ٵõ�ÿ֡
				step = 8;now = 0;
			}
		}
		//���½׶� - ǰ��
		else if (step == 8) {
			Vnow = Vnow + Vend;//Vend�Ѿ��䵽ÿһ֡�ĳ�����
			now++;
			if (now == 200) {
				getVend2();
				step = 9;
				now = 0;
			}
		}
		//���½׶� - ��������2
		else if(step == 9)
		{ 
			now++;
			if (now == 100) {
				Vend = Vend * 0.005;//�������ٵõ�ÿ֡
				step = 10;now = 0;
			}
		}
		//���½׶� - ����
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
			//����
			dh1 = h2;dh2 = dr = dd = 0;
			now = 0;
			base = earth;
		}
	}
	//����һ�ںͻ��ͷ
	void Draw1() {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		GLUquadric* qobj = gluNewQuadric();

		gluQuadricTexture(qobj, GL_TRUE);//��������
		glBindTexture(GL_TEXTURE_2D, texture);
		glPushMatrix();
		glRotatef(-90, 1, 0, 0);//z������y��
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		myDrawSolidCircle(r, 50);
		glPopMatrix();
		gluCylinder(qobj, r, r, h1, 50, 50);//����һ��
		glPopMatrix();
		glTranslatef(0, h1, 0);//��������

		gluQuadricTexture(qobj, GL_FALSE);//��������
		glColor3f(1, 0, 0);
		glRotatef(-90, 1, 0, 0);//z������y��
		gluCylinder(qobj, r, 0, h0, 50, 50);//��ͷ
		glColor3f(1, 1, 1);

		glPopMatrix();
	}
	void Draw() override {
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		GLUquadric* qobj = gluNewQuadric();
		if (step < 3) {
			glTranslatef(0, 100 + dh1, 0);//�ƶ�����һ���ײ�
			Draw1();
			if (dh2 > -0.01) {
				glTranslatef(0,-dh1 + dh2, 0);//�ƶ����ڶ����ײ�
				glRotatef(-90, 1, 0, 0);//z������y��
				gluCylinder(qobj, r, r, h2, 50, 50);//���ڶ���
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
		//�����Ǳ��½׶�
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
		//�������⴦�����ձ仯�����ͷλ��
		//step<=6����׼λ�ö��ǵ�������+������
		//7<=step����׼λ��Ϊ��������+����ϵ
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
		//�����Ǳ��½׶�
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
		glRotatef(90, 1, 0, 0);//����z��ת������y
	}
	void WorldtoThispos() override {
		if (step <= 6) {
			base->WorldtoThis();//��׼�������
		}
		else if (7 <= step && step <= 10) {
			base->WorldtoThispos();//��׼Ϊ�������ϵ
		}
		else if (step >= 11) {
			base->WorldtoThis();//��׼Ϊ����ϵ
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
		glRotatef(-90, 1, 0, 0);//���ػ������z��ת������y
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
		//ͷ
		glBegin(GL_POLYGON);
		glTexCoord2f(80.0 / 512, 400.0 / 512); glVertex3f(-0.5, 4, 0);
		glTexCoord2f(180.0 / 512, 400.0 / 512); glVertex3f(0.5, 4, 0);
		glTexCoord2f(180.0 / 512, 300.0 / 512); glVertex3f(0.5, 3, 0);
		glTexCoord2f(80.0 / 512, 300.0 / 512); glVertex3f(-0.5, 3, 0);
		glTexCoord2f(80.0 / 512, 400.0 / 512); glVertex3f(-0.5, 4, 0);
		glEnd();
		//����
		glBegin(GL_POLYGON);
		glTexCoord2f(230.0 / 512, 300.0 / 512); glVertex3f(1, 3, 0);
		glTexCoord2f(230.0 / 512, 100.0 / 512); glVertex3f(1, 1, 0);
		glTexCoord2f(30.0 / 512, 100.0 / 512); glVertex3f(-1, 1, 0);
		glTexCoord2f(30.0 / 512, 300.0 / 512); glVertex3f(-1, 3, 0);
		glTexCoord2f(230.0 / 512, 300.0 / 512); glVertex3f(1, 3, 0);
		glEnd();
		//��ֻ��(��������һ��)
		glBegin(GL_POLYGON);
		glTexCoord2f(260.0 / 512, 250.0 / 512); glVertex3f(1.3, 2.5, 0);
		glTexCoord2f(260.0 / 512, 150.0 / 512); glVertex3f(1.3, 1.5, 0);
		glTexCoord2f(0.0 / 512, 150.0 / 512); glVertex3f(-1.3, 1.5, 0);
		glTexCoord2f(0.0 / 512, 250.0 / 512); glVertex3f(-1.3, 2.5, 0);
		glTexCoord2f(260.0 / 512, 250.0 / 512); glVertex3f(1.3, 2.5, 0);
		glEnd();
		//���
		glBegin(GL_POLYGON);
		glTexCoord2f(80.0 / 512, 0.0 / 512); glVertex3f(-0.5, 0, 0);
		glTexCoord2f(80.0 / 512, 100.0 / 512); glVertex3f(-0.5, 1, 0);
		glTexCoord2f(110.0 / 512, 100.0 / 512); glVertex3f(-0.2, 1, 0);
		glTexCoord2f(110.0 / 512, 0.0 / 512); glVertex3f(-0.2, 0, 0);
		glTexCoord2f(80.0 / 512, 0.0 / 512); glVertex3f(-0.5, 0, 0);
		glEnd();
		//�ҽ�
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
