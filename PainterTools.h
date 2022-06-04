#pragma once
#include <Windows.h>

class PainterTools {
private:
	int penWidth;
	COLORREF penColor;
	DWORD penStyle;
	COLORREF brushColor;
	DWORD brushStyle;
	HPEN p;
	HBRUSH br;
public:
	PainterTools(int penW, DWORD penStyle, COLORREF penColor, DWORD brushStyle, COLORREF brushColor);
	PainterTools();
	void SetTools(int penW, DWORD penStyle, COLORREF penColor, DWORD brushStyle, COLORREF brushColor);
	void InstallTools(HDC);
	void FreeTools(HDC);
};
