// hello.c -> <preprocessor> -> hello.i -> <compiler> -> 
// hello.s -> <assembler>    -> hello.o -> <linker>   ->  hello <executable>
#include <stdio.h>

int main(void) {
	printf("Hello, World\n");
	return 0;
}
