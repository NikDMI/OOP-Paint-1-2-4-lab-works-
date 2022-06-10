#pragma once
#include <Windows.h>
#include "PainterTools.h"
#include <string>
#include <vector>

#define PI 3.1415

using namespace std;

using DrawBtnFunction = void(*)(HDC, RECT);//������� ��� ��������� ������

class Figure {//������� ����� �������������� �����
protected:
	RECT baseRect;//������������� ��� ����������� ��������
	void NormalizeRect(RECT& r);
public:
	PainterTools* painterTools = new PainterTools();//�������� ��� ���������
	Figure();
	virtual ~Figure() { delete painterTools; };
	virtual void Draw(HDC hdc)=0;
	virtual void StartDraw(POINT p) = 0;//������ ������������ ���������
	virtual void MouseMove(POINT p) {};//������������ ���� �� ������
	virtual int MouseUp(POINT p) { return 1; };// ���� �� ������  1 - ����������� ��������
	virtual void EndDraw() {};//��������� ������ ���� ��� ��������� (��� ������������ �������� ��������������)
	virtual void GetBaseRect(RECT& r);
	virtual void SetScaledRect(RECT& r)=0;//��������� ������ ��������������(��� �����������������)

	virtual Figure* CreateFigureObject()=0;//�������� ���������������� ������
	//������ ��� ������������ ����������
	virtual DrawBtnFunction GetBtnPainter() { return nullptr; }//��������� �������-��������� ��� ������ ������
};