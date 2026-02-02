#include <stdio.h>

void copy_input_to_output_1() {
	int c;

	c = getchar();
	while (c != EOF) {
		putchar(c);
		c = getchar();
	}
}

void copy_input_to_output_2() {
	int c;
	
	while ((c = getchar()) != EOF)
		putchar(c);
}

void print_eof() {
	int c;
	c = EOF;
	putchar(c);
	getchar();
}

void char_counter_1() {
	long nc;

	nc = 0;

	while (getchar() != EOF) {
		++nc;
		printf("%ld\n", nc);
	}
}

void line_counter() {
	int c, nl;

	nl = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n')
			++nl;
	}
	printf("%d\n", nl);
}

void blanks_tabs_newlines() {
	int c, blanks, tabs, newlines;
	blanks = 0;
	tabs = 0;
	newlines = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n')
			++newlines;
		if (c == '\t')
			++tabs;
		if (c == ' ')
			++blanks;
	}
	printf("\nblanks: %d\ntabs: %d\nnewlines: %d\n", blanks, tabs, newlines);
}

void copy_input_to_output_removing_multiple_blanks() {
	int c;
	int blank_flag;

	blank_flag = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (blank_flag == 0) {
				blank_flag = 1;
				putchar(c);
			}
		} else {
			blank_flag = 0;
			putchar(c);
		}
	}
}

void replace_tabs_backspaces_backslashes() {
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			putchar('\\');
			putchar('t');
		} else if (c == '\b') {
			putchar('\\');
			putchar('b');
		} else if (c == '\\') {
			putchar('\\');
			putchar('\\');
		} else {
			putchar(c);
		}
	}
}

#define IN 1
#define OUT 0
void count_lines_words_chars() {
	int c, nl, nw, nc, state;

	state = OUT;
	nl = nw = nc = 0;
	while ((c = getchar()) != EOF) {
		++nc;
		if (c == '\n')
			++nl;
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if (state == OUT) {
			state = IN;
			++nw;
		}
	}
	printf("%d %d %d\n", nl, nw, nc);
}

#define OUT_SPACE 0
#define IN_SPACE 1
void one_word_per_line() {
	int c, state;
	state = OUT_SPACE;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t') {
			if (!state) {
				putchar('\n');
				state = IN_SPACE;
			}
		} else {
			putchar(c);
			state = OUT_SPACE;
		}
	}
}


int main() {
	one_word_per_line();
	return 0;
}
