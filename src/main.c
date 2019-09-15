/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 18:44:38 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/06 20:58:52 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"
#include "container.h"

int		main(void)
{
	return (0);
}

/*
int		cmp(t_avl_node *a, t_avl_node *b)
{
	return (ft_strcmp(((t_node *)a->content)->name, \
			((t_node *)b->content)->name));
}

int		main(void)
{
	t_avl_tree	*tree;
	int			i;
	char		**arr;
	t_avl_tree	*tmp1;
	t_avl_tree	*tmp2;

	tree = avl_new_tree(&cmp);
	i = 1;
	while (i < ac && *av[i] != '-')
	{
		avl_insert(tree, av[i]);
		++i;
	}
	while (i < ac)
	{
		arr = ft_strsplit(av[i], '-');
		tmp1 = avl_find(tree->root, avl_new_node(arr[0], ft_strlen(arr[0]), 0), tree->cmp);
		tmp2 = avl_find(tree->root, avl_new_node(arr[1], ft_strlen(arr[1]), 0), tree->cmp);
	}
	return (0);
}


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
	while (gnl(0, &str, GNL_BUFF))
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
