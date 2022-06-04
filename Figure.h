#pragma once
#include <Windows.h>
#include "PainterTools.h"
#include <string>
#include <vector>

#define PI 3.1415

using namespace std;

using DrawBtnFunction = void(*)(HDC, RECT);//функция для рисования кнопки

class Figure {//главный класс геометрических фигур
protected:
	RECT baseRect;//прямоугольник для соотношения размеров
	void NormalizeRect(RECT& r);
public:
	PainterTools* painterTools = new PainterTools();//элементы для рисования
	Figure();
	virtual ~Figure() { delete painterTools; };
	virtual void Draw(HDC hdc)=0;
	virtual void StartDraw(POINT p) = 0;//начать динамическое рисование
	virtual void MouseMove(POINT p) {};//передвижение мыши по холсту
	virtual int MouseUp(POINT p) { return 1; };// мыши по холсту  1 - закончилось рисовани
	virtual void EndDraw() {};//отпустили кнопку мыши при рисовании (для установления базового прямоугольника)
	virtual void GetBaseRect(RECT& r);
	virtual void SetScaledRect(RECT& r)=0;//установка своего прямоугольника(при трансформировании)

	virtual Figure* CreateFigureObject()=0;//создание соответствующего класса
	//методы для графического интерфейса
	virtual DrawBtnFunction GetBtnPainter() { return nullptr; }//получения функции-художника для кнопки фигуры
};