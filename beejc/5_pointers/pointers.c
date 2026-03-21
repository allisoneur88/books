#include <stdio.h>

void increment(int *num);

int main(void) {
	int a = 5;
	int *p = &a;

	increment(p);

	printf("value of a after call: %d\n", a);
	printf("*p after call: %d\n", *p);
}

void increment(int *num) {
	*num = *num + 1;
}
