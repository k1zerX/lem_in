/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 07:59:29 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 08:07:32 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		del_avl_str(t_avl_str *node)
{
	free(node->key);
	free(node);
}

t_elem		*new_elem(t_avl_str *edge)
{
	t_elem	*tmp;

	if ((tmp = malloc(sizeof(t_elem))))
	{
		tmp->edge = edge;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	return (tmp);
}

void		del_elem(t_elem *elem)
{
	free(elem);
}

void		queue_push(t_my_queue *queue, t_avl_str *room, t_avl_str *edge_in)
{
	t_qelem		*tmp;

	if (!(tmp = malloc(sizeof(t_qelem))))
		ft_exit();
	tmp->next = NULL;
	tmp->room = room;
	tmp->edge_in = edge_in;
	if (queue->end)
		queue->end->next = tmp;
	else
		queue->start = tmp;
	queue->end = tmp;
}

t_qelem		*queue_pop(t_my_queue *queue)
{
	t_qelem		*tmp;

	if (queue->start == NULL)
		return (NULL);
	tmp = queue->start;
	queue->start = tmp->next;
	if (queue->start == NULL)
		queue->end = NULL;
	tmp->next = NULL;
	return (tmp);
}
