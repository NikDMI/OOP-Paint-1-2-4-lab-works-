#pragma once
#include "Polyline.h"

class WavyLine :public Polyline_Figure {
public:
	//WavyLine(COLORREF color);
	int MouseUp(POINT p);// ���� �� ������
	void MouseMove(POINT p);
	Figure* CreateFigureObject();

};