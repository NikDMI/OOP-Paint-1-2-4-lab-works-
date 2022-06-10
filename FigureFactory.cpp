#include "FigureFactory.h"

FigureFactory figureFactory;

void FigureFactory::RegisterNewFigureClass(Figure* figure) {
	if (figure != nullptr) {
		this->registeredFigure.push_back(figure);
		this->btnPainters.push_back(figure->GetBtnPainter());
	}
}




void ButtonMove1(Frame* btn);
void ButtonLeave1(Frame* btn);
void ButtonDown1(Frame* btn);
void CustomButton1(Frame* btn);
void CustomLabel1(LabelClass* label);
void CheckDrawing();


void ButtonChooseNewFigureClick(Frame* btn) {//нажатие на кнопку выбора фигуры
	CheckDrawing();
	figureFactory.ChooseNewFigure(btn);
	//currentFigureButton = &base_Ellipse;
}


WindowClass* FigureFactory::DrawButtonPanel(int startX, int startY, WindowClass* parent) {//генерирует панель для кнопок фигур
	int figCount = this->registeredFigure.size();
	int btnInLine = figCount / 2;//число кнопок на строку
	if (figCount % 2 != 0) btnInLine++;
	this->panelWidth = FigureFactory::btnW * btnInLine + FigureFactory::btnDW * (btnInLine + 1);
	WindowClass* figurePanel = new WindowClass(L"figPanel", Window::WindowType::PanelWindow, Position::absoluteAll, startX, startY, panelWidth, FigureFactory::btnH*2+20+30, parent);
	int dx = FigureFactory::btnDW;
	int dy = FigureFactory::btnDH;
	for (int i = 0; i < figCount; i++) {
		Button* btnFigure = new Button(Position::absoluteAll, dx, dy, FigureFactory::btnW, FigureFactory::btnH, figurePanel);
		CustomButton1(btnFigure);
		if(this->btnPainters[i]!=nullptr) btnFigure->SetOwnerDraw(this->btnPainters[i]);
		btnFigure->eventHandler->SetMouseEvent(MouseEvents::OnClick, ButtonChooseNewFigureClick);
		this->figureButtons.push_back(btnFigure);
		figurePanel->AddChild(btnFigure);
		dx += FigureFactory::btnW + FigureFactory::btnDW;
		if (dx == panelWidth && i+1!=figCount) {//заполнение новой строки
			dx = FigureFactory::btnDW;
			dy += FigureFactory::btnDH+ FigureFactory::btnH;
		}
	}
	LabelClass* lblFig = new LabelClass(L"Фигуры", Position::absolutePosH, 0, dy+FigureFactory::btnH, 100, 20, figurePanel);
	CustomLabel1(lblFig);
	figurePanel->AddChild(lblFig);

	parent->AddChild(figurePanel);
	return figurePanel;
}

int FigureFactory::GetPanelWidth() {
	return this->panelWidth;
}

void FigureFactory::ChooseNewFigure(Frame* btn) {
	//найдем индекс нажатой кнопки
	if (btn == nullptr) {
		this->lastFigureChoise = nullptr;
		return;
	}
	int index = 0;
	for (;; index++) {
		if (this->figureButtons[index] == btn) break;
	}
	this->lastFigureChoise = this->registeredFigure[index];//выбранная фигура
}

bool FigureFactory::IsFigureChoosed() {
	return (this->lastFigureChoise == nullptr) ? false : true;
}

Figure* FigureFactory::CreateChoosedFigure() {
	if (lastFigureChoise != nullptr) {
		return lastFigureChoise->CreateFigureObject();
	}
	return nullptr;
}
