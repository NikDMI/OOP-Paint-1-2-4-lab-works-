#pragma once
#include "Open_Figure.h"

class Polygon_Figure :public Open_Figure {
protected:
	
public:
	//Polygon_Figure(vector<POINT> points);
	Polygon_Figure();
	//void StartDraw(POINT p);//������ ������������ ���������
	///int MouseUp(POINT p);// ���� �� ������
	//void EndDraw();//��������� ������ ���� ��� ��������� (��� ������������ �������� ��������������)
	//void SetScaledRect(const RECT& r);//��������� ������ ��������������
	//void GetBaseRect(RECT& r);
	void Draw(HDC hdc);
	Figure* CreateFigureObject();

};