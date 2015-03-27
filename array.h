#ifndef _UTIL_ARRAY_H
#define _UTIL_ARRAY_H

struct array {
	unsigned size;
	unsigned count;
	void** buffer;
};

/*
 * create array with given initial size.
 */
struct array* array_create(unsigned size);

/*
 * Free the array.
 */
void array_free(struct array* a);

/*
 * Free array and data it points to.
 */
void array_destroy(struct array* a);
void* array_resize(struct array* a, unsigned size);

void* array_grow(struct array* a, int amount);

void* array_shrink(struct array* a, int amount);

void array_fit(struct array* a);

void* array_insert(struct array* a, unsigned i, void* item);
/*replace
move
swap*/

void* array_append(struct array* a, void* item);

void* array_prepend(struct array* a, void* item);

void array_remove(struct array* a, int i);

/* Access functions */

static inline unsigned array_count(struct array* a)
{
	return a->count;
}

static inline void* array_at(struct array* a, unsigned i)
{
	return a->buffer[i];
}

static inline void* array_first(struct array* a)
{
	return a->buffer[0];
}

static inline void* array_last(struct array* a)
{
	return a->buffer[a->count-1];
}

#endif

