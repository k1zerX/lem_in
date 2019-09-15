#include "avl.h"

t_node	*avl_find(t_node *root, T_AVL_KEY key, \
				int (*cmp)(T_AVL_KEY a, T_AVL_KEY b))
{
	int			buf;

	while (root)
		if ((buf = (*cmp)(root->AVL_KEY, key)) < 0)
			root = root->left;
		else if (buf > 0)
			root = root->right;
		else
			break ;
	return (root);
}
