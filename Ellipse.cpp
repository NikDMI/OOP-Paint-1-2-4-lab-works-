#include "Ellipse.h"

Ellipse_Figure::Ellipse_Figure(){
}

/*
void Ellipse_Figure::StartDraw(POINT p) {
	borderRect.left = p.x;
	borderRect.right = p.x;
	borderRect.bottom = p.y;
	borderRect.top = p.y;
	drawedRect = borderRect;
}

void Ellipse_Figure::MouseMove(POINT p) {
	drawedRect.right = p.x;
	drawedRect.bottom = p.y;
	borderRect = drawedRect;
	NormalizeRect(borderRect);
}

int Ellipse_Figure::MouseUp(POINT p) {
	//EndDraw();
	return 1;
}

void Ellipse_Figure::EndDraw() {
	baseRect = borderRect;
}

void Ellipse_Figure::SetScaledRect(const RECT& r) {
	borderRect = r;
	NormalizeRect(borderRect);
	baseRect = borderRect;
}
*/

void Ellipse_Figure::Draw(HDC hdc) {
	painterTools->InstallTools(hdc);
	//Ellipse(hdc, borderRect.left, borderRect.top, borderRect.right, borderRect.bottom);
	Ellipse(hdc, baseRect.left, baseRect.top, baseRect.right, baseRect.bottom);
	painterTools->FreeTools(hdc);
}

Figure* Ellipse_Figure::CreateFigureObject() {
	return new Ellipse_Figure();
}



