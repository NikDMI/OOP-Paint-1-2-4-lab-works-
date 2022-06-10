#pragma once
#include "Figure.h"

class Open_Figure : public Figure {
protected:
	vector<POINT> points;//���������� �����, ������� ������������ ��� ���������()
	vector<POINT> pointsPersents;//������������� �����, � ���������
public:
	Open_Figure();
	void StartDraw(POINT p);
	int MouseUp(POINT p);
	void SetScaledRect(RECT& r);//��������� ������ ��������������
	void EndDraw();
};