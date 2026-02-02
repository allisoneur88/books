#include <stdio.h>

void count_everything() {
	int c, i, nwhite, nother;
	int ndigit[10];

	nwhite = nother = 0;
	for (i = 0; i < 10; ++i)
		ndigit[i] = 0;

	while ((c = getchar()) != EOF)
		if (c >= '0' && c <= '9')
			++ndigit[c - '0'];
		else if (c == ' ' || c == '\n' || c == '\t')
			++nwhite;
		else
			++nother;

	printf("digits =");
	for (i = 0; i < 10; ++i)
		printf(" %d", ndigit[i]);
	printf(", white space = %d, other = %d\n", nwhite, nother);
}

// supporting only length of words up to 20 characters
void histogram_print_helper(int n) {
	for (int i = 0; i < n; ++i) {
		printf("*");
	}
}
void histogram_of_legths() {
	int histogram[20];

	for (int i = 0; i < 20; ++i) {
		histogram[i] = 0;
	}

	int inside_of_the_word = 0;
	int length_of_the_current_word = 0;

	int c;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			if (inside_of_the_word) {
				histogram[length_of_the_current_word - 1] += 1;
				inside_of_the_word = 0;
				length_of_the_current_word = 0;
			}
		} else {
			if (inside_of_the_word) 
				length_of_the_current_word += 1;
			else {
				inside_of_the_word = 1;
				length_of_the_current_word += 1;
			}
		}
	}

	for (int i = 0; i < 20; ++i) {
		printf("length %d: ", i + 1);
		histogram_print_helper(histogram[i]);
		printf("\n");
	}

}

int main() {
	histogram_of_legths();
	return 0;
}
