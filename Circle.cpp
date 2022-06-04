#include "Circle.h"


Circle::Circle(){}

void Circle::CreateSquareFrame(RECT& r) {
	//NormalizeRect(r);
	int w = r.right - r.left;
	int h = r.bottom - r.top;
	if (w < h) {
		r.bottom = r.top + w;
	}
	else {
		r.right = r.left + h;
	}
}

void Circle::MouseMove(POINT p) {
	Ellipse_Figure::MouseMove(p);
	//CreateSquareFrame(borderRect);
	CreateSquareFrame(baseRect);
}

void Circle::SetScaledRect(RECT& r) {
	//borderRect = r;
	//NormalizeRect(borderRect);
	//CreateSquareFrame(borderRect);
	//baseRect = borderRect;
	baseRect = r;
	NormalizeRect(baseRect);
	CreateSquareFrame(baseRect);
	//CreateSquareFrame(r);
}



Figure* Circle::CreateFigureObject() {
	return new Circle();
}
