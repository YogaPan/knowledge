#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

/* Create a queue and return address.
 * If false, return NULL. */
queue *queueCreate(void)
{
	queue *q;

	q = malloc(sizeof(queue));
	if (q == NULL)
		return NULL;
	q->len = 0;
	q->head = q->tail = NULL;
	q->dup = NULL;
	q->free = NULL;
	q->match = NULL;

	return q;
}

/* Release a queue. */
void queueRelease(queue *q)
{
	queueNode *node;
	queueIter *iter;

	iter = queueGetIter(q);
	while ((node = queueNext(iter)) != NULL) {
		if (q->free)
			q->free(node->value);
		free(node);
	}
	queueReleaseIter(iter);
	free(q);
}

/* Reverse queue. */
void queueReverse(queue *q)
{
	queueNode *curr, *prev;
	queueIter *iter;

	prev = NULL;
	iter = queueGetIter(q);
	while ((curr = queueNext(iter)) != NULL) {
		curr->next = prev;
		prev = curr;
	}
	q->tail = q->head;
	q->head = prev;
	queueReleaseIter(iter);
}

/* Copy a new queue and return address.
 * If false, return NULL. */
queue *queueDup(queue *orig)
{
	queue *copy;
	queueNode *node;
	queueIter *iter;

	copy = queueCreate();
	copy->dup = orig->dup;
	copy->free = orig->free;
	copy->match = orig->match;

	iter = queueGetIter(orig);
	while ((node = queueNext(iter)) != NULL) {
		void *value;

		if (copy->dup) {
			value = copy->dup(node->value);
			if (value == NULL) {
				queueReleaseIter(iter);
				queueRelease(copy);
				return NULL;
			}
		} else {
			value = node->value;
		}

		if (queueAdd(copy, value) == NULL) {
			queueRelease(copy);
			queueReleaseIter(iter);
			return NULL;
		}
	}
	queueReleaseIter(iter);
	return copy;
}

/* Search whicj node have key and return address.
 * If not found, return NULL. */
queueNode *queueSearchKey(queue *q, void *key)
{
	queueIter *iter;
	queueNode *node;

	iter = queueGetIter(q);
	while ((node = queueNext(iter)) != NULL) {
		if (q->match) {
			if (q->match(node->value, key)) {
				queueReleaseIter(iter);
				return node;
			}
		} else {
			if (key == node->value) {
				queueReleaseIter(iter);
				return node;
			}
		}
	}
	queueReleaseIter(iter);
	return node;
}

/* Add a new value into queue's tail. */
queue *queueAdd(queue *q, void *value)
{
	queueNode *newNode;

	newNode = malloc(sizeof(queueNode));
	if (newNode == NULL)
		return NULL;
	newNode->value = value;
	newNode->next = NULL;

	if (q->len == 0) {
		q->head = q->tail = newNode;
	} else {
		q->tail->next = newNode;
		q->tail = newNode;
	}
	q->len++;
	return q;
}

/* Delete head node from queue and return value. */
void *queueDelete(queue *q)
{
	void *popValue;
	queueNode *headNode;

	if (q->len == 0)
		return NULL;

	headNode = q->head;
	popValue = headNode->value;

	if (q->len == 1)
		q->head = q->tail = NULL;
	else
		q->head = q->head->next;

	free(headNode);
	q->len--;
	return popValue;
}

/* Create a new iterator and return address.
 * If false, return NULL. */
queueIter *queueGetIter(queue *q)
{
	queueIter *iter;

	iter = malloc(sizeof(queueIter));
	if (iter == NULL)
		return NULL;
	iter->next = q->head;

	return iter;
}

/* Release iterator. */
void queueReleaseIter(queueIter *iter)
{
	free(iter);
}

/* Let iterator go to next node. */
queueNode *queueNext(queueIter *iter)
{
	queueNode *node;

	node = iter->next;
	if (node == NULL)
		return NULL;
	iter->next = node->next;
	return node;
}

/* Show all queue message. */
void queueDebug(queue *q)
{
	queueNode *node;
	queueIter *iter;

	iter = queueGetIter(q);
	printf("length: %ld\n", q->len);
	printf("head -> ");
	while ((node = queueNext(iter)) != NULL)
		printf("%d -> ", *(int *)node->value);
	queueReleaseIter(iter);
	printf("tail\n");
}

void num_free(void *ptr)
{
	free(ptr);
}

void *num_dup(void *ptr)
{
	int *newnum;
	newnum = malloc(sizeof(int));
	*newnum = *(int *)ptr;

	return newnum;
}

int num_match(void *ptr, void *key)
{
	if (*(int *)ptr == *(int *)key)
		return 1;
	return 0;
}

/* This main function used to test and debug. */
int main(void)
{
	int *num;
	char opt[256];
	queue *q, *temp;
	queueNode *node;
	q = queueCreate();
	q->dup = num_dup;
	q->free = num_free;
	q->match = num_match;

	puts("this is queue test and debug.");
	puts("add [number]");
	puts("delete");
	puts("exit\n");

	scanf("%s", opt);
	while (strcmp(opt, "exit") != 0) {
		if (strcmp(opt, "add") == 0) {
			num = malloc(sizeof(int));
			scanf("%d", num);
			queueAdd(q, num);
			queueDebug(q);
			printf("\n");
		} else if (strcmp(opt, "delete") == 0) {
			num = queueDelete(q);
			printf("delete value is %d\n", *num);
			free(num);
			queueDebug(q);
			printf("\n");
		} else if (strcmp(opt, "reverse") == 0) {
			queueReverse(q);
			queueDebug(q);
			printf("\n");
		} else if (strcmp(opt, "dup") == 0) {
			temp = queueDup(q);
			free(q);
			q = temp;
			queueDebug(q);
			printf("\n");
		} else if (strcmp(opt, "search") == 0) {
			num = malloc(sizeof(int));
			scanf("%d", num);
			node = queueSearchKey(q, num);
			free(num);
			if (node)
				printf("yes, %d in the queue.\n\n", *(int *)node->value);
			else
				printf("No this value in queue.\n\n");
		} else if (strcmp(opt, "exit") == 0) {
			break;
		} else {
			fprintf(stderr, "Invalue operation.\n\n");
			fseek(stdin, 0, SEEK_END);
		}
		scanf("%s", opt);
	}

	queueRelease(q);
	return 0;
}
