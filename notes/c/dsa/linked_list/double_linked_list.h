#ifndef _LIST_H
#define _LIST_H

typedef struct listNode {
	int value;
	struct listNode *prev;
	struct listNode *next;
} listNode;

typedef struct list {
	int len;
	struct listNode *head;
	struct listNode *tail;
} list;

list *list_create(void);
void list_destroy(list *list);
void list_insert(list *list, int idx, int value);
void list_append(list *list, int value);
int list_pop(list *list, int idx);
void list_debug(list *list);
listNode *list_getNode(list *list, int idx);
int list_getValue(list *list, int idx);
void list_rotate(list *list, int n);
list *list_reverse(list *list);
list *list_sort(list* list);

#endif
