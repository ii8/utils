
#include <stdlib.h>
#include <string.h>

#include "array.h"

unsigned int auto_grow(unsigned size)
{
	if(size>40) {
		if(size > 1021)
			return 500;
		return size;
	}
	return 8;
}

struct array* array_create(unsigned size)
{
	struct array* a = malloc(sizeof(struct array));
	if(!size) size=1;
	a->count = 0;
	a->size = size;
	a->buffer = malloc(sizeof(void*) * size);
	return a;
}

void array_free(struct array* a)
{
	free(a->buffer);
	free(a);
}

void array_destroy(struct array* a)
{
	while (a->size--)
		free(a->buffer[a->size]);
	free(a->buffer);
	free(a);
}

void* array_resize(struct array* a, unsigned size)
{
	void** indices = realloc(a->buffer, size * sizeof(void*));
	if(indices) {
		a->size = size;
		a->buffer = indices;
		return *indices;
	}
	return NULL;
}

void* array_grow(struct array* a, int amount)
{
	if(amount>0)
		return array_resize(a, a->size+amount);
	/* add feature to grow before start */
	return NULL;
}

void* array_shrink(struct array* a, int amount)
{
	return array_resize(a, a->size-amount);
}

void array_fit(struct array* a)
{
	array_resize(a, a->count);
}

void* array_insert(struct array* a, unsigned i, void* item)
{
	unsigned j;
	if(a->size<=a->count) {
		if(!array_grow(a, auto_grow(a->size)))
			return NULL;
	}
	j = ++a->count;
	while(--j != i) {
		a->buffer[j] = a->buffer[j-1];
	}
	a->buffer[i] = item;
	return item;
}

void* array_append(struct array* a, void* item)
{
	if(a->size<=a->count) {
		if(!array_grow(a, a->size))
			return NULL;
	}
	a->buffer[a->count++] = item;
	return item;
}

void* array_prepend(struct array* a, void* item)
{
	return array_insert(a, 0, item);
}

void array_remove(struct array* a, int i)
{
	memmove(a->buffer+i, a->buffer+i+1, sizeof(void*) * (--a->count-i));
}

