/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:44:38 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/29 19:11:59 by kbatz            ###   ########.fr       */
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

t_content	new_edge(t_avl_str *room, t_state *state)
{
	t_content	c;

	c.edge.room = room;
	c.edge.state = state;
	c.edge.existance = 1;
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

t_elem	*new_elem(t_avl_str *node)
{
	t_elem	*tmp;

	if ((tmp = malloc(sizeof(t_elem))))
	{
		tmp->node = node;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	return (tmp);
}

void		del_elem(t_elem *elem)
{
	free(elem);
}

void		reset_suffix(t_avl_str *root, t_queue *queue)
{
	if (!root)
		return ;
	reset_suffix(root->left, queue);
	reset_suffix(root->right, queue);
	if (root->c.edge.state->is_active)
		return ;
	root->c.edge.state->is_active = 1;
	ft_queue_push(queue, ft_new_sq_elem(root->c.edge.room, sizeof(t_avl_str), 0));
}

void		reset(t_avl_str *start)
{
	t_queue		*queue;
	t_sq_elem	*tmp;

	queue = ft_queue_new();
	ft_queue_push(queue, ft_new_sq_elem(start, sizeof(t_avl_str), 0));
	while (queue->len)
	{
		tmp = ft_queue_pop(queue);
		start = (t_avl_str *)tmp->content;
		ctnr_clear(start->c.room.froms, &del_elem);
		reset_suffix(start->c.room.edges, queue);
		free(tmp);
	}
}

void		all_not_dijkstra_suffix(t_avl_str *root, t_queue *queue, t_avl_str *from, t_avl_str *start, int *len)
{
	t_avl_str	*room;

	if (!root)
		return ;
	all_not_dijkstra_suffix(root->left, queue, from, start, len);
	all_not_dijkstra_suffix(root->right, queue, from, start, len);
	if (!root->c.edge.existance || !root->c.edge.state->is_active || root->c.edge.state->cross == 2)
		return ;
	root->c.edge.state->is_active = 0;
	room = root->c.edge.room;
	if (room == start)
	{
		if (*len)
		{
			ctnr_push_bot(room->c.room.froms, new_elem(from));
			--*len;
		}
	}
	else if (!room->c.room.froms->top)
		ctnr_push_bot(room->c.room.froms, new_elem(from));
	ft_queue_push(queue, ft_new_sq_elem(room, sizeof(t_avl_str), 0));
}

void	all_not_dijkstra(t_avl_str *start, t_avl_str *end, int len)
{
	t_queue		*queue;
	t_sq_elem	*tmp;

//	printf("distance from start:\n");
	queue = ft_queue_new();
	ft_queue_push(queue, ft_new_sq_elem(end, sizeof(t_avl_str), 0));
	while (queue->len)
	{
		tmp = ft_queue_pop(queue);
		end = (t_avl_str *)tmp->content;
		all_not_dijkstra_suffix(end->c.room.edges, queue, end, start, &len);
//		printf("\t%s: %d\n", end->key, end->c.room.distance);
		free(tmp);
	}
}

void		not_dijkstra_suffix(t_avl_str *root, t_queue *queue, t_avl_str *from)
{
	t_avl_str	*room;
	int		buf;

	if (!root)
		return ;
	not_dijkstra_suffix(root->left, queue, from);
	not_dijkstra_suffix(root->right, queue, from);
	if (!root->c.edge.existance || !root->c.edge.state->is_active || root->c.edge.state->cross == 2)
		return ;
	root->c.edge.state->is_active = 0;
	room = root->c.edge.room;
	buf = from->c.room.distance + root->c.edge.state->weight;
	if (room->c.room.froms->top)
	{
		if (room->c.room.distance > buf)
			ctnr_clear(room->c.room.froms, &del_elem);
		else
			return ;
	}
	room->c.room.distance = buf;
	ctnr_push_bot(room->c.room.froms, new_elem(from));
	ft_queue_push(queue, ft_new_sq_elem(room, sizeof(t_avl_str), 0));
}

void	not_dijkstra(t_avl_str *start)
{
	t_queue		*queue;
	t_sq_elem	*tmp;

//	printf("distance from start:\n");
	start->c.room.distance = 0;
	queue = ft_queue_new();
	ft_queue_push(queue, ft_new_sq_elem(start, sizeof(t_avl_str), 0));
	while (queue->len)
	{
		tmp = ft_queue_pop(queue);
		start = (t_avl_str *)tmp->content;
		not_dijkstra_suffix(start->c.room.edges, queue, start);
//		printf("\t%s: %d\n", start->key, start->c.room.distance);
		free(tmp);
	}
}

void		print_path(t_path path)
{
	t_elem	*tmp;

	tmp = path.path->top;
	if (tmp)
	{
		printf("\t%d to %d: ", path.ants, path.len);
		while (tmp->next)
		{
			printf("%s -> ", tmp->node->key);
			tmp = tmp->next;
		}
		printf("%s\n", tmp->node->key);
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

void		edge_reverse(t_avl_str *node, t_avl_str *prev)
{
	t_avl_str	*edge;

	edge = avl_str_find(node->c.room.edges, prev->key, &ft_strcmp);
	edge->c.edge.state->weight *= -1;
	++edge->c.edge.state->cross;
	edge->c.edge.existance = 0;
	edge = avl_str_find(prev->c.room.edges, node->key, &ft_strcmp);
	edge->c.edge.existance = 1;
}

void		path_invert_rec(t_avl_str *node, t_avl_str *prev)
{
	t_elem	*next;
//	t_avl_str	*out;

	(void)prev;
/*	printf("%s\n", node->key);
	printf("\t%p\n", node);
	printf("\t%p\n", node->c.room.froms);
	printf("\t%p\n", node->c.room.froms->top);
	printf("\t%p\n", node->c.room.froms->top->node);*/
	next = node->c.room.froms->top;
	if (!next)
		return ;
//	out = new_avl_str(av[i], new_room());
//	out->c.room.edges = node->c.room.edges;
//	node->c.room.edges = NULL;
	edge_reverse(next->node, node);
	path_invert_rec(next->node, node);
}

void		path_invert(t_avl_str *end)
{
	t_avl_str	*tmp;

	tmp = end->c.room.froms->top->node;
	if (!tmp)
		return ;
	edge_reverse(tmp, end);
	path_invert_rec(tmp, end);
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

void		find_paths(t_avl_str *start, t_avl_str *end, t_path **sols, int len)
{
	t_path	*tmp;
	t_elem	*buf;
	t_avl_str	*node;

	if (!(*sols = malloc((len) * sizeof(t_path))))
		ft_exit();
	tmp = *sols;
	reset(start);
	all_not_dijkstra(start, end, len);
	while (len)
	{
		tmp->path = ctnr_new();
		tmp->len = 1;
		ctnr_push_bot(tmp->path, new_elem(start));
		buf = ctnr_pop_top(start->c.room.froms);
		node = buf->node;
		while (node->c.room.froms->top)
		{
			ctnr_push_bot(tmp->path, new_elem(node));
			++tmp->len;
			node = node->c.room.froms->top->node;
		}
		ctnr_push_bot(tmp->path, new_elem(node));
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
		printf("L%d-%s ", tmp->ind, tmp->room->node->key);
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
		tmp = new_avl_str(tmp1->key, new_edge(tmp1, state));
		tmp2->c.room.edges = avl_str_insert(tmp2->c.room.edges, tmp, &ft_strcmp);
		tmp = new_avl_str(tmp2->key, new_edge(tmp2, state));
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
		not_dijkstra(start);
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
