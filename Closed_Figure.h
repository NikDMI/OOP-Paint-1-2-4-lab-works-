#pragma once
#include "Figure.h"

class Closed_Figure: public Figure {
protected:
	RECT drawedRect;//вспомогатлеьный прямоугольник(при передвижении зажатой мыши)
	//RECT borderRect;//прямоугольник при рисовании
public:
	Closed_Figure();
	void StartDraw(POINT p);//начать динамическое рисование
	void MouseMove(POINT p);//передвижение мыши по холсту
	void EndDraw();//отпустили кнопку мыши при рисовании
	int MouseUp(POINT p);// мыши по холсту  1 - закончилось рисовани
	void SetScaledRect(RECT& r);//установка своего прямоугольника
};
