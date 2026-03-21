#include<stdio.h>
#include<stddef.h>

void print_int(int a) {
	printf("%d\n", a);
}

void map(const int *in, int *out, size_t n,  int (*fn)(int)) {
	for (size_t i = 0; i < n; i++) {
		out[i] = fn(in[i]);
	}
}

void print_arr(const int *arr, size_t n) {
	for (size_t i = 0; i < n; i++) {
		printf("%zu: %d\n", i, arr[i]);
	}
}

int square (int a) {
	return (a * a);
}

int main(void) {
	//void (*p)(int) = print_int;
	//p(389);
	int arr[] = {11, 22, 33};
	int res[3];
	size_t n = sizeof(arr)/sizeof(arr[0]);

	map(arr, res, n, square);
	print_arr(res, n);
}
