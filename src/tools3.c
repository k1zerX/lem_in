/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 07:59:19 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 08:36:31 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	all_not_dijkstra(t_avl_str *start, t_avl_str *end)
{
	t_my_queue		queue;
	t_qelem			*tmp;

	queue = (t_my_queue){NULL, NULL};
	queue_push(&queue, end, NULL);
	while (queue.start)
	{
		tmp = queue_pop(&queue);
		all_not_dijkstra_fill(tmp->room, tmp->edge_in, &queue, start);
		end = tmp->room;
		free(tmp);
	}
}

void	abcdefghijk(t_avl_str *edge_out, t_my_queue *queue)
{
	t_avl_str	*room;
	t_avl_str	*edge_in;
	int			buf;

	if (!edge_out->c.edge.existance || !edge_out->c.edge.state->is_active \
			|| edge_out->c.edge.state->cross == 2)
		return ;
	edge_out->c.edge.state->is_active = 0;
	edge_in = edge_out->c.edge.state->ends[edge_out->c.edge.n];
	room = edge_in->c.edge.room;
	if (room->c.room.divided && edge_out == room->c.room.out_exc)
		if (!room->c.room.is_active && ((room->c.room.is_active = 0) || 1))
			return ;
	buf = edge_out->c.edge.room->c.room.distance + \
			edge_out->c.edge.state->weight;
	if (room->c.room.froms->top)
	{
		if (room->c.room.distance > buf)
			ctnr_clear(room->c.room.froms, &del_elem);
		else
			return ;
	}
	room->c.room.distance = buf;
	ctnr_push_bot(room->c.room.froms, new_elem(edge_in));
	queue_push(queue, room, edge_in);
}

void	not_dijkstra_suffix(t_avl_str *root, t_my_queue *queue, char flag)
{
	t_avl_str	*room;

	if (!root)
		return ;
	not_dijkstra_suffix(root->left, queue, flag);
	not_dijkstra_suffix(root->right, queue, flag);
	room = root->c.edge.room;
	if (flag && room->c.room.in_exc == root)
		return ;
	abcdefghijk(root, queue);
}

void	not_dijkstra_fill(t_avl_str *room, t_avl_str *edge_in, \
		t_my_queue *queue)
{
	t_avl_str	*edge_out;
	t_avl_str	*prev_room;

	if (edge_in != NULL)
	{
		edge_out = edge_in->c.edge.state->ends[edge_in->c.edge.n];
		prev_room = edge_out->c.edge.room;
		if (prev_room->c.room.shortest && room->c.room.divided)
			not_dijkstra_suffix(room->c.room.edges, queue, 0);
		if (!prev_room->c.room.shortest && room->c.room.divided)
			abcdefghijk(room->c.room.in_exc, queue);
		if (!room->c.room.shortest)
			not_dijkstra_suffix(room->c.room.edges, queue, 0);
	}
	else
		not_dijkstra_suffix(room->c.room.edges, queue, 0);
}

void	not_dijkstra(t_avl_str *start)
{
	t_my_queue		queue;
	t_qelem			*tmp;

	start->c.room.distance = 0;
	queue = (t_my_queue){NULL, NULL};
	queue_push(&queue, start, NULL);
	while (queue.start)
	{
		tmp = queue_pop(&queue);
		not_dijkstra_fill(tmp->room, tmp->edge_in, &queue);
		start = tmp->room;
		free(tmp);
	}
}
