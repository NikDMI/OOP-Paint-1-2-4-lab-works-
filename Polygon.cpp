#include "Polygon.h"



Polygon_Figure::Polygon_Figure(){}

/*
void Polygon_Figure::StartDraw(POINT p) {
	points.push_back(p);
}

int Polygon_Figure::MouseUp(POINT p) {
	points.push_back(p);
	return 0;
}
*/

/*
void Polygon_Figure::EndDraw() {
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
		p.x = (w!=0)?(points[i].x-Xmin) * 100 / w:0;
		p.y = (h != 0) ? (points[i].y-Ymin) * 100 / h:0;
		pointsPersents.push_back(p);
	}
}


void Polygon_Figure::SetScaledRect(const RECT& r) {
	baseRect = r;
	NormalizeRect(baseRect);
	int w = baseRect.right - baseRect.left;
	int h = baseRect.bottom - baseRect.top;
	for (int i = 0; i < points.size(); i++) {
		points[i].x = pointsPersents[i].x * w / 100 + baseRect.left;
		points[i].y = pointsPersents[i].y * h / 100 + baseRect.top;
	}
}


void Polygon_Figure::GetBaseRect(RECT& r) {
	r = baseRect;
}
*/


void Polygon_Figure::Draw(HDC hdc) {
	painterTools->InstallTools(hdc);
	Polygon(hdc, &points[0], points.size());
	painterTools->FreeTools(hdc);
}

Figure* Polygon_Figure::CreateFigureObject() {
	return new Polygon_Figure();
}


void DrawButton_Polygon(HDC hdc, RECT r) {
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(10, 10, 10));
	SelectObject(hdc, pen);
	HBRUSH br = CreateSolidBrush(RGB(180, 250, 224));
	SelectObject(hdc, br);
	POINT p; vector<POINT> points;
	p = { 5,7 }; points.push_back(p);
	p = { 22,8 }; points.push_back(p);
	p = { 15,22 }; points.push_back(p);
	p = { 12,12 }; points.push_back(p);
	Polygon(hdc, &points[0], points.size());
	DeleteObject(pen);
}

DrawBtnFunction Polygon_Figure::GetBtnPainter() {
	return DrawButton_Polygon;
}
