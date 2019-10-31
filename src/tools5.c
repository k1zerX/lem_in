/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 07:59:27 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 08:01:27 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		del_list(t_state_list *list)
{
	t_list_elem		*tmp;
	t_list_elem		*next;

	tmp = list->start;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->state);
		free(tmp);
		tmp = next;
	}
}

void		list_add(t_state_list *list, t_state *state)
{
	t_list_elem		*tmp;

	if (!(tmp = malloc(sizeof(t_qelem))))
		ft_exit();
	tmp->next = NULL;
	tmp->state = state;
	if (list->end)
		list->end->next = tmp;
	else
		list->start = tmp;
	list->end = tmp;
}

void		smart_free_rec(t_avl_str *root, t_my_queue *q, t_state_list *l)
{
	t_avl_str	*edge_in;
	t_avl_str	*room;

	if (!root)
		return ;
	smart_free_rec(root->left, q, l);
	smart_free_rec(root->right, q, l);
	if (!root->c.edge.state->is_active)
	{
		free(root);
		return ;
	}
	root->c.edge.state->is_active = 0;
	list_add(l, root->c.edge.state);
	edge_in = root->c.edge.state->ends[root->c.edge.n];
	room = edge_in->c.edge.room;
	queue_push(q, room, edge_in);
	free(root);
}

void		smart_free(t_avl_str *room)
{
	t_my_queue		q;
	t_state_list	l;
	t_qelem			*tmp;

	l = (t_state_list){NULL, NULL};
	q = (t_my_queue){NULL, NULL};
	queue_push(&q, room, NULL);
	while (q.start)
	{
		tmp = queue_pop(&q);
		smart_free_rec(tmp->room->c.room.edges, &q, &l);
		ctnr_clear(tmp->room->c.room.froms, &del_elem);
		free(tmp->room->key);
		free(tmp->room->c.room.froms);
		free(tmp->room);
		free(tmp);
	}
	del_list(&l);
}

void		del_sols(t_path **sols, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		ctnr_clear(sols[i]->path, &del_elem);
		free(sols[i]->path);
		free(sols[i]);
		++i;
	}
	free(sols);
}
