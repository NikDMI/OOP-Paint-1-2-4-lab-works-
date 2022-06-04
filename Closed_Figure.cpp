#include "pch.h"
#include "Closed_Figure.h"

Closed_Figure::Closed_Figure(){
}


void Closed_Figure::StartDraw(POINT p) {
	/*borderRect.left = p.x;
	borderRect.right = p.x;
	borderRect.bottom = p.y;
	borderRect.top = p.y;
	*/
	//drawedRect = borderRect;

	baseRect.left = p.x;
	baseRect.right = p.x;
	baseRect.bottom = p.y;
	baseRect.top = p.y;
	drawedRect = baseRect;
}

void Closed_Figure::MouseMove(POINT p) {
	drawedRect.right = p.x;
	drawedRect.bottom = p.y;
	//borderRect = drawedRect;
	//NormalizeRect(borderRect);
	baseRect = drawedRect;
	NormalizeRect(baseRect);
}

int Closed_Figure::MouseUp(POINT p) {
	//EndDraw();
	return 1;
}

void Closed_Figure::EndDraw() {
	//baseRect = borderRect;
}

void Closed_Figure::SetScaledRect(RECT& r) {
	//borderRect = r;
	//NormalizeRect(borderRect);
	//baseRect = borderRect;
	baseRect = r;
	NormalizeRect(baseRect);
}


