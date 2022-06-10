#pragma once
#include "Ellipse.h"

class Circle : public Ellipse_Figure {
	void CreateSquareFrame(RECT& r);
public:
	//Circle(COLORREF color, COLORREF bk_color);
	//Circle(POINT center, int R);
	Circle();
	void MouseMove(POINT p);//������������ ���� �� ������
	void SetScaledRect(RECT& r);//��������� ������ ��������������
	Figure* CreateFigureObject();
	virtual DrawBtnFunction GetBtnPainter();
};