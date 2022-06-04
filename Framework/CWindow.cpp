#include "CWindow.h"

#pragma comment( lib, "Msimg32.lib" )

using namespace Window;

namespace Window {
	wstring ClassName = L"WindowClass";
}


void Window::InitWindowClass() {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProc;
	wc.hInstance = mainInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = &ClassName[0];
	wc.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszMenuName = NULL;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DLIGHT);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wc);
}

WindowClass::WindowClass(wstring WindowName, Window::WindowType type, Position pos, int x, int y, int w, int h, Frame* parent):
	Frame(mainInstance, Window::ClassName, WindowName, WS_BORDER, pos,x, y, w, h, parent) 
{
	bk_color = COLOR_3DFACE;
	this->type = type;
	switch (type) {
	case Window::WindowType::MainWindow://главное окно с выходом
		WindowStyle = WS_OVERLAPPEDWINDOW;
		break;
	case Window::WindowType::PanelWindow:
		WindowStyle = 0;
		break;
	}
}

void WindowClass::CreateWnd() {
	Frame::CreateWnd();
	int size = childControls.size();
	for (int i = 0; i < size; i++) {
		childControls[i]->CreateWnd();
	}
}

void WindowClass::AddChild(Frame* child) {
	child->parent = (Frame*)this;
	child->WindowStyle |= WS_CHILD;
	childControls.push_back(child);
	if (hWnd != 0) {//если окно уже было создано
		child->CreateWnd();
	}
}

void WindowClass::ChangeChildrenSize() {
	int size = childControls.size();
	for (int i = 0; i < size; i++) {
		childControls[i]->CheckSize();
	}
}



LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	WindowClass* wc = (WindowClass*)GetWindowByHWND(hWnd);
	HDC hdc;
	PAINTSTRUCT ps;
	RECT clRect;
	HBRUSH br;
	switch (uMsg) {
	case WM_SIZE:
		if (wc != NULL) {
			wc->wReal = LOWORD(lParam);
			wc->hReal = HIWORD(lParam);
			wc->ChangeChildrenSize();
		}
		break;
	case WM_PAINT:
		GetClientRect(hWnd, &clRect);
		hdc = BeginPaint(hWnd, &ps);
		wc->PaintWindow(hdc, clRect);
		EndPaint(hWnd, &ps);
		break;
	case WM_ERASEBKGND:
		break;
	case WM_CLOSE:
		if (wc->type == Window::WindowType::MainWindow) {
			PostQuitMessage(0);
		}
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}