#include "Figure_List.h"

Figure_List::Figure_List() {
	capacity = 4;
	size = 0;
	list = new Figure * [capacity];
}

void Figure_List::push_back(Figure* f) {
	if (capacity-1 == size) {
		capacity *= 2;
		Figure** new_list = new Figure * [capacity];
		for (int i = 0; i < size; i++) {
			new_list[i] = list[i];
		}
		delete[] list;
		list = new_list;
	}
	list[size++] = f;
}

Figure* Figure_List::pop_back() {
	if (size > 0) {
		return list[--size];
	}
	else {
		return nullptr;
	}
}

Figure** Figure_List::begin() {
	return &list[0];
}

Figure** Figure_List::end() {
	return &list[size];
}

Figure_List::list_iterator::list_iterator(Figure** start) {
	pointer = start;
}

Figure_List::list_iterator::list_iterator() {
	pointer = nullptr;
}

void Figure_List::list_iterator::operator=(Figure** start) {
	pointer = start;
}

void Figure_List::list_iterator::operator++(int) {
	pointer++;
}

Figure* Figure_List::list_iterator::operator*() {
	return *pointer;
}

bool Figure_List::list_iterator::operator!=(Figure** f) {
	return (*pointer != *f);
}


