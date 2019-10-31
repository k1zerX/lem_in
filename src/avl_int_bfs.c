/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_int_bfs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:49:45 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/31 07:33:43 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"
#include "libft.h"

void	avl_int_bfs(t_avl_int *root, void (*f)(t_avl_int *node))
{
	t_queue		*queue;
	t_sq_elem	*tmp;

	queue = ft_queue_new();
	ft_queue_push(queue, ft_new_sq_elem(root, sizeof(t_avl_int), 0));
	while (queue->len)
	{
		tmp = ft_queue_pop(queue);
		root = (t_avl_int *)tmp->content;
		if (root->left)
			ft_queue_push(queue, ft_new_sq_elem(root->left, \
				sizeof(t_avl_int), 0));
		if (root->right)
			ft_queue_push(queue, ft_new_sq_elem(root->right, \
				sizeof(t_avl_int), 0));
		(*f)(root);
		free(tmp);
	}
}
