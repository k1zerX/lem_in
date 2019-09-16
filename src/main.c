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

	i = 1;
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
		tmp1 = avl_find(root, arr[0], &ft_strcmp);
		tmp2 = avl_find(root, arr[1], &ft_strcmp);
		tmp = new_node(tmp1->name, new_edge(tmp1));
		tmp2->c.room.edges = avl_insert(tmp2->c.room.edges, tmp, &ft_strcmp);
		tmp = new_node(tmp2->name, new_edge(tmp2));
		tmp1->c.room.edges = avl_insert(tmp1->c.room.edges, tmp, &ft_strcmp);
		++i;
	}
	avl_infix(root, &print_room);
	printf("start = %s\n", start ? start->name : NULL);
	printf("end   = %s\n", end ? end->name : NULL);
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
