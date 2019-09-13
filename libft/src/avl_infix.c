#include "libft.h"

void	avl_infix(t_avl_node *node, void (*f)(t_avl_node *node))
{
	if (!node)
		return ;
	avl_infix(node->left, f);
	(*f)(node);
	avl_infix(node->right, f);
}
