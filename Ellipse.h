#pragma once
#include "Closed_Figure.h"

class Ellipse_Figure:public Closed_Figure {
protected:
public:
	Ellipse_Figure();
	void Draw(HDC hdc);
	Figure* CreateFigureObject();
	virtual DrawBtnFunction GetBtnPainter();
};