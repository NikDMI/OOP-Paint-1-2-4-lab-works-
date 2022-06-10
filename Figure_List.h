#pragma once
#include "Figure.h"

class Figure_List {
private:
	int size;//кол-во фигур
	int capacity;//текущая вместительность контейнера
	Figure** list;
public:
	Figure_List();
	void push_back(Figure* f);
	Figure* pop_back();
	Figure** begin();
	Figure** end();

	class list_iterator {
	private:
		Figure** pointer;
	public:
		list_iterator(Figure** start);
		list_iterator();
		void operator=(Figure** start);
		void operator++(int);
		Figure* operator*();
		bool operator!=(Figure**);
	};
};