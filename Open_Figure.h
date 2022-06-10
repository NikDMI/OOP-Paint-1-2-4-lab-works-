#pragma once
#include "Figure.h"

class Open_Figure : public Figure {
protected:
	vector<POINT> points;//фбсолютные точки, которые используются при рисовании()
	vector<POINT> pointsPersents;//относительные точки, в процентах
public:
	Open_Figure();
	void StartDraw(POINT p);
	int MouseUp(POINT p);
	void SetScaledRect(RECT& r);//установка своего прямоугольника
	void EndDraw();
};