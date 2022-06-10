#pragma once
class Figure;
#ifndef INDLL_H
#define INDLL_H
#ifdef EXPORTING_DLL
extern __declspec(dllexport) Figure* CreateFigureObject();
#else
extern __declspec(dllimport) Figure* CreateFigureObject();
#endif

#endif