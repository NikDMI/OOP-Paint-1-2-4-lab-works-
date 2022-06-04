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
