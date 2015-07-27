#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include "bst.h"
#include "rbt.h"

void test_bst()
{
	int array[] = {99,2,3,55,5,67,34,11,16,83};
	printf("=====bst test start=====\n");
	struct bst_node *root = bst_create(array,sizeof(array)/sizeof(int));
	bst_print_inorder(root);


	struct bst_node** dt = malloc(sizeof(struct bst_node*) * root->data->count);
	dump_tree(root, dt);
	int i = 0;
	for(i = 0; i < root->data->count; i++)
	{
		struct bst_node *s = bst_select(root, i + 1);
		assert(s);
		printf("select %d %d %d \n", i + 1, s->data->num, dt[i]->data->num);
		assert(s->data->num == dt[i]->data->num && s->data->count == dt[i]->data->count);
	}
	
	for(i = 0; i < root->data->count; i++)
	{
		int r = bst_rank(root, dt[i]);
		printf("node %d's rank is %d\n", dt[i]->data->num, r);
		assert(r == i + 1);	
	}

	free(dt);

	struct bst_node *s = bst_select(root, -1);
	assert(!s);

	s = bst_select(root, root->data->count + 1);
	assert(!s);
	
	bst_free(root);
	printf("=====bst test end=====\n");

}

void test_rbt()
{
	int array[] = {99,2,3,55,5,67,34,11,16,83};
	struct rbt_node *root = rbt_create(array,sizeof(array)/sizeof(int));
	printf("=====rbt test start=====\n");
	rbt_print_inorder(root);
	rbt_free(root);
	printf("=====rbt test end=====\n");
}

int main(int argc, char **argv)
{
	test_bst();
	test_rbt();
	return 0;
}
