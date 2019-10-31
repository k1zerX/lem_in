/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 07:59:23 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 08:36:58 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		reset_suffix(t_avl_str *root, t_my_queue *queue)
{
	t_avl_str	*room;
	t_avl_str	*edge_in;

	if (!root)
		return ;
	reset_suffix(root->left, queue);
	reset_suffix(root->right, queue);
	if (root->c.edge.state->is_active)
		return ;
	root->c.edge.state->is_active = 1;
	edge_in = root->c.edge.state->ends[root->c.edge.n];
	room = edge_in->c.edge.room;
	queue_push(queue, room, edge_in);
}

void		reset(t_avl_str *start)
{
	t_my_queue		queue;
	t_qelem			*tmp;

	queue = (t_my_queue){NULL, NULL};
	queue_push(&queue, start, NULL);
	while (queue.start)
	{
		tmp = queue_pop(&queue);
		start = tmp->room;
		start->c.room.is_active = 1;
		ctnr_clear(start->c.room.froms, &del_elem);
		reset_suffix(start->c.room.edges, &queue);
		free(tmp);
	}
}

void		all_abcdefghijk(t_avl_str *edge_out, t_my_queue *queue, \
		t_avl_str *start)
{
	t_avl_str	*room;
	t_avl_str	*edge_in;

	if (!edge_out->c.edge.existance || !edge_out->c.edge.state->is_active || \
			edge_out->c.edge.state->cross == 2)
		return ;
	edge_out->c.edge.state->is_active = 0;
	edge_in = edge_out->c.edge.state->ends[edge_out->c.edge.n];
	room = edge_in->c.edge.room;
	if (!room->c.room.shortest)
		return ;
	if (room->c.room.divided && edge_out == room->c.room.out_exc)
		if (!room->c.room.is_active && ((room->c.room.is_active = 0) || 1))
			return ;
	if (room == start)
		ctnr_push_bot(room->c.room.froms, new_elem(edge_in));
	else if (!room->c.room.froms->top)
		ctnr_push_bot(room->c.room.froms, new_elem(edge_in));
	queue_push(queue, room, edge_in);
}

void		all_not_dijkstra_suffix(t_avl_str *root, t_my_queue *queue, \
		t_avl_str *start)
{
	t_avl_str	*room;

	if (!root)
		return ;
	all_not_dijkstra_suffix(root->left, queue, start);
	all_not_dijkstra_suffix(root->right, queue, start);
	room = root->c.edge.room;
	all_abcdefghijk(root, queue, start);
}

void		all_not_dijkstra_fill(t_avl_str *room, t_avl_str *edge_in, \
		t_my_queue *queue, t_avl_str *start)
{
	t_avl_str	*edge_out;
	t_avl_str	*prev_room;

	if (edge_in != NULL)
	{
		edge_out = edge_in->c.edge.state->ends[edge_in->c.edge.n];
		prev_room = edge_out->c.edge.room;
		if (prev_room->c.room.shortest && room->c.room.divided)
			all_not_dijkstra_suffix(room->c.room.edges, queue, start);
		if (!prev_room->c.room.shortest && room->c.room.divided)
			all_abcdefghijk(room->c.room.in_exc, queue, start);
		if (!room->c.room.shortest)
			all_not_dijkstra_suffix(room->c.room.edges, queue, start);
	}
	else
		all_not_dijkstra_suffix(room->c.room.edges, queue, start);
}
