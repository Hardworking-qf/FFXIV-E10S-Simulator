#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#include "Base.h"
#include "Button.h"
#include "Mechanics.h"
extern int winw, winh;
extern Player player;
extern Boss boss;
extern void (*DrawMechanics)(void);
extern time_t currT, lastT, deltaT, MechanicsStartT;
bool Keydown[4] = { false, false, false, false };// WASD
extern Rect safeZone;

extern vector<Button*> buttons;
void ButtonsInit() {
	// 按钮
	buttons.push_back(new Button{ 5,5, 100,25,(char*)"Front-Back", GLUT_BITMAP_HELVETICA_10,[]() {
		player.SHADOW_DIRE = -1;
		 FrontBack();
		} });
	buttons.push_back(new Button{ 120,5, 100,25,(char*)"4 Front-Back", GLUT_BITMAP_HELVETICA_10,[]() {
		player.SHADOW_DIRE = -1;
		 FrontBack4();
		} });
	buttons.push_back(new Button{ 5,40, 100,25,(char*)"Left-Right", GLUT_BITMAP_HELVETICA_10,[]() {
		player.SHADOW_DIRE = -1;
		  LeftRight();
		} });
	buttons.push_back(new Button{ 120,40, 100,25,(char*)"4 Left-Right", GLUT_BITMAP_HELVETICA_10,[]() {
		player.SHADOW_DIRE = -1;
		  LeftRight4();
		} });
	buttons.push_back(new Button{ 5,75, 100,25,(char*)"PlaceShadow", GLUT_BITMAP_HELVETICA_10,[]() {
		boss.SHADOW_DIRE = -1;
		PlaceShadow();
		} });
	buttons.push_back(new Button{ 120,75, 100,25,(char*)"2 PlaceShadow", GLUT_BITMAP_HELVETICA_10,[]() {
		boss.SHADOW_DIRE = -1;
		PlaceShadow2();
		} });
	buttons.push_back(new Button{ 5,110, 100,25,(char*)"All Random", GLUT_BITMAP_HELVETICA_10,[]() {
		boss = Boss{ NORTH, -1, -1 };
		player.SHADOW_DIRE = -1;
		safeZone = Rect{ {0,0},{0,0} };
		srand(currT);
		switch (rand() % 6) {
		case 0:FrontBack(); break;
		case 1:FrontBack4(); break;
		case 2:LeftRight(); break;
		case 3:LeftRight4(); break;
		case 4:PlaceShadow(); break;
		case 5:PlaceShadow2(); break;
		};
		} });
	buttons.push_back(new Button{ 120,110, 100,25,(char*)"Initialize", GLUT_BITMAP_HELVETICA_10,[]() {
		boss = Boss{ NORTH, -1, -1 };
		player = Player{ { 0.5,0.5 },-1 };
		safeZone = Rect{ {0,0},{0,0} };
		DrawMechanics = NULL;
		} });
}

void Resize(int w, int h) {
	winw = w;
	winh = h;
	glViewport(0,0, w, h);
}

void DrawScene() {
	DrawPlatform();
	if (DrawMechanics)DrawMechanics();
	DrawBoss();
	DrawPlayer();
}

void Draw() {
	int minWH = winw < winh ? winw : winh;
	double offx = ((double)winw - minWH) / minWH / 2;
	double offy = ((double)winh - minWH) / minWH / 2;


	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0 - offx, 1 + offx, 0 - offy, 1 + offy, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	DrawScene();

	currT = clock();
	deltaT = currT - lastT;
	lastT = currT;
	if (Keydown[0] && player.pos.y <= 1) player.pos += Vector2Df{ 0,MOV_SPD };
	if (Keydown[1] && player.pos.x >= 0) player.pos += Vector2Df{ -MOV_SPD,0 };
	if (Keydown[2] && player.pos.y >= 0) player.pos += Vector2Df{ 0,-MOV_SPD };
	if (Keydown[3] && player.pos.x <= 1) player.pos += Vector2Df{ MOV_SPD,0 };

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, winw, winh, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	ButtonsDraw();
	glutSwapBuffers();
	glutPostRedisplay();
}
void Init() {

}

void KeyBoard(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':Keydown[0] = true; break;
	case 'a':Keydown[1] = true; break;
	case 's':Keydown[2] = true; break;
	case 'd':Keydown[3] = true; break;
	default:break;
	}
}
void KeyBoardUp(unsigned char key, int x, int y) {
	switch (key) {
	case 'w':Keydown[0] = false; break;
	case 'a':Keydown[1] = false; break;
	case 's':Keydown[2] = false; break;
	case 'd':Keydown[3] = false; break;
	default:break;
	}
	
}
extern Mouse mouse;
// 鼠标拖动
void MouseMotion(int x, int y) {
	// 更新鼠标位置
	mouse.x = x;
	mouse.y = y;
	ButtonsPassive(x, y);

	glutPostRedisplay();
}

// 鼠标滑动
void MousePassiveMotion(int x, int y) {
	// 更新鼠标位置
	mouse.x = x;
	mouse.y = y;
	ButtonsPassive(x, y);
}
void MouseButton(int button, int state, int x, int y) {
	// 刷新鼠标坐标
	mouse.x = x;
	mouse.y = y;

	if (state == GLUT_DOWN) {
		if (!mouse.LPressed) {// 设定起点
			mouse.xpress = x;
			mouse.ypress = y;
		}

		switch (button) {
		case GLUT_LEFT_BUTTON:
			mouse.LPressed = true;
			ButtonsPress(x, y);
			break;
		case GLUT_MIDDLE_BUTTON:
			mouse.MPressed = true;
			break;
		case GLUT_RIGHT_BUTTON:
			mouse.RPressed = true;
			break;
		}
	}
	else {
		switch (button) {
		case GLUT_LEFT_BUTTON:
			mouse.LPressed = false;
			ButtonsRelease(x, y);
			break;
		case GLUT_MIDDLE_BUTTON:
			mouse.MPressed = false;
			break;
		case GLUT_RIGHT_BUTTON:
			mouse.RPressed = false;
			break;
		}
	}
	// 强制重新绘制
	glutPostRedisplay();
}
int main(int argc, char** argv) {
	
	ButtonsInit();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(winw,winh);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("E10S");

	glutDisplayFunc(Draw);
	glutReshapeFunc(Resize);
	glutKeyboardFunc(KeyBoard);
	glutKeyboardUpFunc(KeyBoardUp);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMotion);
	glutPassiveMotionFunc(MousePassiveMotion);
	Init();

	glutMainLoop();
}