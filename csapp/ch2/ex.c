#include <limits.h>
#include <setjmp.h>
#include <stdint.h>
#include <stdio.h>

void ex2_59(int32_t x, int32_t y) {

	int32_t x_masked = x & 0xFF;
	int32_t y_masked = y & ~0xFF;

	x_masked |= y_masked;

	printf("result: %.8x\n", x_masked);
}

unsigned ex2_60_replace_byte(unsigned x, int i, unsigned char b) {
	// replace_byte(0x12345678, 2, 0xAB) --> 0x12AB5678 
	// replace_byte(0x12345678, 0, 0xAB) --> 0x123456AB
	
	unsigned mask = ~(0xFF << (i * 8));  // FF -> 0000FF00 -> FFFF00FF
	unsigned cleared_x = x & mask;

	unsigned replacement = b << (i * 8); 
	unsigned result = cleared_x | replacement;
	return result;
}

void ex2_60() {
	printf("0x12345678, 0, 0xAB: %.8x\n", ex2_60_replace_byte(0x12345678, 0, 0xAB));
	printf("0x12345678, 1, 0xAB: %.8x\n", ex2_60_replace_byte(0x12345678, 1, 0xAB));
	printf("0x12345678, 2, 0xAB: %.8x\n", ex2_60_replace_byte(0x12345678, 2, 0xAB));
	printf("0x12345678, 3, 0xAB: %.8x\n", ex2_60_replace_byte(0x12345678, 3, 0xAB));
	printf("0x12345678, 4, 0xAB: %.8x\n", ex2_60_replace_byte(0x12345678, 4, 0xAB));
	printf("0x12345678, 5, 0xAB: %.8x\n", ex2_60_replace_byte(0x12345678, 5, 0xAB));
}

int get_msb(int x) {
	// shift by w - 8
	int shift_val = (sizeof(int) - 1)<<3; // int = 32bit, size = sizeof(int) = 4, size - 1 = 3, << 3 = 3 * 8 = 24;
	// arithmetic right shift
	int x_right = x >> shift_val;
	// zero all but lsb
	return x_right & 0xFF;
	
}

// any bit of x equals 1
unsigned ex_2_61_a(int x) {
	return x || 0x00;
}

// any bit of x equals 0
unsigned ex_2_61_b(int x) {
	return !!~x;
}

// any bit in lsb of x equals 1
unsigned ex_2_61_c(int x) {
	int lsb = x & 0xFF;
	return lsb || 0x00;
}

// any bit in msb of x equals 0
unsigned ex_2_61_d(int x) {
	int shift_val = (sizeof(int) - 1) << 3;
	int x_right = x >> shift_val;
	u_int8_t msb = x_right & 0xFF;
	return !!~msb;
}

// shift by 1 and check if result has any zeroes
uint8_t ex_2_62_int_shifts_are_arithmetic(void) {
	int32_t minus_1 = -1;

	return !~(minus_1 >> 1);
}

// return 1 if any odd bit of x 
// equals 1; 0 otherwise
// a mask of 0x1010...?
int ex_2_64_any_odd_one(unsigned x) {
	unsigned mask = 0xAAAAAAAA;

	unsigned masked_x = x & mask;

	return !!masked_x;
}

// return 1 when x contains an odd
// number of 1s; 0 otherwise
// w == 32;
// 0000 0000 0000 0001		1
// 0000 0000 0000 0010		2
// 0000 0000 0000 0011 		3
// 0000 0000 0000 0100		4
int ex_2_65_odd_ones(unsigned x) {
	unsigned low16  =  x & 0x0000FFFF;
	unsigned high16 = (x & 0xFFFF0000) >> 16;
	unsigned res16 = low16 ^ high16;

	unsigned low8  =  res16 & 0x000000FF;
	unsigned high8 = (res16 & 0x0000FF00) >> 8;
	unsigned res8 = low8 ^ high8;

	unsigned low4  =  res8 & 0x0000000F;
	unsigned high4 = (res8 & 0x000000F0) >> 4;
	unsigned res4 = low4 ^ high4;

	//0011
	//1100
	unsigned low2  =  res4 & 0x00000003;
	unsigned high2 = (res4 & 0x0000000C) >> 2;
	unsigned res2 = (low2 ^ high2);

	//0001
	//0010
	unsigned low1  =  res2 & 0x00000001;
	unsigned high1 = (res2 & 0x00000002) >> 1;
	return low1 ^ high1;
}

int odd_ones(unsigned x) {
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;
	return x & 1;
}

/*
 * Generate mask indicating leftmost 1 in x. 
 * Assume w=32. 
 * For example, 0xFF00 -> 0x8000, and 0x6600 --> 0x4000.
 * If x = 0, then return 0.
 * 0xFF00 = 1111 1111 0000 0000 -> 1000 0000 0000 0000 = 0x8000
 * 0x6600 = 0110 0110 0000 0000 -> 0100 0000 0000 0000 = 0x4000
 * Hint: First transform x into a bit vector of the form [0...011...1].
 * [1000 0000 0000 0000 ...] x
 *
 * [0100 0000 0000 0000 ...] x >> 1
 * [1100 0000 0000 0000 ...] x |= x >> 1
 * [0011 0000 0000 0000 ...] x >> 2
 * [1111 0000 0000 0000 ...] x |= x >> 2
 * [0000 1111 0000 0000 ...] x >> 4
 * [1111 1111 0000 0000 ...] x |= x >> 4
 * [0000 0000 1111 1111 ...] x >> 8
 * [1111 1111 1111 1111 ...] x |= x >> 8
 * [0000 0000 0000 0000 1111 1111 1111 1111] x >> 16
 * [1111 1111 1111 1111 1111 1111 1111 1111] x |= x >> 16
 *
 * [0000 0101 0101 0101 0000 0000 0000 0000] x
 *
 * [0000 0010 1010 1010 1000 0000 0000 0000] x >> 1
 * [0000 0111 1111 1111 1000 0000 0000 0000] x |= x >> 1
 * [0000 0001 1111 1111 1110 0000 0000 0000] x >> 2
 * [0000 0111 1111 1111 1110 0000 0000 0000] x |= x >> 2
 * [0000 0000 0111 1111 1111 1110 0000 0000] x >> 4
 * [0000 0111 1111 1111 1111 1110 0000 0000] x |= x >> 4
 * [0000 0000 0000 0111 1111 1111 1111 1110] x >> 8
 * [0000 0111 1111 1111 1111 1111 1111 1110] x |= x >> 8
 * [0000 0000 0000 0000 0000 0111 1111 1111] x >> 16
 * [0000 0111 1111 1111 1111 1111 1111 1111] x |= x >> 16
 * 
 * [0000 0111 1111 1111 1111 1111 1111 1111] new x
 * [0000 0011 1111 1111 1111 1111 1111 1111] x >> 1
 * [0000 0100 0000 0000 0000 0000 0000 0000] x ^= x >> 1
*/
int leftmost_one(unsigned x) {
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;

	x ^= x >> 1;

	return x;
}

/* * Mask with least signficant n bits set to 1 
 * Examples: n = 6 --> 0x3F, n = 17 --> 0x1FFFF 
 * Assume 1 <= n <= w 
 * lets consider 8bit integer
 * [0000 0001] n = 3
 * [0000 1000] 1 << 3
 *
 * another approach (1 << n) - 1
 * [0000 0001] n = 5
 * [0010 0000] 1 << 5
 * [0001 1111] (1 << 5) - 1
 *
 * n = 8
 * [0000 0000] 1 << 8
*/ 
int lower_one_mask(int n) {
	int x = 1 << (n - 1);

	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;

	return x;
}

int lower_one_mask_2(int n) {
	return ((1 << n) - 1);
}


int main(void) {
	//ex2_59(0x89ABCDEF, 0x76543210);
	//ex2_60();
	//printf("msb 0x12345678: %.8x\n", get_msb(0x12345678));
	//printf("msb 0x89ABCDEF: %.8x\n", get_msb(0x89ABCDEF));
	//printf("%.2x\n", ex_2_61_a(5));
	//printf("%.2x\n", ex_2_61_a(0));
	//printf("%.2x\n", ex_2_61_b(-1));
	//printf("%.2x\n", ex_2_61_b(261));
	//printf("%.8x\n", lower_one_mask(6));
	printf("%.8x\n", 0x0 - 1);
	return 0;
}
