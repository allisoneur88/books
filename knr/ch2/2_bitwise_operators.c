#include <stdio.h>

int main() {
	printf("x = 8\n");
	int x = 8;
	printf("x >> 1: %d\n", x >> 1);
	printf("x >> 2: %d\n", x >> 2);
	printf("x << 1: %d\n", x << 1);
	printf("x << 2: %d\n", x << 2);

	printf("\n");

	int y = 15;
	printf("y = 15 = 0b1111\n");
	printf("y & 0b0001: %d\n", y & 0b0001);
	printf("y & 0b0011: %d\n", y & 0b0011);
	printf("y & 0b0111: %d\n", y & 0b0111);
	printf("y & 0b0100: %d\n", y & 0b0100);

	int z = 0xFF;
	printf("z =  0x%0x = 0b1111_1111 = %d\n",  z, z);
	
	int a = 1;
	printf("a = 1 = 0b0001 = 0x%0x\n", a);
	printf("a | 0b1000: %d\n", a | 0b1000);

	int b = 4;
	int c = 5;
	printf("b = 4, c = 5\n");

	b = b ^ c;
	printf("1: b = b ^ c => b = %d, c = %d\n", b, c);

	c = b ^ c;
	printf("2: c = b ^ c => b = %d, c = %d\n", b, c);

	b = b ^ c;
	printf("3: b = b ^ c => b = %d, c = %d\n", b, c);

	int d = 9;
	printf("d = 9\n");

	printf("~d = %d\n", ~d);
}
