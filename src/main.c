/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:44:38 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/07 00:44:25 by kbatz            ###   ########.fr       */
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
void		ft_exit(void)
{
	exit(1);
}

t_node		*new_node(T_AVL_KEY key, t_content c)
{
	t_node	*tmp;

	if (!(tmp = malloc(sizeof(t_node))))
		ft_exit();
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

t_state		*new_state(void)
{
	t_state		*state;

	if (!(state = malloc(sizeof(t_state))))
		ft_exit();
	state->weight = 1;
	state->is_active = 1;
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
}

void		not_dijkstra_suffix(t_node *root, t_queue *queue, t_node *from)
{
	t_node	*room;
	int		buf;

	if (!root)
		return ;
	not_dijkstra_suffix(root->left, queue, from);
	not_dijkstra_suffix(root->right, queue, from);
	if (!root->c.edge.existance || !root->c.edge.state->is_active)
		return ;
	root->c.edge.state->is_active = 0;
	room = root->c.edge.room;
//	printf("%s\n", root->name);
//	printf("%p\n", room);
	buf = from->c.room.distance + root->c.edge.state->weight;
	if (room->c.room.froms->top)
	{
//	printf("%s %d vs %d\n", room->name, room->c.room.distance, buf);
		if (room->c.room.distance > buf)
		{
			room->c.room.distance = buf;
			ctnr_clear(room->c.room.froms, &del_elem);
			ctnr_push_bot(room->c.room.froms, new_elem(from));
		}
		else if (room->c.room.distance == buf)
			ctnr_push_bot(room->c.room.froms, new_elem(from));
		else
			return ;
//	printf("before\n");
//	printf("after\n");
	}
	else
	{
		room->c.room.distance = buf;
		ctnr_push_bot(room->c.room.froms, new_elem(from));
	}
	ft_queue_push(queue, ft_new_sq_elem(room, sizeof(t_node), 0));
}

void	not_dijkstra(t_node *start)
{
	t_queue		*queue;
	t_sq_elem	*tmp;

	start->c.room.distance = 0;
	queue = ft_queue_new();
	ft_queue_push(queue, ft_new_sq_elem(start, sizeof(t_node), 0));
	while (queue->len)
	{
		tmp = ft_queue_pop(queue);
		start = (t_node *)tmp->content;
//		printf("%s: %d\n", start->name, start->c.room.distance);
		not_dijkstra_suffix(start->c.room.edges, queue, start);
		free(tmp);
	}
}

void		print_paths(t_ctnr *path)
{
	t_elem	*tmp;
	tmp = path->top;
	while (tmp)
	{
		printf("\t%s\n", ((t_node *)tmp->node)->name);
		tmp = tmp->next;
	}
}

void		edge_reverse(t_node *node, t_node *prev)
{
	t_node	*edge;

	edge = avl_find(node->c.room.edges, prev->name, &ft_strcmp);
	edge->c.edge.state->weight *= -1;
	edge->c.edge.existance = 0;
	edge = avl_find(prev->c.room.edges, node->name, &ft_strcmp);
	edge->c.edge.existance = 1;
}

void		path_invert_rec(t_node *node, t_node *prev)
{
	t_elem	*next;
//	t_node	*out;

	(void)prev;
/*	printf("%s\n", node->name);
	printf("\t%p\n", node);
	printf("\t%p\n", node->c.room.froms);
	printf("\t%p\n", node->c.room.froms->top);
	printf("\t%p\n", node->c.room.froms->top->node);*/
	next = node->c.room.froms->top;
	if (!next)
		return ;
//	out = new_node(av[i], new_room());
//	out->c.room.edges = node->c.room.edges;
//	node->c.room.edges = NULL;
	edge_reverse(next->node, node);
	path_invert_rec(next->node, node);
}

void		path_invert(t_node *end)
{
	t_node	*tmp;

	tmp = end->c.room.froms->top->node;
	if (!tmp)
		return ;
	edge_reverse(tmp, end);
	path_invert_rec(tmp, end);
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
	t_node	*root;
	int		ants;

	root = init(&ants);
}
*/

t_ctnr		*find_paths(t_node *start, t_node *end)
{
	t_ctnr	*tmp;

	reset(start);
	not_dijkstra(end);
	tmp = start->c.room.froms;
	start->c.room.froms = ctnr_new();
	return (tmp);
}

int			main(int ac, char *av[])
{
	t_node	*root;
	int		i;
	char	**arr;
	t_node	*tmp;
	t_node	*tmp1;
	t_node	*tmp2;
	t_node	*start;
	t_node	*end;
	int		n;
	int		max_paths;
	int		s_n;
	int		e_n;
	t_state *state;
	t_ctnr	**sols;

	if (ac > 1)
		n = ft_atoi(av[1]);
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
		state = new_state();
		tmp = new_node(tmp1->name, new_edge(tmp1, state));
		tmp2->c.room.edges = avl_insert(tmp2->c.room.edges, tmp, &ft_strcmp);
		tmp = new_node(tmp2->name, new_edge(tmp2, state));
		tmp1->c.room.edges = avl_insert(tmp1->c.room.edges, tmp, &ft_strcmp);
		++i;
	}
	max_paths = (s_n < e_n) ? (s_n) : (e_n);
	if (!(sols = malloc(max_paths * sizeof(t_ctnr *))))
		ft_exit();
	printf("ants  = %d\n", n);
	printf("start = %s\n", start ? start->name : NULL);
	printf("end   = %s\n", end ? end->name : NULL);
	avl_infix(root, &print_room);
	i = 0;
	while (i < max_paths)
	{
		printf("%d:\n", i);
		ctnr_push_top(start->c.room.froms, new_elem(NULL));
		not_dijkstra(start);
		free(ctnr_pop_top(start->c.room.froms));
		path_invert(end);
		sols[i] = find_paths(start, end);
		print_paths(sols[i]);
		reset(start);
		++i;
	}
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
