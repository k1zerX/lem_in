/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_bfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 23:19:49 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/25 23:20:01 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	avl_bfs(t_avl_node *node, void (*f)(t_avl_node *node))
{
	t_queue		*queue;
	t_elem		*tmp;

	queue = ft_queue_new();
	ft_queue_push(queue, ft_new_elem(node, sizeof(t_avl_node), 0));
	while (queue->len)
	{
		tmp = ft_queue_pop(queue);
		node = (t_avl_node *)tmp->content;
		if (node->left)
			ft_queue_push(queue, ft_new_elem(node->left, \
						sizeof(t_avl_node), 0));
		if (node->right)
			ft_queue_push(queue, ft_new_elem(node->right, \
						sizeof(t_avl_node), 0));
		(*f)(node);
		free(tmp);
	}
}
