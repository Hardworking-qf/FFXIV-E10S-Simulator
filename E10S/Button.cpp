#include "Button.h"
#include "Mouse.h"
vector<Button*> buttons;// 按钮数组
extern Mouse mouse;
// 判断(x,y)是否在按钮b中
bool isPosInBtn(Button* b, int x, int y) {
	if (!b) return false;
	return x > b->x &&
		x < b->x + b->w &&
		y > b->y &&
		y < b->y + b->h;
}

// 按钮按下
void ButtonPress(Button* b, int x, int y) {
	if (!b) return;
	if (isPosInBtn(b, x, y))b->isPressed = true;
}

void ButtonsPress(int x, int y) {
	for (Button* b : buttons)ButtonPress(b, x, y);
}

// 按钮松开
void ButtonRelease(Button* b, int x, int y) {
	if (!b) return;
	if (isPosInBtn(b, mouse.xpress, mouse.ypress) &&
		isPosInBtn(b, x, y)) {// 起始点和结束点都要在按钮内
		if (b->callbackFunction) {// 回调函数存在 触发回调函数
			b->callbackFunction();
		}
	}
	b->isPressed = false;
}

void ButtonsRelease(int x, int y) {
	for (Button* b : buttons)ButtonRelease(b, x, y);
}

// 按钮悬停
void ButtonPassive(Button* b, int x, int y) {
	if (!b)return;
	if (isPosInBtn(b, x, y)) {
		if (!b->isHighlighted) {
			b->isHighlighted = true;
			glutPostRedisplay();
		}
	}
	else if (b->isHighlighted) {
		b->isHighlighted = false;
		glutPostRedisplay();
	}
}

void ButtonsPassive(int x, int y) {
	for (Button* b : buttons)ButtonPassive(b, x, y);
}

// 文字
void addText(void* font, char* text, int x, int y) {
	glRasterPos2i(x, y);

	while (*text != '\0') {
		glutBitmapCharacter(font, *text);
		++text;
	}
}

// 按钮绘制
void ButtonDraw(Button* b) {
	if (!b)return;

	// 按钮背景颜色
	if (b->isHighlighted) glColor3f(0.7f, 0.7f, 0.8f);
	else glColor3f(0.6f, 0.6f, 0.6f);

	// 按钮背景
	glBegin(GL_QUADS); {
		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->h);
		glVertex2i(b->x + b->w, b->y + b->h);
		glVertex2i(b->x + b->w, b->y);
	} glEnd();

	// 边线
	glLineWidth(3);

	// 左、上边线
	if (b->isPressed) glColor3f(0.4f, 0.4f, 0.4f);//按下的颜色
	else glColor3f(0.8f, 0.8f, 0.8f);//释放的颜色 

	glBegin(GL_LINE_STRIP); {
		glVertex2i(b->x + b->w, b->y);
		glVertex2i(b->x, b->y);
		glVertex2i(b->x, b->y + b->h);
	}glEnd();

	// 右、下边线
	if (b->isPressed) glColor3f(0.8f, 0.8f, 0.8f);
	else glColor3f(0.4f, 0.4f, 0.4f);

	glBegin(GL_LINE_STRIP); {
		glVertex2i(b->x, b->y + b->h);
		glVertex2i(b->x + b->w, b->y + b->h);
		glVertex2i(b->x + b->w, b->y);
	}glEnd();

	glLineWidth(1);

	// 计算文字坐标
	int textx = b->x + (b->w - glutBitmapLength(b->font, (const unsigned char*)b->text)) / 2;
	int texty = b->y + (b->h + 10) / 2;

	// 按钮按下时的文字效果
	if (b->isPressed) {
		textx += 2;
		texty += 2;
	}

	//高光时的文字效果
	if (b->isHighlighted) {
		glColor3f(0, 0, 0);
		addText(b->font, b->text, textx, texty);
		textx--;
		texty--;
	}

	glColor3f(1, 1, 1);
	addText(b->font, b->text, textx, texty);
}

void ButtonsDraw() {
	for (Button* b : buttons)ButtonDraw(b);
}