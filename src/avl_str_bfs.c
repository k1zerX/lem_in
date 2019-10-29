/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_str_bfs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:49:45 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/29 19:04:52 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"
#include "libft.h"

void	avl_str_bfs(t_avl_str *root, void (*f)(t_avl_str *node))
{
	t_queue		*queue;
	t_sq_elem	*tmp;

	queue = ft_queue_new();
	ft_queue_push(queue, ft_new_sq_elem(root, sizeof(t_avl_str), 0));
	while (queue->len)
	{
		tmp = ft_queue_pop(queue);
		root = (t_avl_str *)tmp->content;
		if (root->left)
			ft_queue_push(queue, ft_new_sq_elem(root->left, sizeof(t_avl_str), 0));
		if (root->right)
			ft_queue_push(queue, ft_new_sq_elem(root->right, sizeof(t_avl_str), 0));
		(*f)(root);
		free(tmp);
	}
}
