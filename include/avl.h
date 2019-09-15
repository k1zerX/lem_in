#ifndef AVL_H
# define AVL_H

typedef struct s_node		t_node;

# include "container.h"

# define T_AVL_KEY \
	char *

# define AVL_KEY \
	name

# define HEIGHT(x) ((x) ? (x->height) : (0))

struct						s_node
{
	T_AVL_KEY				AVL_KEY;

	t_container				edges;
	int						distance;

	t_node					*left;
	t_node					*right;
	unsigned char			height;
};

t_node						*avl_balance(t_node *node);
t_node						*avl_insert(t_node *root, t_node *node, \
									int (*cmp)(T_AVL_KEY a, T_AVL_KEY b));
t_node						*avl_find(t_node *root, T_AVL_KEY key, \
									int (*cmp)(T_AVL_KEY a, T_AVL_KEY b));
void						avl_bfs(t_node *root, void (*f)(t_node *node));
void						avl_infix(t_node *root, void (*f)(t_node *node));

#endif
