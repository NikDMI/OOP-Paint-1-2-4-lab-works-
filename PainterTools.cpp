#include "pch.h"
#include "PainterTools.h"

PainterTools::PainterTools(int penW, DWORD penStyle, COLORREF penColor, DWORD brushStyle, COLORREF brushColor) {
	SetTools(penW, penStyle, penColor, brushStyle, brushColor);
}

PainterTools::PainterTools() {
	SetTools(1, PS_SOLID, RGB(0, 0, 0), BS_SOLID, RGB(200, 200, 200));
}

void PainterTools::SetTools(int penW, DWORD penStyle, COLORREF penColor, DWORD brushStyle, COLORREF brushColor) {
	this->penWidth = penW;
	this->penStyle = penStyle;
	this->penColor = penColor;
	this->brushColor = brushColor;
	this->brushStyle = brushStyle;
}

void PainterTools::InstallTools(HDC hdc) {
	LOGBRUSH lbr;
	lbr.lbColor = penColor;
	lbr.lbStyle = BS_SOLID;
	p = ExtCreatePen(PS_GEOMETRIC | penStyle, penWidth, &lbr, 0, NULL);
	lbr.lbColor = brushColor;
	if (brushStyle != BS_SOLID) {//тогда HATCHED(чтобы не вводить лишнию переменную)
		lbr.lbStyle = BS_HATCHED;
		lbr.lbHatch = brushStyle;
	}
	else {
		lbr.lbStyle = brushStyle;
	}
	br=CreateBrushIndirect(&lbr);
	SelectObject(hdc, p);
	SelectObject(hdc,br);
}

void PainterTools::FreeTools(HDC) {
	DeleteObject(br);
	DeleteObject(p);
}
