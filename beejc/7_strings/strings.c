#include<stdio.h>

int strleng(char *string);
void strcopy(char *to, char *from);

int main(void) {
	char *s1 = "First!";
	char s2[] = "Second";

	printf("first in first: %c\n", s1[0]);
	printf("first in second: %c\n", s2[0]);

	// s1[0] = 'H'; heap allocated => immutable => UB
	s2[0] = 'H'; // perfectly fine
	printf("first in second: %c\n", s2[0]); 

	printf("%d\n", strleng("123"));
	printf("%d\n", strleng(s1));
	printf("%d\n", strleng(s2));

	char first_copy[100];
	char second_copy[100];

	strcopy(first_copy, s1);
	strcopy(second_copy, s2);

	printf("first copy: %s\n", first_copy);
	printf("second copy: %s\n", second_copy);
}

int strleng(char *string) {
	int len = 0;
	for (int i = 0; string[i] != '\0'; i++) {
		len += 1;
	}
	return len;
} 

void strcopy(char *to, char *from) {
	int i;

	for (i = 0; from[i] != '\0'; i++) {
		to[i] = from[i];
	}
	to[i] = '\0';
}
