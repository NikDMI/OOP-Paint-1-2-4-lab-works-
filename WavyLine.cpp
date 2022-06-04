#include "WavyLine.h"


int WavyLine::MouseUp(POINT p) {
	points.push_back(p);
	return 1;
}

void WavyLine::MouseMove(POINT p) {
	points.push_back(p);
}

Figure* WavyLine::CreateFigureObject() {
	return new WavyLine();
}

void DrawButton_WavyLine(HDC hdc, RECT r) {
	HPEN pen = CreatePen(PS_SOLID, 3, RGB(10, 10, 10));
	SelectObject(hdc, pen);
	vector<POINT> points; POINT p;
	p = { 8,20 }; points.push_back(p);
	p = { 24,14 }; points.push_back(p);
	p = { 10,10 }; points.push_back(p);
	p = { 23,6 }; points.push_back(p);
	PolyBezier(hdc, &points[0], points.size());
	DeleteObject(pen);
}

DrawBtnFunction WavyLine::GetBtnPainter() {
	return DrawButton_WavyLine;
}
