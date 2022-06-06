// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#define EXPORTING_DLL
#include "../DllHeader.h"
#include "../../Closed_Figure.h"

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

void DrawButtonParallelogram(HDC hdc, RECT r) {//функция рисования на кнопке 
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(10, 10, 10));
    SelectObject(hdc, pen);
    HBRUSH br = CreateSolidBrush(RGB(180, 250, 224));
    SelectObject(hdc, br);
    POINT p; vector<POINT> points;
    p = { 12,6 }; points.push_back(p);
    p = { 22,6 }; points.push_back(p);
    p = { 17,22 }; points.push_back(p);
    p = { 5,22 }; points.push_back(p);
    Polygon(hdc, &points[0], points.size());
    DeleteObject(pen);
}

class Parallelogram : public Closed_Figure {
public:
    Parallelogram() {}
    void Draw(HDC hdc) {
        painterTools->InstallTools(hdc);
        int w = baseRect.right - baseRect.left;
        int dw = w * 0.3;//отступ
        POINT points[4] = { {baseRect.left + dw,baseRect.top},{baseRect.right,baseRect.top},{baseRect.right-dw,baseRect.bottom},{baseRect.left,baseRect.bottom} };
        Polygon(hdc, points, 4);
        painterTools->FreeTools(hdc);
    };
    Figure* CreateFigureObject() { return new Parallelogram(); }
    virtual DrawBtnFunction GetBtnPainter() {
        return DrawButtonParallelogram;
    }
};

extern "C" Figure * CreateFigureObject() {
    return new Parallelogram();
}

