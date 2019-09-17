/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:44:38 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/16 00:27:16 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ctnr.h"
#include "avl.h"
#include "libft.h"

#include <stdio.h>

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

t_content	new_edge(t_node *room)
{
	t_content	c;

	c.edge.room = room;
	c.edge.weight = 1;
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

void		node_re(t_node *node)
{
	ctnr_clear(node->c.room.froms, &del_elem);
}

void		s_treatment(t_node *root, char *name)
{
	if (!root)
		return ;
	s_treatment(root->left, name);
	s_treatment(root->right, name);
	free(avl_remove(root->c.edge.room->c.room.edges, name, &ft_strcmp));
}

void		se_treatment(t_node *start, t_node *end)
{
	avl_infix(end->c.room.edges, &del_node);
	end->c.room.edges = NULL;
	(void)start;
//	s_treatment(start->c.room.edges, start->name);
}

void		not_dijkstra_suffix(t_node *root, t_queue *queue, t_node *from)
{
	t_node	*room;
	int		buf;

	if (!root)
		return ;
	not_dijkstra_suffix(root->left, queue, from);
	not_dijkstra_suffix(root->right, queue, from);
	room = root->c.edge.room;
//	printf("%s\n", root->name);
//	printf("%p\n", room);
	buf = from->c.room.distance + root->c.edge.weight;
	if (room->c.room.froms->top)
	{
//	printf("%s %d vs %d\n", room->name, room->c.room.distance, buf);
		if (room->c.room.distance > buf)
			room->c.room.distance = buf;
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
		ctnr_clear(room->c.room.froms, &del_elem);
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
		printf("%s: %d\n", start->name, start->c.room.distance);
		not_dijkstra_suffix(start->c.room.edges, queue, start);
		free(tmp);
	}
}

void		print_path_rec(t_node *node, char *str)
{
	t_elem	*tmp;
	char	*buf;

	tmp = node->c.room.froms->top;
	if (!tmp)
	{
		printf("%s\n", str);
		free(str);
		return ;
	}
	buf = str;
	str = ft_strjoin(buf, " <- ");
	free(buf);
	while (tmp)
	{
		print_path_rec(tmp->node, ft_strjoin(str, tmp->node->name));
		free(str);
		tmp = tmp->next;
	}
}

void		print_paths(t_node *end)
{
	print_path_rec(end, ft_strdup(end->name));
}

void		path_invert_rec(t_node *node, t_node *from) /* seychas eto recursiya no luchshe sdelat' ochered' \
															to est' obhod v shirinu vmesto obhoda v glubinu */
{
	t_elem	*tmp;
	t_node	*buf;

	if (!node)
		return ;
//	printf("%s\n", node->name);
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
}

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
		tmp = new_node(tmp1->name, new_edge(tmp1));
		tmp2->c.room.edges = avl_insert(tmp2->c.room.edges, tmp, &ft_strcmp);
		tmp = new_node(tmp2->name, new_edge(tmp2));
		tmp1->c.room.edges = avl_insert(tmp1->c.room.edges, tmp, &ft_strcmp);
		++i;
	}
	avl_infix(root, &print_room);
	printf("ants  = %d\n", n);
	printf("start = %s\n", start ? start->name : NULL);
	printf("end   = %s\n", end ? end->name : NULL);
	se_treatment(start, end);// ubrat' treatment, prosto ne sozdavat' lishniye svyazi dlya start & end
	ctnr_push_bot(start->c.room.froms, new_elem(start));// ubrat' kogda pofikshu se_treatment
	not_dijkstra(start);
	free(ctnr_pop_top(start->c.room.froms));// ubrat' kogda pofikshu se_treatment
	print_paths(end);
	path_invert(end); // segfault, need to fix
	avl_infix(root, &print_room);
	avl_infix(root, &node_re);
	ctnr_push_bot(start->c.room.froms, new_elem(start));// ubrat' kogda pofikshu se_treatment
	not_dijkstra(start);
	free(ctnr_pop_top(start->c.room.froms));// ubrat' kogda pofikshu se_treatment
	print_paths(end);
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
