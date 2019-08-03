#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

struct dict *dict_init(int size)
{
	struct dict *self;

	self = malloc(sizeof(*self));
	if (self == NULL)
		return NULL;
	self->size  = size;
	self->count = 0;

	self->table = calloc(sizeof(struct entry *), size);
	if (self->table == NULL) {
		free(self);
		return NULL;
	}

	return self;
}

int hash(const char *key, int size)
{
	int i;
	int sum = 0;

	for (i = 0; i < strlen(key); i++)
		sum += key[i];

	return (sum % size);
}

void dict_add(struct dict *self, const char *key, const void *value)
{
	int n;
	struct entry *e;

	e = malloc(sizeof(*e));
	if (e == NULL)
		return;

	strncpy(e->key, key, 64);
	e->value = value;
	e->next = NULL;

	n = hash(key, self->size);

	if (self->table[n] == NULL) {
		self->table[n] = e;
	} else {
		e->next = self->table[n];
		self->table[n] = e;
	}

	self->count++;
}

void dict_delete(struct dict *self, const char *key)
{
	int n;
	struct entry *prev, *curr;

	n = hash(key, self->size);

	curr = self->table[n];
	if (curr != NULL) {
		if (strcasecmp(curr->key, key) == 0) {
			self->table[n] = curr->next;
			free(curr);
			return;
		}
	}

	prev = NULL;
	curr = curr->next;
	while (curr != NULL) {
		if (strcasecmp(curr->key, key) == 0) {
			prev->next = curr->next;
			free(curr);
			return;
		}

		prev = curr;
		curr = curr->next;
	}
}

int dict_search(struct dict *self, const char *key)
{
	int n;
	struct entry *e;

	n = hash(key, self->size);
	
	e = self->table[n];
	while (e != NULL) {
		if (strcasecmp(e->key, key) == 0)
			return 1;
		else
			e = e->next;
	}

	return 0;
}

void dict_destroy(struct dict *self)
{
	int i;
	struct entry *e, *tmp;

	for (i = 0; i < self->size; i++) {
		e = self->table[i];

		while (e != NULL) {
			tmp = e;
			e = e->next;
			free(tmp);
		}
	}

	free(self);
}
