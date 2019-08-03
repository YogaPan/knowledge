#include <stdio.h>
#include <stdlib.h>

#define for_each_node(curr, stack) \
	for (curr = (stack)->head; curr != NULL; curr = curr->next)

struct node {
	int value;
	struct node *next;
};

struct stack {
	int size;
	struct node *head;
};

struct stack *stack_init(void)
{
	struct stack *self;

	self = malloc(sizeof(*self));
	if (self == NULL)
		return NULL;
	self->size = 0;
	self->head = NULL;

	return self;
}

struct node *stack_insert(struct stack *self, int value)
{
	struct node *new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return NULL;
	
	new->value = value;
	new->next  = self->head;

	self->head = new;
	self->size++;
	
	return new;
}

int stack_pop(struct stack *self)
{
	struct node *curr;
	int value;

	if (self->size == 0) {
		fprintf(stderr, "Stack is empty\n");
		return -1;
	}

	curr = self->head;
	self->head = curr->next;
	value = curr->value;

	free(curr);
	self->size--;

	return value;
}

void stack_destroy(struct stack *self)
{
	struct node *curr, *next;

	curr = self->head;
	while (curr != NULL) {
		next = curr->next;
		free(curr);
		curr = next;
	}

	free(self);
}

void stack_reverse(struct stack *self)
{
	struct node *prev, *curr, *next;

	curr = self->head;
	prev = NULL;
	while (curr != NULL) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	self->head = prev;
}

void stack_print(struct stack *self)
{
	struct node *curr;

	printf("\n");
	for_each_node(curr, self) 
		printf("%d -> ", curr->value);
	printf("NULL\n\n");
}

int main(void)
{
	int num;
	struct stack *stack;

	stack = stack_init();

	printf("Enter -1 to exit, -2 to pop, -3 to reverse\n\n");
	scanf("%d", &num);
	while (num != -1) {
		if (num == -2) {
			num = stack_pop(stack);
			printf("pop value is %d\n", num);
			stack_print(stack);
			scanf("%d", &num);
		} else if (num == -3) {
			stack_reverse(stack);
			stack_print(stack);
			scanf("%d", &num);
		} else {
			stack_insert(stack, num);
			stack_print(stack);
			scanf("%d", &num);
		}
	}

	stack_destroy(stack);

	return 0;
}
