#ifndef _BST_H_
#define _BST_H_

struct bst_node_data
{
	int num;
	int count;
};

struct bst_node
{
	struct bst_node* lc;
	struct bst_node* rc;
	struct bst_node* pa;
	struct bst_node_data* data;
};

struct bst_node* bst_new_node(void);
struct bst_node* bst_create(int *array, int size);
void bst_free(struct bst_node* root);
void bst_insert(struct bst_node *root, struct bst_node* in);
void left_rotate(struct bst_node** pp_root, struct bst_node *node);
void right_rotate(struct bst_node **pp_root, struct bst_node *node);
void bst_print_inorder(struct bst_node *root);
void dump_tree(struct bst_node* root, struct bst_node **array);
struct bst_node* bst_select(struct bst_node *node, int idx);
int bst_rank(struct bst_node *root, struct bst_node *node);
#endif
