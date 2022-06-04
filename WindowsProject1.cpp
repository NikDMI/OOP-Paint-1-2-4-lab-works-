#include "framework.h"
#include "WindowFramework.h"
#include <vector>
#include "resource.h"
#include <commdlg.h>
#include <fstream>

#pragma comment(lib,"StaticLib1.lib")

#include "Ellipse.h"
#include "Circle.h"
#include "Figure_List.h"
#include "Polygon.h"
#include "Rectangle.h"
#include "Polyline.h"
#include "WavyLine.h"
#include "PainterTools.h"

#include "FigureFactory.h"




const WCHAR* PaintBoxClassName = L"PaintBox";

void InitWindow();//функция сборки окна через "фреймворк"
void InitPaintBox();//создание класса холста

const int numbOfBimaps = 5;
HBITMAP bitmaps[numbOfBimaps];

Figure_List* figureList = new Figure_List();//лист нарисованных фигур
Figure_List figureStack;
Figure* currentFigure;//текущая фигура для рисования

//характеристики для рисования фигуры
const int maxPenStyles = 4;
DWORD PenStyles[maxPenStyles] = { PS_SOLID,PS_DOT,PS_DASHDOT,PS_DASHDOTDOT };
const int maxBrushStyles = 7;
DWORD BrushStyles[maxBrushStyles] = { BS_SOLID,HS_BDIAGONAL,HS_CROSS,HS_DIAGCROSS,HS_FDIAGONAL,HS_HORIZONTAL,HS_VERTICAL};

const int maxPenWidth = 10;

COLORREF penColor=RGB(0,0,0);
COLORREF brushColor=RGB(255,255,255);
int penStyle = 0;
int brushStyle = 0;
int penWidth = 1;

bool isPressed = false;
bool isModify = false;//рамочка трансформации
bool isDraw = false;
bool isSaveBmp = false;

static RECT ModifyRect;


HWND hMainWindow;
Frame* paintBox;


void LoadBitmaps() {
	bitmaps[0] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BACK));
	bitmaps[1] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_NEXT));
	bitmaps[2] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_SAVE));
	bitmaps[3] = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_ERASER));
	bitmaps[4]=LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_CLEAN));
}

void FreeBitmaps() {
	for (int i = 0; i < numbOfBimaps; i++) {
		DeleteObject(bitmaps[i]);
	}
}

void FreeList() {
	Figure_List::list_iterator iter = figureList->begin();
	while (iter != figureList->end()) {
		delete *iter;
		iter++;
	}
	delete figureList;
}


enum class TypeOfTransformation { None, Move, North, South,East,West };
TypeOfTransformation typeTT;
void SetModifyType(TypeOfTransformation TT);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lcmdLine, int nCmdShow) {
	//регистрация всех доступных классов фигур
	figureFactory.RegisterNewFigureClass(new Ellipse_Figure());
	figureFactory.RegisterNewFigureClass(new Circle());
	figureFactory.RegisterNewFigureClass(new Rectangle_Figure());
	figureFactory.RegisterNewFigureClass(new Polygon_Figure());
	figureFactory.RegisterNewFigureClass(new Polyline_Figure());
	figureFactory.RegisterNewFigureClass(new WavyLine());

	InitWindowFramework();
	AddFontFamily(L"Comfortaa-Regular.ttf");
	InitPaintBox();
	LoadBitmaps();
	InitWindow();

	SetModifyType(TypeOfTransformation::None);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	FreeBitmaps();
	FreeList();
	FreeFontResourses();
	FinallizeFramework();
	return 0;
}


const COLORREF mainWindowBackcolor = RGB(111, 111, 111);
const COLORREF ToolBarBackcolor = RGB(252, 152, 93);
const COLORREF PaintBoxBackcolor = RGB(222, 222, 222);
const COLORREF PanelBackcolor = RGB(222, 222, 222);
const COLORREF PanelBackcolor2 = RGB(240, 240, 240);
const COLORREF ButtonBorderColor1 = RGB(194, 182, 182);
const COLORREF ButtonBorderColor2 = RGB(148, 139, 139);
const COLORREF ButtonBackground1 = RGB(202, 202, 202);//обычный
const COLORREF ButtonBackground2 = RGB(222, 222, 222);//при наведении
const COLORREF ButtonBackground3 = RGB(182, 182, 182);//при зажатии




void ButtonMove1(Frame* btn) {
	btn->SetBackgroundColor(ButtonBackground2);
}

void ButtonLeave1(Frame* btn) {
	btn->SetBackgroundColor(ButtonBackground1);
}

void ButtonDown1(Frame* btn) {
	btn->SetBackgroundColor(ButtonBackground3);
}

void CustomButton1(Frame* btn) {//создание стиля для кнопки
	Border b;
	b.color = ButtonBorderColor1;
	b.style = BorderStyle::solid;
	b.width = 3;
	btn->SetBorder(b, BorderNum::top);
	btn->SetBorder(b, BorderNum::left);
	b.color = ButtonBorderColor2;
	btn->SetBorder(b, BorderNum::right);
	btn->SetBorder(b, BorderNum::btm);
	btn->SetBackgroundColor(ButtonBackground1);
	//обработчики
	btn->eventHandler->SetMouseEvent(MouseEvents::OnMove, ButtonMove1);
	btn->eventHandler->SetMouseEvent(MouseEvents::OnLeave, ButtonLeave1);
	btn->eventHandler->SetMouseEvent(MouseEvents::OnLBDown, ButtonDown1);
	btn->eventHandler->SetMouseEvent(MouseEvents::OnClick, ButtonLeave1);
}


void CustomPanel1(WindowClass* panel) {//стиль для панелек в тул баре
	panel->SetBackgroundColor(PanelBackcolor);
	panel->SetBorderRadius(20);
}

void CustomPanel2(WindowClass* panel) {//стиль для панелек в тул баре
	panel->SetBackgroundColor(PanelBackcolor2);
	panel->SetBorderRadius(10);
}

void CustomLabel1(LabelClass* label) {
	label->SetBackgroundColor(PanelBackcolor);
	label->font->SetFontFamily(L"Comfortaa Regular");
	label->font->SetFontSize(9);
	label->SetTextAlign(TextAlign::Center);
}

void DrawButton_Submit(HDC hdc, RECT r) {//рисование кнопки подтверждения
	HPEN pen = CreatePen(PS_SOLID, 1, RGB(10, 10, 10));
	SelectObject(hdc, pen);
	HBRUSH br = CreateSolidBrush(RGB(30, 250, 124));
	SelectObject(hdc, br);
	vector<POINT> points;
	POINT p;
	p = { 8,20 }; points.push_back(p);
	p = { 14,24 }; points.push_back(p);
	p = { 24,10 }; points.push_back(p);
	p = { 22,7 }; points.push_back(p);
	p = { 13,18 }; points.push_back(p);
	p = {10,16 };points.push_back(p);
	Polygon(hdc, &points[0], points.size());
	DeleteObject(pen);
}


void DrawPanel_ColorPen(HDC hdc, RECT r) {
	HBRUSH br = CreateSolidBrush(penColor);
	SelectObject(hdc, br);
	Rectangle(hdc, -1, -1, r.right + 1, r.bottom + 1);
	DeleteObject(br);
}

void DrawPanel_ColorBrush(HDC hdc, RECT r) {
	HBRUSH br = CreateSolidBrush(brushColor);
	SelectObject(hdc, br);
	Rectangle(hdc, -1, -1, r.right + 1, r.bottom + 1);
	DeleteObject(br);
}

PainterTools painterTools;

void DrawPanel_PenWidth(HDC hdc, RECT r) {
	//static int width = 6;
	painterTools.SetTools(penWidth, PS_SOLID, RGB(0,0,0), BS_SOLID, RGB(10, 10, 10));
	painterTools.InstallTools(hdc);
	int x = (r.right) * 0.2;
	int y = (r.bottom) / 2;
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, r.right - x, y);
	painterTools.FreeTools(hdc);
}

void DrawPanel_PenStyle(HDC hdc, RECT r) {
	static int width = 6;
	painterTools.SetTools(width, PenStyles[penStyle], RGB(0,0,0), BS_SOLID, RGB(10, 10, 10));
	painterTools.InstallTools(hdc);
	int x = (r.right) * 0.2;
	int y = (r.bottom) / 2;
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, r.right - x, y);
	painterTools.FreeTools(hdc);
}

void DrawPanel_BrushStyle(HDC hdc, RECT r) {
	painterTools.SetTools(1, PS_SOLID, RGB(0, 0, 0), BrushStyles[brushStyle], RGB(10, 10, 10));
	painterTools.InstallTools(hdc);
	int dx = r.right * 0.2;
	int dy = r.bottom * 0.2;
	Rectangle(hdc, dx, dy, r.right -dx, r.bottom -dy);
	painterTools.FreeTools(hdc);
}


//ОБРАБОТЧИКИ СОБЫТИЙ
void CheckDrawing() {//проверяет, чтобы не прервать рисование, иначе очистить память
	if (isDraw) {//если происхоит рисование
		delete currentFigure;
		figureList->pop_back();
		isDraw = false;
		//currentFigureButton = nullptr;
		figureFactory.ChooseNewFigure(nullptr);
		InvalidateRect(hMainWindow, NULL, FALSE);
	}
}

void ButtonClick_Submit(Frame* btn) {
	if (isDraw) {
		currentFigure->EndDraw();
		isDraw = false;
		isModify = true;
		currentFigure->GetBaseRect(ModifyRect);//получение прямоугольника с последней фигуры
		InvalidateRect(hMainWindow, NULL, FALSE);
	}
	else if (isModify) {
		isModify = false;
		InvalidateRect(hMainWindow, NULL, FALSE);
	}
}

COLORREF GetColorDialog(COLORREF color) {
	static CHOOSECOLOR cc;
	COLORREF arrColor[16];
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = hMainWindow;
	cc.rgbResult = color;
	cc.lpCustColors = arrColor;
	cc.Flags = CC_RGBINIT;
	ChooseColor(&cc);
	COLORREF res = cc.rgbResult;
	return res;
}

void ButtonClick_PenColor(Frame* btn) {
	penColor=GetColorDialog(penColor);
	btn->Repaint();
}

void ButtonClick_BrushColor(Frame* btn) {
	brushColor = GetColorDialog(brushColor);
	btn->Repaint();
}

void ButtonClick_PenWidth(Frame* btn) {
	penWidth = (penWidth+1) % (maxPenWidth + 1);
	penWidth=penWidth == 0 ? 1 : penWidth;
	btn->Repaint();
}

void ButtonClick_PenStyle(Frame* btn) {
	penStyle = (penStyle + 1) % (maxPenStyles);
	btn->Repaint();
}

void ButtonClick_BrushStyle(Frame* btn) {
	brushStyle = (brushStyle + 1) % (maxBrushStyles);
	btn->Repaint();
}

void ButtonClick_Cancel(Frame* btn) {
	Figure* fig = figureList->pop_back();
	if (fig != nullptr) {
		isDraw = false;
		isModify = false;
		figureStack.push_back(fig);
		paintBox->Repaint();
	}
	
}

void ButtonClick_Repeat(Frame* btn) {
	Figure* fig = figureStack.pop_back();
	if (fig != nullptr) {
		isDraw = false;
		isModify = false;
		figureList->push_back(fig);
		paintBox->Repaint();
	}
}

void ButtonClick_SaveBMP(Frame* btn) {
	isSaveBmp = true;
	paintBox->Repaint();
}

void ButtonClick_Clean(Frame* btn) {
	int ans=MessageBox(hMainWindow, L"Это действие удаляет все созданные объекты - вы не сможете откатиться назад. Продолжить?", L"Warning", MB_OKCANCEL | MB_ICONWARNING);
	if (ans == IDOK) {
		isModify = false;
		isDraw = false;
		Figure* fig = figureList->pop_back();
		while (fig != nullptr) {
			delete fig;
			fig = figureList->pop_back();
		}
		paintBox->Repaint();
	}
}

void InitWindow() {
	WindowClass* mainWindow = new WindowClass(L"Paint", Window::WindowType::MainWindow, Position::percentAll, 15, 15, 70, 70, NULL);

	WindowClass* toolBar = new WindowClass(L"TBar", Window::WindowType::PanelWindow, Position::absolutePosH, 0, 0, 100, 135, mainWindow);
	toolBar->SetBackgroundColor(ToolBarBackcolor);
	//панель системных функций
	WindowClass* systemPanel = new WindowClass(L"sesPanel", Window::WindowType::PanelWindow, Position::absoluteAll, 20, 10, 130, 110, toolBar);
	CustomPanel1(systemPanel);

	Button* btnCancel = new Button(Position::absoluteAll, 10, 10, 30, 30, systemPanel);
	CustomButton1(btnCancel);
	btnCancel->SetPicture(bitmaps[0],true);
	btnCancel->eventHandler->SetMouseEvent(MouseEvents::OnClick, ButtonClick_Cancel);
	systemPanel->AddChild(btnCancel);

	Button* btnRedo = new Button(Position::absoluteAll, 50, 10, 30, 30, systemPanel);
	CustomButton1(btnRedo);
	btnRedo->SetPicture(bitmaps[1], true);
	btnRedo->eventHandler->SetMouseEvent(MouseEvents::OnClick, ButtonClick_Repeat);
	systemPanel->AddChild(btnRedo);

	Button* btnSaveBMP = new Button(Position::absoluteAll, 90, 10, 30, 30, systemPanel);
	CustomButton1(btnSaveBMP);
	btnSaveBMP->SetPicture(bitmaps[2], true);
	btnSaveBMP->eventHandler->SetMouseEvent(MouseEvents::OnClick, ButtonClick_SaveBMP);
	systemPanel->AddChild(btnSaveBMP);

	Button* btnEraser = new Button(Position::absoluteAll, 10, 50, 30, 30, systemPanel);
	CustomButton1(btnEraser);
	btnEraser->SetPicture(bitmaps[3], true);
	systemPanel->AddChild(btnEraser);

	Button* btnClean = new Button(Position::absoluteAll, 50, 50, 30, 30, systemPanel);
	CustomButton1(btnClean);
	btnClean->SetPicture(bitmaps[4], true);
	systemPanel->AddChild(btnClean);
	btnClean->eventHandler->SetMouseEvent(MouseEvents::OnClick, ButtonClick_Clean);

	Button* btnSubmit = new Button(Position::absoluteAll, 90, 50, 30, 30, systemPanel);
	CustomButton1(btnSubmit);
	btnSubmit->SetOwnerDraw(DrawButton_Submit);
	btnSubmit->eventHandler->SetMouseEvent(MouseEvents::OnClick, ButtonClick_Submit);
	systemPanel->AddChild(btnSubmit);

	LabelClass* lblTools = new LabelClass(L"Инструменты", Position::absolutePosH, 0, 80, 100, 20,systemPanel);
	CustomLabel1(lblTools);
	systemPanel->AddChild(lblTools);

	toolBar->AddChild(systemPanel);
	////////////////////////////

	//панель графических фигур
	WindowClass* figPanel = figureFactory.DrawButtonPanel(170, 10, toolBar);
	CustomPanel1(figPanel);
	int deltaW = figureFactory.GetPanelWidth()+20;

	///////////////////////
	//панель Выбора цвета
	//WindowClass* colorPanel = new WindowClass(L"colorPanel", Window::WindowType::PanelWindow, Position::absoluteAll, 320, 10, 130, 110, toolBar);
	WindowClass* colorPanel = new WindowClass(L"colorPanel", Window::WindowType::PanelWindow, Position::absoluteAll, 170+deltaW, 10, 130, 110, toolBar);
	CustomPanel1(colorPanel);

	WindowClass* pColorPen = new WindowClass(L"", Window::WindowType::PanelWindow, Position::absoluteAll, 10, 10, 50, 50, colorPanel);
	CustomButton1(pColorPen);
	pColorPen->SetOwnerDraw(DrawPanel_ColorPen);
	pColorPen->eventHandler->SetMouseEvent(MouseEvents::OnClick, ButtonClick_PenColor);
	colorPanel->AddChild(pColorPen);

	LabelClass* lblColorPen = new LabelClass(L"Перо", Position::absoluteAll, 10, 60, 50, 20, colorPanel);
	CustomLabel1(lblColorPen);
	colorPanel->AddChild(lblColorPen);

	WindowClass* pColorBrush = new WindowClass(L"", Window::WindowType::PanelWindow, Position::absoluteAll, 70, 10, 50, 50, colorPanel);
	CustomButton1(pColorBrush);
	pColorBrush->SetOwnerDraw(DrawPanel_ColorBrush);
	pColorBrush->eventHandler->SetMouseEvent(MouseEvents::OnClick, ButtonClick_BrushColor);
	colorPanel->AddChild(pColorBrush);

	LabelClass* lblColorBrush = new LabelClass(L"Кисть", Position::absoluteAll, 70, 60, 50, 20, colorPanel);
	CustomLabel1(lblColorBrush);
	colorPanel->AddChild(lblColorBrush);

	LabelClass* lblColor = new LabelClass(L"Цвета", Position::absolutePosH, 0, 80, 100, 20, colorPanel);
	CustomLabel1(lblColor);
	colorPanel->AddChild(lblColor);


	toolBar->AddChild(colorPanel);

	//панель выбора стилей
	//WindowClass* stylePanel = new WindowClass(L"stylePanel", Window::WindowType::PanelWindow, Position::absoluteAll, 470, 10, 370, 110, toolBar);
	WindowClass* stylePanel = new WindowClass(L"stylePanel", Window::WindowType::PanelWindow, Position::absoluteAll, 320+deltaW, 10, 370, 110, toolBar);
	CustomPanel1(stylePanel);

	WindowClass* pPenWidth = new WindowClass(L"", Window::WindowType::PanelWindow, Position::absoluteAll, 10, 10, 110, 50, stylePanel);
	CustomPanel2(pPenWidth);
	pPenWidth->SetOwnerDraw(DrawPanel_PenWidth);
	pPenWidth->eventHandler->SetMouseEvent(MouseEvents::OnClick, ButtonClick_PenWidth);
	stylePanel->AddChild(pPenWidth);

	LabelClass* lblPenWidth = new LabelClass(L"Толщина", Position::absoluteAll, 10, 60, 110, 20, stylePanel);
	CustomLabel1(lblPenWidth);
	stylePanel->AddChild(lblPenWidth);

	WindowClass* pPenStyle = new WindowClass(L"", Window::WindowType::PanelWindow, Position::absoluteAll, 130, 10, 110, 50, stylePanel);
	CustomPanel2(pPenStyle);
	pPenStyle->SetOwnerDraw(DrawPanel_PenStyle);
	pPenStyle->eventHandler->SetMouseEvent(MouseEvents::OnClick, ButtonClick_PenStyle);
	stylePanel->AddChild(pPenStyle);

	LabelClass* lblPenStyle = new LabelClass(L"Стиль пера", Position::absoluteAll, 130, 60, 110, 20, stylePanel);
	CustomLabel1(lblPenStyle);
	stylePanel->AddChild(lblPenStyle);

	WindowClass* pBrushStyle = new WindowClass(L"", Window::WindowType::PanelWindow, Position::absoluteAll, 250, 10, 110, 50, stylePanel);
	CustomPanel2(pBrushStyle);
	pBrushStyle->SetOwnerDraw(DrawPanel_BrushStyle);
	pBrushStyle->eventHandler->SetMouseEvent(MouseEvents::OnClick, ButtonClick_BrushStyle);
	stylePanel->AddChild(pBrushStyle);

	LabelClass* lblBrushStyle = new LabelClass(L"Стиль кисти", Position::absoluteAll, 250, 60, 110, 20, stylePanel);
	CustomLabel1(lblBrushStyle);
	stylePanel->AddChild(lblBrushStyle);


	LabelClass* lblStyle = new LabelClass(L"Стили", Position::absolutePosH, 0, 80, 100, 20, stylePanel);
	CustomLabel1(lblStyle);
	stylePanel->AddChild(lblStyle);



	toolBar->AddChild(stylePanel);
	/// <summary>
	/// /////////////
	/// </summary>
	mainWindow->AddChild(toolBar);

	paintBox = new Frame(GetModuleHandle(NULL), PaintBoxClassName, L"PaintBox",0, Position::absolutePosSpaceDown, 0, 135, 0, 0, mainWindow);
	paintBox->SetBackgroundColor(PaintBoxBackcolor);
	mainWindow->AddChild(paintBox);


	mainWindow->CreateWnd();
	hMainWindow = mainWindow->hWnd;
}


LRESULT CALLBACK WndProcPaintBox(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void InitPaintBox() {
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WndProcPaintBox;
	wc.hInstance = GetModuleHandle(NULL);
	wc.hCursor = NULL;
	wc.lpszClassName = PaintBoxClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.lpszMenuName = NULL;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DLIGHT);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClassEx(&wc);
}


const int dx = 5;//разница кнопки в пикселях

void SetModifyType(TypeOfTransformation TT) {//изменение курсора при трансформации фиурки
	HCURSOR cr=0;
	typeTT = TT;
	switch (TT) {
	case TypeOfTransformation::None:
		cr = LoadCursor(NULL, IDC_ARROW);
		break;
	case TypeOfTransformation::Move:
		cr=LoadCursor(NULL, IDC_CROSS);
		break;
	case TypeOfTransformation::North:
		cr=LoadCursor(NULL, IDC_SIZENS);
		break;
	case TypeOfTransformation::South:
		cr=LoadCursor(NULL, IDC_SIZENS);
		break;
	case TypeOfTransformation::East:
		cr = LoadCursor(NULL, IDC_SIZEWE);
		break;
	case TypeOfTransformation::West:
		cr = LoadCursor(NULL, IDC_SIZEWE);
		break;
	}
	SetCursor(cr);

}

//void CreateNewFigure(Figure** figure);
void SaveHdcToBmp(HDC hdc, RECT r);//сохранение картинки

LRESULT CALLBACK WndProcPaintBox(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Frame* wc = GetWindowByHWND(hWnd);
	HDC hdc,hDraw;
	PAINTSTRUCT ps;
	RECT clRect;
	HBRUSH br;
	static POINT p;
	static POINT pressedPoint;
	static HDC hBuffer=0;
	static HBITMAP hBufferBitmap=0;
	static Figure_List::list_iterator iter;
	switch (uMsg) {
	case WM_PAINT:
		GetClientRect(hWnd, &clRect);
		hdc = BeginPaint(hWnd, &ps);
		hDraw=wc->PaintWindow(hdc, clRect);
		//отрисовка всех заданных фигур
		iter = figureList->begin();
		while (iter != figureList->end()) {
			(*iter)->Draw(hDraw);
			iter++;
		}
		if (isSaveBmp) {
			isSaveBmp = false;
			SaveHdcToBmp(hDraw, clRect);
			MessageBox(hMainWindow, L"Сохранение успешно выполнено", L"Mess", MB_OK | MB_ICONINFORMATION);
		}
		if (isModify) {//режим трансформирования фигуры
			DrawFocusRect(hDraw, &ModifyRect);
		}
		wc->EndPaintWindow(hdc, clRect);
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		p.x = LOWORD(lParam);
		p.y = HIWORD(lParam);
		if (isDraw) {//обработка фигурой движения мыши
			currentFigure->MouseMove(p);
			InvalidateRect(hWnd, NULL, FALSE);
		}else if (isModify && !isPressed) {//определение режима трансформации
			//определение режима(для изменения курсора мыши)
			int w = (ModifyRect.right - ModifyRect.left);
			int h = (ModifyRect.bottom - ModifyRect.top);
			if (p.x > ModifyRect.left + dx && p.x < ModifyRect.right - dx && p.y >= ModifyRect.top + dx && p.y <= ModifyRect.bottom - dx) {
				SetModifyType(TypeOfTransformation::Move);
			}
			else if (p.x > ModifyRect.left + w / 3 && p.x < ModifyRect.right - w / 3 && p.y >= ModifyRect.top && p.y <= ModifyRect.top + dx) {
				SetModifyType(TypeOfTransformation::North);
			}
			else if (p.x > ModifyRect.left + w / 3 && p.x < ModifyRect.right - w / 3 && p.y >= ModifyRect.bottom-dx && p.y <= ModifyRect.bottom) {
				SetModifyType(TypeOfTransformation::South);
			}
			else if (p.y > ModifyRect.top + h / 3 && p.y < ModifyRect.bottom - h / 3 && p.x >= ModifyRect.left && p.x <= ModifyRect.left+dx) {
				SetModifyType(TypeOfTransformation::West);
			}
			else if (p.y > ModifyRect.top + h / 3 && p.y < ModifyRect.bottom - h / 3 && p.x >= ModifyRect.right-dx && p.x <= ModifyRect.right) {
				SetModifyType(TypeOfTransformation::East);
			}
			else {
				SetModifyType(TypeOfTransformation::None);
			}
		}
		else if(isModify && isPressed){//трансформация фигуры 
			int dx = p.x - pressedPoint.x;
			int dy = p.y - pressedPoint.y;
			switch (typeTT) {
			case TypeOfTransformation::Move:
				OffsetRect(&ModifyRect, dx, dy);
				pressedPoint = p;
				currentFigure->SetScaledRect(ModifyRect);
				break;
			case TypeOfTransformation::North:
				ModifyRect.top += dy;
				pressedPoint = p;
				currentFigure->SetScaledRect(ModifyRect);
				if (ModifyRect.top > ModifyRect.bottom) {
					SetModifyType(TypeOfTransformation::South);
					ModifyRect.bottom=ModifyRect.top;
				}
				break;
			case TypeOfTransformation::South:
				ModifyRect.bottom += dy;
				pressedPoint = p;
				currentFigure->SetScaledRect(ModifyRect);
				if (ModifyRect.top > ModifyRect.bottom) {
					SetModifyType(TypeOfTransformation::North);
					ModifyRect.bottom = ModifyRect.top;
				}
				break;
			case TypeOfTransformation::East:
				ModifyRect.right += dx;
				pressedPoint = p;
				currentFigure->SetScaledRect(ModifyRect);
				if (ModifyRect.left > ModifyRect.right) {
					SetModifyType(TypeOfTransformation::West);
					ModifyRect.right = ModifyRect.left;
				}
				break;
			case TypeOfTransformation::West:
				ModifyRect.left += dx;
				pressedPoint = p;
				currentFigure->SetScaledRect(ModifyRect);
				if (ModifyRect.left > ModifyRect.right) {
					SetModifyType(TypeOfTransformation::East);
					ModifyRect.right = ModifyRect.left;
				}
				break;
			}
			InvalidateRect(hWnd,NULL, FALSE);
		}
		break;
	case WM_LBUTTONDOWN:
		isPressed = true;
		p.x = LOWORD(lParam);
		p.y = HIWORD(lParam);
		pressedPoint = p;//начальная точка
		if (isModify) {//если это режим рисования и попали в рамочку
			if (p.x >= ModifyRect.left && p.x <= ModifyRect.right && p.y >= ModifyRect.top && p.y <= ModifyRect.bottom) {
				break;
			}
		}
		if (figureFactory.IsFigureChoosed() && !isDraw) {//начало рисования новой фигуры
			isModify = false;
			SetModifyType(TypeOfTransformation::None);
			currentFigure = figureFactory.CreateChoosedFigure();//создание новой фигуры
			figureList->push_back(currentFigure);
			//установить параметры рисования
			currentFigure->painterTools->SetTools(penWidth, PenStyles[penStyle], penColor, BrushStyles[brushStyle], brushColor);
			//начало рисования новой фигуры
			currentFigure->StartDraw(p);
			isDraw = true;
		}
		break;
	case WM_LBUTTONUP:
		isPressed = false;
		p.x = LOWORD(lParam);
		p.y = HIWORD(lParam);
		if (isDraw) {
			int isEndDraw=currentFigure->MouseUp(p);
			if (isEndDraw && !isModify ) {
				isModify = true;
				isDraw = false;
				currentFigure->EndDraw();
				currentFigure->GetBaseRect(ModifyRect);//получение прямоугольника с последней фигуры
			}
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

void SaveHdcToBmp(HDC hdc, RECT r) {
	HBITMAP bmp = CreateCompatibleBitmap(hdc, r.right, r.bottom);
	HDC hMem = CreateCompatibleDC(hdc);
	SelectObject(hMem, bmp);
	BitBlt(hMem, 0, 0, r.right, r.bottom, hdc, 0, 0, SRCCOPY);
	DeleteDC(hMem);
	BITMAP bmpInfo;
	GetObject(bmp, sizeof(bmpInfo), &bmpInfo);
	BITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biCompression = BI_RGB;
	bi.bmiHeader.biBitCount = 0;
	int res=GetDIBits(hdc, bmp, 0, bmpInfo.bmHeight, NULL, &bi, DIB_RGB_COLORS);
	char* bmpBuffer = new char [bi.bmiHeader.biSizeImage];
	bi.bmiHeader.biCompression = BI_RGB;
	res=GetDIBits(hdc, bmp, 0, r.bottom, bmpBuffer, &bi, DIB_RGB_COLORS);
	BITMAPFILEHEADER fileHeader;
	bi.bmiHeader.biCompression = BI_RGB;
	fileHeader.bfType = ((WORD)'M' << (sizeof(WORD)*8 / 2)) | 'B';
	fileHeader.bfSize = bi.bmiHeader.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	fileHeader.bfReserved1 = 0; fileHeader.bfReserved2 = 0;
	fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	std::ofstream of;
	try {
		
		of.open(L"Bitmap.bmp", ios::out | ios::trunc | ios::binary);
		of.write((char*)&fileHeader, sizeof(BITMAPFILEHEADER));
		of.write((char*)&bi.bmiHeader, sizeof(BITMAPINFOHEADER));
		of.write(bmpBuffer, bi.bmiHeader.biSizeImage);
		of.close();
	}
	catch (exception e) {
		throw e;
	}
	delete bmpBuffer;
	DeleteObject(bmp);
}