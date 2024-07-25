#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "myMatrix.h"
#include "myVector.h"
#include "myEuler.h"
#include "myQuaternion.h"
#include "myController.h"
#include "font.h"
//加载图片处理库
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int vw, vh;

int able = 1,count = 0,indexx=0;//全局控制，count为剩余控制帧数,indexx为当前显示
float myTime = 0;
//中间帧
float t[20];
CQuaternion415 Q[20];
CVector415 V[20];
//视角控制
myController controller;
//物体
mySun sun;
myWolrd world;
myEarth earth;
myMoon moon;
myStation station;
myRocket rocket;
myView view[5];
myMan man;
int view_next;
//贴图ID
GLuint texture[20];
//停止功能
void stop() {
	able = controller.able = 0;
}
//重启功能
void restart() {
	able = controller.able = 1;
}
//打印当前世界坐标
void showNow() {
	CMatrix415 T;
	CVector415 V;V.Set(0, 0, 0);
	CEuler415 E;
	glGetFloatv(GL_MODELVIEW_MATRIX, T);
	V = T.posMul(V);
	E = T.toEuler();
	V.print1();printf("\t");E.print();printf("\n");
}
//获取贴图
void loadTexture() {
	//准备纹理
	glEnable(GL_TEXTURE_2D);
	glGenTextures(20, texture);//生成系列序列号

	//获取图片
	int width[20], height[20], nrChannels[20];
	unsigned char* data[20];
	for (int i = 0;i < 20;i++)data[i] = NULL;
	
	//依次赋值
	data[0] = stbi_load("box.jpg", &width[0], &height[0], &nrChannels[0], 0);
	data[1] = stbi_load("sun.bmp", &width[1], &height[1], &nrChannels[1], 0);
	data[2] = stbi_load("earth.bmp", &width[2], &height[2], &nrChannels[2], 0);
	data[3] = stbi_load("moon.bmp", &width[3], &height[3], &nrChannels[3], 0);
	data[4] = stbi_load("wing.jpg", &width[4], &height[4], &nrChannels[4], 0);
	data[5] = stbi_load("rocket.bmp", &width[5], &height[5], &nrChannels[5], 0);
	data[6] = stbi_load("man.bmp", &width[6], &height[6], &nrChannels[6], 0);
	//物体纹理设置
	station.texture1 = texture[4];
	rocket.texture = texture[5];
	man.texture = texture[6];

	for (int i = 0;i < 20;i++) {
		//如果没有图了就退出
		if (!data[i]) {
			//printf("break:%d\n", i);
			break;
		}
		//printf("ok%d\n",i);
		glBindTexture(GL_TEXTURE_2D, texture[i]);//切换当前使用的纹理
		//把图片赋给纹理,参数分别是是：
		//0：2D纹理
		//1:mipmap层次
		//2-4：贴图格式，宽度高度
		//5:平滑
		//6-8：源图格式，源数据类型，实际地址
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width[i], height[i], 0, GL_RGB, GL_UNSIGNED_BYTE, data[i]);
		//创建mipmap
		gluBuild2DMipmaps(GL_TEXTURE_2D, nrChannels[i], width[i], height[i], GL_RGB, GL_UNSIGNED_BYTE, data[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);//图像放大
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);//图像缩小
	}
	//delete[] data;
}
//初始化
void init() {//设置一次的初始化函数
	glClearColor(0.0, 0.0, 0.0, 0.0);//设置背景颜色
	glEnable(GL_DEPTH_TEST);//深度缓冲，处理重叠

	glEnable(GL_LIGHTING);//启用光照
	glEnable(GL_LIGHT0);//启用第0个光照
	glEnable(GL_COLOR_MATERIAL);//材料跟随颜色
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);//正面
	loadTexture();//载入贴图

	for (int i = 0;i < 20;i++)t[i] = 0.05; 

	//视角绑定
	view[0].base = &world;
	view[1].base = &earth;
	view[2].base = &rocket;
	view[3].base = &station;
	view[4].base = &man;
	controller.view = &view[0];
	view_next = 1;
	view[0].V.Set(0, 500, 500);

	//物体基准绑定
	earth.base = &sun;
	station.base = &earth;
	moon.base = &earth;
	rocket.base = &earth; rocket.moon = &moon;rocket.man = &man;rocket.earth = &earth;
	man.base = man.rocket = &rocket;man.moon = &moon;
	
	float color[4] = { 0.6,0.6,0.6,0 };
	float color2[4] = { 0.4,0.4,0.4,0 };

	//设置光照背景色和漫反射参数
	glLightfv(GL_LIGHT0, GL_AMBIENT, color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, color2);
}
//移动到位置后，在位置上变化后绘制，然后把矩阵恢复
void DrawOnPos(myModel* m) {
	glPushMatrix();
	m->changeOnPos();
	m->Draw();
	glPopMatrix();
}
//绘制回调函数
void drawBox() {
	GLUquadric* sphere = gluNewQuadric();
	gluQuadricTexture(sphere, GL_TRUE); // 启用纹理
	gluSphere(sphere, 5000, 50, 50); // 绘制球体
	gluDeleteQuadric(sphere);
}
void printHint() {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, vw, -vh, 0, -1000, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor3f(1, 1, 1);
	selectFont(24, DEFAULT_CHARSET, "华文仿宋");
	/*视角，控制方式，欧拉角模式的位置，旋转方位，速度，阶段，距离*/
	char view[100], mode[100], pos[100],rotate[100],v[100],step[100],dis[100];
	switch (view_next){
		case 1: sprintf(view, "当前视点：世界"); break;
		case 2: sprintf(view, "当前视点：地球"); break;
		case 3: sprintf(view, "当前视点：火箭"); break;
		case 4: sprintf(view, "当前视点：空间站"); break;
		case 0: sprintf(view, "当前视点：太空人"); break;
	}
	if (controller.view->flag == 1) {
		sprintf(mode, "控制方式：欧拉角");
		sprintf(pos, "当前位置：x:%.2f,y:%.2f,z:%.2f", controller.view->V.x, controller.view->V.y, controller.view->V.z);
		sprintf(rotate, "当前旋转：h:%.2f,p:%.2f,b:%.2f", controller.view->E.h, controller.view->E.p, controller.view->E.b);
	}
	else{
		sprintf(mode, "控制方式：自由漫游");
		sprintf(pos, "当前位置：自由漫游");
		sprintf(rotate, "当前位置：自由漫游");
	}
	sprintf(v, "移动速度：%.2f,旋转速度：%.2f", controller.Vm,controller.Vr);
	switch (rocket.step) {
		case 0: sprintf(step, "运行状态：准备发射"); break;
		case 1: sprintf(step, "运行状态：起飞"); break;
		case 2: sprintf(step, "运行状态：起飞-第二级脱落"); break;
		case 3: sprintf(step, "运行状态：对接-旋转"); break;
		case 4: sprintf(step, "运行状态：对接-移动"); break;
		case 5: sprintf(step, "运行状态：对接完成"); break;
		case 6: sprintf(step, "运行状态：奔月-返回上空"); break;
		case 7: sprintf(step, "运行状态：奔月-调整方向"); break;
		case 8: sprintf(step, "运行状态：奔月-前进"); break;
		case 9: sprintf(step, "运行状态：奔月-调整方向"); break;
		case 10: sprintf(step, "运行状态：降落"); break;
		case 11: sprintf(step, "运行状态：到达月球"); break;
		case 12: sprintf(step, "运行状态：太空人活动"); break;
		case 13: sprintf(step, "运行状态：结束"); break;
	}

	glRasterPos2f(0, -30);
	drawCNString(view);
	glRasterPos2f(200, -30);
	drawCNString(mode);
	glRasterPos2f(0, -60);
	drawCNString(pos);
	glRasterPos2f(0, -90);
	drawCNString(rotate);
	glRasterPos2f(0, -120);
	drawCNString(v);
	glRasterPos2f(0, -150);
	drawCNString(step);

	if (rocket.step == 4 || rocket.step == 10) {
		sprintf(dis, "距离对接点：%.2f",rocket.dis);
		glRasterPos2f(0, -180);
		drawCNString(dis);
	}

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
}
void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	

	glLoadIdentity();
	if (count) {
		glMultMatrixf(Q[indexx].toMatrix().getInverse());
		glTranslatef(-V[indexx].x, -V[indexx].y, -V[indexx].z);
		indexx++;
	}
	else
	{
		controller.view->ThistoWorld();
	}
	
	myDrawDirection(1000,50,25,1);
	glColor3f(1, 1, 1);//之后设置为白色，让纹理与明暗效果叠加（默认）
	glPushMatrix();
	//天空盒
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	drawBox();
	//太阳
	glBindTexture(GL_TEXTURE_2D, texture[1]);//太阳纹理
	DrawOnPos(&sun);
	//地球
	glDisable(GL_TEXTURE_2D);
	myDrawCircle(earth.r, 50);//轨道
	glEnable(GL_TEXTURE_2D);
	earth.BasetoThispos();
	glBindTexture(GL_TEXTURE_2D, texture[2]);//地球纹理
	DrawOnPos(&earth);

	//月球
	glPushMatrix();
	glRotatef(5, 0, 0, 1);
	glDisable(GL_TEXTURE_2D);
	myDrawCircle(moon.r, 50);//轨道
	glEnable(GL_TEXTURE_2D);
	glPopMatrix();

	glPushMatrix();
	moon.BasetoThis();
	glBindTexture(GL_TEXTURE_2D, texture[3]);//月亮纹理
	DrawOnPos(&moon);
	glPopMatrix();//恢复到地球位置

	//空间站
	glPushMatrix();
	earth.changeOnPos();
	station.BasetoThis();
	station.Draw();
	glPopMatrix();//恢复到地球位置

	//火箭
	if(rocket.step<=6) earth.changeOnPos();//小于等于6，跟随地球旋转
	if (rocket.step >= 11) {
		moon.BasetoThis();//此时跟随月亮
	}
	rocket.Draw();

	//太空人
	glPopMatrix();//恢复到世界原点
	man.WorldtoThis();
	man.Draw();

	//提示信息
	printHint();

	glFlush();
	//显示完毕重启
	if (count!=0&&indexx==count) {
		count=indexx=0;
		restart();
	}
}
//窗口回调函数
void myReshape(int w,int h) {
	glViewport(0, 0, w, h);
	vw = w;vh = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, GLdouble(w) / h, 1, 10000);
	glMatrixMode(GL_MODELVIEW);
}
//切换视角
void shiftBind() {
	stop();
	controller.shiftView(&view[view_next],V,Q,t,20);
	view_next++;view_next %= 5;
	count = 20;
}
//键盘回调函数
void myKeyboard(unsigned char key, int x, int y) {
	if (!able)return;
	if (key == 'a') {
		controller.startLeft();
	}
	else if (key == 'd') {
		controller.startRight();
	}
	else if (key == 'w') {
		controller.startUp();
	}
	else if (key == 's') {
		controller.startDown();
	}
	else if (key == 'q') {
		controller.startAhead();
	}
	else if (key == 'e') {
		controller.startBack();
	}
	else if (key == 'j') {
		controller.startTurnLeft();
	}
	else if (key == 'l') {
		controller.startTurnRight();
	}
	else if (key == 'i') {
		controller.startTurnUp();
	}
	else if (key == 'k') {
		controller.startTurnDown();
	}
	else if (key == 'u') {
		controller.startRollLeft();
	}
	else if (key == 'o') {
		controller.startRollRight();
	}
	else if (key == '[') {
		controller.downVm();
	}
	else if (key == ']') {
		controller.upVm();
	}
	else if (key == '{') {
		controller.downVr();
	}
	else if (key == '}') {
		controller.upVr();
	}
	else if (key == '2') {
		controller.toFreedom();
	}
	else if (key == '1') {
		controller.toEuler();
	}
	else if (key == '3') {
		shiftBind();
	}
	else if (key == 13) {
		rocket.go();
		//printf("go\n");
	}
}
void myKeyboardUp(unsigned char key, int x, int y) {
	if (key == 'a') {
		controller.stopLeft();
		myDisplay();
	}
	else if (key == 'd') {
		controller.stopRight();
	}
	else if (key == 'w') {
		controller.stopUp();
	}
	else if (key == 's') {
		controller.stopDown();
	}
	else if (key == 'q') {
		controller.stopAhead();
	}
	else if (key == 'e') {
		controller.stopBack();
	}
	else if (key == 'j') {
		controller.stopTurnLeft();
	}
	else if (key == 'l') {
		controller.stopTurnRight();
	}
	else if (key == 'i') {
		controller.stopTurnUp();
	}
	else if (key == 'k') {
		controller.stopTurnDown();
	}
	else if (key == 'u') {
		controller.stopRollLeft();
	}
	else if (key == 'o') {
		controller.stopRollRight();
	}
}
//帧计时器
void addTime() {
	if (!able)return;
	myTime += 0.03;
	sun.time = earth.time = moon.time = myTime;
	rocket.move();//火箭移动
	man.move();//人移动
}
void mytimer(int x) {
	controller.scan(x);//更新摄像机位置
	addTime();
	myDisplay();//重绘
	glutTimerFunc(30, mytimer, 0);
}
//主函数
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);//启动glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//设置单缓存和RGB模式
	glutInitWindowPosition(50, 10);//设置窗口左上角位置
	glutInitWindowSize(1200, 675);//设置
	glutCreateWindow("test3");//窗口名字

	init();
	glutDisplayFunc(myDisplay);//设置执行内容，每帧刷新一次
	glutReshapeFunc(myReshape);
	glutKeyboardFunc(myKeyboard);
	glutKeyboardUpFunc(myKeyboardUp);
	glutTimerFunc(30,mytimer,0);
	
	glutMainLoop();//进入循环和接受响应。
}

