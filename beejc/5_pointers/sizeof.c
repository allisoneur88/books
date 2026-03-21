#include <stdio.h>

int main(void) {
	int a_int = 5;
	float b_float = 5.0;
	double c_double = 5.0;

	char d_char = 'k';

	_Bool e_bool;

	printf("types:\n");
	printf("int: %zu\n", sizeof(a_int));
	printf("float: %zu\n", sizeof(b_float));
	printf("double: %zu\n", sizeof(c_double));
	printf("char: %zu\n", sizeof(d_char));
	printf("bool: %zu\n", sizeof(e_bool));

	printf("pointers:\n");
	printf("&int: %zu\n", sizeof(&a_int));
	printf("&float: %zu\n", sizeof(&b_float));
	printf("&double: %zu\n", sizeof(&c_double));
	printf("&char: %zu\n", sizeof(&d_char));
	printf("&bool: %zu\n", sizeof(&e_bool));
}
