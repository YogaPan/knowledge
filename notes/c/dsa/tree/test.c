#include <stdio.h>
#include "binary_tree.h"

int main(void)
{
	struct node *tree = NULL;

	tree_insert(&tree, 30);
	tree_insert(&tree, 20);
	tree_insert(&tree, 40);

	tree_preorder(tree);
	printf("\n");
	tree_inorder(tree);
	printf("\n");
	tree_postorder(tree);
	printf("\n");

	tree_destroy(tree);

	return 0;
}
