#pragma once
#include "Mouse.h"
#include <GL/glut.h>
#include <vector>
using namespace std;
typedef void (*ButtonCallback)();

struct Button {
	int x;// x坐标
	int y;// y坐标
	int w;// 按钮宽
	int h;// 按钮高
	char* text;// 文字
	void* font;// 字体
	ButtonCallback callbackFunction;// 回调函数
	bool isPressed;// 是否被按下
	bool isHighlighted;// 是否高光（鼠标悬停在按钮上）
};

// 判断(x,y)是否在按钮b中
bool isPosInBtn(Button* b, int x, int y);

// 按钮按下
void ButtonPress(Button* b, int x, int y);
void ButtonsPress(int x, int y);

// 按钮松开
void ButtonRelease(Button* b, int x, int y);
void ButtonsRelease(int x, int y);

// 按钮悬停
void ButtonPassive(Button* b, int x, int y);
void ButtonsPassive(int x, int y);

// 文字
void addText(void* font, char* text, int x, int y);

// 按钮绘制
void ButtonDraw(Button* b);
void ButtonsDraw();