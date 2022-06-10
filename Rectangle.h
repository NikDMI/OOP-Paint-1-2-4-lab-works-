#pragma once
#include "Closed_Figure.h"

class Rectangle_Figure : public Closed_Figure {
protected:
	int w, h;
public:
	//Rectangle_Figure(int x0, int y0, int x1, int y1, COLORREF color, COLORREF bk_color);
	//Rectangle_Figure(int x0, int y0, int x1, int y1);
	Rectangle_Figure();
	//void StartDraw(POINT p);//начать динамическое рисование
	//int MouseUp(POINT p);// мыши по холсту
	//void MouseMove(POINT p);//передвижение мыши по холсту
	void Draw(HDC hdc);
	Figure* CreateFigureObject();
	virtual DrawBtnFunction GetBtnPainter();

};