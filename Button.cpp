#include "Button.h"

namespace CButton {
	wstring ClassName=L"MyButton";
}

Button::Button(Position pos, int x, int y, int w, int h, Frame* parent):
	Frame(mainInstance, CButton::ClassName, L"Button", 0, pos, x, y, w, h,parent) {
}

void Button::SetEvent(MouseEvents me, OnMouse act) {
	switch (me) {
	case MouseEvents::OnClick:
		this->OnClick = act;
		break;
	case MouseEvents::OnMove:
		this->OnMove = act;
		break;
	case MouseEvents::OnLeave:
		this->OnLeave = act;
		break;
	case MouseEvents::OnLBDown:
		this->OnLBDown = act;
		break;
	}
}

void Button::CreateLeave() {
	if (flagLeave != 1) {
		flagLeave = 1;
		TRACKMOUSEEVENT me;
		me.cbSize = sizeof(TRACKMOUSEEVENT);
		me.dwFlags = TME_LEAVE;
		me.dwHoverTime = HOVER_DEFAULT;
		me.hwndTrack = hWnd;
		TrackMouseEvent(&me);
	}
}



void CButton::InitWindowClass() {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = CButton::WndProc;
	wc.hInstance = mainInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = &CButton::ClassName[0];
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszMenuName = NULL;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DLIGHT);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wc);
}

void Button::SetCaption(wstring Caption) {
	this->Caption = Caption;
	if (hWnd != 0) {
		InvalidateRect(hWnd, NULL, FALSE);
	}
}

void Button::DrawCaption(HDC hdc,RECT& rect) {
	SetBkMode(hdc, TRANSPARENT);
	DrawText(hdc, &Caption[0], -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

LRESULT CALLBACK CButton::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Button* wc = (Button*)GetWindowByHWND(hWnd);
	HDC hdc;
	PAINTSTRUCT ps;
	RECT clRect;
	HBRUSH br;
	switch (uMsg) {
	case WM_SIZE:
		
		break;
	case WM_PAINT:
		GetClientRect(hWnd, &clRect);
		hdc = BeginPaint(hWnd, &ps);
		wc->PaintWindow(hdc,clRect);
		wc->DrawCaption(hdc, clRect);
		EndPaint(hWnd, &ps);
		break;
	case WM_ERASEBKGND:
		break;
	case WM_LBUTTONUP:
		if (wc->OnClick != NULL) {
			wc->OnClick(wc);
		}
		break;
	case WM_LBUTTONDOWN:
		if (wc->OnLBDown != NULL) {
			wc->OnLBDown(wc);
		}
		break;
	case WM_MOUSEMOVE:
		wc->CreateLeave();
		if (wc->OnMove != NULL) {
			wc->OnMove(wc);
		}
		break;
	case WM_MOUSELEAVE:
		if (wc->OnLeave != NULL) {
			wc->OnLeave(wc);
		}
		wc->flagLeave = 0;
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}