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
	//void StartDraw(POINT p);//������ ������������ ���������
	//int MouseUp(POINT p);// ���� �� ������
	//void EndDraw();//��������� ������ ���� ��� ��������� (��� ������������ �������� ��������������)
	//void SetScaledRect(const RECT& r);//��������� ������ ��������������
	//void GetBaseRect(RECT& r);
	void Draw(HDC hdc);
	Figure* CreateFigureObject();

};