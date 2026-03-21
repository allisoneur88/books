#include<stdio.h>

struct car {
	char *make;
	char *model;
	int year;
	int mileage;
	float price;
};

struct point {
	float x;
	float y;
};

struct point new_point() {
	struct point new_point = {.x = 0.0, .y = 0.0};
	return new_point;
}

void point_move_x(struct point *p, float by) {
	//(*p).x += by; non-idiomatic
	p->x += by; // idiomatic
}

void point_move_y(struct point *p, float by) {
	p->y += by;
}

void point_print(struct point *p) {
	printf("(%f, %f)\n", p->x, p->y);
}

int main(void) {
	struct point a = new_point();
	point_print(&a);

	point_move_x(&a, 1.0);
	point_move_y(&a, 1.0);

	point_print(&a);

	return 0;
}
