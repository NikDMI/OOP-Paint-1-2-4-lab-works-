#pragma once
#include "Polygon.h"

class Star :public Polygon_Figure {
protected:
	POINT center;
	int R,r;//радиусы
	int edge_count;//кол-во углов
	int start_edge;//угол, с которого нужно начать рассчет(по часовой стрелке, начиная с правой точки)
public:
	Star(POINT center,int edge,int start_edge,int R,int r,COLORREF color,COLORREF bk_color);
	//Star(POINT center, int edge, int start_edge, int R, int r, COLORREF color, COLORREF bk_color);
};