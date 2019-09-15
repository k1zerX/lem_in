#include "avl.h"
#include "libft.h"

void	avl_bfs(t_node *root, void (*f)(t_node *node))
{
	t_queue		*queue;
	t_sq_elem	*tmp;

	queue = ft_queue_new();
	ft_queue_push(queue, ft_new_sq_elem(root, sizeof(t_node), 0));
	while (queue->len)
	{
		tmp = ft_queue_pop(queue);
		root = (t_node *)tmp->content;
		if (root->left)
			ft_queue_push(queue, ft_new_sq_elem(root->left, sizeof(t_node), 0));
		if (root->right)
			ft_queue_push(queue, ft_new_sq_elem(root->right, sizeof(t_node), 0));
		(*f)(root);
		free(tmp);
	}
}
