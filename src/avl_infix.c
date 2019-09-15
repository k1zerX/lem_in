#include "avl.h"

void	avl_infix(t_node *root, void (*f)(t_node *root))
{
	if (!root)
		return ;
	avl_infix(root->left, f);
	(*f)(root);
	avl_infix(root->right, f);
}
