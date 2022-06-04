#pragma once
#include "Figure.h"
#include "WindowFramework.h"
#include <vector>


class FigureFactory {
private:
	std::vector<Figure*> registeredFigure;//������ ������������������ ����� � ���������
	std::vector<DrawBtnFunction> btnPainters;//������ ���������� ��� ������ �����
	std::vector<Frame*> figureButtons;//������ ������
	
	const int btnDW = 10;//������� ������� ����� ��������
	const int btnDH = 10;
	int panelWidth;

	Figure* lastFigureChoise = nullptr;//��������� ����� ������ ��� ������� �� ������
public:

	void RegisterNewFigureClass(Figure* figure);//����������� ������ ������ ����� � ���������

	void ChooseNewFigure(Frame* btn);//������� �� ������ ������
	bool IsFigureChoosed();//���� �� ������� ������ ��� ���������
	Figure* CreateChoosedFigure();

	static const int btnH = 30;
	static const int btnW = 30;
	WindowClass* DrawButtonPanel(int startX, int startY, WindowClass* parent);//���������� ������ ��� ������ �����
	int GetPanelWidth();//
};


extern FigureFactory figureFactory;