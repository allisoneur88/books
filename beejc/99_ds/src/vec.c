#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>

#define start_size 4

typedef struct {
	int *data;
	size_t len;
	size_t cap;
} vec;

vec *vec_new(void) {
	vec *v = malloc(sizeof(*v));
	if (!v) return NULL;

	int *data = calloc((size_t)start_size, sizeof(*v->data));
	if (!data) {
		free(v);
		return NULL;
	}

	v->data = data;
	v->len = 0;
	v->cap = start_size;

	return v;
}

void vec_free(vec *v) {
	if (!v) return;
	free(v->data);
	free(v);
}

void vec_grow(vec *v) {
	v->data = realloc(v->data, 2 * v->cap * sizeof(*v->data));
	v->cap *= 2;
}

void vec_push(vec *v, int item) {
	v->data[v->len] = item;
	v->len = v->len + 1;

	if (v->len == v->cap) {
		vec_grow(v);
	}
}

void vec_display(vec *v) {
	printf("len: %zu, cap: %zu\n", v->len, v->cap);
	printf("[");
	for (int i = 0; i < v->cap; i++) {
		printf("%d ", v->data[i]);
	}
	printf("]\n");
}

int main(void) {
	vec *vec = vec_new();
	vec_push(vec, 55);
	vec_push(vec, 66);
	vec_push(vec, 77);
	vec_push(vec, 88);
	//vec_push(vec, 77);

	vec_display(vec);

	vec_free(vec);
}
