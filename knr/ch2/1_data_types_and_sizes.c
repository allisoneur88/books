#include <stdio.h>
#include <limits.h>

int calc_bits(unsigned long n) {
	int bits = 0;
	while (n > 1) {
		n /= 2;
		bits++;
	}
	return bits;
}

void u_char() {
	unsigned char new_val, old_val;
	old_val = 0;
	new_val = 1;

	while (new_val > old_val) {
		old_val = new_val;
		++new_val;
	}

	printf("u_char: %10d .. %d; %d bits\n", new_val, old_val, calc_bits(old_val - new_val + 1));
}

void s_char() {
	signed char new_val, old_val;
	old_val = 0;
	new_val = 1;

	while (new_val > old_val) {
		old_val = new_val;
		++new_val;
	}

	signed char max_val = old_val;

	old_val = 0;
	new_val = -1;

	while (new_val < old_val) {
		old_val = new_val;
		--new_val;
	}

	printf("s_char: %10d .. %d; %d bits\n", old_val, max_val, calc_bits(max_val - old_val + 1));
}

void u_short() {
	unsigned short new_val, old_val;
	old_val = 0;
	new_val = 1;

	while (new_val > old_val) {
		old_val = new_val;
		++new_val;
	}

	printf("u_short: %10d .. %d; %d bits\n", new_val, old_val, calc_bits(old_val - new_val + 1));
}

void s_short() {
	signed short new_val, old_val;
	old_val = 0;
	new_val = 1;

	while (new_val > old_val) {
		old_val = new_val;
		++new_val;
	}

	signed short max_val = old_val;

	old_val = 0;
	new_val = -1;

	while (new_val < old_val) {
		old_val = new_val;
		--new_val;
	}

	printf("s_short: %10d .. %d; %d bits\n", old_val, max_val, calc_bits(max_val - old_val + 1));
}

void u_int() {
	unsigned int new_val, old_val;
	old_val = 0;
	new_val = 1;

	while (new_val > old_val) {
		old_val = new_val;
		++new_val;
	}

	printf("u_int: %10d .. %d; %d bits\n", new_val, old_val, calc_bits((unsigned long)old_val - new_val + 1UL));
}

void s_int() {
	signed int new_val, old_val;
	old_val = 0;
	new_val = 1;

	while (new_val > old_val) {
		old_val = new_val;
		++new_val;
	}

	signed int max_val = old_val;

	old_val = 0;
	new_val = -1;

	while (new_val < old_val) {
		old_val = new_val;
		--new_val;
	}

	printf("s_int: %10d .. %d; %d bits\n", old_val, max_val, calc_bits((unsigned long)max_val - old_val + 1UL));
}
int main(){
	u_char();
	s_char();
	u_short();
	s_short();
	u_int();
	s_int();

	return 0;
}
