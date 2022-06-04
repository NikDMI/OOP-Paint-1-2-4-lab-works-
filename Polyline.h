#pragma once
#include "Open_Figure.h"

class Polyline_Figure:public Open_Figure{
protected:
	//vector<POINT> nodes;
	//vector<POINT> nodesPersents;
public:
	//Polyline_Figure(vector<POINT> points, COLORREF color);
	//Polyline_Figure(COLORREF color);
	Polyline_Figure();
	//void StartDraw(POINT p);//начать динамическое рисование
	//int MouseUp(POINT p);// мыши по холсту
	//void EndDraw();//отпустили кнопку мыши при рисовании (для установления базового прямоугольника)
	//void SetScaledRect(const RECT& r);//установка своего прямоугольника
	//void GetBaseRect(RECT& r);
	void Draw(HDC hdc);
	Figure* CreateFigureObject();

};