#include <stdio.h>

void ex_2_12(void) {
	int x = 0x87654321;
	printf("ori: %.8x\n", x);

	int lsb = x & 0xFF;
	printf("one: %.8x\n", lsb);

	int two = x ^ (~0xFF);
	printf("two: %.8x\n", two);

	int thr = x | (0xFF);
	printf("thr: %.8x\n", thr);
}

int bis(int x, int mask) {
	int res = x | mask;
	return res;
}

int bic(int x, int mask) {
	int res = x & ~mask;
	return res;
}

int bool_or (int x, int y) {
	int res = bis(x, y);
	return res;
}

int bool_xor(int x, int y) {
	int res = bis(bic(x, y), bic(y, x));
	return res;
}

int equal(int x, int y) {
	int res = !(x ^ y);
	return res;
}

int main(void){
	int a = 0x55;
	int b = 0x46;
	printf("a & b %.08x\n", a & b);
	printf("a | b %.08x\n", a | b);
	printf("~a | ~b %.08x\n", ~a | ~b);
	printf("a & !b %.08x\n", a & !b);
	printf("a && b %.08x\n", a && b);
	printf("a || b %.08x\n", a || b);
	printf("!a || !b %.08x\n", !a || !b);
	printf("a && ~b %.08x\n", a && ~b);
	printf("5 == 3: %.01x\n", equal(5, 3));
	printf("4 == 4: %.01x\n", equal(4, 4));
	return 0;
}
