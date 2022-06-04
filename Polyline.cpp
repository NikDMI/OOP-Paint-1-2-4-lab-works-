#include "Polyline.h"

Polyline_Figure::Polyline_Figure() : Open_Figure() {
}

/*
void Polyline_Figure::StartDraw(POINT p) {
	points.push_back(p);
}

int Polyline_Figure::MouseUp(POINT p) {
	points.push_back(p);
	return 0;
}
*/

/*
void Polyline_Figure::EndDraw() {
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
		p.x = (w != 0) ? (points[i].x - Xmin) * 10000 / w : 0;
		p.y = (h != 0) ? (points[i].y - Ymin) * 10000 / h : 0;
		pointsPersents.push_back(p);
	}
}
*/

/*
void Polyline_Figure::SetScaledRect(const RECT& r) {
	baseRect = r;
	NormalizeRect(baseRect);
	int w = baseRect.right - baseRect.left;
	int h = baseRect.bottom - baseRect.top;
	for (int i = 0; i < points.size(); i++) {
		points[i].x = pointsPersents[i].x * w / 10000 + baseRect.left;
		points[i].y = pointsPersents[i].y * h / 10000 + baseRect.top;
	}
}


void Polyline_Figure::GetBaseRect(RECT& r) {
	r = baseRect;
}
*/



void Polyline_Figure::Draw(HDC hdc) {
	painterTools->InstallTools(hdc);
	Polyline(hdc, &points[0], points.size());
	painterTools->FreeTools(hdc);
}

Figure* Polyline_Figure::CreateFigureObject() {
	return new Polyline_Figure();
}


void DrawButton_Line(HDC hdc, RECT r) {//рисование кнопки линия
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(10, 10, 10));
	SelectObject(hdc, pen);
	MoveToEx(hdc, 8, 21, NULL);
	LineTo(hdc, 21, 8);
	DeleteObject(pen);
}

DrawBtnFunction Polyline_Figure::GetBtnPainter() {
	return DrawButton_Line;
}

