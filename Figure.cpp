#include "Figure.h"

Figure::Figure(){
}

void Figure::NormalizeRect(RECT& r) {
	if (r.left > r.right) {
		int temp = r.left;
		r.left = r.right;
		r.right = temp;
	}
	if (r.top > r.bottom) {
		int temp = r.top;
		r.top = r.bottom;
		r.bottom = temp;
	}
}

void Figure::GetBaseRect(RECT& r) {
	r = baseRect;
}


