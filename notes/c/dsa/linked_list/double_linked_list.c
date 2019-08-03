#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "double_linked_list.h"

list *list_create(void)
{
	list *newList;

	newList = (list *)malloc(sizeof(list));
	if (newList == NULL) {
		fprintf(stderr, "%d: No memory.\n", __LINE__);
		return NULL;
	}
	newList->len = 0;
	newList->head = newList->tail = NULL;

	return newList;
}

void list_destroy(list *list)
{
	listNode *currNode, *tempNode;

	currNode = list->head;
	while (currNode) {
		tempNode = currNode;
		currNode = currNode->next;
		free(tempNode);
	}
	free(list);
}

void list_append(list *list, int value)
{
	listNode *newNode;

	newNode = (listNode *)malloc(sizeof(listNode));
	if (newNode == NULL) {
		fprintf(stderr, "%d: No memory.\n", __LINE__);
		return;
	}
	newNode->value = value;
	newNode->prev = list->tail;
	newNode->next = NULL;
	if (list->tail) {
		list->tail->next = newNode;
		list->tail = newNode;
	} else {
		list->head = list->tail = newNode;
	}
	list->len++;
}


void list_insert(list *list, int idx, int value)
{
	listNode *currNode, *newNode;

	currNode = list_getNode(list, idx);
	if (currNode == NULL) {
		list_append(list, value);
		return;
	}
	newNode = (listNode *)malloc(sizeof(listNode));
	if (newNode == NULL) {
		fprintf(stderr, "%d: No memory.", __LINE__);
		return;
	}
	newNode->value = value;
	newNode->next = currNode;
	newNode->prev = currNode->prev;

	if (currNode == list->head)
		list->head = newNode;
	else
		currNode->prev->next = newNode;
	currNode->prev = newNode;
	list->len++;
}

int list_pop(list *list, int idx)
{
	listNode *currNode;
	int value;

	currNode = list_getNode(list, idx);
	if (!currNode) {
		fprintf(stderr, "%d: Can't delete Node.\n", __LINE__);
		return -1;
	}
	if (list->len == 1) {
		list->head = list->tail = NULL;
	} else if (currNode == list->head) {
		currNode->next->prev = NULL;
		list->head = currNode->next;
	} else if (currNode == list->tail) {
		currNode->prev->next = NULL;
		list->tail = currNode->prev;
	} else {
		currNode->prev->next = currNode->next;
		currNode->next->prev = currNode->prev;
	}

	value = currNode->value;
	free(currNode);
	list->len--;

	return value;
}

listNode *list_getNode(list *list, int idx)
{
	int len;
	int i;
	listNode *currNode;

	len = list->len;
	/* Check index out of boundary. */
	if ((idx >= len) || (idx < -len))
		return NULL;

	if (idx < 0)
		idx = len + idx;

	if (idx < len / 2) {
		currNode = list->head;
		for (i = 0; i < idx; i++)
			currNode = currNode->next;
	} else {
		currNode = list->tail;
		for (i = 0; i < len - idx - 1; i++)
			currNode = currNode->prev;
	}

	return currNode;
}

int list_getValue(list *list, int idx)
{
	int value;
	listNode *currNode;

	currNode = list_getNode(list, idx);
	if (currNode == NULL) {
		fprintf(stderr, "index out of range.\n");
		return -1;
	}
	value = currNode->value;
	return value;
}

/* Show all list message for debuging. */
void list_debug(list *list)
{
	listNode *currNode;

	printf("head");
	currNode = list->head;
	while (currNode) {
		printf(" -> %d", currNode->value);
		currNode = currNode->next;
	}
	puts(" -> tail");
	if (list->len != 0)
		printf("head: %d, tail: %d\n", list->head->value, list->tail->value);
	printf("%d items.\n", list->len);
	puts("");
}


/* This main function used for test and debug. */
int main(void)
{
	char opt[256];
	int num, pos;
	list *list;
	list = list_create();

	puts("this is test and debug");
	puts("append [number]");
	puts("insert [position] [number]");
	puts("pop [number]");
	puts("exit\n");

	scanf("%s", opt);
	while (strcmp(opt, "exit") != 0) {
		if (strcmp(opt, "append") == 0) {
			scanf("%d", &num);
			list_append(list, num);
			list_debug(list);
		} else if (strcmp(opt, "pop") == 0) {
			scanf("%d", &pos);
			list_pop(list, pos);
			list_debug(list);
		} else if (strcmp(opt, "insert") == 0) {
			scanf("%d %d", &pos, &num);
			list_insert(list, pos, num);
			list_debug(list);
		} else if (strcmp(opt, "get") == 0) {
			scanf("%d", &pos);
			printf("%d\n", list_getValue(list, pos));
		} else {
			fprintf(stderr, "Invalid operation.\n");
		}
		scanf("%s", opt);
	}

	list_destroy(list);
	return 0;
}
