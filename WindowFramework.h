#pragma once
#include "Frame.h"
#include "CWindow.h"
#include "Button.h"
#include "Label.h"
#include "Edit.h"
#include "Font.h"
#include "BackBuffer.h"
#include "EventHandler.h"
#include "WindowHandler.h"
#include "ScrollBar.h"
#include "ListBox.h"

//#include <gdiplus.h>

//#pragma comment (lib,"Gdiplus.lib")

void InitWindowFramework();
void FinallizeFramework();
void StartWindowLoop();
void FreeFontResourses();