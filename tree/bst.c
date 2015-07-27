#include <stdio.h>
#include <assert.h>
#include <stddef.h>
#include <stdbool.h>
#include <malloc.h>
#include "bst.h"

static bool compare_node(struct bst_node *lhs, struct bst_node *rhs)
{
	return lhs->data->num <= rhs->data->num;
}

static void count_node(struct bst_node *node)
{
	node->data->count += node->lc ? node->lc->data->count : 0
					   + node->rc ? node->rc->data->count : 0;
}

struct bst_node* bst_create(int *array, int size)
{
	int i = 0;
	struct bst_node* root = bst_new_node();
	root->data->num = array[0];

	for(i = 1; i < size; i++)
	{
		struct bst_node* node = bst_new_node();
		node->data->num = array[i];
 		bst_insert(root, node);
	}

	return root;
}

void bst_insert(struct bst_node *root, struct bst_node* in)
{
	assert(in);
	assert(root);
		
	struct bst_node * it = root;
	struct bst_node * pa = it->pa;

	while (it)
	{
		pa = it;
		if (compare_node(in, it))
		{
			it = it->lc;
		}
		else
		{
			it = it->rc;
		}
		pa->data->count++;
	}
	
	if (compare_node(in, pa))
	{
		pa->lc = in;
		in->pa = pa;
	}
	else
	{
		pa->rc = in;
		in->pa = pa;
	}
}

struct bst_node* bst_new_node(void)
{
	struct bst_node *node = malloc(sizeof(struct bst_node));
	assert(node);
	struct bst_node_data *data = malloc(sizeof(struct bst_node_data));
	assert(data);

	data->count = 1;
	node->data = data;
	node->lc = NULL;
	node->rc = NULL;
	node->pa = NULL;
	return node;
}

void left_rotate(struct bst_node** pp_root, struct bst_node *node)
{
	assert(node->rc);
	struct bst_node *pa = node->pa;
	struct bst_node *rc = node->rc;

	node->rc = rc->lc;
	node->pa = rc;
	if (node->rc)
		node->rc->pa = node;
	rc->lc = node;
	rc->pa = pa;
	if (pa)
	{
		if (pa->lc == node)
		{
			pa->lc = rc;
		}
		else
		{
			pa->rc = rc;
		}
	}
	else
	{
		*pp_root = rc;
	}
	count_node(node);
	count_node(rc);
}

void right_rotate(struct bst_node **pp_root, struct bst_node *node)
{
	assert(node->lc);
	struct bst_node *pa = node->pa;
	struct bst_node *lc = node->lc;

	node->lc = lc->rc;
	node->pa = lc;
	lc->rc = node;
	lc->pa = pa;
	if (node->lc)
		node->lc->pa = node;
	if (pa)
	{
		if (pa->lc == node)
		{
			pa->lc = lc;
		}
		else
		{
			pa->rc = lc;
		}
	}
	else
	{
		*pp_root = lc;
	}
	count_node(node);
	count_node(lc);
}

void bst_free(struct bst_node* root)
{
	if(root)
	{
		if (root->lc)
		{
			bst_free(root->lc);
		}
		if (root->rc)
		{
			bst_free(root->rc);
		}
		if (root->data)
		{
			free(root->data);
			root->data = NULL;
		}
		free(root);
		root = NULL;
	}
}

struct bst_node* bst_select(struct bst_node *node, int idx)
{
	if (!node || idx < 1)
		return NULL;

	if (idx <= node->data->count)
	{
		int lc_count = node->lc ? node->lc->data->count : 0;
		if (lc_count + 1 == idx)
			return node;
		
		if (lc_count >= idx)
			return bst_select(node->lc, idx);
		else
			return bst_select(node->rc, idx - lc_count - 1);
	}
	else
		return NULL;
}

int bst_rank(struct bst_node *root, struct bst_node *node)
{
	assert(root && node);
	int rank = (node->lc ? node->lc->data->count : 0) + 1;
	struct bst_node *it = node;
	while(it != root)
	{
		if (it == it->pa->rc)
		{
			rank += (it->pa->lc ? it->pa->lc->data->count : 0) + 1;
		}
		it = it->pa;
	}
	return rank;
}

void bst_print_inorder(struct bst_node *root)
{
	if (root)
	{
		if (root->lc)
		{
			bst_print_inorder(root->lc);
		}
		printf("node[%d] count[%d]\n", root->data->num, root->data->count);
		if(root->rc)
		{
			bst_print_inorder(root->rc);
		}
	}
}

void dump_tree(struct bst_node* root, struct bst_node **array)
{
	static int i = 0;
	assert(root);
	assert(array);
	if(root->lc)
	{
		dump_tree(root->lc, array);
	}
	array[i++] = root;
	if (root->rc)
	{
		dump_tree(root->rc, array);
	}	
}

