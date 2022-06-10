#include "Star.h"

Star::Star(POINT center, int edge, int start_edge, int R, int r, COLORREF color, COLORREF bk_color) :Polygon_Figure({},color,bk_color) {
	float dq = 2*PI / (edge*2);//растояние в полярных координатах между углами
	POINT p;
	float start = ((float)start_edge) / 180 * PI;//начальный угол в радианах
	for (int i = 0; i < edge * 2; i++) {
		if (i % 2 == 0) {
			p.x = center.x + R * cos(start + i * dq);
			p.y = center.y + R * sin(start + i * dq);
			points.push_back(p);
		}
		else {//вспомогательная точка
			p.x = center.x + r * cos(start + i * dq);
			p.y = center.y + r * sin(start + i * dq);
			points.push_back(p);
		}
	}
}