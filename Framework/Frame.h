#pragma once
//������� ����� ���� ���������
#include <Windows.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Frame;

typedef void (*OnMouse)(Frame* btn);
enum class MouseEvents { OnClick, OnMove, OnLeave, OnLBDown };

enum class Position {absoluteAll,percentAll,absoluteSize,absolutePos,absolutePosSpaceDown,absolutePosH};//��������������

extern int wGlobal, hGlobal;
extern HINSTANCE mainInstance;

void InitClasses();

enum class BorderStyle{solid};
enum class BorderNum {top,btm,left,right};

using DrawFunction = void (*)(HDC hdc, RECT r);

struct Border {//�������� ������� ���� ��� CSS box-sizing: border-box;
	COLORREF color;
	int width;
	BorderStyle style;
};

class Frame {
protected:
	HINSTANCE hInstance;//���������� ����������, � ������� �����
	wstring ClassName;//��� ������ ��� ����/���������
	wstring WindowName;
	Position position;
	int w, h, x, y;
	Border border_top{ 0 };
	Border border_bottom{ 0 };
	Border border_left{ 0 };
	Border border_right{ 0 };
	COLORREF bk_color;
	int borderRadius = 0;
	HBITMAP background_picture=0;
	bool isTrasparentPic = false;
	COLORREF transparent_color;
	DrawFunction ownerDraw=NULL;//������� ��������������� ���������
public:
	Frame* parent;//������������ ����
	DWORD WindowStyle;
	int wReal, hReal;//������� � ��������
	HWND hWnd = 0;


	Frame(HINSTANCE hInstance, wstring ClassName, wstring WindowName, DWORD style, Position pos, int x, int y, int w, int h,Frame* parent);
	virtual void CreateWnd();
	void SetBorder(Border border,BorderNum bn);
	void DrawBorder(HDC hdc, RECT& r);
	void SetBackgroundColor(COLORREF cl);
	void FillBkColor(HDC hdc, RECT& r);
	void CheckSize();//��������� ����� �������� ������� � �������� ��� ������� ��������
	void PaintWindow(HDC hdc,RECT& rect);//�������� ������� ��������� ��� ��������� ����
	void SetBorderRadius(int r);
	void SetPicture(HBITMAP bmp,bool isTransparent=0,COLORREF transparent_color=RGB(255,255,255));
	void SetOwnerDraw(DrawFunction df);
	virtual ~Frame() {}
};

//������, ������� ������ ���� ���������� - ��������� �� ������

extern map<HWND, Frame*> windowTree;

Frame* GetWindowByHWND(HWND);

void FinallizeFramework();