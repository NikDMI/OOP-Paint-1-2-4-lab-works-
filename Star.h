#pragma once
#include "Polygon.h"

class Star :public Polygon_Figure {
protected:
	POINT center;
	int R,r;//�������
	int edge_count;//���-�� �����
	int start_edge;//����, � �������� ����� ������ �������(�� ������� �������, ������� � ������ �����)
public:
	Star(POINT center,int edge,int start_edge,int R,int r,COLORREF color,COLORREF bk_color);
	//Star(POINT center, int edge, int start_edge, int R, int r, COLORREF color, COLORREF bk_color);
};