#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

void tree_insert(struct node **tree, int data)
{
	struct node *new_node;

	if (*tree == NULL) {
		new_node = malloc(sizeof(*new_node));
		new_node->left = new_node->right = NULL;
		new_node->data = data;

		*tree = new_node;
		return;
	}

	if (data < (*tree)->data)
		tree_insert(&(*tree)->left, data);
	else
		tree_insert(&(*tree)->right, data);
}

struct node *tree_search(struct node **tree, int data)
{
	if (*tree == NULL)
		return NULL;

	if (data < (*tree)->data)
		return tree_search(&(*tree)->left, data);
	else if (data > (*tree)->data)
		return tree_search(&(*tree)->right, data);

	return *tree;
}

void tree_preorder(struct node *tree)
{
	if (tree) {
		printf("%d\n", tree->data);
		tree_preorder(tree->left);
		tree_preorder(tree->right);
	}
}

void tree_inorder(struct node *tree)
{
	if (tree) {
		tree_inorder(tree->left);
		printf("%d\n", tree->data);
		tree_inorder(tree->right);
	}
}

void tree_postorder(struct node *tree)
{
	if (tree) {
		tree_postorder(tree->left);
		tree_postorder(tree->right);
		printf("%d\n", tree->data);
	}
}

void tree_destroy(struct node *tree)
{
	if (tree) {
		tree_destroy(tree->left);
		tree_destroy(tree->right);
		free(tree);
	}
}
