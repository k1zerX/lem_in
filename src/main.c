/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:44:38 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/20 23:48:58 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"
#include "avl.h"
#include "libft.h"

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

typedef struct	s_path	t_path;
typedef struct	s_ants	t_ants;
typedef struct	s_ant	t_ant;

struct					s_path
{
	t_ctnr				*path;
	char				len;	// sdelat; int
	char				ants;	// sdelat' int
};

struct					s_ants
{
	t_ant				*start;
	t_ant				*end;
};

struct					s_ant
{
	t_elem				*room;
	t_ant				*next;
	int					ind;
};

void		ft_fucking_exit(void)
{
	exit(1);
}

t_node		*new_node(T_AVL_KEY key, t_content c)
{
	t_node	*tmp;

	if (!(tmp = malloc(sizeof(t_node))))
		ft_fucking_exit();
	tmp->name = key;
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

t_state		*new_state(t_node *a, t_node *b)
{
	t_state		*state;

	if (!(state = malloc(sizeof(t_state))))
		ft_fucking_exit();
	state->weight = 1;
	state->is_active = 1;
	state->cross = 0;
	state->is_deleted = 0;
	state->rooms[0] = a;
	state->rooms[1] = b;
	return (state);
}

t_content	new_edge(t_node *room, t_state *state)
{
	t_content	c;

	c.edge.room = room;
	c.edge.state = state;
	c.edge.existance = 1;
	return (c);
}

void		print_edge(t_node *node)
{
	printf("\t%s\n", node->name);
}

void		print_room(t_node *node)
{
	printf("%s to:\n", node->name);
	avl_infix(node->c.room.edges, &print_edge);
	printf("\n");
}

void		print_node(t_node *node)
{
	printf("%s\n", node->name);
}

void		del_node(t_node *node)
{
	free(node);
}

t_elem	*new_elem(t_node *node)
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

void		reset_suffix(t_node *root, t_queue *queue)
{
	if (!root)
		return ;
	reset_suffix(root->left, queue);
	reset_suffix(root->right, queue);
	if (root->c.edge.state->is_active)
		return ;
	root->c.edge.state->is_active = 1;
	ft_queue_push(queue, ft_new_sq_elem(root->c.edge.room, sizeof(t_node), 0));
}

void		reset(t_node *start)
{
	t_queue		*queue;
	t_sq_elem	*tmp;

//printf("before:\n");
	queue = ft_queue_new();
	ft_queue_push(queue, ft_new_sq_elem(start, sizeof(t_node), 0));
	while (queue->len)
	{
		tmp = ft_queue_pop(queue);
		start = (t_node *)tmp->content;
		ctnr_clear(start->c.room.froms, &del_elem);
		reset_suffix(start->c.room.edges, queue);
		free(tmp);
	}
//printf("after:\n");
}

void		all_not_dijkstra_suffix(t_node *root, t_queue *queue, t_node *from, t_node *start, int *len)
{
	t_node	*room;

	if (!root)
		return ;
	all_not_dijkstra_suffix(root->left, queue, from, start, len);
	all_not_dijkstra_suffix(root->right, queue, from, start, len);
	if (!root->c.edge.existance || !root->c.edge.state->is_active || \
			root->c.edge.state->cross == 2 || root->c.edge.state->is_deleted)
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
	ft_queue_push(queue, ft_new_sq_elem(room, sizeof(t_node), 0));
}

void	all_not_dijkstra(t_node *start, t_node *end, int len)
{
	t_queue		*queue;
	t_sq_elem	*tmp;

//	printf("distance from start:\n");
	queue = ft_queue_new();
	ft_queue_push(queue, ft_new_sq_elem(end, sizeof(t_node), 0));
	while (queue->len)
	{
		tmp = ft_queue_pop(queue);
		end = (t_node *)tmp->content;
		all_not_dijkstra_suffix(end->c.room.edges, queue, end, start, &len);
//		printf("\t%s: %d\n", end->name, end->c.room.distance);
		free(tmp);
	}
}

void		not_dijkstra_suffix(t_node *root, t_queue *queue, t_node *from)
{
	t_node	*room;
	int		buf;

	if (!root)
		return ;
	not_dijkstra_suffix(root->left, queue, from);
	not_dijkstra_suffix(root->right, queue, from);
	if (!root->c.edge.existance || !root->c.edge.state->is_active || \
			root->c.edge.state->cross == 2 || root->c.edge.state->is_deleted)
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
	ft_queue_push(queue, ft_new_sq_elem(room, sizeof(t_node), 0));
}

void	not_dijkstra(t_node *start)
{
	t_queue		*queue;
	t_sq_elem	*tmp;

//	printf("distance from start:\n");
	start->c.room.distance = 0;
	queue = ft_queue_new();
	ft_queue_push(queue, ft_new_sq_elem(start, sizeof(t_node), 0));
	while (queue->len)
	{
		tmp = ft_queue_pop(queue);
		start = (t_node *)tmp->content;
		not_dijkstra_suffix(start->c.room.edges, queue, start);
		printf("\t%s: %d\n", start->name, start->c.room.distance);
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
			printf("%s -> ", tmp->node->name);
			tmp = tmp->next;
		}
		printf("%s\n", tmp->node->name);
	}
}

void		print_paths(t_node *start, t_path *paths, int len)
{
	(void)start;
	while (len)
	{
		print_path(*paths);
		++paths;
		--len;
	}
}

void		edge_reverse(t_node *node, t_node *prev)
{
	t_node	*edge;

	edge = avl_find(node->c.room.edges, prev->name, &ft_strcmp);
	edge->c.edge.state->weight *= -1;
	++edge->c.edge.state->cross;
	edge->c.edge.existance = 0;
	edge = avl_find(prev->c.room.edges, node->name, &ft_strcmp);
	edge->c.edge.existance = 1;
}

t_state		*disconnect(t_node *a, t_node *b)
{
	t_state		*state;
	t_node		*tmp;

	tmp = avl_find(a->c.room.edges, b->name, &ft_strcmp);
	state = tmp->c.edge.state;
	a->c.room.edges = avl_remove(a->c.room.edges, b->name, &ft_strcmp);
	b->c.room.edges = avl_remove(b->c.room.edges, a->name, &ft_strcmp);
	return (state);
}

void		connect(t_node *a, t_node *b, t_state *state)
{
	t_content	edge;

	edge = new_edge(b, state);
//	edge.existance = existance;
	a->c.room.edges = avl_insert(a->c.room.edges, \
			new_node(b->name, edge), &ft_strcmp);
}

t_state		*node_division(t_node *next, t_node *node, t_node *prev, t_state *state_prev)
{/*
	t_node		*out;
	t_state		*state_next;
	t_state		*state;

	state_next = disconnect(node, next);
	out = new_node(node->name, new_room());
	out->c.room.edges = node->c.room.edges;
	node->c.room.edges = NULL;
	connect(prev, out, state_prev);
	state = new_state();
	state->weight = 0;
	connect(out, node, state);
	return (state_next);*/
/*	tmp = avl_find(node->c.room.edges, prev->name, &ft_strcmp);
	tmp->c.edge.state->is_deleted = 1;


	state = tmp->c.edge.state;
	tmp = new_node(out->name, new_edge(out, state));
	prev->c.room.edges = avl_insert(prev->c.room.edges, tmp, &ft_strcmp);
	edge = new_edge(prev, state);
	edge.edge.existance = 0;
	tmp = new_node(prev->name, edge);
	out->c.room.edges = avl_insert(out->c.room.edges, tmp, &ft_strcmp);

	state = new_state();
	state->weight = 0;
	tmp = new_node(node->name, new_edge(node, state));
	out->c.room.edges = avl_insert(out->c.room.edges, tmp, &ft_strcmp);
	edge = new_edge(out, state);
	edge.edge.existance = 0;
	tmp = new_node(out->name, edge);
	node->c.room.edges = avl_insert(node->c.room.edges, tmp, &ft_strcmp);*/
}

void		all_path_invert(t_node *end)
{
	t_elem		*next;

	next = end->c.room.froms->top;
	if (!next)
		return ;
	edge_reverse(next->node, end);
	all_path_invert(next->node);
}

void		path_invert_rec(t_node *node, t_node *prev, t_state *state)
{
	t_elem		*next;

	next = node->c.room.froms->top;
	if (!next)
	{
		connect(prev, node, state);
		return ;
	}
	edge_reverse(next->node, node);
	state = node_division(next->node, node, prev, state);
	path_invert_rec(next->node, node, state);
//	node->c.room.edges = NULL;
}

void		path_invert(t_node *end)
{
	t_node		*tmp;
	t_state		*state;

	tmp = end->c.room.froms->top->node;
	if (!tmp)
		return ;
	edge_reverse(tmp, end);
	printf("before:\n");
	printf("after:\n");
	state = disconnect(end, tmp);
	path_invert_rec(tmp, end, state);
}
/*
void		path_invert_rec(t_node *node, t_node *from) seychas eto recursiya no luchshe sdelat' ochered' \
															to est' obhod v shirinu vmesto obhoda v glubinu 
{
	t_elem	*tmp;
	t_node	*buf;
	t_node	*out;

	if (!node)
		return ;
	node->c.room.edges = avl_remove(node->c.room.edges, from->name, &ft_strcmp);
	tmp = node->c.room.froms->top;
//	printf("\t%p\n", tmp);
	while (tmp)
	{
		path_invert_rec(tmp->node, node);
		buf = avl_find(node->c.room.edges, tmp->node->name, &ft_strcmp);
		buf->c.edge.weight *= -1;
		tmp = tmp->next;
	}
	if (node->c.room.froms->top)
	{
		out = new_node(ft_strjoin(node->name, "-out"), new_room());
		ft_swap(&node->c.room.edges, &out->c.room.edges, sizeof(node->c.room.edges));
		buf = new_node(node->name, new_edge(node));
		buf->c.edge.weight = 0;
		out->c.room.edges = avl_insert(out->c.room.edges, buf, &ft_strcmp);
		print_room(out);
		from->c.room.edges = avl_remove(from->c.room.edges, node->name, &ft_strcmp)
		buf = new_node(out->name, new_edge(out));
		buf->c.edge.weight *= -1;
		from->c.room.edges = avl_insert(from->c.room.edges, buf, &ft_strcmp);
		// dodelat', peredelat
seychas posle razbiyeniya in ukazyvaet na out, a dolzhno byt' naoborot.
	}
}*/
/*
void		path_invert(t_node *end)
{
	t_elem	*tmp;
	t_node	*buf;

	tmp = end->c.room.froms->top;
	while (tmp)
	{
		path_invert_rec(tmp->node, end);
//		buf = avl_find(end->c.room.edges, tmp->node->name, &ft_strcmp);
		buf = new_node(tmp->node->name, new_edge(tmp->node));
		end->c.room.edges = avl_insert(end->c.room.edges, buf, &ft_strcmp);
		buf->c.edge.weight *= -1;
		tmp = tmp->next;
	}
}*/
/*
t_node		*fill_start(void)
{
	
}

t_node		*fill_end(void)
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

t_node		*init(int *ants)
{
	char	*str;
	int		n;
	char	**arr;

	if ((n = gnl(0, &str) < 0))
		ft_fucking_exit();
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
		ft_fucking_exit();
}

int			main(void)
{
	t_node	*root;
	int		ants;

	root = init(&ants);
}
*/

void		find_paths(t_node *start, t_node *end, t_path **sols, int len)
{
	t_path	*tmp;
	t_elem	*buf;
	t_node	*node;

	if (!(*sols = malloc((len) * sizeof(t_path))))
		ft_fucking_exit();
	tmp = *sols;
	reset(start);
	all_not_dijkstra(start, end, len);
//	all_path_invert(start);
//	reset(start);
	while (len)
	{
		tmp->path = ctnr_new();
		tmp->len = 1;
		ctnr_push_bot(tmp->path, new_elem(start));
		buf = ctnr_pop_top(start->c.room.froms);
//		printf("before: %p\n", buf);
		node = buf->node;
//		printf("after:\n");
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
		ft_fucking_exit();
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
		printf("L%d-%s ", tmp->ind, tmp->room->node->name);
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

t_node		*is_valid_map(t_node **start, t_node **end, int *ants, int *max_paths);

int			main(int ac, char *av[])
{
	t_node	*root;
	int		i;
	int		j;
	char	**arr;
	t_node	*tmp;
	t_node	*tmp1;
	t_node	*tmp2;
	t_node	*start;
	t_node	*end;
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
		tmp = new_node(av[i], new_room());
		if (ft_strequ(av[i - 1], "##start"))
			start = tmp;
		if (ft_strequ(av[i - 1], "##end"))
			end = tmp;
		root = avl_insert(root, tmp, &ft_strcmp);
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
		tmp1 = avl_find(root, arr[0], &ft_strcmp);
		tmp2 = avl_find(root, arr[1], &ft_strcmp);
		free(arr);
		if (tmp1 == start || tmp2 == start)
			++s_n;
		if (tmp1 == end || tmp2 == end)
			++e_n;
		t_content edge;
		state = new_state(tmp1, tmp2);
		edge = new_edge(tmp1, state);
		edge.edge.n = 1;
		tmp = new_node(tmp1->name, edge);
		tmp2->c.room.edges = avl_insert(tmp2->c.room.edges, tmp, &ft_strcmp);
		edge = new_edge(tmp2, state);
		edge.edge.n = 0;
		tmp = new_node(tmp2->name, edge);
		tmp1->c.room.edges = avl_insert(tmp1->c.room.edges, tmp, &ft_strcmp);
		++i;
	}
	max_paths = (s_n < e_n) ? (s_n) : (e_n);
	if (!(sols = malloc(max_paths * sizeof(t_path *))))
		ft_fucking_exit();
	printf("ants  = %d\n", ants);
	printf("start = %s\n", start ? start->name : NULL);
	printf("end   = %s\n", end ? end->name : NULL);
//	avl_infix(root, &print_room);
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
				paths[-1].ants = 0; // vynesti za cycle
				break ;
			}
			++paths;
			++j;
		}
		if (j == i)
		{
			n += paths[-1].ants * j;
			paths[-1].ants = 0;
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
void	ft_add_node(t_node *nodes, int *len, char *str)
{
	int		name_len;

	nodes = ft_realloc(nodes, *len * sizeof(t_node), sizeof(t_node));
	nodes[len] = ft_memalloc(sizeof(t_node));
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
	t_node	*nodes;
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
			ft_add_node(nodes, &len, str);
		}
		if (ft_strequ(str, "##end"))
		{
			free(str);
			gnl(0, &str, GNL_BUFF);
			start = end;
			ft_add_node(nodes, &len, str);
		}
		ft_add_node(nodes, &len, str);
		free(str);
	}
	return (0);
}*/
