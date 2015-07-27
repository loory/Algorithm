#ifndef _RBT_H_
#define _RBT_H_
#include "bst.h"

enum color
{
	BLACK = 0,
	RED
};

struct rbt_node_data
{
	struct bst_node_data bst;
	int color;	
};

struct rbt_node
{
	struct rbt_node* lc;
	struct rbt_node* rc;
	struct rbt_node* pa;
	struct rbt_node_data* data;
};

struct rbt_node* rbt_new_node(void);
struct rbt_node* rbt_create(int*, int);
void rbt_free(struct rbt_node *root);
void rbt_insert(struct rbt_node **root, struct rbt_node *in);
void rbt_print_inorder(struct rbt_node *root);



#endif
