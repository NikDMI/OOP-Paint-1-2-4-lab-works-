#include "Rectangle.h"

Rectangle_Figure::Rectangle_Figure()
{}

/*
void Rectangle_Figure::StartDraw(POINT p) {
	points[0] = p;
	points[1] = p;
}

int Rectangle_Figure::MouseUp(POINT p) {
	points[1] = p;
	return 1;
}

void Rectangle_Figure::MouseMove(POINT p) {
	points[1] = p;
}
*/



void Rectangle_Figure::Draw(HDC hdc) {
	painterTools->InstallTools(hdc);
	//Rectangle(hdc, borderRect.left, borderRect.top, borderRect.right, borderRect.bottom);
	Rectangle(hdc, baseRect.left, baseRect.top, baseRect.right, baseRect.bottom);
	painterTools->FreeTools(hdc);
}

Figure* Rectangle_Figure::CreateFigureObject() {
	return new Rectangle_Figure();
}

void DrawButton_Rectangle(HDC hdc, RECT r) {
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(10, 10, 10));
	SelectObject(hdc, pen);
	HBRUSH br = CreateSolidBrush(RGB(180, 250, 224));
	SelectObject(hdc, br);
	Rectangle(hdc, 5, 10, 25, 20);
	DeleteObject(pen);
}

DrawBtnFunction Rectangle_Figure::GetBtnPainter() {
	return DrawButton_Rectangle;
}
