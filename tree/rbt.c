#include "stdio.h"
#include "assert.h"
#include "stddef.h"
#include "stdbool.h"
#include "malloc.h"
#include "rbt.h"

#if 0 
#define printf(...)

#endif

static bool is_red(struct rbt_node *node)
{
	assert(node);
	return node->data->color == RED;
}

static void set_color(struct rbt_node *node, int color)
{
	assert(node);
	node->data->color = color;
}

static bool is_root(struct rbt_node *node)
{
	assert(node);
	return node->pa == NULL;
}

static void rb_balance(struct rbt_node **pp_root, struct rbt_node *node);

static void pop_red_up(struct rbt_node **pp_root, struct rbt_node *papa)
{	
	set_color(papa->lc, BLACK);
	set_color(papa->rc, BLACK);
	if (is_root(papa))
		set_color(papa, BLACK);
	else
	{
		set_color(papa, RED);
		rb_balance(pp_root, papa);
	}
}

static void rb_balance(struct rbt_node **pp_root, struct rbt_node *node)
{
	struct rbt_node* root = *pp_root;
	assert(root);
	assert(node);
	if (is_root(node))
	{
		*pp_root = node;
		set_color(root,BLACK);
		return;
	}
	struct rbt_node *pa = node->pa;

	assert(pa);

	if (!is_red(pa))
		return;
	else
	{
		struct rbt_node *papa = pa->pa;
		assert(papa);
		if (papa->lc == pa)//if pa is grandpa's left child
		{
			if (papa->rc && is_red(papa->rc))// if pa has red uncle
			{
				pop_red_up(pp_root, papa);	
				return;
			}
			else
			{
				if (pa->rc == node)// rotate for straight
				{
					left_rotate((struct bst_node**)pp_root, (struct bst_node*)pa);				
				}
				right_rotate((struct bst_node**)pp_root, (struct bst_node*)papa);
				set_color(papa, RED);
				set_color(papa->pa, BLACK);
			}
		}
		else
		{
		
			if (papa->lc && is_red(papa->lc))
			{
				pop_red_up(pp_root, papa);
				return;
			}
			else
			{
				if (pa->lc == node)
				{
					right_rotate((struct bst_node**)pp_root, (struct bst_node*)pa);
				}
				left_rotate((struct bst_node**)pp_root, (struct bst_node*)papa);
				set_color(papa, RED);
				set_color(papa->pa, BLACK);
			}
		}
	}
}

struct rbt_node* rbt_create(int *array, int size)
{
	int i = 0;
	struct rbt_node* root = rbt_new_node();
	root->data->bst.num = array[0];
	root->data->color = BLACK;

	for(i = 1; i < size; i++)
	{
		struct rbt_node* node = rbt_new_node();
		node->data->bst.num = array[i];
 		node->data->color = RED;
		rbt_insert(&root, node);
	}
	return root;
}

void rbt_insert(struct rbt_node **root, struct rbt_node *in)
{
	bst_insert((struct bst_node*)*root, (struct bst_node*)in);
	rb_balance(root, in);
}

struct rbt_node* rbt_new_node(void)
{
	struct rbt_node *node = malloc(sizeof(struct rbt_node));
	assert(node);
	struct rbt_node_data *data = malloc(sizeof(struct rbt_node_data));
	assert(data);
	
	node->data = data;
	node->lc = NULL;
	node->rc = NULL;
	node->pa = NULL;
	return node;
}

void rbt_free(struct rbt_node* root)
{
	bst_free((struct bst_node*)root);
}

void rbt_print_inorder(struct rbt_node *root)
{
	if (root)
	{
		if (root->lc)
		{
			rbt_print_inorder(root->lc);
		}
		printf("%d %s\n", root->data->bst.num, root->data->color==RED ? "red":"black");
		if(root->rc)
		{
			rbt_print_inorder(root->rc);
		}
	}
}

