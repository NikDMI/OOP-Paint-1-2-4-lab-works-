#pragma once
#include "Polyline.h"

class WavyLine :public Polyline_Figure {
public:
	//WavyLine(COLORREF color);
	int MouseUp(POINT p);// мыши по холсту
	void MouseMove(POINT p);
	Figure* CreateFigureObject();

};