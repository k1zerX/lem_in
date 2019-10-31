/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 07:59:15 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 08:00:37 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		edge_reverse(t_avl_str *edge)
{
	edge->c.edge.state->weight *= -1;
	++edge->c.edge.state->cross;
	edge->c.edge.existance = 1;
	edge->c.edge.state->ends[edge->c.edge.n]->c.edge.existance = 0;
}

void		path_invert_rec(t_avl_str *node)
{
	t_elem		*next;
	t_avl_str	*edge;

	next = node->c.room.froms->top;
	if (!next)
		return ;
	edge = next->edge;
	edge_reverse(edge);
	path_invert_rec(\
		edge->c.edge.state->ends[edge->c.edge.n]->c.edge.room);
}

void		path_invert(t_avl_str *end)
{
	t_avl_str	*tmp;
	t_avl_str	*edge;

	edge = end->c.room.froms->top->edge;
	tmp = edge->c.edge.state->ends[edge->c.edge.n]->c.edge.room;
	if (!tmp)
		return ;
	edge_reverse(edge);
	path_invert_rec(tmp);
}

void		check_shortest_rec(t_avl_str *edge_out)
{
	t_avl_str	*edge_in;
	t_elem		*tmp;
	t_avl_str	*room;

	edge_in = edge_out->c.edge.state->ends[edge_out->c.edge.n];
	room = edge_in->c.edge.room;
	tmp = room->c.room.froms->top;
	room->c.room.shortest = 1;
	if (tmp)
	{
		edge_out = room->c.room.froms->top->edge;
		room->c.room.divided = 1;
		room->c.room.in_exc = edge_out;
		room->c.room.out_exc = edge_in;
		check_shortest_rec(edge_out);
	}
}

void		check_shortest(t_avl_str *end)
{
	t_avl_str	*edge;
	t_elem		*tmp;

	tmp = end->c.room.froms->top;
	end->c.room.shortest = 1;
	if (tmp)
	{
		edge = end->c.room.froms->top->edge;
		check_shortest_rec(edge);
	}
}
