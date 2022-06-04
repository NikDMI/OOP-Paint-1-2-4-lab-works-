#pragma once
#include "Frame.h"

class Button;


namespace CButton {
	extern wstring ClassName;
	void InitWindowClass();
	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
}


class Button :public Frame {
private:
public:
	int flagLeave = -1;
	void CreateLeave();
	wstring Caption;
	OnMouse OnClick=NULL;
	OnMouse OnMove=NULL;
	OnMouse OnLeave = NULL;
	OnMouse OnLBDown=NULL;
	Button(Position pos, int x, int y, int w, int h, Frame* parent);
	void SetEvent(MouseEvents me,OnMouse act);
	void SetCaption(wstring Caption);
	void DrawCaption(HDC hdc, RECT& rect);
};