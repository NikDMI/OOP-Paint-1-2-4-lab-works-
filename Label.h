#pragma once
#include "Frame.h"

namespace Label {
	extern wstring ClassName;

	void InitWindowClass();

	//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
}

enum class TextAlign {Center,Left,Right};

class LabelClass :public Frame {
protected:
	wstring Caption{};
	TextAlign TA = {TextAlign::Left};
	//COLORREF textColor = RGB(0, 0, 0);
	bool isSingleLine = true;
public:
	bool isTransparentBackground = false;

	LabelClass(wstring Caption, Position pos, int x, int y, int w, int h, Frame* parent);
	void SetCaption(wstring Caption);
	wstring GetCaption();
	void SetTextAlign(TextAlign TA);
	void DrawTextL(HDC hdc, RECT& rect);
	void SetTextColor(COLORREF color);
	void SetTransparetnBk(bool transparent);
	void SetSingleLine(bool isSingle);
	void CorrectTransparentBkColor();//функция прозрачного блиттинга некорректно работает
};

