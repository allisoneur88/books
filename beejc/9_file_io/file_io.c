#include <stdio.h>

void read_char(void);
void read_file(void);
void read_file_by_line(void);
void read_whales(void);
void write_file(int mode);
void write_bytes(void);
void read_bytes(void);

int main(void) {
	printf("Hello IO!\n");
	read_char();
	read_file();
	read_file_by_line();
	read_whales();
	write_file(0);
	write_bytes();
	read_bytes();
	return 0;
}

void read_char(void) {
	FILE *fp;
	fp = fopen("hello.txt", "r");

	int c = fgetc(fp);

	printf("%c\n", c);

	fclose(fp);
} 

void read_file(void) {
	FILE *fp;
	int c;

	fp = fopen("hello.txt", "r");

	while ((c = fgetc(fp)) != EOF) {
		printf("%c", c);
	}

	fclose(fp);
}

void read_file_by_line(void) {
	FILE *fp;
	char buffer[1024];

	int line_count = 0;

	fp = fopen("quote.txt", "r");

	while ((fgets(buffer, sizeof buffer, fp) != NULL)) {
		printf("%d: %s", ++line_count, buffer);
	}

	fclose(fp);
}

struct whale {
	char *name;
	float length;
	int mass;
};

struct whale new_whale(char *name, float length, int mass) {
	struct whale new_whale = {.name = name, .length = length, .mass = mass};
	return new_whale;
}

void print_whale(struct whale *whale) {
	printf("%s whale, %.1f meters, %d tonnes\n", whale->name, whale->length, whale->mass);
}

void read_whales(void) {
	FILE *fp;
	char name[1024];
	float length;
	int mass;

	fp = fopen("whales.txt", "r");

	while (fscanf(fp, "%s %f %d", name, &length, &mass) != EOF) {
		struct whale nw = new_whale(name, length, mass);
		print_whale(&nw);
	}

	fclose(fp);
}

void write_file(int mode) {
	FILE *fp;
	int x = 32;

	if (mode == 0) {
		fp = stdout;
	} else {
		fp = fopen("output.txt", "w");
	}

	fputc('B', fp);
	fputc('\n', fp);
	fprintf(fp, "x = %d\n", x);
	fputs("Hello fputs!\n", fp);

	fclose(fp);
}

void write_bytes(void) {
	FILE *fp;
	unsigned char bytes[6] = {5, 37, 0, 88, 255, 12};

	fp = fopen("output.bin", "wb");

	// In the call to fwrite(), the arguments are:
	//
	// * Pointer to data to write
	// * Size of each 'piece' of data
	// * Count of each 'piece' of data
	// * FILE*
	
	fwrite(bytes, sizeof(char), 6, fp);

	fclose(fp);
}

void read_bytes(void) {
	FILE *fp;
	unsigned char c;

	fp = fopen("output.bin", "rb");

	while (fread(&c, sizeof(char), 1, fp) > 0) {
		printf("%d\n", c);
	}

	fclose(fp);
}
