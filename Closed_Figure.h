#pragma once
#include "Figure.h"

class Closed_Figure: public Figure {
protected:
	RECT drawedRect;//��������������� �������������(��� ������������ ������� ����)
	//RECT borderRect;//������������� ��� ���������
public:
	Closed_Figure();
	void StartDraw(POINT p);//������ ������������ ���������
	void MouseMove(POINT p);//������������ ���� �� ������
	void EndDraw();//��������� ������ ���� ��� ���������
	int MouseUp(POINT p);// ���� �� ������  1 - ����������� ��������
	void SetScaledRect(RECT& r);//��������� ������ ��������������
};
