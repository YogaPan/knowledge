#ifndef __BINARY_TREE__
#define __BINARY_TREE__

struct node {
	int data;
	struct node *left;
	struct node *right;
};

void tree_insert(struct node **tree, int data);
void tree_destroy(struct node *tree);
void tree_preorder(struct node *tree);
void tree_inorder(struct node *tree);
void tree_postorder(struct node *tree);

#endif /* __BINARY_TREE__ */
