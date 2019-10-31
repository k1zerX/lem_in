/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:44:38 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 07:18:27 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"
#include "avl.h"
#include "libft.h"
#include "types.h"
#include "lem_in.h"
#include "read.h"

void		ft_exit(void)
{
	write(1, "Error\n", 6);
	exit(1);
}

t_avl_str		*new_avl_str(char *key, t_content c)
{
	t_avl_str	*tmp;

	if (!(tmp = malloc(sizeof(t_avl_str))))
		ft_exit();
	tmp->key = key;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->c = c;
	return (tmp);
}

t_content	new_room(void)
{
	t_content	c;

	c.room.edges = NULL;
	c.room.froms = ctnr_new();
	c.room.out_exc = NULL;
	c.room.in_exc = NULL;
	c.room.divided = 0;
	c.room.shortest = 0;
	c.room.is_active = 1;
	return (c);
}

t_state		*new_state(void)
{
	t_state		*state;

	if (!(state = malloc(sizeof(t_state))))
		ft_exit();
	state->weight = 1;
	state->is_active = 1;
	state->cross = 0;
	return (state);
}

t_content	new_edge(t_avl_str *room, t_state *state, unsigned char n)
{
	t_content	c;

	c.edge.room = room;
	c.edge.state = state;
	c.edge.existance = 1;
	c.edge.n = n;
	return (c);
}

void		del_avl_str(t_avl_str *node)
{
	free(node->key);
	free(node);
}

t_elem	*new_elem(t_avl_str *edge)
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
		t_avl_str *start, int *len)
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
	{
		if (*len)
		{
			ctnr_push_bot(room->c.room.froms, new_elem(edge_in));
			--*len;
		}
	}
	else if (!room->c.room.froms->top)
		ctnr_push_bot(room->c.room.froms, new_elem(edge_in));
	queue_push(queue, room, edge_in);
}

void		all_not_dijkstra_suffix(t_avl_str *root, t_my_queue *queue, \
		t_avl_str *start, int *len, char flag)
{
	t_avl_str	*room;

	if (!root)
		return ;
	all_not_dijkstra_suffix(root->left, queue, start, len, flag);
	all_not_dijkstra_suffix(root->right, queue, start, len, flag);
	room = root->c.edge.room;
	if (flag && room->c.room.in_exc == root)
		return ;
	all_abcdefghijk(root, queue, start, len);
}

void	all_not_dijkstra_fill(t_avl_str *room, t_avl_str *edge_in, \
		t_my_queue *queue, t_avl_str *start, int *len)
{
	t_avl_str	*edge_out;
	t_avl_str	*prev_room;

	if (edge_in != NULL)
	{
		edge_out = edge_in->c.edge.state->ends[edge_in->c.edge.n];
		prev_room = edge_out->c.edge.room;
		if (prev_room->c.room.shortest && room->c.room.divided)
			all_not_dijkstra_suffix(room->c.room.edges, queue, start, len, 0);
		if (!prev_room->c.room.shortest && room->c.room.divided)
			all_abcdefghijk(room->c.room.in_exc, queue, start, len);
		if (!room->c.room.shortest)
			all_not_dijkstra_suffix(room->c.room.edges, queue, start, len, 0);
	}
	else
		all_not_dijkstra_suffix(room->c.room.edges, queue, start, len, 0);
}

void	all_not_dijkstra(t_avl_str *start, t_avl_str *end, int len)
{
	t_my_queue		queue;
	t_qelem		*tmp;

	queue = (t_my_queue){NULL, NULL};
	queue_push(&queue, end, NULL);
	while (queue.start)
	{
		tmp = queue_pop(&queue);
		all_not_dijkstra_fill(tmp->room, tmp->edge_in, &queue, start, &len);
		end = tmp->room;
		free(tmp);
	}
}

void		abcdefghijk(t_avl_str *edge_out, t_my_queue *queue)
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

void		not_dijkstra_suffix(t_avl_str *root, t_my_queue *queue, char flag)
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
	static int i = 0;

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
		room->c.room.in_exc = edge_out; //
		room->c.room.out_exc = edge_in; //
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

void		find_paths(t_avl_str *start, t_avl_str *end, t_path **sols, int len)
{
	t_path		*tmp;
	t_elem		*buf;
	t_avl_str	*node;
	t_avl_str	*edge_out;
	t_avl_str	*edge_in;

	if (!(*sols = ft_memalloc((len) * sizeof(t_path))))
		ft_exit();
	tmp = *sols;
	check_shortest(end);
	reset(start);
	all_not_dijkstra(start, end, len);
	while (len)
	{
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

void		move_ants(t_ants *ingame)
{
	t_ant	*tmp;
	t_ant	*prev;

	tmp = ingame->start;
	prev = NULL;
	while (tmp->next)
	{
		tmp->room = tmp->room->next;
		printf("L%d-%s ", tmp->ind, tmp->room->edge->c.edge.room->key);
		if (!tmp->room->next)
		{
			if (prev)
			{
				prev->next = tmp->next;
				free(tmp);
				tmp = prev->next;
			}
			else
			{
				ingame->start = tmp->next;
				free(tmp);
				tmp = ingame->start;
			}
		}
		else
		{
			prev = tmp;
			tmp = prev->next;
		}
	}
	tmp->room = tmp->room->next;
	printf("L%d-%s\n", tmp->ind, tmp->room->edge->c.edge.room->key);
}

void		print_ants(t_path **sols, int min, int ind)
{
	int		i;
	int		j;
	t_ants	ingame;

	printf("\n");
	ingame = (t_ants){NULL, NULL};
	i = 0;
	while (i < min)
	{
		j = 0;
		while (j < ind)
		{
			if ((*sols)[j].ants > 0)
			{
				add_ant(&ingame, (*sols)[j].path->top);
				--(*sols)[j].ants;
			}
			++j;
		}
		move_ants(&ingame);
		++i;
	}
}

void		count_ants2(t_path *paths, int n, int j)
{
	int		buf;
	int		div;
	int		mod;

	div = n / j;
	mod = n % j;
	--paths;
	--j;
	buf = 0;
	while (j >= mod)
	{
		paths->ants += buf;
		buf = paths->ants;
		paths->ants += div;
		--j;
		--paths;
	}
	while (j >= 0)
	{
		paths->ants += buf;
		buf = paths->ants;
		paths->ants += div + 1;
		--j;
		--paths;
	}
}

void		count_ants(t_path *paths, int n, int i)
{
	int		div;
	int		mod;
	int		j;

	paths[-1].ants = 0;
	j = 1;
	while (j < i)
	{
		paths[-1].ants = paths->len - paths[-1].len;
		n -= paths[-1].ants * j;
		div = n / j;
		mod = n % j;
		if (n <= 0 || div == 0 || (div == 1 && mod == 0))
		{
			n += paths[-1].ants * j;
			break ;
		}
		++paths;
		++j;
	}
	paths[-1].ants = 0;
	count_ants2(paths, n, j);
}

int			main_cycle(t_path **sols, t_min *min, t_read *terminates)
{
	int		i;

	i = 1;
	while (i <= terminates->max_paths)
	{
		ctnr_push_top(terminates->start->c.room.froms, new_elem(NULL));
		not_dijkstra(terminates->start);
		free(ctnr_pop_top(terminates->start->c.room.froms));
		if (terminates->end->c.room.froms->top == NULL)
			break ;
		path_invert(terminates->end);
		find_paths(terminates->start, terminates->end, sols, i);
		count_ants(*sols + 1, terminates->ants, i);
		if ((*sols)->ants + (*sols)->len - 1 < min->min || min->min == -1)
			*min = (t_min){(*sols)->ants + (*sols)->len - 1, i};
		reset(terminates->start);
		++sols;
		++i;
	}
	return (i);
}

int			main(int ac, char *av[])
{
	int		i;
	t_path	**sols;
	t_min	min;
	t_read		terminates;
	t_str_list	*str_list;
	
	terminates = (t_read){NULL, NULL, NULL, 0, 0};
	str_list = is_valid_map(&terminates);
	print_map(str_list->start);
	if (!(sols = ft_memalloc(terminates.max_paths * sizeof(t_path *))))
		ft_exit();
	min.min = -1;
	i = main_cycle(sols, &min, &terminates);
	if (min.min == -1)
		ft_exit();
	print_ants(sols + min.ind - 1, min.min, min.ind);
	free_str_list(str_list);
	smart_free(terminates.start);
	del_sols(sols, i);
	return (0);
}
