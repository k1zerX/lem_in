/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:44:38 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/30 22:17:17 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"
#include "avl.h"
#include "libft.h"
#include "types.h"
#include "lem_in.h"

#include <stdio.h>
/*
enum e_err = 
{
	READ_ERR,
	MALLOC_ERR,
	VALID_ERR,
	LEN
};

char	*g_str_err[LEN] = 
{
	[READ_ERR] = "read error\n",
	[MALLOC_ERR] = "cant allocate\n",
	[VALID_ERR] = "fuck\n",
};
*/

void		ft_exit(void)
{
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

void		print_edge(t_avl_str *node)
{
	printf("\t%s\n", node->key);
}

void		print_room(t_avl_str *node)
{
	printf("%s to:\n", node->key);
	avl_str_infix(node->c.room.edges, &print_edge);
	printf("\n");
}

void		print_avl_str(t_avl_str *node)
{
	printf("%s\n", node->key);
}

void		del_avl_str(t_avl_str *node)
{
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
	t_qelem		*tmp;

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

void		all_abcdefghijk(t_avl_str *edge_out, t_my_queue *queue, t_avl_str *start, int *len)
{
	t_avl_str	*room;
	t_avl_str	*edge_in;

	if (!edge_out->c.edge.existance || !edge_out->c.edge.state->is_active || edge_out->c.edge.state->cross == 2)
		return ;
	edge_out->c.edge.state->is_active = 0;
	edge_in = edge_out->c.edge.state->ends[edge_out->c.edge.n];
	room = edge_in->c.edge.room;
	if (!room->c.room.shortest)
		return ;
	if (room->c.room.divided && edge_out == room->c.room.out_exc)
	{
		if (!room->c.room.is_active)
			return ;
		room->c.room.is_active = 0;
	}
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

void		all_not_dijkstra_suffix(t_avl_str *root, t_my_queue *queue, t_avl_str *start, int *len, char flag)
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

void	all_not_dijkstra_fill(t_avl_str *room, t_avl_str *edge_in, t_my_queue *queue, t_avl_str *start, int *len)
{
	t_avl_str	*edge_out;
	t_avl_str	*prev_room;

	if (edge_in != NULL)
	{
//		if (ft_strequ("10", room->key))
		edge_out = edge_in->c.edge.state->ends[edge_in->c.edge.n];
		prev_room = edge_out->c.edge.room;
			printf(">>>%d %d\n", prev_room->c.room.shortest, room->c.room.divided);
		if (prev_room->c.room.shortest && room->c.room.divided) // from in to out
		{
			printf("gg\n");
			all_not_dijkstra_suffix(room->c.room.edges, queue, start, len, 0);
//			all_abcdefghijk(room->c.room.in_exc, queue, start, len);
			printf("ok\n");
		}
		if (!prev_room->c.room.shortest && room->c.room.divided) // from other to in
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

//	printf("distance from start:\n");
	queue = (t_my_queue){NULL, NULL};
	queue_push(&queue, end, NULL);
	while (queue.start)
	{
		tmp = queue_pop(&queue);
		all_not_dijkstra_fill(tmp->room, tmp->edge_in, &queue, start, &len);
		end = tmp->room;
		printf("\t%3s, %d:\n", end->key, end->c.room.divided);
		free(tmp);
	}
}

void		abcdefghijk(t_avl_str *edge_out, t_my_queue *queue)
{
	t_avl_str	*room;
	t_avl_str	*edge_in;
	int			buf;

	if (!edge_out->c.edge.existance || !edge_out->c.edge.state->is_active || edge_out->c.edge.state->cross == 2)
		return ;
	edge_out->c.edge.state->is_active = 0;
	edge_in = edge_out->c.edge.state->ends[edge_out->c.edge.n];
	room = edge_in->c.edge.room;
	if (room->c.room.divided && edge_out == room->c.room.out_exc)
	{
		if (!room->c.room.is_active)
			return ;
		room->c.room.is_active = 0;
	}
	buf = edge_out->c.edge.room->c.room.distance + edge_out->c.edge.state->weight;
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

void	not_dijkstra_fill(t_avl_str *room, t_avl_str *edge_in, t_my_queue *queue)
{
	t_avl_str	*edge_out;
	t_avl_str	*prev_room;

	if (edge_in != NULL)
	{
		edge_out = edge_in->c.edge.state->ends[edge_in->c.edge.n];
		prev_room = edge_out->c.edge.room;
//		printf("\t\tbefore: %p, %d %d\n", room->c.room.in_exc, prev_room->c.room.shortest, room->c.room.shortest);
		if (prev_room->c.room.shortest && room->c.room.divided) // from in to out
		{
			not_dijkstra_suffix(room->c.room.edges, queue, 0); // except in_exc
//			abcdefghijk(room->c.room.in_exc, queue);
		}
		if (!prev_room->c.room.shortest && room->c.room.divided) // from other to in
			abcdefghijk(room->c.room.in_exc, queue);
		if (!room->c.room.shortest)
			not_dijkstra_suffix(room->c.room.edges, queue, 0);
//		printf("\t\tafter:\n");
	}
	else
		not_dijkstra_suffix(room->c.room.edges, queue, 0);
}

void	not_dijkstra(t_avl_str *start)
{
	t_my_queue		queue;
	t_qelem			*tmp;
	static int i = 0;

//	printf("distance from start:\n");
	start->c.room.distance = 0;
	queue = (t_my_queue){NULL, NULL};
	queue_push(&queue, start, NULL);
	while (queue.start)
	{
		tmp = queue_pop(&queue);
//		printf("\tbefore: %s\n", tmp->room->key);
//		if (start->c.room.divided)
//			abcdefghijk(start->c.room.in_exc, queue);
//		else
		not_dijkstra_fill(tmp->room, tmp->edge_in, &queue);
		start = tmp->room;
		printf("\t%3s, %d: %d\n", start->key, start->c.room.divided, start->c.room.distance);
		free(tmp);
//		printf("\tafter:\n");
	}
}

void		print_path(t_path path)
{
	t_elem		*tmp;
	t_avl_str	*room;
	t_avl_str	*left;
	t_avl_str	*right;

	tmp = path.path->top;
	if (tmp)
	{
		printf("\t%d to %d: ", path.ants, path.len);
			printf("%s -> ", tmp->edge->c.edge.room->key);
		tmp = tmp->next;
		while (tmp->next)
		{
			room = tmp->edge->c.edge.room;
			left = room->c.room.in_exc;
			left = left->c.edge.state->ends[left->c.edge.n];
			right = room->c.room.out_exc;
			right = right->c.edge.state->ends[right->c.edge.n];
//			printf("(%s<-%s->%s) ==> ", left->c.edge.room->key , room->key, right->c.edge.room->key);
			printf("%s -> ", room->key);
			tmp = tmp->next;
		}
		printf("%s\n", tmp->edge->c.edge.room->key);
	}
}

void		print_paths(t_avl_str *start, t_path *paths, int len)
{
	(void)start;
	while (len)
	{
		print_path(*paths);
		++paths;
		--len;
	}
}

void		edge_reverse(t_avl_str *edge)
{
//	printf("\t\tbefore:\n");
//	edge = avl_str_find(node->c.room.edges, prev->key, &ft_strcmp);
	edge->c.edge.state->weight *= -1;
	++edge->c.edge.state->cross;
	edge->c.edge.existance = 1;
	edge->c.edge.state->ends[edge->c.edge.n]->c.edge.existance = 0;
//	printf("\t\tafter:\n");
}

void		path_invert_rec(t_avl_str *node)
{
	t_elem		*next;
	t_avl_str	*edge;

/*	printf("%s\n", node->key);
	printf("\t%p\n", node);
	printf("\t%p\n", node->c.room.froms);
	printf("\t%p\n", node->c.room.froms->top);
	printf("\t%p\n", node->c.room.froms->top->node);*/
	next = node->c.room.froms->top;
	printf(" %s", node->key);
	if (!next)
		return ;
//	printf("%s\n", node->key);
	edge = next->edge;
//	out = new_avl_str(av[i], new_room());
//	out->c.room.edges = node->c.room.edges;
//	node->c.room.edges = NULL;
	edge_reverse(edge);
	path_invert_rec(\
		edge->c.edge.state->ends[edge->c.edge.n]->c.edge.room);
}

void		path_invert(t_avl_str *end)
{
	t_avl_str	*tmp;
	t_avl_str	*edge;

	printf("path invert:");
	edge = end->c.room.froms->top->edge;
	tmp = edge->c.edge.state->ends[edge->c.edge.n]->c.edge.room;
	if (!tmp)
		return ;
//	printf("\tbefore:\n");
	edge_reverse(edge);
	printf(" %s", end->key);
	path_invert_rec(tmp);
	printf("\n");
//	printf("\tafter:\n");
}
/*
void		path_invert_rec(t_avl_str *node, t_avl_str *from) seychas eto recursiya no luchshe sdelat' ochered' \
															to est' obhod v shirinu vmesto obhoda v glubinu 
{
	t_elem	*tmp;
	t_avl_str	*buf;
	t_avl_str	*out;

	if (!node)
		return ;
	node->c.room.edges = avl_str_remove(node->c.room.edges, from->key, &ft_strcmp);
	tmp = node->c.room.froms->top;
//	printf("\t%p\n", tmp);
	while (tmp)
	{
		path_invert_rec(tmp->node, node);
		buf = avl_str_find(node->c.room.edges, tmp->node->key, &ft_strcmp);
		buf->c.edge.weight *= -1;
		tmp = tmp->next;
	}
	if (node->c.room.froms->top)
	{
		out = new_avl_str(ft_strjoin(node->key, "-out"), new_room());
		ft_swap(&node->c.room.edges, &out->c.room.edges, sizeof(node->c.room.edges));
		buf = new_avl_str(node->key, new_edge(node));
		buf->c.edge.weight = 0;
		out->c.room.edges = avl_str_insert(out->c.room.edges, buf, &ft_strcmp);
		print_room(out);
		from->c.room.edges = avl_str_remove(from->c.room.edges, node->key, &ft_strcmp)
		buf = new_avl_str(out->key, new_edge(out));
		buf->c.edge.weight *= -1;
		from->c.room.edges = avl_str_insert(from->c.room.edges, buf, &ft_strcmp);
		// dodelat', peredelat
seychas posle razbiyeniya in ukazyvaet na out, a dolzhno byt' naoborot.
	}
}*/
/*
void		path_invert(t_avl_str *end)
{
	t_elem	*tmp;
	t_avl_str	*buf;

	tmp = end->c.room.froms->top;
	while (tmp)
	{
		path_invert_rec(tmp->node, end);
//		buf = avl_str_find(end->c.room.edges, tmp->node->key, &ft_strcmp);
		buf = new_avl_str(tmp->node->key, new_edge(tmp->node));
		end->c.room.edges = avl_str_insert(end->c.room.edges, buf, &ft_strcmp);
		buf->c.edge.weight *= -1;
		tmp = tmp->next;
	}
}*/
/*
t_avl_str		*fill_start(void)
{
	
}

t_avl_str		*fill_end(void)
{
}

char		smart_split(char *str, char ***arr)
{
	char	*start;
	int		length;
	char	res;

	res = 0;
	start = str;
	while (*str)
	{
		
		++str;
	}
	while (!ft_issapce(*str) && !(*str == '-'))
	{
	}
	return (res);
}

t_avl_str		*init(int *ants)
{
	char	*str;
	int		n;
	char	**arr;

	if ((n = gnl(0, &str) < 0))
		ft_exit();
	ants = atoi(str);
	free(str);
	flag = 0;
	while ((n = gnl(0, &str)) > 0)
	{
		if (*str == '#')
		{
			if (ft_strequ(str, "##start")
				start = fill_start();
			else if (ft_strequ(str, "##end")
				end = fill_end();
		}
		else
		{
			if (smart_split(str, &arr))
			{
			}
		}
		free(str);
	}
	if (n < 0)
		ft_exit();
}

int			main(void)
{
	t_avl_str	*root;
	int		ants;

	root = init(&ants);
}
*/
/*
void		fill_queue(t_avl_str *edge_out, t_my_queue *q)
{
	t_avl_str	*prev_room;
	t_avl_str	*room;
	t_avl_str	*edge_in;

	if (!edge_out)
		return ;
	fill_queue(edge_out->left, q);
	fill_queue(edge_out->right, q);
	prev_room = edge_out->c.edge.room;
	if (prev_room->c.room.divided && )
		if (roo
	edge_in = edge_out->c.edge.state->ends[edge_out->c.edge.n];
	room = edge_in->c.edge.room;
	if (!edge_out->c.edge.existance || !edge_out->c.edge.state->is_active || edge_out->c.edge.state->cross == 2)
		return ;
	queue_push(room, edge_in);
}

void		great_func(t_avl_str *start)
{
	t_my_queue		q;
	t_qelem		*tmp;
	t_avl_str	*edge_in;

	q = (t_my_queue){NULL, NULL};
	start->c.room.distance = 0;
	queue_push(&q, start, NULL);
	while (q.start)
	{
		tmp = queue_pop(&q);
		start = tmp->room;
		if (start->c.room.divided)
		{
			if (start->c.room.out_exc == edge_in) // out
			{
				fill_queue(start->c.room.edges);
			}
			else // in
			{
				t_avl_str *room;
				t_avl_str *edge_out;
				edge_out = start->in_exc;
				edge_in = edge_out->c.edge.state->ends[edge_out->c.edge.n];
				room = edge_in->c.edge.room;
				queue_push(&q, room, edge_in);
			}
		}
		else
			fill_queue(start->c.room.edges, &q);
		free(tmp);
	}
}
*/
void		check_shortest_rec(t_avl_str *room)
{
	t_avl_str	*next;
	t_avl_str	*edge;
	t_elem		*tmp;
	
	tmp = room->c.room.froms->top;
	room->c.room.shortest = 1;
	if (tmp)
	{
		room->c.room.divided = 1;
		edge = room->c.room.froms->top->edge;
		next = edge->c.edge.state->ends[edge->c.edge.n]->c.edge.room;
		check_shortest_rec(next);
	}
}

void		check_shortest(t_avl_str *end)
{
	t_avl_str	*next;
	t_avl_str	*edge;
	t_elem		*tmp;

	printf(" %s", end->key);
	tmp = end->c.room.froms->top;
	end->c.room.shortest = 1;
	if (tmp)
	{
		edge = end->c.room.froms->top->edge;
		next = edge->c.edge.state->ends[edge->c.edge.n]->c.edge.room;
		check_shortest_rec(next);
	}
}

void		find_paths(t_avl_str *start, t_avl_str *end, t_path **sols, int len)
{
	t_path		*tmp;
	t_elem		*buf;
	t_avl_str	*node;
	t_avl_str	*edge_out;
	t_avl_str	*edge_in;

	if (!(*sols = malloc((len) * sizeof(t_path))))
		ft_exit();
	tmp = *sols;
	printf("shortest path: ");
	check_shortest(end);
	reset(start);
	printf("\n");
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
//	printf("\tbefore: %s\n", node->key);
			ctnr_push_bot(tmp->path, new_elem(node->c.room.edges));
			++tmp->len;
			edge_out = node->c.room.froms->top->edge;
			node->c.room.divided = 1;
			printf("||| %s, %d\n", node->key, node->c.room.divided);
//
			node->c.room.in_exc = edge_in; //
			node->c.room.out_exc = edge_out; //
//
			edge_in = edge_out->c.edge.state->ends[edge_out->c.edge.n];
			node = edge_in->c.edge.room;
//	printf("\tafter:\n");
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
	while (tmp)
	{
//		printf("before:\n");
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
//		printf("after:\n");
	}
	printf("\n");
}

int			main(int ac, char *av[])
{
	t_avl_str	*root;
	int		i;
	int		j;
	char	**arr;
	t_avl_str	*tmp;
	t_avl_str	*tmp1;
	t_avl_str	*tmp2;
	t_avl_str	*start;
	t_avl_str	*end;
	int		n;
	int		ants;
	int		max_paths;
	int		s_n;
	int		e_n;
	t_state *state;
	t_edge	*edge;
	t_path	**sols;
	t_path	*paths;
	int		div;
	int		mod;
	int		min;
	int		ind;
	t_ants	ingame;

	if (ac > 1)
		ants = ft_atoi(av[1]);
	i = 2;
	start = NULL;
	end = NULL;
	root = NULL;
	while (i < ac && *av[i] != ';')
	{
		if (*av[i] == '#')
		{
			++i;
			continue ;
		}
		tmp = new_avl_str(av[i], new_room());
		if (ft_strequ(av[i - 1], "##start"))
			start = tmp;
		if (ft_strequ(av[i - 1], "##end"))
			end = tmp;
		root = avl_str_insert(root, tmp, &ft_strcmp);
		++i;
	}
	++i;
	s_n = 0;
	e_n = 0;
	while (i < ac)
	{
		arr = ft_strsplit(av[i], '-');
		if (ft_strequ(arr[0], arr[1]))
		{
			++i;
			continue ;// ????
		}
		tmp1 = avl_str_find(root, arr[0], &ft_strcmp);
		tmp2 = avl_str_find(root, arr[1], &ft_strcmp);
		free(arr);
		if (tmp1 == start || tmp2 == start)
			++s_n;
		if (tmp1 == end || tmp2 == end)
			++e_n;
		state = new_state();
		tmp = new_avl_str(tmp1->key, new_edge(tmp2, state, 1));
		state->ends[0] = tmp;
		tmp2->c.room.edges = avl_str_insert(tmp2->c.room.edges, tmp, &ft_strcmp);
		tmp = new_avl_str(tmp2->key, new_edge(tmp1, state, 0));
		state->ends[1] = tmp;
		tmp1->c.room.edges = avl_str_insert(tmp1->c.room.edges, tmp, &ft_strcmp);
		++i;
	}
	max_paths = (s_n < e_n) ? (s_n) : (e_n);
	if (!(sols = malloc(max_paths * sizeof(t_path *))))
		ft_exit();
	printf("ants  = %d\n", ants);
	printf("start = %s\n", start ? start->key : NULL);
	printf("end   = %s\n", end ? end->key : NULL);
//	avl_str_infix(root, &print_room);
	min = -1;
	i = 1;
	while (i <= max_paths)
	{
		printf("%d:\n", i);
		ctnr_push_top(start->c.room.froms, new_elem(NULL));
//		printf("before:\n");
		not_dijkstra(start);
//		printf("after:\n");
		free(ctnr_pop_top(start->c.room.froms));
		path_invert(end);
		find_paths(start, end, sols, i);
		paths = *sols + 1;
		n = ants;
		(paths - 1)->ants = 0;
		j = 1;
		while (j < i)
		{
			(paths - 1)->ants = paths->len - (paths - 1)->len;
			n -= (paths - 1)->ants * j;
			div = n / j;
			mod = n % j;
			if (n <= 0 || div == 0 || (div == 1 && mod == 0))
			{
				n += (paths - 1)->ants * j;
				(paths - 1)->ants = 0;
				break ;
			}
			++paths;
			++j;
		}
		if (j == i)
		{
			n += (paths - 1)->ants * j;
			(paths - 1)->ants = 0;
		}
		div = n / j;
		mod = n % j;
		--paths;
		--j;
		int		buf = 0;
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
		print_paths(start, *sols, i);
		if ((*sols)->ants + (*sols)->len - 1 < min || min == -1)
		{
			min = (*sols)->ants + (*sols)->len - 1;
			ind = i;
		}
		reset(start);
		++sols;
		++i;
	}
	sols -= max_paths;
	sols += ind - 1;
	(void)ind;
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
//	printf("before:\n");
		move_ants(&ingame);
//	printf("after:\n");
		++i;
	}
	sols -= ind - 1;
	return (0);
}
/*
void	ft_add_avl_str(t_avl_str *nodes, int *len, char *str)
{
	int		name_len;

	nodes = ft_realloc(nodes, *len * sizeof(t_avl_str), sizeof(t_avl_str));
	nodes[len] = ft_memalloc(sizeof(t_avl_str));
	name_len = str - ft_strchr(str, ' ');
	nodes[len].name = malloc((name_len + 1) * sizeof(char));
	nodes[len].name[name_len] = 0;
	ft_memcpy(&nodes[len].name, str, name_len);
	++len;
}

int		main(int ac, char **av)
{
	int		start;
	int		end;
	t_avl_str	*nodes;
	int		len;
	int		ants;
	char	*str;

	nodes = NULL;
	len = 0;
	gnl(0, &str, GNL_BUFF);
	ants = ft_atoi(str);
	free(str);
	while (gnl(0, &str, GNL_BUFF) > 0)
	{
		if (ft_strequ(str, "##start"))
		{
			free(str);
			gnl(0, &str, GNL_BUFF);
			start = len;
			ft_add_avl_str(nodes, &len, str);
		}
		if (ft_strequ(str, "##end"))
		{
			free(str);
			gnl(0, &str, GNL_BUFF);
			start = end;
			ft_add_avl_str(nodes, &len, str);
		}
		ft_add_avl_str(nodes, &len, str);
		free(str);
	}
	return (0);
}*/
