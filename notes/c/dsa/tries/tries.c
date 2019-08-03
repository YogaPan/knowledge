#include <stdio.h>
#include <stdlib.h>

struct node {
	char name[32];
	struct node path[10];
};

struct tries {
	struct node *root;
}

struct tries *tries_init(void)
{
	struct tries *self;

	self = malloc(sizeof(*self));
	if (self == NULL)
		return NULL;
	self->root = NULL;

	return self;
}

void tries_destroy(struct tries *self)
{
	free(self);
}

int main(void)
{
	return 0;
}
