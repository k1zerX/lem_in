#include "avl.h"

static t_node	*findmin(t_node *node)
{
	return ((node->left) ? (findmin(node->left)) : (node));
}

static t_node	*removemin(t_node *node)
{
	if (!node->left)
		return (node->right);
	node->left = removemin(node->left);
	return (avl_balance(node));
}

t_node	*avl_remove(t_node *root, T_AVL_KEY key, \
		int (*cmp)(T_AVL_KEY a, T_AVL_KEY b))
{
	int		buf;
	t_node	*l;
	t_node	*r;
	t_node	*min;

	if (!root)
		return (NULL);
	if ((buf = (*cmp)(key, root->AVL_KEY)) < 0)
		root->left = avl_remove(root->left, key, cmp);
	else if (buf > 0)
		root->right = avl_remove(root->right, key, cmp);
	else
	{
		l = root->left;
		r = root->right;
		free(root);
		if (!r)
			return (l);
		min = findmin(r);
		min->right = removemin(r);
		min->left = l;
		return (avl_balance(min));
	}
	return (avl_balance(root));
}
