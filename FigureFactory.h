#pragma once
#include "Figure.h"
#include "WindowFramework.h"
#include <vector>


class FigureFactory {
private:
	std::vector<Figure*> registeredFigure;//массив зарегистрированных фигур в программе
	std::vector<DrawBtnFunction> btnPainters;//массив художников для кнопок фигур
	std::vector<Frame*> figureButtons;//массив кнопок
	
	const int btnDW = 10;//внешние отступы между кнопками
	const int btnDH = 10;
	int panelWidth;

	Figure* lastFigureChoise = nullptr;//последний выбор фигуры при нажатии на кнопку
public:

	void RegisterNewFigureClass(Figure* figure);//регистрация нового класса фигур в программе

	void ChooseNewFigure(Frame* btn);//нажатие на кнопку фигуры
	bool IsFigureChoosed();//была ли выбрана фигура для рисования
	Figure* CreateChoosedFigure();

	static const int btnH = 30;
	static const int btnW = 30;
	WindowClass* DrawButtonPanel(int startX, int startY, WindowClass* parent);//генерирует панель для кнопок фигур
	int GetPanelWidth();//
};


extern FigureFactory figureFactory;