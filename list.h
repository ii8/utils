/**
 * Doubly-linked circular list.
 * Each node in a list need not be the same type;
 *
 * Example:
 *
 * //the list_link macro must always be the first
 * //thing in a structure you want to link.
 * struct test {
 *     list_link;
 *     char somedata;
 * };
 *
 * struct test* a = malloc(sizeof(*a)*4);
 * list_init(a);
 * list_insert(a, a+1);
 * list_insert(a+1, a+2);
 *
 * //Iterating:
 * struct test* i=a;
 * do {
 *     do_something(i->somedata);
 *     i = list_next(i);
 * }while(a != i);
 *
 */

#ifndef _UTIL_LIST_H
#define _UTIL_LIST_H

#define list_link \
	struct list* list_next; \
	struct list* list_prev

struct list {
	struct list* list_next;
	struct list* list_prev;
};

/*
 * list_init must be run on each list exactly once.
 * Subsequent entries should be made with list_insert.
 */
void list_init(void* node);

/*
 * Clear all links in a list completely destroying the list.
 * Careful: Does not free any allocated data of the entries.
 */
void list_clear(void* node);

void list_insert(void* node, void* new);

void list_remove(void* node);

/*
 * Merge list _other_ after node _node_,
 * both lists must be initialized.
 */
void list_join(void* node, void* other);

/*
 * Move _node_ by _pos_ relative to itself.
 */
void list_move(void* node, int pos);

/*
 * Replace _node_ in a list with item _new_, _new_ should not be
 * in the same list
 */
void list_replace(void* node, void* new);

/*
 * Swap positions of two nodes.
 */
void list_swap(void* node, void* other);

/*
 * Returns number of entries in list containing _node_
 */
unsigned list_count(void* node);

/*
 * Returns pointer to a node at _i_ relative to _node_
 */
void* list_seek(void* node, int i);

/*
 * Find offset of _node_ relative to _start_, both must be
 * in the same list. Result will be the shortest distance so
 * may be negative. If _start_ != _node_ and 0 is returned,
 * _node_ does not exist in the list.
 */
int list_find(void* start, void* node);


static inline void* list_next(void* node)
{
	return ((struct list*)node)->list_next;
}

static inline void* list_prev(void* node)
{
	return ((struct list*)node)->list_prev;
}


/* Stack functions */
static inline void list_push(void* stack, void* item)
{
	list_insert(stack, item);
}

static inline void* list_pop(void* stack)
{
	void* item = ((struct list*)stack)->list_next;
	list_remove(item);
	return item;
}

static inline void* list_top(void* stack)
{
	return list_next(stack);
}

/* Queue functions */
static inline void list_enqueue(void* queue, void* item)
{
	list_insert(((struct list*)queue)->list_prev, item);
}

static inline void* list_dequeue(void* queue)
{
	return list_pop(queue);
}

static inline void* list_head(void* queue)
{
	return list_next(queue);
}

/* Double ended queue functions */

static inline void list_inject(void* dequeue, void* item)
{
	list_insert(((struct list*)dequeue)->list_prev, item);
}

/* list_push(void* dequeue, void* item) */

static inline void* list_eject(void* dequeue)
{
	void* item = ((struct list*)dequeue)->list_prev;
	list_remove(item);
	return item;
}

/* list_pop(void* dequeue, void* item) */

static inline void* list_tail(void* dequeue)
{
	return list_prev(dequeue);
}

/* list_head(void* dequeue) */

#endif

