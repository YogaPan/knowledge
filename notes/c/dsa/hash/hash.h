#ifndef __DICT_H__
#define __DICT_H__

struct entry {
	char key[64];
	const void *value;
	struct entry *next;
};

struct dict {
	struct entry **table;
	int size;
	int count;
};

struct dict *dict_init(int size);
void dict_add(struct dict *self, const char *key, const void *value);
void dict_delete(struct dict *self, const char *key);
int dict_search(struct dict *self, const char *key);
void dict_destroy(struct dict *self);

static inline int dict_count(struct dict *self)
{
	return self->count;
}

#endif /* __DICT_H__ */
