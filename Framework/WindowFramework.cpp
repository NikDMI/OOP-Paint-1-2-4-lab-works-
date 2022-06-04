#include "WindowFramework.h"

void InitWindowFramework() {
	InitClasses();
	Window::InitWindowClass();
	CButton::InitWindowClass();
}