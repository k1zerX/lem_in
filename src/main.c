/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:44:38 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 03:55:45 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"
#include "avl.h"
#include "libft.h"
#include "types.h"
#include "lem_in.h"
#include "read.h"

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
void			free_str_list(t_str_list *term);

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
/*
void		smart_free_rec(t_avl_str *root, t_my_queue *q)

void		smart_free(t_avl_str *room)
{
	t_my_queue		q;
	t_qelem			*tmp;

	q = (t_my_queue){NULL, NULL};
	while (q.start)
	{
		tmp = queue_pop(&queue);
		smart_free_rec(tmp->room->c.room.edges, q);
		free(tmp);
	}
}
*/
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
//			printf(">>>%d %d\n", prev_room->c.room.shortest, room->c.room.divided);
		if (prev_room->c.room.shortest && room->c.room.divided) // from in to out
		{
//			printf("gg\n");
			all_not_dijkstra_suffix(room->c.room.edges, queue, start, len, 0);
//			all_abcdefghijk(room->c.room.in_exc, queue, start, len);
//			printf("ok\n");
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
//		printf("\t%3s, %d:\n", end->key, end->c.room.divided);
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
		{
			if (room->c.room.in_exc == NULL)
				printf("%s : %p\n", room->key, room);
			abcdefghijk(room->c.room.in_exc, queue);
		}
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
//		printf("\t%3s, %d: %d\n", start->key, start->c.room.divided, start->c.room.distance);
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
//	printf(" %s", node->key);
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

//	printf("path invert:");
	edge = end->c.room.froms->top->edge;
	tmp = edge->c.edge.state->ends[edge->c.edge.n]->c.edge.room;
	if (!tmp)
		return ;
//	printf("\tbefore:\n");
	edge_reverse(edge);
//	printf(" %s", end->key);
	path_invert_rec(tmp);
//	printf("\n");
//	printf("\tafter:\n");
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
//		printf("\t%s - %s - %s\n", edge_in->c.edge.room->key, room->key, edge_out->c.edge.room->key);
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

//	printf("AAAAAAAAAAAAAAAAAAAAA %s\n", end->key);
//	printf(" %s", end->key);
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

	if (!(*sols = malloc((len) * sizeof(t_path))))
		ft_exit();
	tmp = *sols;
//	printf("shortest path: ");
	check_shortest(end);
	reset(start);
//	printf("\n");
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
//			node->c.room.divided = 1;
//			printf("||| %s, %d\n", node->key, node->c.room.divided);
//
//			node->c.room.in_exc = edge_in; //
//			node->c.room.out_exc = edge_out; //
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
	while (tmp->next)
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
	tmp->room = tmp->room->next;
	printf("L%d-%s\n", tmp->ind, tmp->room->edge->c.edge.room->key);
}

t_str_list		*is_valid_map(t_read *term);//
void print_map(t_str_list_elem *start);
	
int			main(int ac, char *av[])
{
	int		i;
	int		j;
	char	**arr;
	int		n;
	t_state *state;
	t_edge	*edge;
	t_path	**sols;
	t_path	*paths;
	int		div;
	int		mod;
	int		min;
	int		ind;
	t_ants	ingame;
	t_read		terminates;
	t_str_list	*str_list;
	
	terminates = (t_read){NULL, NULL, NULL, 0, 0};
	str_list = is_valid_map(&terminates);
	print_map(str_list->start);
	if (!(sols = malloc(terminates.max_paths * sizeof(t_path *))))
		ft_exit();
//	printf("terminates.ants  = %d\n", terminates.ants);
//	printf("terminates.start = %s\n", terminates.start ? terminates.start->key : NULL);
//	printf("terminates.end   = %s\n", terminates.end ? terminates.end->key : NULL);
	min = -1;
	i = 1;
	while (i <= terminates.max_paths)
	{
//		printf("%d:\n", i);
		ctnr_push_top(terminates.start->c.room.froms, new_elem(NULL));
//		printf("before:\n");
		not_dijkstra(terminates.start);
//		printf("after:\n");
		free(ctnr_pop_top(terminates.start->c.room.froms));
		if (terminates.end->c.room.froms->top == NULL)
			break ;
		path_invert(terminates.end);
		find_paths(terminates.start, terminates.end, sols, i);
		paths = *sols + 1;
		n = terminates.ants;
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
		div = n / j;
		mod = n % j;
//		printf("%d | %d / %d = %d | %d %% %d = %d\n", i, n, j, div, n, j, mod);
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
//			printf("%d\n", paths->ants);
			buf = paths->ants;
			paths->ants += div + 1;
			--j;
			--paths;
		}
//		printf("after\n");
//		print_paths(terminates.start, *sols, i); //
		if ((*sols)->ants + (*sols)->len - 1 < min || min == -1)
		{
			min = (*sols)->ants + (*sols)->len - 1;
			ind = i;
		}
		reset(terminates.start);
		++sols;
		++i;
	}
	sols -= i - 1;
	sols += ind - 1;
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
	sols -= ind - 1;
	return (0);
//	printf("\n------------\n\n");
//	print_test_avl(&terminates);
//	smart_free(start);
//	avl_str_infix(terminates.root, &del_avl_str);
	free_str_list(str_list);
}
