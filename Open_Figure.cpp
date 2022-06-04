#include "Open_Figure.h"

Open_Figure::Open_Figure(){
}

const int precision = 10000;//точность в процентах

void Open_Figure::StartDraw(POINT p) {
	points.push_back(p);
}

int Open_Figure::MouseUp(POINT p) {
	points.push_back(p);
	return 0;
}

void Open_Figure::EndDraw() {
	int Xmin = points[0].x, Xmax = points[0].x, Ymin = points[0].y, Ymax = points[0].y;
	for (auto& p : points) {
		if (p.x > Xmax) Xmax = p.x;
		if (p.x < Xmin) Xmin = p.x;
		if (p.y > Ymax) Ymax = p.y;
		if (p.y < Ymin) Ymin = p.y;
	}
	int w = Xmax - Xmin;
	int h = Ymax - Ymin;
	baseRect = { Xmin,Ymin,Xmax,Ymax };
	POINT p;
	for (int i = 0; i < points.size(); i++) {
		p.x = (w != 0) ? (points[i].x - Xmin) * precision / w : 0;
		p.y = (h != 0) ? (points[i].y - Ymin) * precision / h : 0;
		pointsPersents.push_back(p);
	}
}

void Open_Figure::SetScaledRect(RECT& r) {
	baseRect = r;
	NormalizeRect(baseRect);
	int w = baseRect.right - baseRect.left;
	int h = baseRect.bottom - baseRect.top;
	for (int i = 0; i < points.size(); i++) {
		points[i].x = pointsPersents[i].x * w / precision + baseRect.left;
		points[i].y = pointsPersents[i].y * h / precision + baseRect.top;
	}
}



