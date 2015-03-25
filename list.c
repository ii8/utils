#include "list.h"

#define list_(ptr) ((struct list*)ptr)

void list_init(void* node)
{
	list_(node)->list_next = node;
	list_(node)->list_prev = node;
}

void list_clear(void* node)
{
	struct list* i = list_(node)->list_next;
	do {
		list_(node)->list_next = 0;
		list_(node)->list_prev = 0;
		node = i;
		i = i->list_next;
	}while(i != 0);
}

void list_insert(void* node, void* new)
{
	list_(new)->list_next = list_(node)->list_next;
	list_(new)->list_prev = node;
	list_(node)->list_next->list_prev = new;
	list_(node)->list_next = new;
}

void list_remove(void* node)
{
	list_(node)->list_prev->list_next = list_(node)->list_next;
	list_(node)->list_next->list_prev = list_(node)->list_prev;
	list_(node)->list_next = 0;
	list_(node)->list_prev = 0;
}

void list_join(void* node, void* other)
{
	list_(other)->list_prev->list_next = list_(node)->list_next;
	list_(node)->list_next->list_prev = list_(other)->list_prev;
	list_(other)->list_prev = node;
	list_(node)->list_next = other;
}

void list_move(void* node, int pos)
{
	if(pos <= 0) pos--;
	list_(node)->list_prev->list_next = list_(node)->list_next;
	list_(node)->list_next->list_prev = list_(node)->list_prev;
	list_insert(list_seek(node, pos), node);
}

void list_replace(void* node, void* new)
{
	list_(new)->list_prev = list_(node)->list_prev;
	list_(new)->list_next = list_(node)->list_next;
	list_(node)->list_next->list_prev = new;
	list_(node)->list_prev->list_next = new;
	list_(node)->list_prev = 0;
	list_(node)->list_next = 0;
}

void list_swap(void* node, void* other)
{
	void* next = list_(other)->list_next;
	void* prev = list_(other)->list_prev;
	list_(other)->list_next->list_prev = node;
	list_(other)->list_prev->list_next = node;
	list_(node)->list_prev->list_next = other;
	list_(node)->list_next->list_prev = other;
	list_(other)->list_next = list_(node)->list_next;
	list_(other)->list_prev = list_(node)->list_prev;
	list_(node)->list_next = next;
	list_(node)->list_prev = prev;
}

unsigned list_count(void* node)
{
	unsigned count = 1;
	void* head = node;
	while(list_(node)->list_next != head) {
		count++;
		node = list_(node)->list_next;
	}
	return count;
}

void* list_seek(void* node, int i)
{
	if(i>0) {
		while(i--)
			node = list_(node)->list_next;
		return node;
	} if(i<0) {
		while(i++)
			node = list_(node)->list_prev;
		return node;
	}
	return node;
}

int list_find(void* start, void* node)
{
	struct list *f=start, *b=start;
	int count = 0;
	do {
		if(f == node)
			return count;
		if(b == node)
			return -count;
		count++;
		f = f->list_next;
		b = b->list_prev;
	}while(f!=start);
	return 0;
}
