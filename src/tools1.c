/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 07:59:03 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 08:35:39 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		find_paths_cycle(t_path *tmp, t_avl_str *start)
{
	t_elem		*buf;
	t_avl_str	*node;
	t_avl_str	*edge_out;
	t_avl_str	*edge_in;

	tmp->path = ctnr_new();
	tmp->len = 1;
	ctnr_push_bot(tmp->path, new_elem(start->c.room.edges));
	buf = ctnr_pop_top(start->c.room.froms);
	edge_out = buf->edge;
	edge_in = edge_out->c.edge.state->ends[edge_out->c.edge.n];
	node = edge_in->c.edge.room;
	while (node->c.room.froms->top)
	{
		ctnr_push_bot(tmp->path, new_elem(node->c.room.edges));
		++tmp->len;
		edge_out = node->c.room.froms->top->edge;
		edge_in = edge_out->c.edge.state->ends[edge_out->c.edge.n];
		node = edge_in->c.edge.room;
	}
	ctnr_push_bot(tmp->path, new_elem(node->c.room.edges));
	free(buf);
}

void		find_paths(t_avl_str *start, t_avl_str *end, t_path **sols, int len)
{
	t_path		*tmp;

	if (!(*sols = ft_memalloc((len) * sizeof(t_path))))
		ft_exit();
	tmp = *sols;
	check_shortest(end);
	reset(start);
	all_not_dijkstra(start, end);
	while (len)
	{
		find_paths_cycle(tmp, start);
		++tmp;
		--len;
	}
}

void		add_ant(t_ants *ingame, t_elem *start)
{
	t_ant		*ant;
	static int	i = 1;

	if (!(ant = malloc(sizeof(t_ant))))
		ft_exit();
	ant->next = NULL;
	ant->room = start;
	ant->ind = i;
	++i;
	if (ingame->end)
		ingame->end->next = ant;
	else
		ingame->start = ant;
	ingame->end = ant;
}

void		move_ants_if(t_ant **tmp, t_ant **prev, t_ants *ingame)
{
	if (!(*tmp)->room->next)
	{
		if (*prev)
		{
			(*prev)->next = (*tmp)->next;
			free(*tmp);
			*tmp = (*prev)->next;
		}
		else
		{
			ingame->start = (*tmp)->next;
			free(*tmp);
			(*tmp) = ingame->start;
		}
	}
	else
	{
		*prev = *tmp;
		*tmp = (*prev)->next;
	}
}

void		move_ants(t_ants *ingame)
{
	t_ant	*tmp;
	t_ant	*prev;

	tmp = ingame->start;
	prev = NULL;
	while (tmp->next)
	{
		tmp->room = tmp->room->next;
		ft_printf("L%d-%s ", tmp->ind, tmp->room->edge->c.edge.room->key);
		move_ants_if(&tmp, &prev, ingame);
	}
	tmp->room = tmp->room->next;
	ft_printf("L%d-%s\n", tmp->ind, tmp->room->edge->c.edge.room->key);
}
