/*
 * =============================================================================
 *
 *       Filename:  red_black_tree_app.c
 *
 *    Description:  red black tree app test
 *
 *        Created:  19/03/2017 11:39:34 PM
 *
 *         Author:  raoping,raoping456136@sohu.com
 *
 * =============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "rbtree.h"

#define NUM_NODES 1000000

struct mynode {
  	struct rb_node node;
  	char *string;
};

struct rb_root mytree = RB_ROOT;

struct mynode * my_search(struct rb_root *root, char *string)
{
  	struct rb_node *node = root->rb_node;

  	while (node) {
  		struct mynode *data = container_of(node, struct mynode, node);
		int result;

		result = strcmp(string, data->string);

		if (result < 0)
  			node = node->rb_left;
		else if (result > 0)
  			node = node->rb_right;
		else
  			return data;
	}
	return NULL;
}

int my_insert(struct rb_root *root, struct mynode *data)
{
  	struct rb_node **new = &(root->rb_node), *parent = NULL;

  	/* Figure out where to put new node */
  	while (*new) {
  		struct mynode *this = container_of(*new, struct mynode, node);
  		int result = strcmp(data->string, this->string);

		parent = *new;
  		if (result < 0)
  			new = &((*new)->rb_left);
  		else if (result > 0)
  			new = &((*new)->rb_right);
  		else
  			return 0;
  	}

  	/* Add new node and rebalance tree. */
  	rb_link_node(&data->node, parent, new);
  	rb_insert_color(&data->node, root);

	return 1;
}

void my_free(struct mynode *node)
{
	if (node != NULL) {
		if (node->string != NULL) {
			free(node->string);
			node->string = NULL;
		}
		free(node);
		node = NULL;
	}
}

static float get_more_sec_time(struct timeval start, struct timeval end)
{
	float ftime =  (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec)/1000000.0;
	return ftime;
}

int main()
{

	struct mynode *mn[NUM_NODES];

    struct timeval start, end;
    gettimeofday( &start, NULL );
    /*
    printf("start : %d.%d\n", start.tv_sec, start.tv_usec);
    sleep(3);
    gettimeofday( &end, NULL );
    printf("end   : %d.%d\n", end.tv_sec, end.tv_usec);
    printf("run time: %d.%06d\n", (end.tv_sec-start.tv_sec), (end.tv_usec-start.tv_usec));
    return 0;
    */

	/* *insert */
	int i = 0;
	for (; i < NUM_NODES; i++)
	{
		mn[i] = (struct mynode *)malloc(sizeof(struct mynode));
		mn[i]->string = (char *)malloc(sizeof(char) * 4);
		sprintf(mn[i]->string, "%d", i);
		my_insert(&mytree, mn[i]);
	}
	gettimeofday( &end, NULL );
	printf("insert %d figure run time:%f s.\n", NUM_NODES, get_more_sec_time(start, end));



	/*
	struct rb_node *node;
	printf("search all nodes: \n");
	for (node = rb_first(&mytree); node; node = rb_next(node))
		printf("key = %s\n", rb_entry(node, struct mynode, node)->string);
	*/

	/* search 1 test */
	gettimeofday( &start, NULL );
	struct mynode *data = my_search(&mytree, "20");
	if (data)
	{
		gettimeofday( &end, NULL );
		printf("get one data(%s) from red_black_tree run time: %d.%06d s.\n", data->string,(end.tv_sec-start.tv_sec), (end.tv_usec-start.tv_usec));
	}

	/* *delete */
	/*
	printf("delete node 20: \n");
	struct mynode *data = my_search(&mytree, "20");
	if (data) {
		rb_erase(&data->node, &mytree);
		my_free(data);
	}
	*/

	/* *delete again*/
	/*
	printf("delete node 10: \n");
	data = my_search(&mytree, "10");
	if (data) {
		rb_erase(&data->node, &mytree);
		my_free(data);
	}
	*/

	/* *delete once again*/
	/*
	printf("delete node 15: \n");
	data = my_search(&mytree, "15");
	if (data) {
		rb_erase(&data->node, &mytree);
		my_free(data);
	}
	*/

	/* *search again*/
	/*
	printf("search again:\n");
	for (node = rb_first(&mytree); node; node = rb_next(node))
		printf("key = %s\n", rb_entry(node, struct mynode, node)->string);
	*/
	return 0;
}


