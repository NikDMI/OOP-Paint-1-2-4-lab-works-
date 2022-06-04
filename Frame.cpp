#include "Frame.h"

int wGlobal, hGlobal;
HINSTANCE mainInstance;
map<HWND, Frame*> windowTree;
const float sqrt2 = 1.41421356237;

Frame::Frame(HINSTANCE hInstance, wstring ClassName, wstring WindowName, DWORD style, Position pos, int x, int y, int w, int h,Frame* parent) {
	this->hInstance = hInstance;
	this->ClassName = ClassName;
	this->WindowName = WindowName;
	this->WindowStyle = style;
	this->position = pos;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->parent = parent;
}

void Frame::CreateWnd() {
	int wParent, hParent;
	int W, H, X, Y;
	if (parent != NULL) {
		wParent = parent->wReal;
		hParent = parent->hReal;
	}
	else {
		wParent = wGlobal;
		hParent = hGlobal;
	}
	switch (position) {
	case Position::absoluteAll:
		wReal = w;
		hReal = h;
		X = x;
		Y = y;
		H = h;
		W = w;
		break;
	case Position::absolutePos:
		wReal = wParent * w / 100;
		hReal = hParent * h / 100;
		X = x;
		Y = y;
		H = hReal;
		W = wReal;
		break;
	case Position::absolutePosSpaceDown:
		wReal = wParent - x;
		hReal = hParent - y;
		X = x;
		Y = y;
		H = hReal;
		W = wReal;
		break;
	case Position::absolutePosH:
		wReal = wParent * w / 100;
		hReal = h;
		X = x;
		Y = y;
		H = hReal;
		W = wReal;
		break;
	case Position::absoluteSize:
		wReal = w;
		hReal = h;
		X = wParent*x/100;
		Y = hParent*y/100;
		H = h;
		W = w;
		break;
	case Position::percentAll:
		wReal = wParent * w / 100;
		hReal = hParent * h / 100;
		X = wParent * x / 100;
		Y = hParent * y / 100;
		H = hReal;
		W = wReal;
		break;
	}
	if(parent!=NULL){
		hWnd=CreateWindow(&ClassName[0], &WindowName[0], WindowStyle, X, Y, W, H, parent->hWnd, NULL, hInstance, 0);
	}
	else {
		hWnd=CreateWindow(&ClassName[0], &WindowName[0], WindowStyle, X, Y, W, H, NULL, NULL, hInstance, 0);
	}
	windowTree.insert(pair<HWND,Frame*>(hWnd,this));//добавление окна к дереву окон
	if (borderRadius > 0) {
		HRGN rgn = CreateRoundRectRgn(0, 0, wReal, hReal, borderRadius, borderRadius);
		SetWindowRgn(hWnd, rgn, FALSE);
	}
	ShowWindow(hWnd, SW_SHOW);
}

void Frame::SetBorder(Border border, BorderNum bn) {
	switch (bn) {
	case BorderNum::btm:
		border_bottom = border;
		break;
	case BorderNum::top:
		border_top = border;
		break;
	case BorderNum::left:
		border_left = border;
		break;
	case BorderNum::right:
		border_right = border;
		break;
	}
	if (hWnd != 0) {
		InvalidateRect(hWnd, NULL, FALSE);
	}
}

void DrawStyleBorder(HDC hdc,vector<POINT>& points, Border& border) {
	HBRUSH br, oldBr;
	HPEN pen, oldPen;
	switch (border.style) {
	case BorderStyle::solid:
		br = CreateSolidBrush(border.color);
		pen = CreatePen(PS_SOLID, 1, border.color);
		oldBr = (HBRUSH)SelectObject(hdc, br);
		oldPen = (HPEN)SelectObject(hdc, pen);
		Polygon(hdc, &points[0], 4);
		SelectObject(hdc, oldBr);
		SelectObject(hdc, oldPen);
		DeleteObject(br);
		DeleteObject(pen);
		break;
	}
}

void Frame::DrawBorder(HDC hdc,RECT& r) {
	vector<POINT> points(4);
	int width;
	if (border_top.width) {
		width = border_top.width;
		points[0] = {0,0};
		points[1] = { r.right,0 };
		points[2] = { r.right-(LONG)(width * sqrt2)+2,width };
		points[3] = { (LONG)(width*sqrt2)-2,width };
		DrawStyleBorder(hdc, points, border_top);
	}
	if (border_bottom.width) {
		width = border_bottom.width;
		points[0] = { 0,r.bottom };
		points[1] = { r.right,r.bottom };
		points[2] = { r.right - (LONG)(width * sqrt2)+2,r.bottom-width };
		points[3] = { (LONG)(width * sqrt2)-2,r.bottom-width };
		DrawStyleBorder(hdc, points, border_bottom);
	}
	if (border_left.width) {
		width = border_left.width;
		points[0] = { 0,0 };
		points[1] = { 0,r.bottom };
		points[2] = { width,r.bottom - (LONG)(width * sqrt2)+2 };
		points[3] = { width,(LONG)(width * sqrt2)-2 };
		DrawStyleBorder(hdc, points, border_left);
	}
	if (border_right.width) {
		width = border_right.width;
		points[0] = { r.right,0 };
		points[1] = { r.right,r.bottom };
		points[2] = { r.right-width,r.bottom - (LONG)(width * sqrt2)+2 };
		points[3] = { r.right-width,(LONG)(width * sqrt2)-2 };
		DrawStyleBorder(hdc, points, border_right);
	}
}

void Frame::SetPicture(HBITMAP bmp, bool isTransparent, COLORREF transparent_color) {
	background_picture = bmp;
	isTrasparentPic = isTransparent;
	this->transparent_color = transparent_color;
	if (hWnd != 0) {
		InvalidateRect(hWnd, NULL, FALSE);
	}
}


void Frame::SetBackgroundColor(COLORREF cl) {
	bk_color = cl;
	if (hWnd != 0) {
		InvalidateRect(hWnd, NULL, FALSE);
	}
}

void Frame::FillBkColor(HDC hdc,RECT& r) {
	HBRUSH br;
	br = CreateSolidBrush(bk_color);
	FillRect(hdc,&r,br);
	DeleteObject(br);
}

void Frame::CheckSize() {
	if (parent != NULL) {
		int wParent, hParent;
		int W, H, X, Y;
		wParent = parent->wReal;
		hParent = parent->hReal;
		switch (position) {
		case Position::absoluteAll:
			break;
		case Position::absolutePos:
			wReal = wParent * w / 100;
			hReal = hParent * h / 100;
			X = x;
			Y = y;
			H = hReal;
			W = wReal;
			break;
		case Position::absolutePosSpaceDown:
			wReal = wParent-x;
			hReal = hParent-y;
			X = x;
			Y = y;
			H = hReal;
			W = wReal;
			break;
		case Position::absolutePosH:
			wReal = wParent * w / 100;
			hReal = h;
			X = x;
			Y = y;
			H = hReal;
			W = wReal;
			break;
		case Position::absoluteSize:
			wReal = w;
			hReal = h;
			X = wParent * x / 100;
			Y = hParent * y / 100;
			H = h;
			W = w;
			break;
		case Position::percentAll:
			wReal = wParent * w / 100;
			hReal = hParent * h / 100;
			X = wParent * x / 100;
			Y = hParent * y / 100;
			H = hReal;
			W = wReal;
			break;
		}
		if (position != Position::absoluteAll) {
			if (borderRadius > 0) {
				HRGN rgn = CreateRoundRectRgn(0, 0, wReal, hReal, borderRadius, borderRadius);
				SetWindowRgn(hWnd, rgn, FALSE);
			}
			MoveWindow(hWnd, X, Y, W, H, TRUE);
		}
	}
}


void Frame::SetBorderRadius(int r) {
	borderRadius = r;
	if (hWnd != 0) {
		HRGN rgn = CreateRoundRectRgn(0, 0, wReal, hReal, r, r);
		SetWindowRgn(hWnd, rgn, TRUE);
	}
}

void Frame::SetOwnerDraw(DrawFunction df) {
	ownerDraw = df;
	if (hWnd != 0) {
		InvalidateRect(hWnd, NULL, FALSE);
	}
}

void InitClasses() {
	wGlobal=GetSystemMetrics(SM_CXSCREEN);
	hGlobal = GetSystemMetrics(SM_CYSCREEN);
	mainInstance = GetModuleHandle(NULL);
}

Frame* GetWindowByHWND(HWND hWnd) {
	map<HWND, Frame*>::const_iterator iter = windowTree.find(hWnd);
	if (iter != windowTree.end()) {
		pair<const HWND, Frame*> p = *iter;
		return p.second;
	}
	else {
		return NULL;
	}
}


void Frame::PaintWindow(HDC hdc, RECT& rect) {
	HDC hBackBuf = CreateCompatibleDC(hdc);
	HBITMAP buff = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	SelectObject(hBackBuf, buff);
	FillBkColor(hBackBuf, rect);
	//кртинка
	if (background_picture != 0) {
		HDC hMem = CreateCompatibleDC(hdc);
		SelectObject(hMem, background_picture);
		BITMAP bi;
		if (isTrasparentPic) {
			GetObject(background_picture, sizeof(BITMAP), &bi);
			TransparentBlt(hBackBuf, 0, 0, rect.right, rect.bottom, hMem, 0, 0, bi.bmWidth, bi.bmHeight, transparent_color);
		}
		else {
			BitBlt(hBackBuf, 0, 0, rect.right, rect.bottom, hMem, 0, 0, SRCCOPY);
		}
		DeleteDC(hMem);
	}
	//принудительное рисование на окне
	if (ownerDraw != NULL) {
		SaveDC(hBackBuf);
		ownerDraw(hBackBuf, rect);
		RestoreDC(hBackBuf, -1);
	}
	DrawBorder(hBackBuf, rect);
	BitBlt(hdc, 0, 0, rect.right, rect.bottom, hBackBuf, 0, 0, SRCCOPY);
	DeleteObject(buff);
	DeleteDC(hBackBuf);
}

void FinallizeFramework() {
	map<HWND, Frame*>::const_iterator iter = windowTree.begin();
	while (iter != windowTree.end()) {
		pair<HWND, Frame*> p = *iter;
		delete p.second;
		iter++;
	}
}
