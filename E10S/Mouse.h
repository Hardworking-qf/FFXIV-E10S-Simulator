#pragma once
struct Mouse {
	int x;// 鼠标当前x值
	int y;// 鼠标当前y值
	bool LPressed;// 左键是否被按下
	bool MPressed;// 中键是否被按下
	bool RPressed;// 右键是否被按下

	int xpress;// 鼠标按下时的x值
	int ypress;// 鼠标按下时的y值
};