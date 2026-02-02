#include <stdio.h>

int power(int m, int n);
int factorial(int n);
int fact_iter(int n);
int fact_iter_helper(int product, int counter, int max_count);

int main() {
	int i;

	for (i = 0; i < 10; ++i) {
		printf("%d %d %d\n", i, power(2, i), power(-3, i));
	}

	for (i = 0; i < 10; ++i) {
		printf("rec %d! = %d\n", i, factorial(i));
	}

	for (i = 0; i < 10; ++i) {
		printf("iter %d! = %d\n", i, fact_iter(i));
	}

	return 0;
}

int power(int base, int n) {
	int i, product;

	product = 1;
	for (i = 1; i <= n; ++i) {
		product = product * base;
	}
	return product;
}

int factorial(int n) {
	if (n < 3) {
		return n;
	} else {
		return n * factorial(n - 1);
	}
}

int fact_iter(int n) {
	return fact_iter_helper(1, 1, n);
}

int fact_iter_helper(int product, int counter, int max_count) {
	if (counter > max_count) {
		return product;
	} else {
		return fact_iter_helper(product * counter, counter + 1, max_count);
	}
}

